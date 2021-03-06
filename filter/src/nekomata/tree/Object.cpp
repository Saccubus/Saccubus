/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */


#include "Node.h"
#include <memory>

namespace nekomata{
namespace tree
{
ObjectNode::ObjectNode(const Location& loc):ExprNode(loc){

}
void ObjectNode::append(std::string name, std::shared_ptr<const ExprNode> exprNode){
	if(name.size() == 0){
		exprList.push_back(exprNode);
	}else{
		exprMap.insert(std::pair<std::string, std::shared_ptr<const ExprNode> >(name, exprNode));
	}
}
const ExprNode* ObjectNode::getSlot(std::string const& name) const
{
	std::map<std::string, std::shared_ptr<const ExprNode> >::const_iterator it = exprMap.find(name);
	if(it != exprMap.end()){
		return it->second.get();
	}else{
		return 0;
	}
}
const ExprNode* ObjectNode::index(const size_t idx) const
{
	if(has(idx)){
		return exprList.at(idx).get();
	}else{
		return 0;
	}
}

std::vector<std::string> ObjectNode::getSlotNames() const

{
	std::vector<std::string> names;
	for(std::map<std::string, std::shared_ptr<const ExprNode> >::const_iterator it = exprMap.begin(); it != exprMap.end();++it){
		names.push_back(it->first);
	}
	return names;

}
size_t ObjectNode::size() const
{
	return exprList.size();
}
size_t ObjectNode::slotSize() const
{
	return exprMap.size();
}


}}
