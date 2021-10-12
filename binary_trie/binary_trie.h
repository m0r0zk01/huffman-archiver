#pragma once

#include <vector>
#include <memory>

class BinaryTrie {
public:
    struct Node;
    using NodePtr = std::shared_ptr<Node>;
    struct Node {
        uint16_t value = 0;
        bool is_leaf = false;
        NodePtr _0 = nullptr, _1 = nullptr;

        Node() = default;
        Node(uint16_t value, bool is_leaf, NodePtr _0, NodePtr _1);
    };

    NodePtr GetRoot();
    NodePtr CreateNode(uint16_t value, bool is_leaf, NodePtr _0 = nullptr, NodePtr _1 = nullptr);
    void SetRoot(NodePtr root);
    void AddCode(uint16_t value, std::vector<bool> code, uint16_t code_len, NodePtr node = nullptr);

    std::vector<std::pair<uint16_t, uint16_t>> RetrieveCodeSizes();

private:
    void RetrieveCodeSizeDFS(std::vector<std::pair<uint16_t, uint16_t>>& result, NodePtr cur_node, uint16_t cur_code_len);

    NodePtr root_;
};