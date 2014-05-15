/*
 * File:   robust_max_backpropagation.hpp
 * Author: batman
 *
 * Created on August 7, 2013, 4:30 PM
 */

#ifndef ROBUST_MAX_BACKPROPAGATION_H
#define ROBUST_MAX_BACKPROPAGATION_H

#include "backpropagation_strategy.hpp"

// TODO IMPLEMENT
namespace MC {
class RobustMaxBackpropagationStrategy : BackpropagationStrategy {
  virtual void on_backpropagate(double value) = 0;
};
}

#endif /* ROBUST_MAX_BACKPROPAGATION_H */

