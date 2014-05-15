/*
 * File:   context.hpp
 * Author: batman
 *
 * Created on July 31, 2013, 11:00 PM
 */

#ifndef CONTEXT_H
#define CONTEXT_H

#include <vector>
#include "visitor.hpp"

namespace MC {

using std::vector;

/**
 * Context is meant to describe the
 * simulation as accurate as possible, and transisition  to the next possible
 * ones in line. central piece of mcts.
 **/
class Context {
public:

  /**
   * calculates all possible contexts, that can be reached from the
   * current context.
   * @return  vector of new contexts
   */
  virtual vector<Context *> transition() = 0;

  virtual Context *clone() const = 0;

  /**
   * checks if the current context is at the last possible state, and
   * can't be transitioned any further.
   * @return
   */
  virtual bool is_terminal() const = 0;

  virtual ~Context() {}
};
}

#endif /* CONTEXT_H */

