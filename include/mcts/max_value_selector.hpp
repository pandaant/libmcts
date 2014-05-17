#ifndef MAX_VALUE_SELECTOR_H
#define MAX_VALUE_SELECTOR_H

#include "max_function_selector.hpp"

namespace mcts {

/**
 * MaxValueSelector
 * selects child with max ev
 **/
template <typename Context, typename Config>
class MaxValueSelector : public MaxFunctionSelector<Context, Config> {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  virtual double evaluate(node_t *node){ return node->ev(); }
};
}

#endif
