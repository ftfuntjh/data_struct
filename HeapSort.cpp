//
// Created by ftfunjth on 2020/2/13.
//

#include "HeapSort.h"

HeapSort::HeapSort(std::initializer_list<int> elements) : arr{elements}, heap_size{elements.size()} {

}

std::vector<int> &HeapSort::sort() {
    for (int i = arr.size() / 2; i >= 0; i--) {
        maxHeapify(i);
    }
    for (int i = arr.size() - 1; i >= 1; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heap_size--;
        maxHeapify(0);
    }
    return arr;
}

int HeapSort::leftChildren(int index) {
    return index * 2 + 1;
}

int HeapSort::rightChildren(int index) {
    return index * 2 + 2;
}

int HeapSort::parent(int index) {
    return (index - 1) / 2;
}

void HeapSort::maxHeapify(int index) {
    if (index > heap_size) {
        return;
    }
    int left_index = leftChildren(index);
    int right_index = rightChildren(index);
    int largest = index;
    if (left_index < heap_size) {
        if (arr[left_index] > arr[largest]) {
            largest = left_index;
        }
    }
    if (right_index < heap_size) {
        if (arr[right_index] > arr[largest]) {
            largest = right_index;
        }
    }
    if (largest != index) {
        int tmp = arr[largest];
        arr[largest] = arr[index];
        arr[index] = tmp;
        maxHeapify(largest);
    }
}
