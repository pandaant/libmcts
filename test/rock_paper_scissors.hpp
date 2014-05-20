#ifndef Player_H
#define	Player_H

#include <string>
#include <vector>
#include "action_type.hpp"

using std::string;
using std::vector;

struct Player {
  string name;
  int won;
  int tie;
  int lost;

  Player() : won(0), tie(0), lost(0) {}

  Player(string _name) : name(_name), won(0), tie(0), lost(0) {}

  Player(const Player &p)
      : name(p.name), won(p.won), tie(p.tie), lost(p.lost) {}

  Player& operator=(const Player &p)
  {
      name = p.name;
      won = p.won;
      tie = p.tie;
      lost =p.lost;
      return *this;
  }

  int sum() const { return won + tie + lost; }

  double pwin() const { return (double)won / sum(); }

  double ptie() const { return (double)tie / sum(); }

  double plos() const { return (double)lost / sum(); }
};

#endif

#ifndef ROCK_PAPER_SCISSORS_H
#define	ROCK_PAPER_SCISSORS_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class RockPaperScissors {
public:
  int nb_game;
  Player p1, p2;
  ActionType::Enum p1_action, p2_action;

  RockPaperScissors() {}

  RockPaperScissors(const RockPaperScissors &orps)
      : p1(orps.p1), p2(orps.p2), p1_action(orps.p1_action),
        p2_action(orps.p2_action), nb_game(orps.nb_game) {}

  RockPaperScissors &operator=(const RockPaperScissors &orps) {
    p1 = orps.p1;
    p2 = orps.p2;
    p1_action = orps.p1_action;

    p2_action = orps.p2_action;
    nb_game = orps.nb_game;
    return *this;
  }

  RockPaperScissors(Player _p1_bot, Player _p2, ActionType::Enum _p1_action,
                    ActionType::Enum _p2_action, int _nb_game)
      : p1(_p1_bot), p2(_p2), p1_action(_p1_action), p2_action(_p2_action),
        nb_game(_nb_game) {}

  ~RockPaperScissors() {}

  RockPaperScissors *clone() const { return new RockPaperScissors(*this); }

  virtual vector<RockPaperScissors> transition() const {
    using namespace ActionType;
    vector<RockPaperScissors> next(0);
    // all possible combinations of actions from both players
    Player p1n, p2n;
    for (int action1 = 0; action1 < 3; ++action1)
      for (int action2 = 0; action2 < 3; ++action2) {
        p1n = p1;
        p2n = p2;

        if (action1 == action2) {
          ++p1n.tie;
          ++p2n.tie;
        }

        if (action1 == ROCK && action2 == PAPER) {
          ++p1n.lost;
          ++p2n.won;
        }

        if (action1 == ROCK && action2 == SCISSORS) {
          ++p1n.won;
          ++p2n.lost;
        }

        if (action1 == PAPER && action2 == ROCK) {
          ++p1n.won;
          ++p2n.lost;
        }

        if (action1 == PAPER && action2 == SCISSORS) {
          ++p1n.lost;
          ++p2n.won;
        }

        if (action1 == SCISSORS && action2 == ROCK) {
          ++p1n.lost;
          ++p2n.won;
        }

        if (action1 == SCISSORS && action2 == PAPER) {
          ++p1n.won;
          ++p2n.lost;
        }

        next.push_back(RockPaperScissors(p1n, p2n, (ActionType::Enum)action1,
                                         (ActionType::Enum)action2,
                                         nb_game + 1));
      }
    return next;
  }

  virtual bool is_terminal() const {
    return nb_game >= 3; // we play only three games
  }
};

#endif	/* ROCK_PAPER_SCISSORS_H */
