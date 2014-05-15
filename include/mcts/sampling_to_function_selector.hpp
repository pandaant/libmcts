/*
 * File:   sampling_to_function_selector.hpp
 * Author: batman
 *
 * Created on August 5, 2013, 10:43 PM
 */

#ifndef SAMPLING_TO_FUNCTION_SELECTOR_H
#define SAMPLING_TO_FUNCTION_SELECTOR_H

#include "sampling_selector.hpp"

namespace MC {

/**
 * SamplingToFunctionSelector
 * Uses the Sampling selector until a given
 * threshold is exeeded. After that the supplied
 * SelectionStrategy is used.
 **/
class SamplingToFunctionSelector : public SelectionStrategy {
public:
  int threshold;
  SamplingSelector sselector;
  SelectionStrategy *function_strat;

  /**
   * @param _threshold	if exeeded, _functionStrategy is used
   * @param _functionStrat..	Strategy to use if theshold is exeeded
   **/
  SamplingToFunctionSelector(int _threshold, SelectionStrategy *_function_strat)
      : threshold(_threshold), sselector(SamplingSelector()),
        function_strat(_function_strat) {}

  INode *select(INode *node) {
    // choose random child if smaller than threshold
    if (node->get_nb_samples() < threshold)
      return sselector.select(node);
    else
      return function_strat->select(node);
  }
};
}

#endif /* SAMPLING_TO_FUNCTION_SELECTOR_H */

