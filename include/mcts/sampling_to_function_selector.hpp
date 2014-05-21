#ifndef SAMPLING_TO_FUNCTION_SELECTOR_H
#define SAMPLING_TO_FUNCTION_SELECTOR_H

#include "sampling_selector.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   Uses sampling selector until threshold is reached.
///          After that a supplied selection strategy is applied.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config>
class SamplingToFunctionSelector : public ISelectionStrategy<Context, Config> {
  typedef SamplingSelector<Context, Config> sampling_selector_t;
  typedef typename INode<Context, Config>::node_t node_t;
  typedef typename ISelectionStrategy<Context, Config>::sstrategy_t sstrategy_t;

public:
  /// number of samples before the strategy is switched.
  int threshold;
  sstrategy_t *function_strat;
  sampling_selector_t sselector;

  // ----------------------------------------------------------------------
  /// @brief   create new selector
  ///
  /// @param threshold_ number of samples that must have run through
  ///                   the node before strategies are switched.
  /// @param function_strat_ pointer to selection strategy to switch to.
  // ----------------------------------------------------------------------
  SamplingToFunctionSelector(int threshold_, sstrategy_t *function_strat_)
      : threshold(threshold_), sselector(sampling_selector_t()),
        function_strat(function_strat_) {}

  node_t *select(node_t *node) {
    return (node->nb_samples() < threshold) ? sselector.select(node)
                                            : function_strat->select(node);
  }
};
}

#endif
