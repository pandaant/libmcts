#ifndef MAXFUNCTIONSELECTOR_H
#define MAXFUNCTIONSELECTOR_H

#include <vector>
#include <stdexcept>
#include <algorithm>
#include "iselection_strategy.hpp"

namespace mcts {
using std::vector;

// ----------------------------------------------------------------------
/// @brief   selector selects the child of a node that maximises a given
///          metric.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config>
class MaxFunctionSelector : public ISelectionStrategy<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  node_t *select(node_t *node) {
    node_t *max_node = NULL;
    vector<node_t *> children = node->children();
    vector<double> values(children.size());

    for (unsigned i = 0; i < children.size(); i++)
      values[i] = evaluate(children[i]);

    size_t max_index =
        std::max_element(values.begin(), values.end()) - values.begin();
    max_node = children[max_index];

    if (max_node == NULL) {
      throw std::logic_error("MaxFunctionSelector failed to select a node.");
    }
    return max_node;
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
