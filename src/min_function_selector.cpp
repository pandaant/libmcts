#include "min_function_selector.hpp"

namespace MC {

INode *MinFunctionSelector::select(INode *node) {
  vector<INode *> children = node->get_children();
  vector<double> values(0);
  INode *min_node = NULL;

  // evaluate all children
  for (unsigned i = 0; i < children.size(); i++)
    values.push_back(evaluate(children[i]));

  // find min element
  int min_index =
      std::min_element(values.begin(), values.end()) - values.begin();
  min_node = children[min_index];

  if (min_node == NULL) {
    // fallback strategy
  }
  return min_node;
}
}
