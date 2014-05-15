#include <UnitTest++.h>
#include <sw_backpropagation.hpp>
#include <max_value_selector.hpp>
#include <root_node.hpp>
#include "rock_paper_scissors.hpp"
#include "rps_config.hpp"
#include "rps_node.hpp"
#include "end_node.hpp"

SUITE(NodeTests) {
  using namespace MC;

  struct Setup {
    RockPaperScissors *context;
    Player p1, p2;
    ActionType::Enum p1a, p2a;
    RPSConfig *conf;
    int game;
    BackpropagationStrategy *bp_strat;
    SelectionStrategy *select_strat;
    SelectionStrategy *move_select_strat;

    Setup() {
      game = 1;
      p1 = Player("mark");
      p2 = Player("simon");
      p1a = ActionType::PAPER;
      p2a = ActionType::ROCK;
      context = new RockPaperScissors(p1, p2, p1a, p2a, game);
      bp_strat = new SampleWeightedBackpropagationStrategy();
      select_strat = new MaxValueSelector();
      move_select_strat = new MaxValueSelector();

      conf = new RPSConfig(bp_strat, select_strat, move_select_strat, false);
    }

    ~Setup() {
      delete context;
      delete conf;
      delete move_select_strat;
      delete bp_strat;
      delete select_strat;
    }
  };

  TEST_FIXTURE(Setup, TestEndNodeSimulation) {
    p1.won = 2;
    p1.tie = 0;
    p1.lost = 1;

    p2.won = 1;
    p2.tie = 0;
    p2.lost = 2;

    RockPaperScissors *c = new RockPaperScissors(p1, p2, p1a, p2a, game);

    EndNode *n = new EndNode(c, NULL, conf);
    double ev = n->simulate();

    CHECK_CLOSE(2, ev, 0.001);

    p1.won = 3;
    p1.tie = 0;
    p1.lost = 0;

    p2.won = 0;
    p2.tie = 0;
    p2.lost = 3;

    c = new RockPaperScissors(p1, p2, p1a, p2a, game);

    delete n;
    n = new EndNode(c, NULL, conf);
    ev = n->simulate();

    CHECK_CLOSE(3, ev, 0.001);

    delete n;
  }

  TEST_FIXTURE(Setup, TestSelectNode) {

    RPSNode *n = new RootNode<RPSNode>(context->clone(), conf);
    n->expand();

    // backpropagate some values
    n->get_children()[0]->backpropagate(7);
    n->get_children()[1]->backpropagate(3);
    n->get_children()[2]->backpropagate(2);

    CHECK_EQUAL(n->get_children()[0], n->select_child());

    n->get_children()[3]->backpropagate(12);
    n->get_children()[4]->backpropagate(17);
    n->get_children()[5]->backpropagate(18);

    CHECK_EQUAL(n->get_children()[5], n->select_child());

    n->get_children()[4]->backpropagate(9);
    n->get_children()[4]->backpropagate(30);

    CHECK_EQUAL(n->get_children()[4], n->select_child());

    n->get_children()[7]->backpropagate(60);
    n->get_children()[8]->backpropagate(60);

    // first max element
    CHECK_EQUAL(n->get_children()[7], n->select_child());

    delete n;
  }

  TEST_FIXTURE(Setup, TestSelectRecusively) {
    RPSNode *n = new RootNode<RPSNode>(context->clone(), conf);

    INode *selected = n->select_recusively();
    CHECK(selected->get_context()->is_terminal());

    delete n;
  }

  /*  TEST_FIXTURE(Setup, TestSimulate){
        RPSConfig* conf = new RPSConfig(
                    new SampleWeightedBackpropagationStrategy(),
                    new MaxValueSelector()
                    );

        RPSNode* n = new RootNode(context, conf);

        INode* selected = n->select_recusively();

        delete conf;
    }*/
}
