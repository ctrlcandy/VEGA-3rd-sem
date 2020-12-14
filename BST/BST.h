#ifndef BST_BST_H
#define BST_BST_H

#include <memory>
#include <iostream>

class BST {
    struct Node {
        std::weak_ptr<Node> parent;

        int value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
    };

    std::shared_ptr<Node> root;


    void insert(std::shared_ptr<Node> &parent_node, std::shared_ptr<Node> &node, int value) {
        if (!node.get()) {
            node = std::make_shared<Node>();
            node->parent = parent_node;
            node->value = value;
            return;
        }
        if (node->value < value) {
            insert(node, node->right, value);
        } else {
            insert(node, node->left, value);
        }
    }

    std::shared_ptr<Node> &find_node_min_value(std::shared_ptr<Node> &node) {
        int value;
        std::shared_ptr<Node> buf_node = node;
        std::shared_ptr<Node> result;

        while (buf_node.get()) {
            if (buf_node->value < value) {
                value = buf_node->value;
                result = buf_node;
            }
            buf_node = buf_node->left;
        }

        return result;
    }

    void remove(std::shared_ptr<Node> &node, int value) {
        if (!node.get()) {
            return;
        }

        if (node->value == value) {
            if (node->right.get() == nullptr || node->left.get() == nullptr) {
                if (node->right.get() != nullptr) {
                    node = node->right;
                } else {
                    node = node->left;
                }
            } else {
                std::shared_ptr<Node> replaced_node = find_node_min_value(node->right);
                node->value = replaced_node->value;
                node->parent = replaced_node->parent;
            }
        } else {
            if (node->value > value) {
                remove(node->left, value);
            } else {
                remove(node->right, value);
            }
        }
    }

public:
    BST() = default;

    void insert(int value) {
        if (!root.get()) {
            root = std::make_shared<Node>();
            root->value = value;
            return;
        }

        insert(root, root, value);
    }

    void remove(int value) {
        remove(root, value);
    }

    bool find(int value) {
        std::shared_ptr<Node> buf_node = root;

        while (buf_node.get()) {
            if (buf_node->value == value) {
                return true;
            } else if (buf_node->value > value) {
                buf_node = buf_node->left;
            } else {
                buf_node = buf_node->right;
            }
        }
        return false;
    }

};

#endif //BST_H
