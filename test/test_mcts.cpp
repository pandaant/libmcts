#include <UnitTest++.h>
#include <mcts.hpp>
#include <sw_backpropagation.hpp>
#include <max_value_selector.hpp>
#include <min_sample_selector.hpp>
#include "rock_paper_scissors.hpp"
#include "result.hpp"
#include "rps_config.hpp"
#include "rps_node.hpp"

SUITE(MCTSTests) {
  using namespace mcts;
  typedef typename INode<RockPaperScissors, RPSConfig>::node_t node_t;
  typedef typename ISelectionStrategy<RockPaperScissors, RPSConfig>::sstrategy_t sstrategy_t;

  struct Setup {
    RockPaperScissors context;
    RPSConfig *conf;
    Player p1, p2;
    ActionType::Enum p1a, p2a;
    MCTS<RockPaperScissors, RPSConfig, RPSNode<RockPaperScissors,RPSConfig>, RPSResult<RockPaperScissors,RPSConfig>> *mcts;
    IBackpropagationStrategy *bp_strat;
    ISelectionStrategy<RockPaperScissors,RPSConfig> *select_strat;
    ISelectionStrategy<RockPaperScissors,RPSConfig> *move_select_strat;

    Setup() {
      int game = 1;
      p1 = Player("mark");
      ++p1.won;
      p2 = Player("simon");
      ++p2.lost;
      p1a = ActionType::PAPER;
      p2a = ActionType::ROCK;
      context = RockPaperScissors(p1, p2, p1a, p2a, game);
      bp_strat = new SampleWeightedBackpropagationStrategy();
      select_strat = new MaxValueSelector<RockPaperScissors,RPSConfig>();
      move_select_strat = new MaxValueSelector<RockPaperScissors,RPSConfig>();

      conf = new RPSConfig(bp_strat, select_strat, move_select_strat, false);
      mcts = new MCTS<RockPaperScissors, RPSConfig, RPSNode<RockPaperScissors,RPSConfig>, RPSResult<RockPaperScissors,RPSConfig>>(context, conf);
    }

    ~Setup() {
      delete mcts;
      delete conf;
      delete move_select_strat;
      delete bp_strat;
      delete select_strat;
    }
  };

  TEST_FIXTURE(Setup, TestIteration) {
    mcts->iterate();

    // 19 because root is 1 plus 2 levels of 9 nodes each
    CHECK_EQUAL(19, mcts->nb_nodes());
  }

  TEST_FIXTURE(Setup, TestTreeExploration) {
    // min selection used so every node is expanded with enough iterations
    sstrategy_t *selector = new MinSampleSelector<RockPaperScissors,RPSConfig>();
    RPSConfig *c = new RPSConfig(bp_strat, selector, move_select_strat, false);

    MCTS<RockPaperScissors, RPSConfig, RPSNode<RockPaperScissors, RPSConfig>, RPSResult<RockPaperScissors, RPSConfig> > *m =
        new MCTS<RockPaperScissors, RPSConfig, RPSNode<RockPaperScissors, RPSConfig>, RPSResult<RockPaperScissors, RPSConfig>>(context, c);

    for (int i = 0; i < 81; ++i)
      m->iterate();

    // 91 because root is 1 + 9 first lvl + 9*9 second lvl nodes each.
    // so every leaf node in the tree will be visited once.
    CHECK_EQUAL(91, m->nb_nodes());

    vector<node_t *> children = m->root()->children();
    std::for_each(children.begin(), children.end(), [](node_t * n) {
      RockPaperScissors state = n->context();
      /*std::cout << ActionType::ToStr[state->p1_action]
      << "/" << ActionType::ToStr[state->p2_action] << " | EV: "
      << n->get_ev() << " | samples: " << n->get_nb_samples() << std::endl;*/
      vector<node_t *> children = n->children();
      std::for_each(children.begin(), children.end(), [](node_t * n) {
        /*RockPaperScissors* state = (RockPaperScissors*) n->get_context();
        std::cout << "    " << ActionType::ToStr[state->p1_action]
                << "/" << ActionType::ToStr[state->p2_action] << " | EV: "
                << n->get_ev() << " | samples: " << n->get_nb_samples() << "
        " << state->p1.won << ";" << state->p1.tie << ";" << state->p1.lost <<
        std::endl;*/
        CHECK_EQUAL(1, n->nb_samples());
      });

      if (state.p1_action == state.p2_action)
        CHECK_EQUAL(2, n->ev());

      if (state.p1_action == ActionType::PAPER &&
          state.p2_action == ActionType::ROCK)
        CHECK_EQUAL(2.5, n->ev());

      if (state.p1_action == ActionType::ROCK &&
          state.p2_action == ActionType::PAPER)
        CHECK_EQUAL(1.5, n->ev());
    });

    delete m;
    delete c;
    delete selector;
  }

  TEST_FIXTURE(Setup, TestResultSelection) {
    for (int i = 0; i < 81; ++i)
      mcts->iterate();

    RPSResult<RockPaperScissors, RPSConfig> r = mcts->result();

    CHECK_EQUAL(ActionType::ROCK, r.action);
  }
}

