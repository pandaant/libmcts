/*
 * File:   root_node.hpp
 * Author: batman
 *
 * Created on August 5, 2013, 7:52 PM
 */

#ifndef ROOT_NODE_H
#define ROOT_NODE_H

namespace MC {

/**
 * the root node is a special node to start the tree with.
 * its a wrapper for some kind of (inner)node.
 **/
template <class Node> class RootNode : public Node {
public:

  RootNode(Context *_context, Config *_config)
      : Node(_context, NULL, _config) {}

  /**
   * root node has no parent. so backpropagation an get_parent
   * are not available.
   * @return
   */
  virtual INode *get_parent() { return NULL; }

  virtual void backpropagate(double value) {
    Node::backprop_strat->on_backpropagate(value);
  }
};
}

#endif /* ROOT_NODE_H */

