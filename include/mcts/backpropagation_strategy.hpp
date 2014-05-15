/*
 * File:   backpropagation_strategy.h
 * Author: batman
 *
 * Created on July 31, 2013, 11:04 PM
 */

#ifndef BACKPROPAGATION_STRATEGY_H
#define BACKPROPAGATION_STRATEGY_H

namespace MC {

/**
     * BackpropagationStrategy interface
     * Backpropagates a given value in a specific
     * way though all nodes on the taken path
     **/
class BackpropagationStrategy {
public:
  // called in every node
  virtual void on_backpropagate(double value) = 0;

  // returns ev of node
  virtual double get_ev() = 0;

  // standard deviation
  virtual double get_std_deviation() = 0;
  virtual double get_variance() = 0;
  virtual int get_nb_samples() = 0;

  virtual BackpropagationStrategy *create() = 0;

  virtual ~BackpropagationStrategy() {}
};
}

#endif /* BACKPROPAGATION_STRATEGY_H */

