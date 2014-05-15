/*
 * File:   inode.hpp
 * Author: batman
 *
 * Created on July 31, 2013, 9:09 PM
 */

#ifndef INODE_H
#define INODE_H

#include <vector>
#include <algorithm>
#include "config.hpp"
#include "context.hpp"
#include "visitor.hpp"

namespace MC {
using std::vector;

class Config;
class Context;
class Visitor;

/**
 * INode Interface
 * All nodes used in MCTS derive from this baseclass
 * and must implement the functions below.
 **/
class INode {
public:
  /**
   * add children to node unless
   * node is terminal.
   **/
  virtual void expand() = 0;
  virtual INode *get_parent() = 0;

  /**
   * uses some metric to select a specific child
   * @return one childnode
   */
  virtual INode *select_child() = 0;

  /**
   * recursively selects a node with a
   * given simulation strategy until an
   * terminal node is reached.
   **/
  virtual INode *select_recusively() = 0;

  virtual Config *get_config() = 0;

  /**
   * number of samples that ran through
   * this node.
   * @return
   */
  virtual int get_nb_samples() = 0;
  virtual vector<INode *> get_children() = 0;
  virtual Context *get_context() = 0;

  virtual double get_ev() = 0;
  virtual double get_std_dev() = 0;
  virtual double get_variance() = 0;

  /**
   * Applies SimulationStrategy to a
   * terminal node.
   **/
  virtual double simulate() = 0;

  virtual void accept(Visitor *visitor) = 0;

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
  int count_recusive();
};
}

#endif /* INODE_H */

