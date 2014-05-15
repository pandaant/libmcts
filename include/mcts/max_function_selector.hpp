/*
 * File:   max_function_selector.hpp
 * Author: batman
 *
 * Created on August 2, 2013, 3:16 PM
 */

#ifndef MAXFUNCTIONSELECTOR_H
#define MAXFUNCTIONSELECTOR_H

#include <vector>
#include <algorithm>
#include "selection_strategy.hpp"

namespace MC {
using std::vector;

/**
 * MaxFunctionSelector
 * Selects the child that maximizes the
 * evaluation function.
 **/
class MaxFunctionSelector : public SelectionStrategy {
public:
  INode *select(INode *node);

  /**
   * implement in derived classes.
   * evaluates a node and returns the numerical value.
   **/
  virtual double evaluate(INode *node) = 0;
};
}

#endif /* MAX_FUNCTION_SELECTOR_H */

