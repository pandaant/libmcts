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

using mcts::InnerNode;
using mcts::SampleWeightedBackpropagationStrategy;

template<typename Context, typename Config>
class RPSNode : public InnerNode<Context, Config> {
    typedef typename mcts::INode<Context, Config>::node_t node_t;
    typedef EndNode<Context, Config> end_node_t;
    typedef RPSNode<Context, Config> rps_node_t;
public:
    RPSNode(const Context &_context, Config* _config, node_t* _parent) :
    InnerNode<Context, Config>(_context, _config, _parent, new SampleWeightedBackpropagationStrategy()) {
    }

    ~RPSNode() {
    }

    void expand() {
        vector<Context> contexts = this->context().transition();
        std::for_each(contexts.begin(), contexts.end(), [&](Context& c) {
            if (c.is_terminal())
                this->add_child((node_t*) new end_node_t(c, this->config(), (node_t*)this));
            else
                this->add_child((node_t*) new rps_node_t(c, this->config(), (node_t*)this));
        });
        contexts.clear();
    }

    virtual node_t* select_child() {
        return this->config()->select_strat->select((node_t*)this);
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

