#ifndef MCTS_H
#define MCTS_H

#include "root_node.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   mainclass to interact with the library. it holds the root
///          of the searchtree.
///
/// @tparam Context @README
/// @tparam Config  @README
/// @tparam WrapNode type derived from  inner node class
/// @tparam ResultType type of resulttype
// ----------------------------------------------------------------------
template <typename Context, typename Config, typename WrapNode,
          typename ResultType>
class MCTS {
  typedef typename INode<Context, Config>::node_t node_t;
  typedef typename RootNode<Context, Config, WrapNode>::root_node_t root_node_t;

public:
  // ----------------------------------------------------------------------
  /// @brief   creates a new empty mcts object. only a root node exists.
  ///
  /// @param context base context from which all possible states stem
  /// @param config a pointer to a config object that stores user defined
  ///               data and some required functions
  // ----------------------------------------------------------------------
  MCTS(const Context &context, Config *config)
      : tree(new root_node_t(context, config)), iteration_cnt(0) {}

  virtual ~MCTS() { delete tree; }

  // ----------------------------------------------------------------------
  /// @brief   executes one interation step. Each iteration consists of
  ///          the following actions:
  ///           - select a terminal node
  ///           - simulate that node to get it's ev
  ///           - backpropagate that value back in the tree
  ///           - increase the iteration counter
  ///          The iteration step expands undexpanded nodes if necessary.
  // ----------------------------------------------------------------------
  void iterate() {
    node_t *selected_leaf = tree->select_recusively();
    double value = selected_leaf->simulate();
    selected_leaf->backpropagate(value);
    ++iteration_cnt;
  }

  // ----------------------------------------------------------------------
  /// @brief   gets the current result node. The node is selected according
  ///          to a metric defined in a selection strategy. The result is
  ///          returned to a template container that accepts a node_t*
  ///          object as constructor.
  ///
  /// @return a resultobject
  // ----------------------------------------------------------------------
  ResultType result() {
    return ResultType(tree->config()->move_selector()->select(tree));
  }

  // ----------------------------------------------------------------------
  /// @brief   gets the root of the node.
  ///
  /// @return pointer to root node.
  // ----------------------------------------------------------------------
  const node_t *root() const { return tree; }

  // ----------------------------------------------------------------------
  /// @brief   gets the number of nodes the tree is currently holding.
  ///
  /// @return number of nodes
  // ----------------------------------------------------------------------
  unsigned nb_nodes() { return tree->count_recursive(); }

  // ----------------------------------------------------------------------
  /// @brief   gets the number of performed iterations. the counter is
  ///          increased each time the function iterate() is called.
  ///
  /// @return number of iterations
  // ----------------------------------------------------------------------
  unsigned nb_iterations() { return iteration_cnt; }

private:
  /// stores first nodes of the tree (root)
  node_t *tree;
  unsigned iteration_cnt;
};
}

#endif
