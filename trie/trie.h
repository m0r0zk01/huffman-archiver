#include <vector>
#include <memory>

class Trie {
public:
    struct Node {
        size_t value = 0;
        bool is_leaf = false;
        Node* _0 = nullptr, *_1 = nullptr;
    };

    ~Trie();

    Node* InsertNode(size_t value, bool is_leaf, Node* _0= nullptr, Node* _1= nullptr);

    void SetRoot(Node* root);
    void AddCode(size_t value, size_t code, size_t code_len, Node* node=nullptr);

    Node* GetRoot();

    std::vector<std::pair<size_t, size_t>> RetrieveCodeSizes();

private:
    void DeleteNode(Node* node);
    void RetrieveCodeSizeDFS(std::vector<std::pair<size_t, size_t>>& result, Node* cur_node, size_t cur_code_len);

    Node* root_;
};