/*
 * File:   uct_selector.hpp
 * Author: batman
 *
 * Created on August 5, 2013, 11:34 PM
 */

#ifndef UCT_SELECTOR_H
#define UCT_SELECTOR_H

#include <cmath>
#include "inode.hpp"
#include "max_function_selector.hpp"

namespace MC {

/**
 * UCTSelectionStrategy
 * Selects the childnode, witch maximizes the ratio
 * between samples and ev of the parent node.
 **/
class UCTSelector : public MaxFunctionSelector {
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
  double evaluate(INode *node);
};
}

#endif /* UCT_SELECTOR_H */

