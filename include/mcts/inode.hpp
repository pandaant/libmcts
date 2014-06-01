#ifndef INODE_H
#define INODE_H

#include <vector>
#include <algorithm>
#include "ivisitor.hpp"

namespace mcts {
using std::vector;

// ----------------------------------------------------------------------
/// @brief   basic interface for a node in the tree. Every node has to
///          implement this functions.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config> class INode {
  typedef typename IVisitor<Context, Config>::visitor_t visitor_t;

public:
  typedef INode<Context, Config> node_t;

  virtual ~INode() {}

  // ----------------------------------------------------------------------
  /// @brief   expand the current context and add all possible derived
  ///          contexts as children.
  // ----------------------------------------------------------------------
  virtual void expand() = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the parent of the current node
  ///
  /// @return pointer to parent
  // ----------------------------------------------------------------------
  virtual node_t *parent() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   selects a childnode according to a configurable metric
  ///
  /// @return pointer to a child node
  // ----------------------------------------------------------------------
  virtual node_t *select_child() = 0;

  // ----------------------------------------------------------------------
  /// @brief   recursively selects nodes with a given simulation strategy
  ///          until an terminal node is reached.
  ///
  /// @return pointer to a terminal node
  // ----------------------------------------------------------------------
  virtual node_t *select_recusively() = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the config object
  ///
  /// @return pointer to config object
  // ----------------------------------------------------------------------
  virtual Config *config() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   number of times a selection strategy selected the current
  ///          node.
  ///
  /// @return a selection count
  // ----------------------------------------------------------------------
  virtual int nb_samples() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   get the children of the current node
  ///
  /// @return list of pointers of nodes
  // ----------------------------------------------------------------------
  virtual const vector<node_t *> children() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   insert a new node as a child of the current one.
  ///
  /// @param child pointer to a node
  // ----------------------------------------------------------------------
  virtual void add_child(node_t *child) = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the context associated with the current node
  ///
  /// @return a context
  // ----------------------------------------------------------------------
  virtual const Context context() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the current expected value.
  ///
  /// @return ev
  // ----------------------------------------------------------------------
  virtual double ev() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the standard deviation.
  ///
  /// @return std_dev
  // ----------------------------------------------------------------------
  virtual double std_dev() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   gets the variance.
  ///
  /// @return variance of node
  // ----------------------------------------------------------------------
  virtual double variance() const = 0;

  // ----------------------------------------------------------------------
  /// @brief   applies a simulation strategy to a terminal node.
  ///
  /// @return the expected value of the evaluated context.
  // ----------------------------------------------------------------------
  virtual double simulate() = 0;

  // ----------------------------------------------------------------------
  /// @brief   accepts a visitor according to the visitor pattern.
  ///
  /// @param visitor object
  // ----------------------------------------------------------------------
  virtual void accept(visitor_t *visitor) = 0;

  // ----------------------------------------------------------------------
  /// @brief   applies a backpropagation strategy to traverse the simulated
  ///          result back up in the tree.
  ///
  /// @param value
  // ----------------------------------------------------------------------
  virtual void backpropagate(const double &value) = 0;

  // ----------------------------------------------------------------------
  /// @brief   recursively counts number of childen beneth this nodes.
  ///          counts in the current node.
  ///
  /// @return number of all children + 1
  // ----------------------------------------------------------------------
  virtual unsigned count_recursive() const {
    unsigned sum = 0;
    vector<node_t *> children = this->children();
    for (unsigned i = 0; i < children.size(); ++i) {
      sum += children[i]->count_recursive();
    }
    return 1 + sum;
  }
};
}

#endif
