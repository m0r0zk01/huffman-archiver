#include "trie.h"

Trie::~Trie() {
    DeleteNode(root_);
}

Trie::Node* Trie::InsertNode(size_t value, bool is_leaf, Node* _0, Node* _1) {
    return new Node{.value=value, .is_leaf=is_leaf, ._0=_0, ._1=_1};
}

void Trie::SetRoot(Node* root) {
    root_ = root;
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
    if (!node->is_leaf) {
        DeleteNode(node->_0);
        DeleteNode(node->_1);
    }
    delete node;
}
