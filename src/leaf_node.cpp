#include "leaf_node.hpp"

namespace MC {

void LeafNode::accept(Visitor *visitor) { visitor->visit(this); }

void LeafNode::expand() {}

Context *LeafNode::get_context() { return context; }

INode *LeafNode::get_parent() { return parent; }

int LeafNode::get_nb_samples() { return nb_samples; }

Config *LeafNode::get_config() { return config; }

vector<INode *> LeafNode::get_children() { return vector<INode *>(); }

INode *LeafNode::select_recusively() { return this; }

INode *LeafNode::select_child() { return this; }

LeafNode::~LeafNode() {
  // TODO CHECK FOR LEAKS
  delete context;
}
}
