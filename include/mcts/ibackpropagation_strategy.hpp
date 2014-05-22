#ifndef IBACKPROPAGATION_STRATEGY_H
#define IBACKPROPAGATION_STRATEGY_H

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   A backpropagation strategy is used in each node. when a
///          terminal node is simulated, its value is propagated back
///          through every node on the path. every node saves that value
///          according to the implementation of a specific
///          on_backpropagate function.
// ----------------------------------------------------------------------
class IBackpropagationStrategy {
public:
  // ----------------------------------------------------------------------
  /// @brief  saves an value according to some metric.
  ///
  /// @param value to store
  // ----------------------------------------------------------------------
  virtual void on_backpropagate(const double &value) = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the current expected value
  ///
  /// @return current ev
  // ----------------------------------------------------------------------
  virtual double ev() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the current standard deviation
  ///
  /// @return current std dev
  // ----------------------------------------------------------------------
  virtual double std_deviation() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the current variance
  ///
  /// @return current var
  // ----------------------------------------------------------------------
  virtual double variance() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the number of samples that are saved in the strat.
  ///
  /// @return count of backpropagated values
  // ----------------------------------------------------------------------
  virtual int nb_samples() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   creates a new object of the same type and with the same
  ///          constructor as the current object.
  ///
  /// @return pointer to a new backprop strat.
  // ----------------------------------------------------------------------
  virtual IBackpropagationStrategy *create() = 0;

  virtual ~IBackpropagationStrategy() {}
};
}

#endif /* BACKPROPAGATION_STRATEGY_H */

