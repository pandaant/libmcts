/*
 * File:   visitor.hpp
 * Author: batman
 *
 * Created on August 18, 2013, 1:59 AM
 */

#ifndef VISITOR_H
#define VISITOR_H

#include "inode.hpp"
#include "context.hpp"

namespace MC {

class INode;
class Context;

class Visitor {
public:
  virtual void visit(INode *node) = 0;
  virtual ~Visitor(){}
};
}

#endif /* VISITOR_H */

