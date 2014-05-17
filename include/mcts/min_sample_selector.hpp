/*
 * File:   min_sample_selector.hpp
 * Author: batman
 *
 * Created on August 5, 2013, 11:22 PM
 */

#ifndef MIN_SAMPLE_SELECTOR_H
#define MIN_SAMPLE_SELECTOR_H

#include "min_function_selector.hpp"

namespace mcts {

/**
 * MinSampleSelector
 * Selects the childnode with the lowest samples.
 **/
template <typename Context, typename Config>
class MinSampleSelector : public MinFunctionSelector<Context, Config> {
public:

  MinSampleSelector() {}

  virtual double evaluate(INode<Context, Config> *node) { return node->get_nb_samples(); }
};
}

#endif /* MIN_SAMPLE_SELECTOR_H */

