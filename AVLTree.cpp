//
// Created by ftfunjth on 2020/2/8.
//

#include <algorithm>
#include "AVLTree.h"

AVLTree::AVLTree(std::initializer_list<int> elements) : root{nullptr} {
    for (auto &element : elements) {
        insert(element);
    }
}

AVLTree::~AVLTree() {

}

void AVLTree::rotate_right(AVLNode *node) {
    if (node == nullptr) {
        return;
    }
    AVLNode *y = node->left;
    AVLNode *parent = node->parent;
    node->left = y->right;
    y->right = node;
    y->parent = node->parent;
    if (parent == nullptr) {
        root = y;
    } else if (parent->left == node) {
        parent->left = y;
    } else {
        parent->right = y;
    }
    node->parent = y;
    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    y->height = 1 + std::max(get_height(y->left), get_height(y->right));
}

void AVLTree::rotate_left(AVLNode *node) {
    if (node == nullptr) {
        return;
    }
    AVLNode *y = node->right;
    AVLNode *parent = node->parent;
    node->right = y->left;
    y->left = node;
    y->parent = node->parent;
    if (parent == nullptr) {
        root = y;
    } else if (parent->left == node) {
        parent->left = y;
    } else {
        parent->right = y;
    }
    node->parent = y;
    node->height = 1 + std::max(get_height(node->left), get_height(node->right));
    y->height = 1 + std::max(get_height(y->left), get_height(y->right));
}

void AVLTree::insert(int element) {
    if (root == nullptr) {
        root = new AVLNode(element);
        return;
    }
    AVLNode *t = root;
    while (t != nullptr) {
        if (element > t->key) {
            if (t->right == nullptr) {
                t->right = new AVLNode(element, t);
                update_height(t->right);
                fixup(root);
                return;
            }
            t = t->right;
        } else {
            if (t->left == nullptr) {
                t->left = new AVLNode(element, t);
                update_height(t->left);
                fixup(root);
                return;
            }
            t = t->left;
        }
    }
}

int AVLTree::factor(AVLNode *node) {
    return get_height(node->left) - get_height(node->right);
}

void AVLTree::update_height(AVLNode *node) {
    AVLNode *p = node->parent;
    while (p != nullptr) {
        p->height = 1 + std::max(get_height(p->left), get_height(p->right));
        p = p->parent;
    }
}

int AVLTree::get_height(AVLNode *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

void AVLTree::fixup(AVLNode *node) {
    if (factor(node) > 1 && factor(node->left) >= 0) {
        rotate_right(node);
        return;
    }
    if (factor(node) < -1 && factor(node->right) <= 0) {
        rotate_left(node);
        return;
    }
    if (factor(node) > 1 && factor(node->left) < 0) {
        rotate_left(node->left);
        rotate_right(node);
        return;
    }
    if (factor(node) < -1 && factor(node->right) > 0) {
        rotate_right(node->right);
        rotate_left(node);
        return;
    }
}
