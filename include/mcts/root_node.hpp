#ifndef ROOT_NODE_H
#define ROOT_NODE_H

#include "inode.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   special node that is the root of each tree. Its merely a
///          wrapper that wrapps around a inner node.
///
/// @tparam Context @README
/// @tparam Config  @README
/// @tparam WrapNode node to derive from. ( has to be derived from
///                  inner node )
// ----------------------------------------------------------------------
template <typename Context, typename Config, typename WrapNode>
class RootNode : public WrapNode {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  typedef RootNode<Context, Config, WrapNode> root_node_t;

  // ----------------------------------------------------------------------
  /// @brief   constructs a new object and passes all parameters to the
  ///          wrapped node.
  ///
  /// @param context describing a state
  /// @param config pointer to config object.
  // ----------------------------------------------------------------------
  RootNode(const Context &context, Config *config)
      : WrapNode(context, config, NULL) {}

  // ----------------------------------------------------------------------
  /// @brief   disabled in root node, to end backpropagating actions.
  ///
  /// @return nullptr
  // ----------------------------------------------------------------------
  virtual node_t *parent() const { return NULL; }

  // ----------------------------------------------------------------------
  /// @brief   consume value and do noting more.
  ///
  /// @param value to consume
  // ----------------------------------------------------------------------
  virtual void backpropagate(const double& value) {
    WrapNode::backprop_strat_->on_backpropagate(value);
  }

  using WrapNode::select_child;
};
}

#endif
