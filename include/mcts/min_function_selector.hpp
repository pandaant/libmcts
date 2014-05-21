#ifndef MIN_FUNCTION_SELECTOR_H
#define MIN_FUNCTION_SELECTOR_H

#include <vector>
#include "iselection_strategy.hpp"
#include "inode.hpp"

namespace mcts {
using std::vector;

/**
 * MinFunctionSelector
 * Selects the child that minimizes the
 * evaluation function.
 **/
template <typename Context, typename Config>
class MinFunctionSelector : public ISelectionStrategy<Context, Config> {
    typedef typename INode<Context, Config>::node_t node_t;

public:
  node_t *select(node_t *node) {
    vector<node_t *> children = node->children();
    vector<double> values(0);
    node_t *min_node = NULL;

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

  /**
   * implement in derived classes.
   * evaluates a node and returns the numerical value.
   **/
  virtual double evaluate(node_t *node) = 0;
};
}

#endif /* MIN_FUNCTION_SELECTOR_H */

