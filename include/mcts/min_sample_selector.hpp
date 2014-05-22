#ifndef MIN_SAMPLE_SELECTOR_H
#define MIN_SAMPLE_SELECTOR_H

#include "min_function_selector.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   selects the child with the lowest number of samples.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config>
class MinSampleSelector : public MinFunctionSelector<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  MinSampleSelector() {}

  virtual double evaluate(node_t *node) const { return node->nb_samples(); }
};
}

#endif
