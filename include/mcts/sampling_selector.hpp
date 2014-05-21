#ifndef SAMPLING_SELECTOR_H
#define SAMPLING_SELECTOR_H

#include <random>
#include "inode.hpp"
#include "iselection_strategy.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   selector that chooses random children uniformly
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config>
class SamplingSelector : public ISelectionStrategy<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  typedef std::uniform_int_distribution<> DistributionType;

  // ----------------------------------------------------------------------
  /// @brief   randomly chooses a child of node
  ///
  /// @param node to select child from
  ///
  /// @return a random node
  // ----------------------------------------------------------------------
  node_t *select(node_t *node) {
    DistributionType dist(0, node->children().size() - 1);
    int rand = dist(*node->config()->nb_gen());
    return node->children()[rand];
  }
};
}

#endif
