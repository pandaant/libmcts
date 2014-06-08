#ifndef RPS_CONFIG_H
#define RPS_CONFIG_H

#include <iselection_strategy.hpp>
#include <avg_backpropagation_strategy.hpp>
#include <max_value_selector.hpp>

using mcts::IBackpropagationStrategy;
using mcts::ISelectionStrategy;

class RPSConfig {
  typedef std::mt19937 generator_t;
  typedef typename ISelectionStrategy<RockPaperScissors, RPSConfig>::sstrategy_t
  sstrategy_t;

public:
  generator_t *nb_gen_;
  IBackpropagationStrategy *bp_strat;
  sstrategy_t *select_strat;
  sstrategy_t *move_selection_strat_;

  RPSConfig(IBackpropagationStrategy *bps, sstrategy_t *ss, sstrategy_t *mss,
            bool seed = true)
      : bp_strat(bps), select_strat(ss), move_selection_strat_(mss),
        nb_gen_(new generator_t(0)) {}

  RPSConfig(const RPSConfig &c)
      : bp_strat(c.bp_strat), select_strat(c.select_strat),
        move_selection_strat_(c.move_selection_strat_) {}

  ~RPSConfig() {}

  generator_t *nb_gen() { return nb_gen_; }

  sstrategy_t *move_selector() { return move_selection_strat_; }
};

#endif
