#ifndef AVG_BACKPROPAGATION_H
#define AVG_BACKPROPAGATION_H

#include "running_stats.hpp"
#include "ibackpropagation_strategy.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   adds the backpropagated value to a running stats object
///          that calculates the ev, mean and variance.
// ----------------------------------------------------------------------
class AvgBackpropagationStrategy : public IBackpropagationStrategy {
public:
  RunningStats stats;

  AvgBackpropagationStrategy() : stats() {}

  virtual void on_backpropagate(const double &value) { stats.push(value); }

  virtual double ev() const { return stats.mean(); }

  virtual double std_deviation() const { return stats.standard_deviation(); }

  virtual double variance() const { return stats.variance(); }

  virtual int nb_samples() const { return stats.num_data_values(); }

  virtual IBackpropagationStrategy *create() {
    return new AvgBackpropagationStrategy();
  }
};
}

#endif
