#ifndef ROOT_NODE_H
#define ROOT_NODE_H

#include "inode.hpp"

namespace mcts {

template <typename Context, typename Config, typename WrapNode>
class RootNode : public WrapNode {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  typedef RootNode<Context, Config, WrapNode> root_node_t;

  RootNode(const Context &context, Config *config)
      : WrapNode(context, config, NULL) {}

  virtual node_t *parent() const{
    return NULL;
  }

  virtual void backpropagate(double value){
      WrapNode::backprop_strat_->on_backpropagate(value); 
  }

  using WrapNode::select_child;
};
}

#endif
