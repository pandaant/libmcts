#ifndef SAMPLING_SELECTOR_H
#define SAMPLING_SELECTOR_H

#include <random>
#include "inode.hpp"
#include "selection_strategy.hpp"

namespace mcts {

/**
 * SamplingSelector
 * Selects a random child, based on an uniform distribution.
 **/
template <typename Context, typename Config>
class SamplingSelector : public SelectionStrategy<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  typedef std::uniform_int_distribution<> DistributionType;

  node_t *select(node_t *node) {
    DistributionType dist(0, node->children().size() - 1);
    int rand = dist(*node->config()->nb_gen());
    return node->children()[rand];
  }
};
}

#endif
