#ifndef RESULT_H
#define	RESULT_H

#include <inode.hpp>
#include "action_type.hpp"
#include "rock_paper_scissors.hpp"

template<typename Context, typename Config>
class RPSResult {
    typedef typename mcts::INode<Context, Config>::node_t node_t;
public:
  ActionType::Enum action;

  RPSResult(node_t *next_move_node) {
    action = (next_move_node->context()).p1_action;
  }

  string to_str(){
    return ActionType::ToStr[action];
  }
};

#endif
