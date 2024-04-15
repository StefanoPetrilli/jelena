#include "node.h"

namespace kd_tree {

template <typename T>
struct Node {
  std::vector<T> kValue;
  std::shared_ptr<Node<T>> kRightChild;
  std::shared_ptr<Node<T>> kLeftChild;

  Node(std::vector<T> value) : kValue(value) {}

  std::string ToString() const {
    std::ostringstream oss;
    std::string result;

    if (kRightChild) {
      result += kRightChild->ToString();
    }

    oss << '(';
    for (const auto& value : kValue) {
      oss << value << ' ';
    }
    result += oss.str();
    result.back() = ')';

    if (kLeftChild) {
      result += kLeftChild->ToString();
    }

    return result;
  }

  T at(int index) { return kValue.at(index); }
};

template <typename T>
class KdTree {
 private:
  std::shared_ptr<Node<T>> root_;

  void Insert(std::vector<T> element, std::shared_ptr<Node<T>>& node,
              uint16_t depth) {
    if (!node) {
      node = std::make_shared<Node<T>>(Node(element));
      return;
    }

    depth = depth % element.size();
    if (element.at(depth) > node->at(depth)) {
      Insert(element, node->kRightChild, depth + 1);
    } else {
      Insert(element, node->kLeftChild, depth + 1);
    }
  }

 public:
  KdTree(){};

  void Insert(std::vector<T> element) { Insert(element, root_, 0); }

  std::string ToString() { return root_ ? root_->ToString() : std::string(); }
};
}  // namespace kd_tree