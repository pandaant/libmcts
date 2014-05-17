#ifndef SAMPLING_TO_FUNCTION_SELECTOR_H
#define SAMPLING_TO_FUNCTION_SELECTOR_H

#include "sampling_selector.hpp"

namespace mcts {

/**
 * SamplingToFunctionSelector
 * Uses the Sampling selector until a given
 * threshold is exeeded. After that the supplied
 * SelectionStrategy is used.
 **/
template <typename Context, typename Config>
class SamplingToFunctionSelector : public SelectionStrategy<Context, Config> {
public:
  int threshold;
  SamplingSelector<Context, Config> sselector;
  SelectionStrategy<Context, Config> *function_strat;

  /**
   * @param _threshold	if exeeded, _functionStrategy is used
   * @param _functionStrat..	Strategy to use if theshold is exeeded
   **/
  SamplingToFunctionSelector(int _threshold, SelectionStrategy<Context, Config> *_function_strat)
      : threshold(_threshold), sselector(SamplingSelector<Context, Config>()),
        function_strat(_function_strat) {}

  INode<Context, Config> *select(INode<Context, Config> *node) {
    // choose random child if smaller than threshold
    if (node->get_nb_samples() < threshold)
      return sselector.select(node);
    else
      return function_strat->select(node);
  }
};
}

#endif /* SAMPLING_TO_FUNCTION_SELECTOR_H */

