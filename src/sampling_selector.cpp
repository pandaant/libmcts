#include "sampling_selector.hpp"

namespace MC {

INode *SamplingSelector::select(INode *node) {
  DistributionType dist(0, node->get_children().size() - 1);
  int rand = dist(*node->get_config()->get_nb_gen());
  return node->get_children()[rand];
}
}
