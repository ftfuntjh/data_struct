//
// Created by ftfunjth on 2020/2/13.
//

#ifndef DATA_STRUCT_HEAPSORT_H
#define DATA_STRUCT_HEAPSORT_H

#include <initializer_list>
#include <vector>

class HeapSort {
public:
    HeapSort(std::initializer_list<int> elements);

    std::vector<int> &sort();

private:
    static int leftChildren(int index);

    static int rightChildren(int index);

    static int parent(int index);

    void maxHeapify(int index);

    std::vector<int> arr;

    size_t heap_size;
};


#endif //DATA_STRUCT_HEAPSORT_H
