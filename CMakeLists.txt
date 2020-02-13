cmake_minimum_required(VERSION 3.15)
project(data_struct)

set(CMAKE_CXX_STANDARD 14)

add_executable(data_struct main.cpp AVLTree.cpp AVLTree.h RedBlackTree.cpp RedBlackTree.h QuickSort.cpp QuickSort.h HeapSort.cpp HeapSort.h)