//
// Created by ftfunjth on 2020/2/13.
//

#include "QuickSort.h"

QuickSort::QuickSort(std::initializer_list<int> elements) : arr{elements} {
}

std::vector<int> &QuickSort::sort() {
    sortRange(0, arr.size() - 1, arr[0]);
    return arr;
}

void QuickSort::sortRange(int start, int end, int slot) {
    auto i = start;
    auto j = end;
    if (i >= j) {
        return;
    }
    while (i < j) {
        // 寻找一个比i小的数
        while (i < j && arr[j] >= slot) {
            j--;
        }
        if (i < j) {
            arr[i] = arr[j];
            i++;
        }
        while (i < j && arr[i] < slot) {
            i++;
        }
        if (i < j) {
            arr[j] = arr[i];
            j--;
        }
    }
    arr[i] = slot;
    sortRange(start, j - 1, arr[start]);
    sortRange(i + 1, end, arr[i + 1]);
}
