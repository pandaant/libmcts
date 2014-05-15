#include <UnitTest++.h>
#include "running_stats.hpp"

SUITE(MCTSTests) {
  using namespace MC;

  TEST(RunningStatsCorrectness) {
    RunningStats stats = RunningStats();

    CHECK_EQUAL(0, stats.mean());
    CHECK_EQUAL(0, stats.variance());
    CHECK_EQUAL(0, stats.standard_deviation());

    stats.push(1);
    stats.push(2);

    CHECK_CLOSE(1.5, stats.mean(), 0.01);
    CHECK_CLOSE(0.5, stats.variance(), 0.01);
    CHECK_CLOSE(0.70711, stats.standard_deviation(), 0.01);

    stats.push(17);
    stats.push(44);

    CHECK_CLOSE(16, stats.mean(), 0.01);
    CHECK_CLOSE(402, stats.variance(), 0.01);
    CHECK_CLOSE(20.04994, stats.standard_deviation(), 0.01);

    stats.push(-12);

    CHECK_CLOSE(10.4, stats.mean(), 0.01);
    CHECK_CLOSE(458.3, stats.variance(), 0.01);
    CHECK_CLOSE(21.40794, stats.standard_deviation(), 0.01);
  }
}
