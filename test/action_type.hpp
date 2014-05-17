#ifndef ACTION_TYPE_H
#define	ACTION_TYPE_H

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace ActionType {

enum Enum { ROCK, PAPER, SCISSORS };

static const char *ToStr[] = {"Rock", "Paper", "Scissors"};
}

#endif
