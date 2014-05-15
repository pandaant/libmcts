/* 
 * File:   result.hpp
 * Author: batman
 *
 * Created on August 4, 2013, 12:41 PM
 */

#ifndef RESULT_H
#define	RESULT_H

#include <inode.hpp>
#include "action_type.hpp"
#include "rock_paper_scissors.hpp"

class RPSResult {
public:
    ActionType::Enum action;

    RPSResult(MC::INode* next_move_node) {
        action = ((RockPaperScissors*) next_move_node->get_context())->p1_action;
    }
};

#endif	/* RESULT_H */

