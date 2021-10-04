#include <vector>
#include <memory>

class Trie {
public:
    struct Node {
        size_t value;
        bool is_leaf;
        Node* _0, *_1;
    };

    ~Trie();

    Node* InsertNode(size_t value, bool is_leaf, Node* _0=0, Node* _1=0);

    void SetRoot(Node* root);

    std::vector<std::pair<size_t, size_t>> RetrieveCodeSizes();

private:
    void DeleteNode(Node* node);
    void RetrieveCodeSizeDFS(std::vector<std::pair<size_t, size_t>>& result, Node* cur_node, size_t cur_code_len);

    Node* root_;
};