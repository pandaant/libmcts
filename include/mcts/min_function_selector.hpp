/*
 * File:   min_function_selector.hpp
 * Author: batman
 *
 * Created on August 5, 2013, 11:21 PM
 */

#ifndef MIN_FUNCTION_SELECTOR_H
#define MIN_FUNCTION_SELECTOR_H

#include <vector>
#include "selection_strategy.hpp"
#include "inode.hpp"

namespace MC {
using std::vector;

/**
 * MinFunctionSelector
 * Selects the child that minimizes the
 * evaluation function.
 **/
class MinFunctionSelector : public SelectionStrategy {
public:
  INode *select(INode *node);

  /**
   * implement in derived classes.
   * evaluates a node and returns the numerical value.
   **/
  virtual double evaluate(INode *node) = 0;
};
}

#endif /* MIN_FUNCTION_SELECTOR_H */

