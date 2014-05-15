#include "uct_selector.hpp"

namespace MC {

double UCTSelector::evaluate(INode *node) {
  int nb_samples = node->get_nb_samples();
  if (nb_samples == 0)
    return 0;

  int nb_parent_samples = node->get_parent()->get_nb_samples();
  return node->get_ev() + C * sqrt(log((double)nb_parent_samples) / nb_samples);
}
}
