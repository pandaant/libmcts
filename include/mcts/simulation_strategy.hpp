#ifndef SIMULATION_STRATEGY_H
#define SIMULATION_STRATEGY_H

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

#endif
