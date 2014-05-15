/*
 * File:   sampling_selector.hpp
 * Author: batman
 *
 * Created on August 5, 2013, 9:24 PM
 */

#ifndef SAMPLING_SELECTOR_H
#define SAMPLING_SELECTOR_H

#include <tr1/random>
#include "inode.hpp"
#include "selection_strategy.hpp"

namespace MC {

/**
 * SamplingSelector
 * Selects a random child, based on an uniform distribution.
 **/
class SamplingSelector : public SelectionStrategy {
public:
  typedef std::tr1::uniform_int<> DistributionType;

  SamplingSelector() {}
  INode *select(INode *node);
};
}

#endif /* SAMPLING_SELECTOR_H */

