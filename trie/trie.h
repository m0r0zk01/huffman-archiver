class Trie {
public:
    struct Node {
        bool is_leaf;
        Node* _0, *_1;
    };

    Node* InsertNode(bool is_leaf, Node*& _0=0, Node*& _1=0);

    void SetRoot(Node* root);

private:
    Node* root_;
};