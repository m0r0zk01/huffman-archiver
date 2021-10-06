#include "trie.h"

Trie::~Trie() {
    DeleteNode(root_);
}

Trie::Node::Node(size_t value, bool is_leaf, std::unique_ptr<Node> _0, std::unique_ptr<Node> _1) :
      value(value),
      is_leaf(is_leaf),
      _0(std::move(_0)),
      _1(std::move(_1)) {}

std::unique_ptr<Trie::Node> Trie::InsertNode(size_t value, bool is_leaf,
                                             std::unique_ptr<Trie::Node> _0,
                                             std::unique_ptr<Trie::Node> _1) {
    return std::make_unique<Trie::Node>(value, is_leaf, std::move(_0), std::move(_1));
}

void Trie::AddCode(size_t value, size_t code, size_t code_len, Node* node) {
    if (!code_len) {
        node->is_leaf = true;
        node->value = value;
        return;
    }
    if (!node) {
        node = root_;
    }
    bool cur_bit = (code >> (code_len - 1)) % 2;
    Node*& son = cur_bit ? node->_1 : node->_0;
    if (!son) {
        son = new Node;
    }
    AddCode(value, code & ((1 << code_len) - 1), code_len - 1, son);
}

void Trie::SetRoot(Node* root) {
    root_ = root;
}

Trie::Node* Trie::GetRoot() {
    return root_;
}

void Trie::RetrieveCodeSizeDFS(std::vector<std::pair<size_t, size_t>>& result, Node* cur_node, size_t cur_code_len) {
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

void Trie::DeleteNode(Trie::Node* node) {
    if (!node) {
        return;
    }
    DeleteNode(node->_0);
    DeleteNode(node->_1);
    delete node;
}
