#ifndef SELECTION_STRATEGY_H
#define SELECTION_STRATEGY_H

#include <random>
#include "inode.hpp"

namespace mcts {

template <typename Context, typename Config> class SelectionStrategy {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  virtual node_t *select(node_t *node) = 0;

  virtual ~SelectionStrategy() {}
};
}

#endif
