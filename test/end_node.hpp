/* 
 * File:   end_node.hpp
 * Author: batman
 *
 * Created on August 4, 2013, 12:11 PM
 */

#ifndef END_NODE_H
#define	END_NODE_H

#include <leaf_node.hpp>

#include "rock_paper_scissors.hpp"

using MC::LeafNode;

class EndNode : public LeafNode{
    
public:
    EndNode(Context* _context, INode* _parent, Config* _config):
    LeafNode(_context, _parent, _config){}
    
    virtual double get_ev(){
        return this->simulate();
    }
    
    virtual double get_std_dev(){
        return 0;
    }
    
    virtual double get_variance(){
        return 0;
    }
    
    virtual double simulate(){
        double payoff_3_games = 3;
        RockPaperScissors* con = (RockPaperScissors*)context;
        return ( con->p1.pwin() * payoff_3_games ) + ( con->p1.ptie() * payoff_3_games * 0.5 );
    }
    
    virtual void backpropagate( double value ){
        ++nb_samples;
        this->parent->backpropagate(value);
    }
};

#endif	/* END_NODE_H */

