#include "inode.hpp"

namespace MC {

int INode::count_recusive() {
  int sum = 0;
  vector<INode *> children = this->get_children();
  std::for_each(children.begin(), children.end(), [&sum](INode * child) {
    sum += child->count_recusive();
  });
  return 1 + sum;
}
}
