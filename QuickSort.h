//
// Created by ftfunjth on 2020/2/13.
//

#ifndef DATA_STRUCT_QUICKSORT_H
#define DATA_STRUCT_QUICKSORT_H

#include <initializer_list>
#include <vector>

class QuickSort {
public:
    QuickSort(std::initializer_list<int> elements);

    std::vector<int> &sort();

private:
    void sortRange(int start, int end, int slot);

    std::vector<int> arr;
};


#endif //DATA_STRUCT_QUICKSORT_H
