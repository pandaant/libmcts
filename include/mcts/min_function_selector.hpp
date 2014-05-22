#ifndef MIN_FUNCTION_SELECTOR_H
#define MIN_FUNCTION_SELECTOR_H

#include <vector>
#include "iselection_strategy.hpp"
#include "inode.hpp"

namespace mcts {
using std::vector;

// ----------------------------------------------------------------------
/// @brief  selects a node that minimises a given metric
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config>
class MinFunctionSelector : public ISelectionStrategy<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  node_t *select(node_t *node) {
    vector<node_t *> children = node->children();
    vector<double> values(children.size());
    node_t *min_node = NULL;

    for (unsigned i = 0; i < children.size(); i++) {
      values[i] = evaluate(children[i]);
    }

    size_t min_index =
        std::min_element(values.begin(), values.end()) - values.begin();
    min_node = children[min_index];

    if (min_node == NULL) {
      throw std::logic_error("MinFunctionSelector failed to select a node.");
    }
    return min_node;
  }

  // ----------------------------------------------------------------------
  /// @brief   this function has to be implemented in derived classes that
  ///          specializes the metric to be used. every child is evaluated
  ///          against this method.
  ///
  /// @param node to evaluate
  ///
  /// @return number representing some metric.
  // ----------------------------------------------------------------------
  virtual double evaluate(node_t *node) const = 0;
};
}

#endif
