#ifndef MAXFUNCTIONSELECTOR_H
#define MAXFUNCTIONSELECTOR_H

#include <vector>
#include <stdexcept>
#include <algorithm>
#include "selection_strategy.hpp"

namespace mcts {
using std::vector;

/**
 * MaxFunctionSelector
 * Selects the child that maximizes the
 * evaluation function.
 **/
template <typename Context, typename Config>
class MaxFunctionSelector : public SelectionStrategy<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  node_t *select(node_t *node) {
    vector<node_t *> children = node->children();
    vector<double> values(children.size());
    node_t *max_node = NULL;

    // evaluate all children
    for (unsigned i = 0; i < children.size(); i++)
      values[i] = evaluate(children[i]);

    // find max element
    size_t max_index =
        std::max_element(values.begin(), values.end()) - values.begin();
    max_node = children[max_index];

    if (max_node == NULL) {
      // fall back on max value selector which can't fail;
      // return (new MaxValueSelector())->select(node);
      throw std::logic_error(
          "MaxFunctionSelector failed to select a max node.");
    }
    return max_node;
  }

  /**
   * implement in derived classes.
   * evaluates a node and returns the numerical value.
   **/
  virtual double evaluate(node_t *node) = 0;
};
}

#endif /* MAX_FUNCTION_SELECTOR_H */

