/*
 * File:   config.hpp
 * Author: batman
 *
 * Created on July 31, 2013, 9:11 PM
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <ctime>
// TODO replace with random
#include <tr1/random>
#include "backpropagation_strategy.hpp"
#include "selection_strategy.hpp"

namespace MC {
    class SelectionStrategy;

    /**
     * Stores all datastructs that are needed in every
     * part of the simulation. data should be fix and should
     * not change over the course of the simulation.
     **/
    class Config {
        typedef std::tr1::mt19937 GeneratorType;

    public:
        GeneratorType *nb_gen = NULL;

        /**
         * The moveselection strat is used to select
         * an resultnode at the end of the simulation.
         **/
        SelectionStrategy *move_selection_strat;

        // TODO change to random device as seed
        Config(bool seed = true) : nb_gen(new GeneratorType(seed ? ((unsigned) std::time(0)) : 0)) {
        }

        /**
         * Constructor
         * @param _move_selection_strat  - strategy that is used to get the next move
         *                                 at the end of the mcts evaluation.
         * @param seed      nb_gen gets seeded or init with 0
         */
        Config(SelectionStrategy *_move_selection_strat, bool seed = true)
        : move_selection_strat(_move_selection_strat) {
            nb_gen = new GeneratorType(seed ? ((unsigned) std::time(0)) : 0);
        }

        virtual ~Config() {
            delete nb_gen;
        }

        GeneratorType *get_nb_gen() {
            return nb_gen;
        }
    };
}

#endif /* CONFIG_H */

