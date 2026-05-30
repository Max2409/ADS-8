// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node *left;
        Node *right;
        explicit Node(const T &k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node *root;

    void destroy(Node *node);
    Node *insert(Node *node, const T &value);
    int  depth(Node *node) const;
    void inorder(Node *node, std::vector<std::pair<T, int>> &res) const;

 public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    BST(const BST &) = delete;
    BST &operator=(const BST &) = delete;

    void insert(const T &value);
    int  search(const T &value) const;   // теперь возвращает счётчик
    int  depth() const;
    void inorder(std::vector<std::pair<T, int>> &result) const;
};

template <typename T>
void BST<T>::destroy(Node *node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

template <typename T>
typename BST<T>::Node *BST<T>::insert(Node *node, const T &value) {
    if (node == nullptr) {
        return new Node(value);
    }
    if (value < node->key) {
        node->left = insert(node->left, value);
    } else if (value > node->key) {
        node->right = insert(node->right, value);
    } else {
        node->count++;
    }
    return node;
}

template <typename T>
void BST<T>::insert(const T &value) {
    root = insert(root, value);
}

template <typename T>
int BST<T>::search(const T &value) const {
    for (Node *cur = root; cur != nullptr; ) {
        if (value < cur->key) {
            cur = cur->left;
        } else if (value > cur->key) {
            cur = cur->right;
        } else {
            return cur->count;      // возвращаем счётчик
        }
    }
    return 0;                      // не найдено
}

template <typename T>
int BST<T>::depth(Node *node) const {
    if (node == nullptr) {
        return -1;                 // база: высота пустого поддерева в рёбрах
    }
    int leftDepth  = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + (rightDepth > leftDepth ? rightDepth : leftDepth);
}

template <typename T>
int BST<T>::depth() const {
    return depth(root);
}

template <typename T>
void BST<T>::inorder(Node *node, std::vector<std::pair<T, int>> &res) const {
    if (node != nullptr) {
        inorder(node->left, res);
        res.push_back({node->key, node->count});
        inorder(node->right, res);
    }
}

template <typename T>
void BST<T>::inorder(std::vector<std::pair<T, int>> &result) const {
    result.clear();
    inorder(root, result);
}
#endif  // INCLUDE_BST_H_
