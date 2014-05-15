/* 
 * File:   max_variance_selector.hpp
 * Author: batman
 *
 * Created on March 20, 2014, 11:40 AM
 */

#ifndef MAX_VARIANCE_SELECTOR_H
#define	MAX_VARIANCE_SELECTOR_H

#include "inode.hpp"
#include "selection_strategy.hpp"

namespace MC {

/**
 * Selects the child with the largest standard deviation.
 * This tries to search the parts of the tree
 * with the greatest uncertainty.
 *
 * Completly unexpanded/unexplored branches have no
 * std dev. every childnode needs min 2 samples for this
 * selector to work.
 */
class MaxStdDeviationSelector : public MaxFunctionSelector {
public:
  virtual double evaluate(INode *node) {
    int nb_samples = node->get_nb_samples();
    if (nb_samples < 2)
      return 0;
    return node->get_std_dev();
  }
};
}

#endif	/* MAX_VARIANCE_SELECTOR_H */

