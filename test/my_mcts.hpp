#ifndef MY_MCTS_H
#define	MY_MCTS_H

#include <mcts.h>
#include "result.h"

class RPSMCTS : public MCTS<RockPaperScissors, RPSConfig, RPSNode, RPSResult>{
    RPSResult evaluate(){
        for( int i = 0; i < 100; ++i)
            iterate();  
    }
};

#endif
