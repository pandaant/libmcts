#ifndef UCT_SELECTOR_H
#define UCT_SELECTOR_H

#include <cmath>
#include "inode.hpp"
#include "max_function_selector.hpp"

namespace mcts {

/**
 * UCTSelectionStrategy
 * Selects the childnode, witch maximizes the ratio
 * between samples and ev of the parent node.
 **/
template <typename Context, typename Config>
class UCTSelector : public MaxFunctionSelector<Context, Config> {
private:
  /**
   * C - Exploration vs Exploitation
   * small C = tree will be expanded deeper,
   *           the best node will be evaluated often
   * big C = the tree will be expanded wider.
   *         more nodes in one level will be evaluated.
   **/
  double C;

public:
  /**
   * @param _C	tuningparameter ( has to be found experimentally )
   **/
  UCTSelector(double _C) : C(_C) {}

  // for formular look at : Technical Report TUD�KE�2009-2
  double evaluate(INode<Context, Config> *node) {
    int nb_samples = node->nb_samples();
    if (nb_samples == 0)
      return 0;

    int nb_parent_samples = node->parent()->nb_samples();
    return node->ev() +
           C * sqrt(log((double)nb_parent_samples) / nb_samples);
  }
};
}

#endif /* UCT_SELECTOR_H */

