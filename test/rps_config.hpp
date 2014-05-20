#ifndef RPS_CONFIG_H
#define	RPS_CONFIG_H

#include <selection_strategy.hpp>
#include <sw_backpropagation.hpp>
#include <max_value_selector.hpp>

using mcts::BackpropagationStrategy;
using mcts::SelectionStrategy;

class RPSConfig {
    typedef std::mt19937 generator_t;

public:
  generator_t* nb_gen_;
  BackpropagationStrategy *bp_strat;
  SelectionStrategy<RockPaperScissors, RPSConfig> *select_strat;
  SelectionStrategy<RockPaperScissors, RPSConfig> *move_selection_strat_;

  RPSConfig(BackpropagationStrategy *bps,
            SelectionStrategy<RockPaperScissors, RPSConfig> *ss,
            SelectionStrategy<RockPaperScissors, RPSConfig> *mss,
            bool seed = true)
      : bp_strat(bps), select_strat(ss), move_selection_strat_(mss),
        nb_gen_(new generator_t(0)) {}

  RPSConfig(const RPSConfig& c)
      : bp_strat(c.bp_strat), select_strat(c.select_strat), move_selection_strat_(c.move_selection_strat_) {
  }

  ~RPSConfig() {
  }

   generator_t* nb_gen(){
    return nb_gen_;
   }

  SelectionStrategy<RockPaperScissors, RPSConfig> *move_selection_strat(){
   return move_selection_strat_;   
  }
};

#endif
