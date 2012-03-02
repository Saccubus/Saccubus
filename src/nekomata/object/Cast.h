/*
 * Opt.h
 *
 *  Created on: 2012/02/29
 *      Author: psi
 */

#ifndef CAST_H_
#define CAST_H_

#include <string>
#include <vector>
#include "Object.h"

namespace nekomata{
namespace object
{

template <typename T>
T cast(const Handler<Object> obj)
{
	return static_cast<T>(obj->toNumeric());
}
template<> double cast<double>(const Handler<Object> obj);
template<> std::string cast<std::string>(const Handler<Object> obj);
template<> bool cast<bool>(const Handler<Object> obj);
template<> std::vector<std::tr1::shared_ptr<system::Sum> > cast<std::vector<std::tr1::shared_ptr<system::Sum> > >(const Handler<Object> obj);
template<> std::vector<std::string> cast<std::vector<std::string> >(const Handler<Object> obj);

//---------------------------------------------------------------------------------------------------------------------

template <typename T>
T opt(const Handler<Object> obj, const std::string& key, const T& def)
{
	if(obj->has(key)){
		return cast<T>(obj->getSlot(key));
	}else{
		return def;
	}
}

std::string opt(const Handler<Object> obj, const std::string& key, const std::string& def);
template <typename T>
T opt(Object* const obj, size_t index, const T& def)
{
	if(obj->has(index)){
		return cast<T>(obj->index(index));
	}else{
		return def;
	}
}
std::string opt(const Handler<Object> obj, size_t index, const std::string& def);


}}

#endif /* CAST_H_ */
