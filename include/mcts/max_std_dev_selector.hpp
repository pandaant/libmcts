#ifndef MAX_VARIANCE_SELECTOR_H
#define	MAX_VARIANCE_SELECTOR_H

#include "inode.hpp"
#include "selection_strategy.hpp"

namespace mcts {

/**
 * Selects the child with the largest standard deviation.
 * This tries to search the parts of the tree
 * with the greatest uncertainty.
 *
 * Completly unexpanded/unexplored branches have no
 * std dev. every childnode needs min 2 samples for this
 * selector to work.
 */
template <typename Context, typename Config>
class MaxStdDeviationSelector : public MaxFunctionSelector<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  virtual double evaluate(node_t *node) {
    int nb_samples = node->nb_samples();
    if (nb_samples < 2)
      return 0;
    return node->std_dev();
  }
};
}

#endif
