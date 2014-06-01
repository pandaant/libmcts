#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include <stdexcept>

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   implements methods of the inode interface that are used
///          for terminal contexts. all leaf nodes are terminal.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config>
class LeafNode : public INode<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;
  typedef typename IVisitor<Context, Config>::visitor_t visitor_t;

public:
  LeafNode(const Context &context, Config *config, node_t *parent)
      : context_(context), parent_(parent), config_(config), nb_samples_(0) {}

  virtual ~LeafNode() {}

  virtual void expand() { throw std::runtime_error("not supported"); }

  virtual void accept(visitor_t *visitor) { visitor->visit(this); }

  virtual node_t *parent() const { return parent_; }

  virtual int nb_samples() const { return nb_samples_; }

  virtual Config *config() const { return config_; }

  virtual const Context context() const { return context_; }

  virtual const vector<node_t *> children() const { return vector<node_t *>(); }

  virtual void add_child(node_t *child) {
    throw std::runtime_error("not supported");
  }

  virtual node_t *select_recusively() { return this; }

  virtual node_t *select_child() { return this; }

protected:
  Context context_;
  Config *config_;
  node_t *parent_;
  int nb_samples_;
};
}

#endif
