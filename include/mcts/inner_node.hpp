/*
 * File:   inner_node.hpp
 * Author: batman
 *
 * Created on July 31, 2013, 9:52 PM
 */

#ifndef INNER_NODE_H
#define INNER_NODE_H

#include <stdexcept>
#include "inode.hpp"
#include "backpropagation_strategy.hpp"

namespace MC {

/**
 * InnerNode
 * implements most basic Inner nodes represent all non terminal
 * contexts. terminal nodes must be derived from leaf_node
 **/
class InnerNode : public INode {
public:
  Context *context;
  INode *parent;
  Config *config;
  vector<INode *> children;
  BackpropagationStrategy *backprop_strat;

  /**
   * @param _context		gamestate assosicated with this node
   * @param _parent	parent of the node
   * @param _config	used mcts config
   * @param _backPropStrat	specific strategy for this node
   **/
  InnerNode(Context *_context, INode *_parent, Config *_config,
            BackpropagationStrategy *_backprop_strat)
      : context(_context), parent(_parent), config(_config),
        backprop_strat(_backprop_strat) {}

  virtual void accept(Visitor *visitor);
  virtual vector<INode *> get_children();
  virtual Config *get_config();
  virtual Context *get_context();
  virtual INode *get_parent();
  virtual INode *select_recusively();

  // only implemented in leaf nodes
  virtual double simulate();

  virtual double get_ev();
  virtual double get_std_dev();
  virtual double get_variance();
  virtual int get_nb_samples();
  virtual void backpropagate(double value);
  virtual ~InnerNode();
};
}

#endif /* INNER_NODE_H */

