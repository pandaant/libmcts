#include <map>
#include <iostream>
#include <UnitTest++.h>
#include <max_value_selector.hpp>
#include <sampling_selector.hpp>
#include <sampling_to_function_selector.hpp>
#include <min_sample_selector.hpp>
#include <max_std_dev_selector.hpp>
#include <uct_selector.hpp>
#include <root_node.hpp>
#include "rock_paper_scissors.hpp"
#include "rps_node.hpp"
#include "rps_config.hpp"

SUITE(SelectionTests) {
  using namespace MC;

  struct Setup {
    RPSConfig *conf;
    BackpropagationStrategy *bp_strat;
    SelectionStrategy *select_strat;
    SelectionStrategy *move_select_strat;
    Context *rps;
    RootNode<RPSNode> *root;

    Setup() {
      bp_strat = new SampleWeightedBackpropagationStrategy();
      select_strat = new MaxValueSelector();
      move_select_strat = new MaxValueSelector();
      conf = new RPSConfig(bp_strat, select_strat, move_select_strat, false);

      rps = new RockPaperScissors(Player("mark"), Player("simon"),
                                  ActionType::PAPER, ActionType::ROCK, 1);
      root = new RootNode<RPSNode>(rps->clone(), conf);
      root->expand();
    }

    ~Setup() {
      delete move_select_strat;
      delete rps;
      delete root;
      delete conf;
      delete bp_strat;
      delete select_strat;
    }
  };

  TEST_FIXTURE(Setup, TestMaxValueSelector) {
    MaxValueSelector selector = MaxValueSelector();

    CHECK_EQUAL(9, root->get_children().size());

    // backpropagate some values
    root->get_children()[0]->backpropagate(7);
    root->get_children()[1]->backpropagate(3);
    root->get_children()[2]->backpropagate(2);

    CHECK_EQUAL(root->get_children()[0], selector.select(root));

    root->get_children()[3]->backpropagate(12);
    root->get_children()[4]->backpropagate(17);
    root->get_children()[5]->backpropagate(18);

    CHECK_EQUAL(root->get_children()[5], selector.select(root));

    root->get_children()[4]->backpropagate(9);
    root->get_children()[4]->backpropagate(30);

    CHECK_EQUAL(root->get_children()[4], selector.select(root));

    root->get_children()[7]->backpropagate(60);
    root->get_children()[8]->backpropagate(60);

    // first max element
    CHECK_EQUAL(root->get_children()[7], selector.select(root));
  }

  TEST_FIXTURE(Setup, TestSamplingSelector) {
    SamplingSelector selector = SamplingSelector();
    std::map<INode *, int> counts;
    for (int i = 0; i < 200; ++i) {
      ++counts[selector.select(root)];
    }

    CHECK_EQUAL(9, counts.size());

    std::for_each(counts.begin(), counts.end(),
                  [](std::pair<INode *, int> d) { CHECK(d.second > 10); });
  }

  TEST_FIXTURE(Setup, TestSamplingToFunctionSelector) {
    MaxValueSelector *s = new MaxValueSelector();
    SamplingToFunctionSelector selector = SamplingToFunctionSelector(200, s);
    std::map<INode *, int> counts;
    INode *n;
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

    CHECK_EQUAL(root->get_children()[0], selector.select(root));
    CHECK(root->get_children()[0]->get_nb_samples() > 800);

    delete s;
  }

  TEST_FIXTURE(Setup, TestMinSampleSelector) {
    MinSampleSelector selector = MinSampleSelector();
    std::map<INode *, int> counts;
    INode *n;
    for (int i = 0; i < 9; ++i) {
      n = selector.select(root);
      ++counts[n];
      n->backpropagate(i);
    }

    CHECK_EQUAL(9, counts.size());

    std::for_each(counts.begin(), counts.end(),
                  [](std::pair<INode *, int> d) { CHECK_EQUAL(1, d.second); });
  }

  TEST_FIXTURE(Setup, TestUCTSelector) {
    // big factor
    UCTSelector selector = UCTSelector(10000);
    vector<INode *> children = root->get_children();
    for (int i = 0; i < 9; ++i) {
      children[i]->backpropagate(i);
    }

    std::map<INode *, int> counts;
    INode *n;
    for (int i = 0; i < 1000; ++i) {
      n = selector.select(root);
      ++counts[n];
      n->backpropagate(0);
    }

    /**
     * because of the big factor in UCT constructor, nodes will be selected
     * boarder.
    **/
    std::for_each(counts.begin(), counts.end(),
                  [](std::pair<INode *, int> d) { CHECK(d.second > 100); });

    selector = UCTSelector(0);
    for (int i = 0; i < 1000; ++i) {
      n = selector.select(root);
      ++counts[n];
      n->backpropagate(0);
    }

    std::for_each(counts.begin(), counts.end(),
                  [](std::pair<INode *, int> d) { CHECK(d.second > 100); });

    /**
     * because of the small factor in UCT constructor,
     * after value rather than samples. only the node with highest value is
    *choosen.
    **/
    CHECK_EQUAL(children[8], selector.select(root));
  }

  TEST_FIXTURE(Setup, TestMaxStdDevSelectoTestMaxStdDevSelector) {
    MaxStdDeviationSelector selector = MaxStdDeviationSelector();

    CHECK_EQUAL(9, root->get_children().size());

    // backpropagate some values
    root->get_children()[0]->backpropagate(7);
    root->get_children()[0]->backpropagate(17);
    root->get_children()[0]->backpropagate(33);
    root->get_children()[1]->backpropagate(3);
    root->get_children()[1]->backpropagate(3);
    root->get_children()[1]->backpropagate(3);
    root->get_children()[1]->backpropagate(3);
    root->get_children()[2]->backpropagate(2);

    CHECK_EQUAL(root->get_children()[0], selector.select(root));

    root->get_children()[3]->backpropagate(12);
    root->get_children()[3]->backpropagate(13);
    root->get_children()[4]->backpropagate(17);
    root->get_children()[4]->backpropagate(177);
    root->get_children()[5]->backpropagate(18);
    root->get_children()[5]->backpropagate(18);

     CHECK_EQUAL(root->get_children()[4], selector.select(root));

    root->get_children()[5]->backpropagate(-10);
    root->get_children()[5]->backpropagate(300);
    root->get_children()[4]->backpropagate(177);

    CHECK_EQUAL(root->get_children()[5], selector.select(root));

    root->get_children()[7]->backpropagate(999);
    root->get_children()[7]->backpropagate(0);
    root->get_children()[7]->backpropagate(10);

    CHECK_EQUAL(root->get_children()[7], selector.select(root));
  }
}

