/*
 * Object.h
 *
 *  Created on: 2012/02/11
 *      Author: psi
 */

#ifndef MACHINE_OBJECT_H_
#define MACHINE_OBJECT_H_

#include <string>
#include <vector>
#include <map>
#include <tr1/memory>
#include "../classdefs.h"

namespace nekomata{
namespace object{

class Object
{
public:
	explicit Object(ObjectHeap& heap);
	explicit Object(ObjectHeap& heap, bool isRaw);
	explicit Object(Object& parent, const unsigned int hash);
	virtual ~Object();
public: /* Builtin Method Utils */
#define ADD_BUILTIN(builtins, heap, name) \
		(builtins)->insert(BuiltinMethodPair(#name, NativeMethodObject((heap), _method_##name)));
	typedef std::map<std::string, NativeMethodObject> BuiltinMethods;
	typedef std::pair<std::string, NativeMethodObject> BuiltinMethodPair;
protected:
	void includeBuitin(BuiltinMethods* const method);
public: /* SlotTypeDefinition */
	typedef std::vector<Object*>::iterator SlotListIterator;
	typedef std::map<std::string, Object*>::iterator SlotMapIterator;
	typedef std::pair<std::string, Object*> SlotMapPair;
private: /* Heap management */
	ObjectHeap& heap;
	const int hash;
	int color;
	std::vector<Object*> objectList;
	std::map<std::string, Object*> objectMap;
	BuiltinMethods* const builtins;
protected:
	ObjectHeap& getHeap(){return heap;};
public:
	unsigned int getHash(){return hash;};
	void mark(int color);
	int getColor();
public: /* INDEXアクセス */
	virtual Object* unshift(Object* const item);
	virtual Object* push(Object* const item);
	virtual Object* shift();
	virtual Object* pop();
	virtual Object* index(size_t idx);
	virtual Object* indexSet(size_t idx, Object* item);
	virtual size_t size();
	virtual bool has(size_t idx);
public: /* KEYアクセス */
	virtual Object* setSlot(const std::string& key, Object* const value);
	virtual Object* getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
public: /* 基本操作 */
	virtual bool isUndefined();
	virtual void eval(machine::Machine& machine);
	virtual StringObject* toStringObject();
	virtual NumericObject* toNumericObject();
	virtual BooleanObject* toBooleanObject();
private:
	static bool _sort_func(machine::Machine& machine, Object* const self, Object* const other);
public:
	static void _method_def(NativeMethodObject* method, machine::Machine& machine);
	static void _method_def_kari(NativeMethodObject* method, machine::Machine& machine);

	static void _method_index(NativeMethodObject* method, machine::Machine& machine);
	static void _method_indexSet(NativeMethodObject* method, machine::Machine& machine);
	static void _method_size(NativeMethodObject* method, machine::Machine& machine);
	static void _method_unshift(NativeMethodObject* method, machine::Machine& machine);
	static void _method_push(NativeMethodObject* method, machine::Machine& machine);
	static void _method_shift(NativeMethodObject* method, machine::Machine& machine);
	static void _method_pop(NativeMethodObject* method, machine::Machine& machine);
	static void _method_sort(NativeMethodObject* method, machine::Machine& machine);
	static void _method_sum(NativeMethodObject* method, machine::Machine& machine);
	static void _method_product(NativeMethodObject* method, machine::Machine& machine);
	static void _method_join(NativeMethodObject* method, machine::Machine& machine);

	static void _method_setSlot(NativeMethodObject* method, machine::Machine& machine);
	static void _method_getSlot(NativeMethodObject* method, machine::Machine& machine);
	static void _method_clone(NativeMethodObject* method, machine::Machine& machine);
public:
	static void _method_if(NativeMethodObject* method, machine::Machine& machine);
	static void _method_while_kari(NativeMethodObject* method, machine::Machine& machine);
	static void _method_lambda(NativeMethodObject* method, machine::Machine& machine);
public:
	static void _method_distance(NativeMethodObject* method, machine::Machine& machine);
	static void _method_rand(NativeMethodObject* method, machine::Machine& machine);
};
//-----------------------------------------------------------------------------

class TopLevelObject : public Object
{
private:
	typedef Object* (*Getter)(TopLevelObject& self, ObjectHeap& heap);
	typedef void (*Setter)(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	std::map<std::string, Getter> getterList;
	std::map<std::string, Setter> setterList;
	machine::System& system;
public:
	explicit TopLevelObject(ObjectHeap& heap, machine::System& system);
	virtual ~TopLevelObject();
public:
	virtual Object* setSlot(const std::string& key, Object* const value);
	virtual Object* getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
public:
	static Object* __getter__commentColor(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentColor(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentPlace(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentPlace(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentSize(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentSize(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentInvisible(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentInvisible(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__commentReverse(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__commentReverse(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__defaultSage(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__defaultSage(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__postDisabled(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__postDisabled(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__seekDisabled(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__seekDisabled(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__isLoaded(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__isLoaded(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__isWide(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__isWide(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
	static Object* __getter__lastVideo(TopLevelObject& self, ObjectHeap& heap);
	static void __setter__lastVideo(TopLevelObject& self, ObjectHeap& heap, Object* const obj);
public:

};

//-----------------------------------------------------------------------------

class LazyEvalObject : public Object
{
private:
	machine::Machine& machine;
	const tree::ObjectNode* const node;
	std::map<std::string, bool> slotEvalState;
	std::map<size_t, bool> indexEvalState;
public:
	explicit LazyEvalObject(Object& parent, const unsigned int hash, machine::Machine& machine, const tree::ObjectNode* const node);
	virtual ~LazyEvalObject();
public: /* INDEXアクセス */
	virtual Object* unshift(Object* const item);
	virtual Object* push(Object* const item);
	virtual Object* shift();
	virtual Object* pop();
	virtual Object* index(size_t idx);
	virtual Object* indexSet(size_t idx, Object* item);
	virtual size_t size();
	virtual bool has(size_t idx);
public: /* KEYアクセス */
	virtual Object* setSlot(const std::string& key, Object* const value);
	virtual Object* getSlot(const std::string& key);
	virtual bool has(const std::string& key);
	virtual std::vector<std::string> getSlotNames();
	virtual size_t slotSize();
public:
	const tree::ObjectNode* const getRawNode() const{return node;};
};

//---------------------------------------------------------------------------------------------------------------------

class MethodObject : public Object{
protected:
	MethodObject(ObjectHeap& heap):Object(heap){};
	MethodObject(Object& parent, const unsigned int hash):Object(parent, hash){};
	virtual ~MethodObject(){}
};

class NativeMethodObject : public MethodObject
{
public:
	typedef void (*Method)(NativeMethodObject* method, machine::Machine& machine);
private:
	const Method method;
public:
	explicit NativeMethodObject(ObjectHeap& heap, Method method):MethodObject(heap), method(method){};
	virtual ~NativeMethodObject(){};
	virtual void eval(machine::Machine& machine){method(this, machine);}
};
class MethodNodeObject : public MethodObject
{
public:
	enum LocalScopeRule{
			def_kari,
			def
	};
private:
	const tree::Node* const node;
	const std::vector<std::string> argList;
	const LocalScopeRule rule;
	void mergeArg(machine::Machine& machine, Object* const local, Object* const arg);
public:
	explicit MethodNodeObject(Object& parent, const unsigned int hash, Object* const scope, const tree::Node* const node, LocalScopeRule rule, std::vector<std::string>& argList);
	explicit MethodNodeObject(Object& parent, const unsigned int hash, Object* const scope, const tree::Node* const node, LocalScopeRule rule);
	virtual ~MethodNodeObject();
	virtual void eval(machine::Machine& machine);
};

class LambdaObject : public MethodObject
{
private:
	BuiltinMethods* const builtins;
	const tree::Node* const node;
public:
	explicit LambdaObject(ObjectHeap& heap);
	explicit LambdaObject(LambdaObject& parent, const unsigned int hash, Object* const scope, const tree::Node* const node);
	virtual ~LambdaObject();
public:
	static void _method_index(NativeMethodObject* method, machine::Machine& machine);
};

class LambdaScopeObject : public Object
{
public:
	BuiltinMethods* const builtins;
	explicit LambdaScopeObject(ObjectHeap& heap);
	explicit LambdaScopeObject(LambdaScopeObject& parent, const unsigned int hash, Object* const arg);
	virtual ~LambdaScopeObject();
public:
	static void _method_atmark(NativeMethodObject* method, machine::Machine& machine);
};

//---------------------------------------------------------------------------------------------------------------------

class LiteralObject : public Object
{
protected:
	explicit LiteralObject(Object& parent):Object(parent, 0){};
	explicit LiteralObject(LiteralObject& parent, int hash):Object(parent, hash){};
	virtual ~LiteralObject(){};
};
class StringObject : public LiteralObject
{
private:
	const std::string value;
	BuiltinMethods* builtins;
public:
	explicit StringObject(Object& parent);
	explicit StringObject(StringObject& parent, int hash, const std::string& literal);
	virtual ~StringObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	const std::string& toString();
public:
	static void _method_equals(NativeMethodObject* method, machine::Machine& machine);
	static void _method_notEquals(NativeMethodObject* method, machine::Machine& machine);
	static void _method_notLessThan(NativeMethodObject* method, machine::Machine& machine);
	static void _method_notGreaterThan(NativeMethodObject* method, machine::Machine& machine);
	static void _method_greaterThan(NativeMethodObject* method, machine::Machine& machine);
	static void _method_lessThan(NativeMethodObject* method, machine::Machine& machine);
public:
	static void _method_index(NativeMethodObject* method, machine::Machine& machine);
	static void _method_size(NativeMethodObject* method, machine::Machine& machine);
	static void _method_indexOf(NativeMethodObject* method, machine::Machine& machine);
	static void _method_slice(NativeMethodObject* method, machine::Machine& machine);
	static void _method_toInteger(NativeMethodObject* method, machine::Machine& machine);
	static void _method_toFloat(NativeMethodObject* method, machine::Machine& machine);
	static void _method_eval(NativeMethodObject* method, machine::Machine& machine);
public:
	static void _method_add(NativeMethodObject* method, machine::Machine& machine);
};
class BooleanObject : public LiteralObject
{
private:
	const bool value;
	BuiltinMethods* builtins;
public:
	explicit BooleanObject(Object& parent, bool literal);
	virtual ~BooleanObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	bool toBool();
public:
	static void _method_and(NativeMethodObject* method, machine::Machine& machine);
	static void _method_or(NativeMethodObject* method, machine::Machine& machine);
	static void _method_not(NativeMethodObject* method, machine::Machine& machine);
	static void _method_alternate(NativeMethodObject* method, machine::Machine& machine);
};
class NumericObject : public LiteralObject
{
private:
	const double value;
	BuiltinMethods* builtins;
public:
	const static double EPSILON;
	explicit NumericObject(Object& parent);
	explicit NumericObject(NumericObject& parent, int hash, const double literal);
	virtual ~NumericObject();
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	double toNumeric();
public:
	static void _method_plus(NativeMethodObject* method, machine::Machine& machine);
	static void _method_minus(NativeMethodObject* method, machine::Machine& machine);
	static void _method_increase(NativeMethodObject* method, machine::Machine& machine);
	static void _method_decrease(NativeMethodObject* method, machine::Machine& machine);
	static void _method_add(NativeMethodObject* method, machine::Machine& machine);
	static void _method_subtract(NativeMethodObject* method, machine::Machine& machine);
	static void _method_multiply(NativeMethodObject* method, machine::Machine& machine);
	static void _method_divide(NativeMethodObject* method, machine::Machine& machine);
	static void _method_modulo(NativeMethodObject* method, machine::Machine& machine);
	static void _method_clone(NativeMethodObject* method, machine::Machine& machine);
public:
	static void _method_equals(NativeMethodObject* method, machine::Machine& machine);
	static void _method_notEquals(NativeMethodObject* method, machine::Machine& machine);
	static void _method_notLessThan(NativeMethodObject* method, machine::Machine& machine);
	static void _method_notGreaterThan(NativeMethodObject* method, machine::Machine& machine);
	static void _method_greaterThan(NativeMethodObject* method, machine::Machine& machine);
	static void _method_lessThan(NativeMethodObject* method, machine::Machine& machine);
public:
	static void _method_floor(NativeMethodObject* method, machine::Machine& machine);
	static void _method_sin(NativeMethodObject* method, machine::Machine& machine);
	static void _method_cos(NativeMethodObject* method, machine::Machine& machine);
	static void _method_pow(NativeMethodObject* method, machine::Machine& machine);

};

class UndefinedObject : public Object
{
public:
	explicit UndefinedObject(ObjectHeap& heap);
	virtual ~UndefinedObject();
public:
	StringObject* toStringObject();
	NumericObject* toNumericObject();
	BooleanObject* toBooleanObject();
	bool isUndefined();
};


}
}
#endif /* MACHINE_OBJECT_H_ */
