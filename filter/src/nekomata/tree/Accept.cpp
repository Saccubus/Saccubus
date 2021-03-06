/* coding: utf-8 */
/**
 * Nekomata
 *
 * Copyright 2012-2013, PSI
 */

#include "Node.h"
#include "NodeWalker.h"

namespace nekomata{
namespace tree{
void BoolLiteralNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void NumericLiteralNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void StringLiteralNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}

void AssignNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void OpAssignNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void IndexAcessNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void BindNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void PostOpNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void PreOpNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void BinOpNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void ObjectNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void InvokeNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}
void ContNode::accept(NodeWalker& walker) const{
	walker.walk(*this);
}


}}

