#include "trie.h"

Trie::Node* Trie::InsertNode(bool is_leaf, Node*& _0, Node*& _1) {
    return new Node{.is_leaf=is_leaf, ._0=_0, ._1=_1};
}

void Trie::SetRoot(Node* root) {
    root_ = root;
}