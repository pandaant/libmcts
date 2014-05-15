/*
 * File:   leaf_node.hpp
 * Author: batman
 *
 * Created on July 31, 2013, 9:50 PM
 */

#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include "config.hpp"
#include "context.hpp"

namespace MC {

/**
 * LeafNode
 * Terminal node of the Tree
 * all types of terminal nodes must be derived from this.
 **/
class LeafNode : public INode {
public:
  Context *context;
  INode *parent;
  Config *config;
  int nb_samples;

  LeafNode(Context *_context, INode *_parent, Config *_config)
      : context(_context), parent(_parent), config(_config), nb_samples(0) {}

  /**
   * transition current context and store resulting
   * contexts as children.
   * not implemented in leaf nodes.
   */
  virtual void expand();
  virtual void accept(Visitor *visitor);
  virtual Context *get_context();
  virtual INode *get_parent();
  virtual int get_nb_samples();
  virtual Config *get_config();
  virtual vector<INode *> get_children();
  virtual INode *select_recusively();
  virtual INode *select_child();
  virtual ~LeafNode();
};
}

#endif /* LEAF_NODE_H */

