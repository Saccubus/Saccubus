/*
 * PyBridgeImpl.cpp
 *
 *  Created on: 2012/03/25
 *	  Author: psi
 */

#include <string>
#include <sstream>

#include "../logging/Exception.h"
#include "../logging/Logger.h"
#include "./ScriptException.h"

#include "PyBridgeImpl.h"
namespace saccubus {
namespace python {

static const std::string TAG("PyBridgeImpl");

PyBridgeImpl::PyBridgeImpl(logging::Logger& log)
:log(log)
{
	Py_Initialize();
	if(!Py_IsInitialized()){
		throw logging::Exception("Failed to init Python!!");
	}
	Session session(log);
}
std::auto_ptr<Session> PyBridgeImpl::createSession()
{
	std::auto_ptr<Session> session(new Session(this->log));

	return session;
}
PyBridgeImpl::~PyBridgeImpl() {
	Py_Finalize();
}

Session::Session(logging::Logger& log)
:log(log)
{
	PyObject* module = PyImport_AddModule("__main__");
	this->global = PyModule_GetDict(module);
	this->local = PyDict_New();
}
/**
 * ファイルを読んで実行します。
 * ユーザースクリプトの読み込みなどに。
 * （さきゅばす本体はパスに入っているので、これを使わなくても読み込めます）
 */
void Session::loadFile(const std::string& file)
{
	FILE* f = fopen(file.c_str(), "rb");
	if(!f){
		log.e(TAG, "Failed to open: %s", file.c_str());
		throw ScriptException("Failed to open: %s", file.c_str());
	}
	PyObject* res = PyRun_FileExFlags(f, file.c_str(), Py_file_input, this->global, this->local, 1, 0);
	if(!res){
		log.e(TAG, "Failed to run: %s", file.c_str());
		this->printExceptionLog();
		throw ScriptException("Failed to run: %s", file.c_str());
	}
}

/**
 *
 */
void Session::outException(std::stringstream& msg, PyObject* v){
	Py_INCREF(v);
	PyObject* cause = PyException_GetCause(v);
	if(cause){
		outException(msg, cause);
	}
	PyObject* type = (PyObject*)Py_TYPE(v);
	Py_INCREF(type);
	//FIXME: うまく出力できないことがある
	msg << "File \"" << toString(PyObject_GetAttrString(v, "filename")) << "\", line " << toString(PyObject_GetAttrString(v, "lineno")) << ", in " << toString(PyObject_GetAttrString(type, "__module__")) << std::endl;
	msg << PyExceptionClass_Name(type) << ": " << toString(v) << std::endl;
	msg << "here: " << toString(PyObject_GetAttrString(v, "text")) << std::endl;
	Py_XDECREF(v);
	Py_DECREF(type);
}
void Session::printExceptionLog()
{
	PyObject *exception, *v, *tb;
	PyErr_Fetch(&exception, &v, &tb);
	PyErr_NormalizeException(&exception, &v, &tb);
	std::stringstream msg;
	msg << "Python says: \n";
	outException(msg, v);
	log.e(TAG, msg.str());
}

/**
 * from {module} import {name}して、その{name}の関数ポインタを返します。
 */
PyObject* Session::findMethod(const std::string& module, const std::string& name)
{
	PyObject* imported = 0;
	{
		PyObject* const impList = PyList_New(1);
		PyObject* const impName = PyUnicode_DecodeUTF8(name.c_str(), name.size(), "ignore");
		PyList_Append(impList, impName);
		imported = PyImport_ImportModuleEx(const_cast<char*>(module.c_str()), this->global, this->local, impList);
		Py_DecRef(impName);
		Py_DecRef(impList);
	}

	if(!imported){
		log.e(TAG, "'%s.%s' is not found!", module.c_str(), name.c_str());
		throw ScriptException("'%s.%s' is not found!", module.c_str(), name.c_str());
	}else{
		if(log.t()) log.t(TAG, "Module for \"%s\" imported: '%s'", name.c_str(), toRepr(imported).c_str());
	}

	PyObject* func = PyDict_GetItemString(PyModule_GetDict(imported), name.c_str());
	if(!func){
		log.e(TAG, "\"%s.%s\" is not found!", module.c_str(), name.c_str());
		throw ScriptException("\"%s.%s\" is not found!", module.c_str(), name.c_str());
	}
	std::string repr = toRepr(func).c_str();
	if(!PyCallable_Check(func)){
		this->printExceptionLog();
		log.e(TAG, "\"%s.%s\" is not callable! It's '%s'", module.c_str(), name.c_str(), repr.c_str());
		throw ScriptException("\"%s.%s\" is not callable! It's '%s'", module.c_str(), name.c_str(), repr.c_str());
	}
	Py_XINCREF(func);
	Py_XDECREF(imported);imported = 0;
	return func;

}
/**
 * import済みのシンボルを返します。
 * ユーザースクリプトや、ビルトイン関数用。
 */
PyObject* Session::findMethod(const std::string& name)
{
	PyObject* func = PyDict_GetItemString(this->local, name.c_str());
	if(!func){
		log.e(TAG, "\"%s\" is not found!", name.c_str());
		throw ScriptException("\"%s\" is not found!", name.c_str());
	}
	std::string repr = toRepr(func).c_str();
	if(!PyCallable_Check(func)){
		this->printExceptionLog();
		log.e(TAG, "\"%s\" is not callable! It's '%s'", name.c_str(), repr.c_str());
		throw ScriptException("\"%s\" is not callable! It's '%s'", name.c_str(), repr.c_str());
	}else{
		if(log.t()) log.t(TAG, "\"%s\" found: %s", name.c_str(), repr.c_str());
	}
	Py_XINCREF(func);
	return func;
}

/**
 * dictObjectを、mapに変換する
 */
std::map<std::string, std::string> Session::parseDict(PyObject* dictObj)
{
	std::map<std::string, std::string> map;
	if(!PyDict_Check(dictObj)){
		log.w(TAG, "The object is not a dictionary. It's '%s'", toRepr(dictObj).c_str());
		return map;
	}
	PyObject* keys = PyDict_Keys(dictObj);
	const size_t max =PyList_Size(keys);
	for(size_t i=0;i<max;++i){
		PyObject* keyObj = PyList_GetItem(keys, i);
		std::string key = toString(keyObj);
		PyObject* valObj = PyDict_GetItem(dictObj, keyObj);
		std::string val = toString(valObj);
		map.insert(std::pair<std::string, std::string>(key, val));
	}
	Py_DECREF(keys);
	Py_DECREF(dictObj);
	return map;
}

bool Session::parseBool(PyObject* boolObj)
{
	if(PyBool_Check(boolObj)){
		log.w(TAG, "The object is not a bool object. It's '%s'", toRepr(boolObj).c_str());
		return false;
	}
	bool result = Py_True == boolObj;
	Py_DECREF(boolObj);
	return result;
}

/**
 * std::mapからPyObjectに変換する。新しい参照を返します。
 */
PyObject* Session::createDict(const std::map<std::string, std::string>& args)
{
	PyObject* const dictObj = PyDict_New();
	for(std::map<std::string, std::string>::const_iterator it = args.begin(); it != args.end();++it)
	{
		PyObject* key = PyUnicode_DecodeUTF8(it->first.c_str(), it->first.size(), "ignore");
		PyObject* val = PyUnicode_DecodeUTF8(it->second.c_str(), it->second.size(), "ignore");
		PyDict_SetItem(dictObj, key, val);
		Py_XDECREF(key);
		Py_XDECREF(val);
	}
	return dictObj;
}
/**
 * str(obj)の結果を返す。
 */
std::string Session::toString(PyObject* obj)
{
	PyObject* const val_o = PyObject_Str(obj);
	PyObject* const val_s = PyUnicode_AsUTF8String(val_o);
	std::string val(PyBytes_AsString(val_s));
	Py_XDECREF(val_s);
	Py_XDECREF(val_o);
	return val;
}
/**
 * repr(obj)の結果を返す。
 */
std::string Session::toRepr(PyObject* obj)
{
	PyObject* const repr_o = PyObject_Repr(obj);
	PyObject* const repr = PyUnicode_AsUTF8String(repr_o);
	std::string val(PyBytes_AsString(repr));
	Py_XDECREF(repr);
	Py_XDECREF(repr_o);
	return val;

}

/**
 * obj(*dict)を実行して結果を返します
 */
PyObject* Session::executeCallable(PyObject* obj, PyObject* argDict)
{
	PyObject* res = 0;
	{
		PyObject* const argsObj = PyTuple_New(0);
		res = PyObject_Call(obj, argsObj, argDict);
		Py_XDECREF(argsObj);
		Py_XDECREF(argDict);
		Py_XDECREF(obj);
	}
	if(!res){
		this->printExceptionLog();
		log.e(TAG, "Failed to run: %s", toRepr(obj).c_str());
		throw ScriptException("Failed to run: %s", toRepr(obj).c_str());
	}
	return res;
}

std::map<std::string, std::string> Session::executeMethodDict(const std::string& module, const std::string& name, const std::map<std::string, std::string>& args)
{
	return parseDict(executeCallable(findMethod(module, name), createDict(args)));
}

std::map<std::string, std::string> Session::executeMethodDict(const std::string& name, const std::map<std::string, std::string>& args)
{
	return parseDict(executeCallable(findMethod(name), createDict(args)));
}
bool Session::executeMethodBool(const std::string& module, const std::string& name, const std::map<std::string, std::string>& args)
{
	return parseBool(executeCallable(findMethod(module, name), createDict(args)));
}
bool Session::executeMethodBool(const std::string& name, const std::map<std::string, std::string>& args)
{
	return parseBool(executeCallable(findMethod(name), createDict(args)));
}

Session::~Session(){
	Py_DECREF(this->local);
	this->global = 0;
	this->local = 0;
}

}}
