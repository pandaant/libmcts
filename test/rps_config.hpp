/* 
 * File:   rps_config.hpp
 * Author: batman
 *
 * Created on August 2, 2013, 5:07 PM
 */

#ifndef RPS_CONFIG_H
#define	RPS_CONFIG_H

#include <config.hpp>
#include <selection_strategy.hpp>
#include <sw_backpropagation.hpp>
#include <max_value_selector.hpp>

using namespace MC;

class RPSConfig : public Config {
public:
    BackpropagationStrategy* bp_strat;
    SelectionStrategy* select_strat;
    SelectionStrategy* move_selection_strat;

    RPSConfig(BackpropagationStrategy* bps, SelectionStrategy* ss, SelectionStrategy* mss, bool seed = true):
    Config(mss,seed),
    bp_strat(bps),
    select_strat(ss){
    }
    
    ~RPSConfig(){}
};

#endif	/* RPS_CONFIG_H */

