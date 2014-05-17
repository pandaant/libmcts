#ifndef BACKPROPAGATION_STRATEGY_H
#define BACKPROPAGATION_STRATEGY_H

namespace mcts {

class BackpropagationStrategy {
public:
  // called in every node
  virtual void on_backpropagate(double value) = 0;

  // returns ev of node
  virtual double ev() = 0;

  // standard deviation
  virtual double std_deviation() = 0;
  virtual double variance() = 0;
  virtual int nb_samples() = 0;

  virtual BackpropagationStrategy *create() = 0;

  virtual ~BackpropagationStrategy() {}
};
}

#endif /* BACKPROPAGATION_STRATEGY_H */

