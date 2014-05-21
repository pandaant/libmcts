#ifndef UCT_SELECTOR_H
#define UCT_SELECTOR_H

#include <cmath>
#include "inode.hpp"
#include "max_function_selector.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   selector that selects the childnode, that maximises the
///          ratio between samples and ev of the parent node.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config>
class UCTSelector : public MaxFunctionSelector<Context, Config> {
private:
  typedef typename INode<Context, Config>::node_t node_t;

  /// tuning parameter
  double C;

public:
  // ----------------------------------------------------------------------
  /// @brief constructs a new selector
  ///
  /// @param _C Exploration vs Exploitation
  ///           small C = tree will be expanded deeper, the best node will
  ///           be evaluated often.
  ///           big C = the tree will be expanded wider.More nodes in one
  ///           level will be evaluated.
  // ----------------------------------------------------------------------
  UCTSelector(double _C) : C(_C) {}

  double evaluate(node_t *node) const {
    int nb_samples = node->nb_samples();
    if (nb_samples == 0)
      return 0;

    int nb_parent_samples = node->parent()->nb_samples();
    return node->ev() + C * sqrt(log((double)nb_parent_samples) / nb_samples);
  }
};
}

#endif
