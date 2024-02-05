#include "primer/trie.h"
#include <cstddef>
#include <memory>
#include <string_view>
#include "common/exception.h"

namespace bustub {

template <class T>
auto Trie::Get(std::string_view key) const -> const T * {
  auto root = this->GetRoot();
  auto now_node = std::const_pointer_cast<TrieNode>(root);
  for (const auto &c : key) {
    if (now_node->children_.find(c) == now_node->children_.end()) {
      return nullptr;
    }
    now_node = std::const_pointer_cast<TrieNode>(now_node->children_.at(c));
  }
  if (!now_node->is_value_node_) {
    return nullptr;
  }
  auto node = std::dynamic_pointer_cast<const TrieNodeWithValue<T>>(now_node);
  if (node == nullptr) {
    return nullptr;
  }
  return node->value_.get();
  // You should walk through the trie to find the node corresponding to the key. If the node doesn't exist, return
  // nullptr. After you find the node, you should use `dynamic_cast` to cast it to `const TrieNodeWithValue<T> *`. If
  // dynamic_cast returns `nullptr`, it means the type of the value is mismatched, and you should return nullptr.
  // Otherwise, return the value.
}

template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie {
  // Note that `T` might be a non-copyable type. Always use `std::move` when creating `shared_ptr` on that value.
  auto root = this->GetRoot();
  auto new_root = root->Clone();
  auto now_node = std::const_pointer_cast<TrieNode>(root);
  auto now_now_node = std::make_shared<TrieNode>(new_root);
  for (const auto &c : key) {
    if (now_node->children_.find(c) == now_node->children_.end()) {
      now_node->children_.insert({c, std::make_shared<TrieNode>()});
    }
    now_node = std::const_pointer_cast<TrieNode>(now_node->children_.at(c));
  }
  now_node = std::dynamic_pointer_cast<TrieNode>(std::make_shared<TrieNodeWithValue<T>>(new TrieNodeWithValue<T>(std::make_shared<T>(value))));
  now_node->is_value_node_ = true;
  return Trie(root);
  // You should walk through the trie and create new nodes if necessary. If the node corresponding to the key already
  // exists, you should create a new `TrieNodeWithValue`.
}

auto Trie::Remove(std::string_view key) const -> Trie {
  throw NotImplementedException("Trie::Remove is not implemented.");

  // You should walk through the trie and remove nodes if necessary. If the node doesn't contain a value any more,
  // you should convert it to `TrieNode`. If a node doesn't have children any more, you should remove it.
}

// Below are explicit instantiation of template functions.
//
// Generally people would write the implementation of template classes and functions in the header file. However, we
// separate the implementation into a .cpp file to make things clearer. In order to make the compiler know the
// implementation of the template functions, we need to explicitly instantiate them here, so that they can be picked up
// by the linker.

template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint32_t *;

template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint64_t *;

template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const std::string *;

// If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.

using Integer = std::unique_ptr<uint32_t>;

template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const Integer *;

template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;

}  // namespace bustub
