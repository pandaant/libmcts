/*
 * File:   mcts.hpp
 * Author: batman
 *
 * Created on July 31, 2013, 9:05 PM
 */

#ifndef MCTS_H
#define MCTS_H

#include "config.hpp"
#include "context.hpp"
#include "inode.hpp"
#include "inner_node.hpp"
#include "root_node.hpp"

namespace MC {
// USE BOOST OBJECT_POOL

/**
 * Monte Carlo Tree Search
 * see http://de.wikipedia.org/wiki/Monte-Carlo-Simulation
 **/
template <class Node, class ResultType> class MCTS {
  Config *config;
  RootNode<Node> *root;

public:

  MCTS(Context *_context, Config *_config)
      : config(_config), root(new RootNode<Node>(_context->clone(), _config)) {}

  ~MCTS() {
    if (root != NULL)
      delete root;
  }

  /**
   * iterate
   * every iteration that is performed, a selection strategy
   * retrives a new node. the result of the simulation is then
   * backpropagated trough the tree.
   **/
  void iterate() {
    INode *selected_leaf = root->select_recusively();
    double value = selected_leaf->simulate();
    selected_leaf->backpropagate(value);
  }

  RootNode<Node> *get_root() { return this->root; }

  ResultType get_result() {
    INode *next_move = config->move_selection_strat->select(this->root);
    return ResultType(next_move);
  }

  /**
   * counts nodes in the tree
   * @return nb_nodes
   */
  int size() { return root->count_recusive(); }
};
}

#endif /* MCTS_H */

