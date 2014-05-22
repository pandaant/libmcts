#ifndef ISELECTION_STRATEGY_H
#define ISELECTION_STRATEGY_H

#include <random>
#include "inode.hpp"

namespace mcts {

// ----------------------------------------------------------------------
/// @brief   interface for all selection strategies. A selection strategy
///          selects one child of a parent node according to implementation
///          specific metrics.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config> class ISelectionStrategy {
  typedef typename INode<Context, Config>::node_t node_t;

public:
  typedef ISelectionStrategy<Context, Config> sstrategy_t;

  // ----------------------------------------------------------------------
  /// @brief   select a child of node
  ///
  /// @param node to select child from
  ///
  /// @return pointer to childnode of node
  // ----------------------------------------------------------------------
  virtual node_t *select(node_t *node) = 0;

  virtual ~ISelectionStrategy() {}
};
}

#endif
