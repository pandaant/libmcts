#include "max_value_selector.hpp"

namespace MC {

double MaxValueSelector::evaluate(INode *node) { return node->get_ev(); }
}
