/* 
 * File:   rps_node.hpp
 * Author: batman
 *
 * Created on August 2, 2013, 2:22 PM
 */

#ifndef RPS_NODE_H
#define	RPS_NODE_H

#include <inode.hpp>
#include <inner_node.hpp>
#include <sw_backpropagation.hpp>
#include "rps_config.hpp"
#include "end_node.hpp"

class RPSNode : public InnerNode {
public:

    RPSNode(Context* _context, INode* _parent, Config* _config) :
    InnerNode(_context, _parent, _config, new SampleWeightedBackpropagationStrategy()) {
    }

    ~RPSNode() {
    }

    void expand() {
        vector<Context*> contexts = context->transition();
        std::for_each(contexts.begin(), contexts.end(), [&](Context * c) {
            if (c->is_terminal())
                this->children.push_back((INode*) new EndNode(c, (INode*)this, this->config));
            else
                this->children.push_back((INode*) new RPSNode(c, (INode*)this, this->config));
        });
        contexts.clear();
    }

    virtual INode* select_child() {
        return ((RPSConfig*) this->config)->select_strat->select((INode*)this);
    }
    
    /*virtual INode* select_child() {
        RPSConfig* conf = (RPSConfig*) this->config;
        SelectionStrategy* st = conf->select_strat.get();
        INode* node;
        try{
            node = st->select((INode*)this);
        }
        catch(std::exception e){
            std::cout << e.what() << std::endl;
        }
        return node;
    }*/
};

#endif	/* RPS_NODE_H */

