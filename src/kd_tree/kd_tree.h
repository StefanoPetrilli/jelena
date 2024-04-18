#include "node.h"

namespace kd_tree {

template <typename T>
struct Node {
  std::vector<T> kValue;
  std::shared_ptr<Node<T>> kRightChild;
  std::shared_ptr<Node<T>> kLeftChild;

  Node(std::vector<T> value) : kValue(value) {}

  std::string ToString() const {
    std::string result;

    if (kRightChild) {
      result += kRightChild->ToString();
    }

    std::ostringstream oss;
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

  T At(int index) { return kValue.at(index); }

  bool IsPartOfResult(const std::vector<T>& query,
                      const std::vector<bool>& mask) {
    for (size_t i = 0; i < mask.size(); i++) {
      if (!mask.at(i))
        continue;
      if (kValue.at(i) != query.at(i))
        return false;
    }
    return true;
  }
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
    if (element.at(depth) > node->At(depth)) {
      Insert(element, node->kRightChild, depth + 1);
    } else {
      Insert(element, node->kLeftChild, depth + 1);
    }
  }

  bool IsNotPartOfMask(const std::vector<bool>& mask, uint16_t depth) {
    return !mask.at(depth);
  }

  std::set<std::vector<T>> ExploreAllChild(const std::vector<T>& query,
                                           const std::vector<bool>& mask,
                                           std::shared_ptr<Node<T>>& node,
                                           uint16_t depth,
                                           std::set<std::vector<T>>& result) {
    PartialMatch(query, mask, node->kRightChild, depth + 1, result);
    PartialMatch(query, mask, node->kLeftChild, depth + 1, result);
    return result;
  }

  std::set<std::vector<T>> PartialMatch(const std::vector<T>& query,
                                        const std::vector<bool>& mask,
                                        std::shared_ptr<Node<T>>& node,
                                        uint16_t depth,
                                        std::set<std::vector<T>>& result) {
    if (node.get() == nullptr)
      return result;

    depth %= query.size();

    if (node->IsPartOfResult(query, mask))
      result.insert(node->kValue);

    if (IsNotPartOfMask(mask, depth))
      return ExploreAllChild(query, mask, node, depth, result);

    auto node_to_explore = query.at(depth) > node->At(depth) ? node->kRightChild
                                                             : node->kLeftChild;

    return PartialMatch(query, mask, node_to_explore, depth + 1, result);
  }

 public:
  KdTree(){};

  void Insert(std::vector<T> element) { Insert(element, root_, 0); }

  std::string ToString() { return root_ ? root_->ToString() : std::string(); }

  std::set<std::vector<T>> PartialMatch(const std::vector<T>& query,
                                        const std::vector<bool>& mask) {
    std::set<std::vector<T>> result;
    // TODO(StefanoPetrilli): Preprocess mask here.
    // If the mask is sparse it's useless to move around the whole mask
    PartialMatch(query, mask, root_, 0, result);
    return result;
  }
};
}  // namespace kd_tree