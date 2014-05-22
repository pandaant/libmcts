#ifndef MCTS_H
#define MCTS_H

#include "root_node.hpp"

namespace mcts {

template <typename Context, typename Config, typename WrapNode,
          typename ResultType>
class MCTS {
  typedef typename INode<Context, Config>::node_t node_t;
  typedef typename RootNode<Context, Config, WrapNode>::root_node_t root_node_t;

public:
  MCTS(const Context &context, Config *config)
      : tree(new root_node_t(context, config)), iteration_cnt(0) {}

  ~MCTS() { delete tree; }

  void iterate() {
    node_t *selected_leaf = tree->select_recusively();
    double value = selected_leaf->simulate();
    selected_leaf->backpropagate(value);
    ++iteration_cnt;
  }

  ResultType result() {
    return ResultType(tree->config()->move_selection_strat()->select(tree));
  }

  const node_t* root() const { return tree; }
  unsigned nb_nodes() { return tree->count_recursive(); }
  unsigned nb_iterations() { return iteration_cnt; }

private:
  node_t *tree;
  unsigned iteration_cnt;
};
}

#endif
