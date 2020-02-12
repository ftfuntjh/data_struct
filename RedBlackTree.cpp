//
// Created by ftfunjth on 2020/2/10.
//

#include "RedBlackTree.h"

void RedBlackTree::insert(int element) {
    if (root == nullptr) {
        root = new RedBlackNode(element);
        root->color = NodeColor::BLACK;
        return;
    }
    RedBlackNode *ptr = root;
    while (ptr != nullptr) {
        if (element < ptr->key) {
            if (ptr->left == nullptr) {
                ptr->left = new RedBlackNode(element, ptr, NodeColor::RED);
                fixInsert(ptr->left);
                return;
            }
            ptr = ptr->left;
        } else {
            if (ptr->right == nullptr) {
                ptr->right = new RedBlackNode(element, ptr, NodeColor::RED);
                fixInsert(ptr->right);
                return;
            }
            ptr = ptr->right;
        }
    }
}

RedBlackTree::RedBlackTree(std::initializer_list<int> elements) : root{nullptr} {
    for (auto &element : elements) {
        insert(element);
    }
}

void RedBlackTree::fixInsert(RedBlackNode *node) {
    RedBlackNode *uncle_node;
    while (node->parent->color == NodeColor::RED) {
        if (node->parent->parent->left == node->parent) {
            uncle_node = node->parent->parent->right;
            NodeColor uncle_color = uncle_node == nullptr ? NodeColor::BLACK : uncle_node->color;
            if (uncle_color == NodeColor::RED) {
                // case 1 如果节点x的叔叔节点y是红色的,将节点x和节点y都置为黑色,将节点x的父节点置为红色
                node->parent->color = NodeColor::BLACK;
                if (uncle_node != nullptr) {
                    uncle_node->color = NodeColor::BLACK;
                }
                node->parent->parent->color = NodeColor::RED;
                node = node->parent->parent;
            } else if (node->parent->right == node) {
                // case 2 如果节点x的叔叔节点y是黑色的，节点x是其父节点p的右子节点,将节点p左旋转
                node = node->parent;
                rotateLeft(node->parent);
            } else {
                // case 2如果节点x的叔叔节点y是黑色的，节点x是其父节点p的左子节点,将节点p的父节点右旋转
                node->parent->color = NodeColor::BLACK;
                node->parent->parent->color = NodeColor::RED;
                rotateRight(node->parent->parent);
            }
        } else {
            uncle_node = node->parent->parent->left;
            NodeColor uncle_color = uncle_node == nullptr ? NodeColor::BLACK : uncle_node->color;
            if (uncle_color == NodeColor::RED) {
                node->parent->color = NodeColor::BLACK;
                if (uncle_node != nullptr) {
                    uncle_node->color = NodeColor::BLACK;
                }
                node->parent->parent->color = NodeColor::RED;
                node = node->parent->parent;
            } else if (node->parent->left == node) {
                node = node->parent;
                rotateRight(node->parent);
            } else {
                node->parent->color = NodeColor::BLACK;
                node->parent->parent->color = NodeColor::RED;
                rotateLeft(node->parent->parent);
            }
        }
        if (node == root) {
            break;
        }
    }
    if (root != nullptr) {
        root->color = NodeColor::BLACK;
    }
}

void RedBlackTree::rotateLeft(RedBlackNode *node) {
    // left rotate 将根节点x的右子节点y作为根节点,并且将节点y的左子节点作为节点x的右子节点。将节点x作为节点y的左子节点。
    if (node == nullptr) {
        return;
    }
    RedBlackNode *right_node = node->right;
    RedBlackNode *parent_node = node->parent;
    node->right = right_node->left;
    right_node->left = node;

    if (right_node->left != nullptr) {
        right_node->left->parent = node;
    }

    if (parent_node != nullptr) {
        if (parent_node->left == node) {
            parent_node->left = right_node;
        } else {
            parent_node->right = right_node;
        }
    } else {
        root = right_node;
    }

    node->parent = right_node;
    right_node->parent = parent_node;
}

void RedBlackTree::rotateRight(RedBlackNode *node) {
    if (node == nullptr) {
        return;
    }

    // right rotate 将根节点x的左子节点y作为根节点，将节点y的右子节点作为节点x的左子节点，将节点x作为节点y的右子节点
    RedBlackNode *left_node = node->left;
    RedBlackNode *parent_node = node->parent;
    node->left = left_node->right;
    left_node->right = node;

    if (left_node->right != nullptr) {
        left_node->right->parent = node;
    }

    if (parent_node != nullptr) {
        if (parent_node->left == node) {
            parent_node->left = left_node;
        } else {
            parent_node->right = left_node;
        }
    } else {
        root = left_node;
    }

    node->parent = left_node;
    left_node->parent = parent_node;
}


