#ifndef VISITOR_H
#define VISITOR_H

namespace mcts {

template <typename Context, typename Config> class INode;

template<typename Context, typename Config>
class Visitor {
public:
    typedef Visitor<Context, Config> visitor_t;

  virtual void visit(INode<Context, Config> *node) = 0;
  virtual ~Visitor(){}
};
}

#endif /* VISITOR_H */

