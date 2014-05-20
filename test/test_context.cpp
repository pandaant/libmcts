#include <UnitTest++.h>
#include <algorithm>
#include "rock_paper_scissors.hpp"

SUITE(ContextTests) {
  struct Setup {
    RockPaperScissors context;
    Player p1, p2;
    ActionType::Enum p1a, p2a;

    Setup() {
      int game = 1;
      p1 = Player("mark");
      p2 = Player("simon");
      p1a = ActionType::PAPER;
      p2a = ActionType::ROCK;
      context = RockPaperScissors(p1, p2, p1a, p2a, game);
    }
  };

  TEST_FIXTURE(Setup, TestTransition) {
    vector<RockPaperScissors> next_contexts = context.transition();

    CHECK_EQUAL(9, next_contexts.size());

    RockPaperScissors first_new = next_contexts[0];
    CHECK_EQUAL(2, first_new.nb_game);
    CHECK_EQUAL(ActionType::ROCK, first_new.p1_action);
    CHECK_EQUAL(ActionType::ROCK, first_new.p2_action);

    RockPaperScissors second_new = next_contexts[1];
    CHECK_EQUAL(ActionType::ROCK, second_new.p1_action);
    CHECK_EQUAL(ActionType::PAPER, second_new.p2_action);

    RockPaperScissors last_new = next_contexts[8];
    CHECK_EQUAL(ActionType::SCISSORS, last_new.p1_action);
    CHECK_EQUAL(ActionType::SCISSORS, last_new.p2_action);
  }

  TEST_FIXTURE(Setup, TestIsFinalState) {
    CHECK_EQUAL(false, context.is_terminal());
    RockPaperScissors c(p1, p2, p1a, p2a, 3);
    CHECK_EQUAL(true, c.is_terminal());
  }
}
