#include <stdexcept>

#include "max_function_selector.hpp"

namespace MC {

INode *MaxFunctionSelector::select(INode *node) {
  vector<INode *> children = node->get_children();
  vector<double> values(0);
  INode *max_node = NULL;

  // evaluate all children
  for (unsigned i = 0; i < children.size(); i++)
    values.push_back(evaluate(children[i]));

  // find max element
  int max_index =
      std::max_element(values.begin(), values.end()) - values.begin();
  max_node = children[max_index];

  if (max_node == NULL) {
    // fall back on max value selector which can't fail;
    // return (new MaxValueSelector())->select(node);
    throw std::logic_error("MaxFunctionSelector failed to select a max node.");
  }
  return max_node;
}
}
