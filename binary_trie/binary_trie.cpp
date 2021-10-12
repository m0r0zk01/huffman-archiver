#include "binary_trie.h"

BinaryTrie::Node::Node(uint16_t value, bool is_leaf, NodePtr _0, NodePtr _1) :
      value(value),
      is_leaf(is_leaf),
      _0(_0),
      _1(_1) {}

BinaryTrie::NodePtr BinaryTrie::CreateNode(uint16_t value, bool is_leaf, NodePtr _0, NodePtr _1) {
    return std::make_shared<BinaryTrie::Node>(value, is_leaf, _0, _1);
}

void BinaryTrie::AddCode(uint16_t value, std::vector<bool> code, uint16_t code_len, NodePtr node) {
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

void BinaryTrie::SetRoot(NodePtr root) {
    root_ = root;
}

BinaryTrie::NodePtr BinaryTrie::GetRoot() {
    return root_;
}

void BinaryTrie::RetrieveCodeSizeDFS(std::vector<std::pair<uint16_t, uint16_t>>& result, NodePtr cur_node, uint16_t cur_code_len) {
    if (cur_node->is_leaf) {
        result.push_back({cur_code_len, cur_node->value});
        return;
    }
    RetrieveCodeSizeDFS(result, cur_node->_0, cur_code_len + 1);
    RetrieveCodeSizeDFS(result, cur_node->_1, cur_code_len + 1);
}

std::vector<std::pair<uint16_t, uint16_t>> BinaryTrie::RetrieveCodeSizes() {
    std::vector<std::pair<uint16_t, uint16_t>> result;
    RetrieveCodeSizeDFS(result, root_, 0);
    return result;
}
