#ifndef END_NODE_H
#define	END_NODE_H

#include <leaf_node.hpp>

#include "rock_paper_scissors.hpp"

using mcts::INode;
using mcts::LeafNode;

template <typename Context, typename Config>
struct EndNode : public LeafNode<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

  EndNode(const Context &_context, Config *_config, node_t *_parent)
      : LeafNode<Context, Config>(_context, _config, _parent) {}

  virtual double ev() const { return this->simulate(); }

  virtual double std_dev() const { return 0; }

  virtual double variance() const { return 0; }

  virtual double simulate() const {
    double payoff_3_games = 3;
    return (this->context().p1.pwin() * payoff_3_games) +
           (this->context().p1.ptie() * payoff_3_games * 0.5);
  }

  virtual void backpropagate(const double& value) {
    ++this->nb_samples_;
    this->parent_->backpropagate(value);
  }
};

#endif
