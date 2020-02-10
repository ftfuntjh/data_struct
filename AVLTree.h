//
// Created by ftfunjth on 2020/2/8.
//

#ifndef AVLTTREE_AVLTREE_H
#define AVLTTREE_AVLTREE_H

#include <initializer_list>

struct AVLNode {
    int key;
    int height;
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

    explicit AVLNode(int val) : key(val), height(1), left(nullptr), right(nullptr), parent(nullptr) {
    }

    explicit AVLNode(int val, AVLNode *p) : key(val), height(1), left(nullptr), right(nullptr), parent(p) {
    }
};

class AVLTree {
public:
    AVLTree(std::initializer_list<int> elements);

    ~AVLTree();

private:
    void rotate_left(AVLNode *node);

    void rotate_right(AVLNode *node);

    int factor(AVLNode *node);

    void insert(int element);

    void update_height(AVLNode *node);

    void fixup(AVLNode *node);

    int get_height(AVLNode *node);

    AVLNode *root;

};


#endif //AVLTTREE_AVLTREE_H
