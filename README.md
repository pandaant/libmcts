# Libmcts
Monte Carlo Simulation library

## Requirements
* UnitTest++ for tests (expects headers and lib to be in /usr/{lib,include})

## Build
```bash
$ git clone --recursive https://github.com/pandaant/libemcts

# compile lib
$ cd libmcts
$ make all

# build documentation (requires doxygen)
$ make doc

# if you want to run tests
$ cd test 
$ make all run
```

## Usage

The usage will be demonstrated using an example implementation for the game of Rock, Paper, Scissors (found in the test folder).

```c++
using namespace mcts;

// define the nodetype
typedef typename INode<RockPaperScissors, RPSConfig>::node_t node_t;

// define the selection strategy
typedef typename ISelectionStrategy<RockPaperScissors, RPSConfig>::sstrategy_t sstrategy_t;

// define the mcts with the types for your implementation
typedef typename MCTS<RockPaperScissors, RPSConfig, RPSNode<RockPaperScissors,RPSConfig>, RPSResult<RockPaperScissors,RPSConfig>> mcts_t;

// create needed variables
RockPaperScissors context;
RPSConfig *conf;
Player p1, p2;
ActionType::Enum p1a, p2a;
mcts_t *mcts;
IBackpropagationStrategy *bp_strat;
sstrategy_t *select_strat;
sstrategy_t *move_select_strat;

// creates an initial game state to start simulations from
int game = 1;
p1 = Player("mark");
++p1.won;
p2 = Player("simon");
++p2.lost;
p1a = ActionType::PAPER;
p2a = ActionType::ROCK;
context = RockPaperScissors(p1, p2, p1a, p2a, game);

// initialize strategies
bp_strat = new AvgBackpropagationStrategy();
select_strat = new MaxValueSelector<RockPaperScissors,RPSConfig>();
move_select_strat = new MaxValueSelector<RockPaperScissors,RPSConfig>();

conf = new RPSConfig(bp_strat, select_strat, move_select_strat, false);
mcts = new mcts_t(context, conf);

// iterate 1000 times
for (int i = 0; i < 1000; ++i)
	mcts->iterate();

// get the result of the simulations
RPSResult<RockPaperScissors, RPSConfig> result = mcts->result();

// free variables
delete mcts;
delete conf;
delete move_select_strat;
delete bp_strat;
delete select_strat;
```







The used Context object has to implement the following functions to interact properly with the library.
     class Context{
         vector<Context> transition();    
     }

The used Config object has to implement the following functions to interact properly with the library.
     class Config{
        generator\_t *nb_gen();
     }