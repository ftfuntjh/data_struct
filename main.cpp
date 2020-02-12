#include "AVLTree.h"
#include "RedBlackTree.h"

int main(int argc, char *argv[]) {
    AVLTree avl_tree{1, 2, 3, 4, 5, -1, -2};
    RedBlackTree rb_tree{1, 2, 3, 4, 5, 6};
    rb_tree.remove(3);
    rb_tree.remove(5);
    return 0;
}

