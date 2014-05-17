/*
 * File:   simulation_strategy.hpp
 * Author: batman
 *
 * Created on August 10, 2013, 10:14 AM
 */

#ifndef SIMULATION_STRATEGY_H
#define SIMULATION_STRATEGY_H

#include "context.hpp"

namespace mcts {

/**
 * SimulationStrategy
 * evaluates the context in a terminal node.
 **/
class SimulationStrategy {
public:

  virtual ~SimulationStrategy() {}

  /**
   * calculate ev of a given context.
   * @param context
   * @return
   */
  virtual double simulate(Context *context) const = 0;
};
}
#endif /* SIMULATION_STRATEGY_H */

