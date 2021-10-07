#include "trie.h"

Trie::Node::Node(size_t value, bool is_leaf, NodePtr _0, NodePtr _1) :
      value(value),
      is_leaf(is_leaf),
      _0(_0),
      _1(_1) {}

Trie::NodePtr Trie::CreateNode(size_t value, bool is_leaf, NodePtr _0, NodePtr _1) {
    return std::make_shared<Trie::Node>(value, is_leaf, _0, _1);
}

void Trie::AddCode(size_t value, std::vector<bool> code, size_t code_len, NodePtr node) {
    if (!code_len) {
        node->is_leaf = true;
        node->value = value;
        return;
    }
    if (!node) {
        node = root_;
    }
    bool cur_bit = code.front();
    NodePtr& son = cur_bit ? node->_1 : node->_0;
    if (!son) {
        son = std::make_shared<Node>();
    }
    code.erase(code.begin());
    AddCode(value, code, code_len - 1, son);
}

void Trie::SetRoot(NodePtr root) {
    root_ = root;
}

Trie::NodePtr Trie::GetRoot() {
    return root_;
}

void Trie::RetrieveCodeSizeDFS(std::vector<std::pair<size_t, size_t>>& result, NodePtr cur_node, size_t cur_code_len) {
    if (cur_node->is_leaf) {
        result.push_back({cur_code_len, cur_node->value});
        return;
    }
    RetrieveCodeSizeDFS(result, cur_node->_0, cur_code_len + 1);
    RetrieveCodeSizeDFS(result, cur_node->_1, cur_code_len + 1);
}

std::vector<std::pair<size_t, size_t>> Trie::RetrieveCodeSizes() {
    std::vector<std::pair<size_t, size_t>> result;
    RetrieveCodeSizeDFS(result, root_, 0);
    return result;
}
