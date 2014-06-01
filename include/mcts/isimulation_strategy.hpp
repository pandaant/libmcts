#ifndef SIMULATION_STRATEGY_H
#define SIMULATION_STRATEGY_H

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   interface class for simulation strategies. this strategies
///          are called in terminal nodes to evaluate the context in them.
// ----------------------------------------------------------------------
template<typename Context>
class ISimulationStrategy {
public:
  typedef ISimulationStrategy<Context> simstrategy_t;

  virtual ~ISimulationStrategy() {}

  // ----------------------------------------------------------------------
  /// @brief   calculate the ev of a given context.
  ///
  /// @param context context to be evaluated.
  ///
  /// @return ev of context
  // ----------------------------------------------------------------------
  virtual double simulate(const Context &context) = 0;
};
}

#endif
