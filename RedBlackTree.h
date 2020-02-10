//
// Created by ftfunjth on 2020/2/10.
//

#ifndef AVLTTREE_REDBLACKTREE_H
#define AVLTTREE_REDBLACKTREE_H

#include <initializer_list>

enum class NodeColor {
    RED,
    BLACK,
};

struct RedBlackNode {
    int key;
    NodeColor color;
    RedBlackNode *parent;
    RedBlackNode *left;
    RedBlackNode *right;

    explicit RedBlackNode(int val) : key{val},
                                     parent{nullptr},
                                     left{nullptr},
                                     right{nullptr},
                                     color{NodeColor::BLACK} {}

    explicit RedBlackNode(int val, RedBlackNode *parent_node, NodeColor node_color) : key{val},
                                                                                      parent{parent_node},
                                                                                      left{nullptr},
                                                                                      right{nullptr},
                                                                                      color{node_color} {}
};

class RedBlackTree {
public:
    RedBlackTree(std::initializer_list<int> elements);

    ~RedBlackTree();
    void insert(int element);

private:
    void fixInsert(RedBlackNode *node);

    void rotateLeft(RedBlackNode *node);

    void rotateRight(RedBlackNode *node);

    static void releaseTravel(RedBlackNode * node);
    RedBlackNode *root;

};


#endif //AVLTTREE_REDBLACKTREE_H
