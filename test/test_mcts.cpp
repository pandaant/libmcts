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
  using namespace MC;

  struct Setup {
    Context *context;
    RPSConfig *conf;
    Player p1, p2;
    ActionType::Enum p1a, p2a;
    MCTS<RPSNode, RPSResult> *mcts;
    BackpropagationStrategy *bp_strat;
    SelectionStrategy *select_strat;
    SelectionStrategy *move_select_strat;

    Setup() {
      int game = 1;
      p1 = Player("mark");
      ++p1.won;
      p2 = Player("simon");
      ++p2.lost;
      p1a = ActionType::PAPER;
      p2a = ActionType::ROCK;
      context = new RockPaperScissors(p1, p2, p1a, p2a, game);
      bp_strat = new SampleWeightedBackpropagationStrategy();
      select_strat = new MaxValueSelector();
      move_select_strat = new MaxValueSelector();

      conf = new RPSConfig(bp_strat, select_strat, move_select_strat, false);
      mcts = new MCTS<RPSNode, RPSResult>(context, conf);
    }

    ~Setup() {
      delete context;
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
    CHECK_EQUAL(19, mcts->size());
  }

  TEST_FIXTURE(Setup, TestTreeExploration) {
    // min selection used so every node is expanded with enough iterations
    SelectionStrategy *selector = new MinSampleSelector();
    RPSConfig *c = new RPSConfig(bp_strat, selector, move_select_strat, false);

    MCTS<RPSNode, RPSResult> *m = new MCTS<RPSNode, RPSResult>(context, c);

    for (int i = 0; i < 81; ++i)
      m->iterate();

    // 91 because root is 1 + 9 first lvl + 9*9 second lvl nodes each.
    // so every leaf node in the tree will be visited once.
    CHECK_EQUAL(91, m->size());

    vector<INode *> children = m->get_root()->get_children();
    std::for_each(children.begin(), children.end(), [](INode * n) {
      RockPaperScissors *state = (RockPaperScissors *)n->get_context();
      /*std::cout << ActionType::ToStr[state->p1_action]
      << "/" << ActionType::ToStr[state->p2_action] << " | EV: "
      << n->get_ev() << " | samples: " << n->get_nb_samples() << std::endl;*/
      vector<INode *> children = n->get_children();
      std::for_each(children.begin(), children.end(), [](INode * n) {
        /*RockPaperScissors* state = (RockPaperScissors*) n->get_context();
        std::cout << "    " << ActionType::ToStr[state->p1_action]
                << "/" << ActionType::ToStr[state->p2_action] << " | EV: "
                << n->get_ev() << " | samples: " << n->get_nb_samples() << "
        " << state->p1.won << ";" << state->p1.tie << ";" << state->p1.lost <<
        std::endl;*/
        CHECK_EQUAL(1, n->get_nb_samples());
      });

      if (state->p1_action == state->p2_action)
        CHECK_EQUAL(2, n->get_ev());

      if (state->p1_action == ActionType::PAPER &&
          state->p2_action == ActionType::ROCK)
        CHECK_EQUAL(2.5, n->get_ev());

      if (state->p1_action == ActionType::ROCK &&
          state->p2_action == ActionType::PAPER)
        CHECK_EQUAL(1.5, n->get_ev());
    });

    delete m;
    delete c;
    delete selector;
  }

  TEST_FIXTURE(Setup, TestResultSelection) {
    for (int i = 0; i < 81; ++i)
      mcts->iterate();

    RPSResult r = mcts->get_result();

    CHECK_EQUAL(ActionType::ROCK, r.action);
  }
}

