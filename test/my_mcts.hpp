/* 
 * File:   my_mcts.h
 * Author: batman
 *
 * Created on August 4, 2013, 12:59 PM
 */

#ifndef MY_MCTS_H
#define	MY_MCTS_H

#include <mcts.h>
#include "result.h"

using namespace MCTS;

class RPSMCTS : public MCTS{
    RPSResult evaluate(){
        for( int i = 0; i < 100; ++i)
            iterate();  
    }
};

#endif	/* MY_MCTS_H */