RedBlackTree::~RedBlackTree() {
    releaseTravel(root);
}

void RedBlackTree::releaseTravel(RedBlackNode *node) {
    if (node == nullptr) {
        return;
    }
    RedBlackNode *left_children = node->left;
    RedBlackNode *right_children = node->right;
    delete node;
    releaseTravel(left_children);
    releaseTravel(right_children);
}

void RedBlackTree::remove(int element) {
    RedBlackNode *ptr = search(element);
    RedBlackNode *node = ptr;
    if (ptr == nullptr) {
        return;
    }
    if (ptr->left != nullptr && ptr->right != nullptr) {
        node = successor(ptr);
        ptr->key = node->key;
    }
    RedBlackNode *replace_node = node->left != nullptr ? node->left : node->right;
    if (replace_node != nullptr) {
        replace_node->parent = node->parent;
        if (node->parent == nullptr) {
            root = replace_node;
        } else if (node == node->parent->left) {
            node->parent->left = replace_node;
        } else {
            node->parent->right = replace_node;
        }
        if (node->color == NodeColor::BLACK) {
            fixDelete(replace_node);
        }
        delete node;
    } else if (node->parent == nullptr) {
        root = nullptr;
        delete node;
    } else {
        if (node->color == NodeColor::BLACK) {
            fixDelete(node);
        }
        if (node->parent != nullptr) {
            if (node == node->parent->left) {
                node->parent->left = nullptr;
            } else if (node == node->parent->right) {
                node->parent->right = nullptr;
            }
            node->parent = nullptr;
        }
        delete node;
    }
}

RedBlackNode *RedBlackTree::successor(RedBlackNode *node) {
    RedBlackNode *ptr = node;
    if (node == nullptr) {
        return node;
    }
    if (node->left != nullptr) {
        // node的左子树不为空，则node的后继是其左子树中最小的那个
        while (true) {
            if (ptr->left == nullptr) {
                return ptr;
            } else {
                ptr = ptr->left;
            }
        }
    } else if (node->right != nullptr) {
        // node的右子树不空，则node的后继是 第一个其作为左节点的祖先
        while (true) {
            if (ptr->parent == nullptr) {
                return ptr->parent;
            }

            if (ptr == ptr->parent->left) {
                return ptr->parent;
            } else {
                ptr = ptr->parent;
            }
        }
    }
    return node;
}

RedBlackNode *RedBlackTree::search(int val) {
    RedBlackNode *ptr = root;
    while (ptr != nullptr) {
        if (ptr->key < val) {
            ptr = ptr->right;
        } else if (ptr->key > val) {
            ptr = ptr->left;
        } else {
            return ptr;
        }
    }
    return nullptr;
}

void RedBlackTree::fixDelete(RedBlackNode *node) {
    if (node == nullptr) {
        return;
    }
    while (node != nullptr && node != root && node->color == NodeColor::BLACK) {
        RedBlackNode *sibling = getSibling(node);
        if (RedBlackNode::getColor(sibling) == NodeColor::RED) {
            sibling->color = NodeColor::BLACK;
            node->parent->color = NodeColor::RED;
            if (node->parent->left == node) {
                rotateLeft(node->parent);
            } else {
                rotateRight(node->parent);
            }
        } else if (RedBlackNode::getColor(sibling->left) == NodeColor::BLACK &&
                   RedBlackNode::getColor(sibling->right) == NodeColor::BLACK) {
            sibling->color = NodeColor::RED;
            node = node->parent;
        } else if (RedBlackNode::getColor(sibling->right) == NodeColor::BLACK) {
            sibling->color = NodeColor::RED;
            sibling->left->color = NodeColor::BLACK;
            if (node->parent->left == node) {
                rotateRight(sibling);
            } else {
                rotateLeft(sibling);
            }
        } else if (RedBlackNode::getColor(sibling->right) == NodeColor::RED) {
            sibling->right->color = NodeColor::BLACK;
            // sibling->color = NodeColor::RED;
            node->parent->color = NodeColor::BLACK;
            if (node->parent->left == node) {
                rotateLeft(node->parent);
            } else {
                rotateRight(node->parent);
            }
            node = sibling->parent;
        }
    }
    if (node != nullptr) {
        node->color = NodeColor::BLACK;
    }
}

RedBlackNode *RedBlackTree::getSibling(RedBlackNode *node) {
    if (node == nullptr || node->parent == nullptr) {
        return nullptr;
    }
    if (node == node->parent->left) {
        return node->parent->right;
    } else {
        return node->parent->left;
    }
}
