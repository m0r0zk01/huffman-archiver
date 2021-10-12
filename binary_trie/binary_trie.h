#pragma once

#include <vector>
#include <memory>

class BinaryTrie {
public:
    struct Node;
    using NodePtr = std::shared_ptr<Node>;
    struct Node {
        size_t value = 0;
        bool is_leaf = false;
        NodePtr _0 = nullptr, _1 = nullptr;

        Node() = default;
        Node(size_t value, bool is_leaf, NodePtr _0, NodePtr _1);
    };

    NodePtr GetRoot();
    NodePtr CreateNode(size_t value, bool is_leaf, NodePtr _0 = nullptr, NodePtr _1 = nullptr);
    void SetRoot(NodePtr root);
    void AddCode(size_t value, std::vector<bool> code, size_t code_len, NodePtr node = nullptr);

    std::vector<std::pair<size_t, size_t>> RetrieveCodeSizes();

private:
    void RetrieveCodeSizeDFS(std::vector<std::pair<size_t, size_t>>& result, NodePtr cur_node, size_t cur_code_len);

    NodePtr root_;
};