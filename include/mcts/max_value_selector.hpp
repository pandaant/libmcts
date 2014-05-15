/*
 * File:   max_value_selector.hpp
 * Author: batman
 *
 * Created on August 2, 2013, 3:32 PM
 */

#ifndef MAX_VALUE_SELECTOR_H
#define MAX_VALUE_SELECTOR_H

#include "max_function_selector.hpp"

namespace MC {

/**
 * MaxValueSelector
 * selects child with max ev
 **/
class MaxValueSelector : public MaxFunctionSelector {
public:
  virtual double evaluate(INode *node);
};
}

#endif /* MAX_VALUE_SELECTOR_H */

