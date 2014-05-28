#ifndef VISITOR_H
#define VISITOR_H

namespace mcts {

// forward declaring node interface
template <typename Context, typename Config> class INode;

// ----------------------------------------------------------------------
/// @brief   implements interface for visitor objects.
///
/// @tparam Context @README
/// @tparam Config  @README
// ----------------------------------------------------------------------
template <typename Context, typename Config> class IVisitor {
  typedef INode<Context, Config> node_t;

public:
  typedef IVisitor<Context, Config> visitor_t;

  virtual ~IVisitor() {}
  virtual void visit(node_t *node) = 0;
};
}

#endif
