#include "inner_node.hpp"

namespace MC {

void InnerNode::accept(Visitor *visitor) { visitor->visit(this); }

vector<INode *> InnerNode::get_children() { return children; }

Config *InnerNode::get_config() { return config; }

Context *InnerNode::get_context() { return context; }

INode *InnerNode::get_parent() { return parent; }

INode *InnerNode::select_recusively() {
  // expand non terminal nodes
  if (children.size() == 0)
    expand();
  INode *selec = select_child();
  INode *selectedChild = selec->select_recusively();
  return selectedChild;
}

// only implemented in leaf nodes

double InnerNode::simulate() {
  throw std::runtime_error("Simulation not possible in Inner Nodes.");
}

double InnerNode::get_ev() { return backprop_strat->get_ev(); }

int InnerNode::get_nb_samples() { return backprop_strat->get_nb_samples(); }

double InnerNode::get_std_dev() { return backprop_strat->get_std_deviation(); }

double InnerNode::get_variance() { return backprop_strat->get_variance(); }

void InnerNode::backpropagate(double value) {
  backprop_strat->on_backpropagate(value);
  parent->backpropagate(value);
}

InnerNode::~InnerNode() {
  for (auto child : children)
    delete child;
  delete backprop_strat;
  delete context;
}
}
