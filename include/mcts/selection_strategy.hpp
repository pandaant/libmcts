/*
 * File:   selection_strategy.hpp
 * Author: batman
 *
 * Created on July 31, 2013, 11:05 PM
 */

#ifndef SELECTION_STRATEGY_H
#define SELECTION_STRATEGY_H

#include "inode.hpp"
#include <tr1/random>

namespace MC {

class INode;

/**
 * SelectionStrategy interface
 * Selects one of multiple possible children
 * of an node in a specific way.
 **/
class SelectionStrategy {
public:
  typedef std::tr1::mt19937 GeneratorType;

  virtual INode *select(INode *node) = 0;

  virtual ~SelectionStrategy() {}
};
}

#endif /* SELECTION_STRATEGY_H */

