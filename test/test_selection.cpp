#include <map>
#include <iostream>
#include <UnitTest++.h>
#include <max_value_selector.hpp>
#include <sampling_selector.hpp>
#include <sampling_to_function_selector.hpp>
#include <min_sample_selector.hpp>
#include <uct_selector.hpp>
#include <root_node.hpp>
#include "rock_paper_scissors.hpp"
#include "rps_node.hpp"
#include "rps_config.hpp"

SUITE(SelectionTests) {
  using namespace mcts;
  typedef typename INode<RockPaperScissors, RPSConfig>::node_t node_t;
  typedef typename ISelectionStrategy<RockPaperScissors, RPSConfig>::sstrategy_t
  sstrategy_t;

  struct Setup {
    Player p1, p2;
    RPSConfig *conf;
    RockPaperScissors context;
    ActionType::Enum p1a, p2a;
    sstrategy_t *select_strat;
    sstrategy_t *move_select_strat;
    IBackpropagationStrategy *bp_strat;
    RootNode<RockPaperScissors, RPSConfig,
             RPSNode<RockPaperScissors, RPSConfig>> *root;

    Setup() {
      context = RockPaperScissors(Player("mark"), Player("simon"),
                                  ActionType::PAPER, ActionType::ROCK, 1);
      bp_strat = new AvgBackpropagationStrategy();
      select_strat = new MaxValueSelector<RockPaperScissors, RPSConfig>();
      move_select_strat = new MaxValueSelector<RockPaperScissors, RPSConfig>();

      conf = new RPSConfig(bp_strat, select_strat, move_select_strat, false);
      root = new RootNode<RockPaperScissors, RPSConfig,
                          RPSNode<RockPaperScissors, RPSConfig>>(context, conf);
      root->expand();
    }

    ~Setup() {
      delete conf;
      delete root;
      delete move_select_strat;
      delete bp_strat;
      delete select_strat;
    }
  };

  TEST_FIXTURE(Setup, TestMaxValueSelector) {
    MaxValueSelector<RockPaperScissors, RPSConfig> selector =
        MaxValueSelector<RockPaperScissors, RPSConfig>();

    CHECK_EQUAL(9, root->children().size());

    // backpropagate some values
    root->children()[0]->backpropagate(7);
    root->children()[1]->backpropagate(3);
    root->children()[2]->backpropagate(2);

    CHECK_EQUAL(root->children()[0], selector.select(root));

    root->children()[3]->backpropagate(12);
    root->children()[4]->backpropagate(17);
    root->children()[5]->backpropagate(18);

    CHECK_EQUAL(root->children()[5], selector.select(root));

    root->children()[4]->backpropagate(9);
    root->children()[4]->backpropagate(30);

    CHECK_EQUAL(root->children()[4], selector.select(root));

    root->children()[7]->backpropagate(60);
    root->children()[8]->backpropagate(60);

    // first max element
    CHECK_EQUAL(root->children()[7], selector.select(root));
  }

  TEST_FIXTURE(Setup, TestSamplingSelector) {
    SamplingSelector<RockPaperScissors, RPSConfig> selector =
        SamplingSelector<RockPaperScissors, RPSConfig>();
    std::map<node_t *, int> counts;
    for (int i = 0; i < 200; ++i) {
      // std::cout << (*root->config()->nb_gen())() << std::endl;
      ++counts[selector.select(root)];
    }

    CHECK_EQUAL(9, counts.size());

    std::for_each(counts.begin(), counts.end(),
                  [](std::pair<node_t *, int> d) { CHECK(d.second > 10); });
  }

  TEST_FIXTURE(Setup, TestSamplingToFunctionSelector) {
    MaxValueSelector<RockPaperScissors, RPSConfig> *s =
        new MaxValueSelector<RockPaperScissors, RPSConfig>();
    SamplingToFunctionSelector<RockPaperScissors, RPSConfig> selector(200, s);
    std::map<node_t *, int> counts;
    node_t *n;
    for (int i = 0; i < 200; ++i) {
      n = selector.select(root);
      ++counts[n];
      n->backpropagate(i);
    }

    CHECK_EQUAL(9, counts.size());

    // maxvalueselector should be active now
    for (int i = 0; i < 1000; ++i) {
      n = selector.select(root);
      ++counts[n];
      n->backpropagate(i);
    }

    CHECK_EQUAL(root->children()[0], selector.select(root));
    CHECK(root->children()[0]->nb_samples() > 800);

    delete s;
  }

  TEST_FIXTURE(Setup, TestMinSampleSelector) {
    MinSampleSelector<RockPaperScissors, RPSConfig> selector;
    std::map<node_t *, int> counts;
    node_t *n;
    for (int i = 0; i < 9; ++i) {
      n = selector.select(root);
      ++counts[n];
      n->backpropagate(i);
    }

    CHECK_EQUAL(9, counts.size());

    std::for_each(counts.begin(), counts.end(),
                  [](std::pair<node_t *, int> d) { CHECK_EQUAL(1, d.second); });
  }

  TEST_FIXTURE(Setup, TestUCTSelector) {
    // big factor
    UCTSelector<RockPaperScissors, RPSConfig> selector(10000);
    vector<node_t *> children = root->children();
    for (int i = 0; i < 9; ++i) {
      children[i]->backpropagate(i);
    }

    std::map<node_t *, int> counts;
    node_t *n;
    for (int i = 0; i < 1000; ++i) {
      n = selector.select(root);
      ++counts[n];
      n->backpropagate(0);
    }

    //*
    // because of the big factor in UCT constructor, nodes will be selected
    // broader.

    std::for_each(counts.begin(), counts.end(),
                  [](std::pair<node_t *, int> d) { CHECK(d.second > 100); });

    selector = UCTSelector<RockPaperScissors, RPSConfig>(0);
    for (int i = 0; i < 1000; ++i) {
      n = selector.select(root);
      ++counts[n];
      n->backpropagate(0);
    }

    std::for_each(counts.begin(), counts.end(),
                  [](std::pair<node_t *, int> d) { CHECK(d.second > 100); });

    //*
    // because of the small factor in UCT constructor,
    // after value rather than samples. only the node with highest value is
    // choosen.

    CHECK_EQUAL(children[8], selector.select(root));
  }
}

