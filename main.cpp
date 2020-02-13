#include "AVLTree.h"
#include "RedBlackTree.h"
#include "QuickSort.h"

int main(int argc, char *argv[]) {
    AVLTree avl_tree{1, 2, 3, 4, 5, -1, -2};
    RedBlackTree rb_tree{20, 19, 25, 23, 28};
    rb_tree.remove(19);
    QuickSort qs{8, 2, 10, 7, 9};
    auto &p = qs.sort();
    return 0;
}

