#include <UnitTest++.h>
#include <sw_backpropagation.hpp>

SUITE(BackpropagationTests) {
  using namespace MC;

  TEST(TestSWBackpropagation) {
    SampleWeightedBackpropagationStrategy stats;

    CHECK_EQUAL(0, stats.get_ev());
    CHECK_EQUAL(0, stats.get_variance());
    CHECK_EQUAL(0, stats.get_std_deviation());

    stats.on_backpropagate(1);
    stats.on_backpropagate(2);

    CHECK_CLOSE(1.5, stats.get_ev(), 0.01);
    CHECK_CLOSE(0.5, stats.get_variance(), 0.01);
    CHECK_CLOSE(0.70711, stats.get_std_deviation(), 0.01);

    stats.on_backpropagate(17);
    stats.on_backpropagate(44);

    CHECK_CLOSE(16, stats.get_ev(), 0.01);
    CHECK_CLOSE(402, stats.get_variance(), 0.01);
    CHECK_CLOSE(20.04994, stats.get_std_deviation(), 0.01);

    stats.on_backpropagate(-12);

    CHECK_CLOSE(10.4, stats.get_ev(), 0.01);
    CHECK_CLOSE(458.3, stats.get_variance(), 0.01);
    CHECK_CLOSE(21.40794, stats.get_std_deviation(), 0.01);
  }
}

