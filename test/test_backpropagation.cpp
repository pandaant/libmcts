#include <UnitTest++.h>
#include <avg_backpropagation_strategy.hpp>

SUITE(BackpropagationTests) {
  using namespace mcts;

  TEST(TestSWBackpropagation) {
    AvgBackpropagationStrategy stats;

    CHECK_EQUAL(0, stats.ev());
    CHECK_EQUAL(0, stats.variance());
    CHECK_EQUAL(0, stats.std_deviation());

    stats.on_backpropagate(1);
    stats.on_backpropagate(2);

    CHECK_CLOSE(1.5, stats.ev(), 0.01);
    CHECK_CLOSE(0.5, stats.variance(), 0.01);
    CHECK_CLOSE(0.70711, stats.std_deviation(), 0.01);

    stats.on_backpropagate(17);
    stats.on_backpropagate(44);

    CHECK_CLOSE(16, stats.ev(), 0.01);
    CHECK_CLOSE(402, stats.variance(), 0.01);
    CHECK_CLOSE(20.04994, stats.std_deviation(), 0.01);

    stats.on_backpropagate(-12);

    CHECK_CLOSE(10.4, stats.ev(), 0.01);
    CHECK_CLOSE(458.3, stats.variance(), 0.01);
    CHECK_CLOSE(21.40794, stats.std_deviation(), 0.01);
  }
}

