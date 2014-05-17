#ifndef INODE_H
#define INODE_H

#include <vector>
#include <algorithm>
#include "visitor.hpp"

namespace mcts {
using std::vector;

/**
 * INode Interface
 * All nodes used in MCTS derive from this baseclass
 * and must implement the functions below.
 **/
template <typename Context, typename Config> class INode {
  typedef typename Visitor<Context, Config>::visitor_t visitor_t;

public:
  typedef INode<Context, Config> node_t;

  /**
   * add children to node unless
   * node is terminal.
   **/
  virtual void expand() = 0;
  virtual node_t *parent() const = 0;

  /**
   * uses some metric to select a specific child
   * @return one childnode
   */
  virtual node_t *select_child() = 0;

  /**
   * recursively selects a node with a
   * given simulation strategy until an
   * terminal node is reached.
   **/
  virtual node_t *select_recusively() = 0;

  virtual Config *config() const = 0;

  /**
   * number of samples that ran through
   * this node.
   * @return
   */
  virtual int nb_samples() const = 0;
  virtual const vector<node_t *> children() const = 0;
  virtual void add_child(node_t *child) = 0;
  virtual const Context context() const = 0;

  virtual double ev() const = 0;
  virtual double std_dev() const = 0;
  virtual double variance() const = 0;

  /**
   * Applies SimulationStrategy to a
   * terminal node.
   **/
  virtual double simulate() const = 0;

  virtual void accept(visitor_t *visitor) = 0;

  /**
   * Applies a BackpropagationStrategy
   * to traverse a simulated result back in the tree.
   **/
  virtual void backpropagate(double value) = 0;

  virtual ~INode() {}

  /**
   * counts number of nodes recusive
   * including the node calling the function.
   * so: nb_all_children + 1
   * @return treesize
   */
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
