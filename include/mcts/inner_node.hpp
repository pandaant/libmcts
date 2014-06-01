#ifndef INNER_NODE_H
#define INNER_NODE_H

#include <stdexcept>
#include "inode.hpp"
#include "ibackpropagation_strategy.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief implements most methods of the inode interface. some methods
///        have to be implemented problem dependend. Inner nodes are
///        all nonterminal nodes.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config>
class InnerNode : public INode<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;
  typedef typename IVisitor<Context, Config>::visitor_t visitor_t;

  /// stores the context for the current node
  Context context_;

  /// stores a pointer to the config obj
  Config *config_;
  node_t *parent_;
  vector<node_t *> children_;

public:
  /// strategy that is used for propagating values back in the tree.
  IBackpropagationStrategy *backprop_strat_;

  InnerNode(const Context &context, Config *config, node_t *parent,
            IBackpropagationStrategy *backprop_strat)
      : context_(context), config_(config), parent_(parent),
        backprop_strat_(backprop_strat) {}

  virtual void expand() = 0;

  virtual node_t *select_child() = 0;

  virtual void accept(visitor_t *visitor) { visitor->visit(this); }

  virtual const vector<node_t *> children() const { return children_; }

  virtual void add_child(node_t *child) { children_.push_back(child); }

  virtual Config *config() const { return config_; }

  virtual const Context context() const { return context_; }

  virtual node_t *parent() const { return parent_; }

  virtual node_t *select_recusively() {
    if (children_.size() == 0)
      expand();
    node_t *selec = select_child();
    node_t *selectedChild = selec->select_recusively();
    return selectedChild;
  }

  virtual double simulate() {
    throw std::runtime_error("not supported.");
  }

  virtual double ev() const { return backprop_strat_->ev(); }

  virtual double std_dev() const { return backprop_strat_->std_deviation(); }

  virtual double variance() const { return backprop_strat_->variance(); }

  virtual int nb_samples() const { return backprop_strat_->nb_samples(); }

  virtual void backpropagate(const double &value) {
    backprop_strat_->on_backpropagate(value);
    parent_->backpropagate(value);
  }

  virtual ~InnerNode() {
    for (unsigned i = 0; i < children_.size(); ++i) {
      delete children_[i];
    }
  }
};
}

#endif
