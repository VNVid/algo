#include "sort.h"

#include <cstdio>

////////// Bubble sort //////////
void templates::simpleSort(void **ppArray, int length, CompareSortType pCompareFunc)
{
    for (size_t i = length - 1; i > 0; i--)
    {
        for (size_t j = 0; j < i; j++)
        {
            if (pCompareFunc(ppArray[j], ppArray[j + 1]) < 0)
            {
                void *ptr = ppArray[j];
                ppArray[j] = ppArray[j + 1];
                ppArray[j + 1] = ptr;
                ptr = nullptr;
            }
        }
    }
}

////////// Merge sort //////////
void templates::merge(void **ppArray, void **ppSorted, int left, int mid, int right, CompareSortType pCompareFunc)
{
    if (mid - left > 1) // sort left part
    {
        merge(ppArray, ppSorted, left, (left + mid) / 2, mid, pCompareFunc);
    }
    if (right - mid > 1) // sort right part
    {
        merge(ppArray, ppSorted, mid, (mid + right) / 2, right, pCompareFunc);
    }

    int left_ind = left;
    int right_ind = mid;
    int sorted_ind = 0;
    while (left_ind < mid && right_ind < right)
    {
        if (pCompareFunc(ppArray[left_ind], ppArray[right_ind]) > 0)
        {
            ppSorted[sorted_ind++] = ppArray[left_ind++];
        }
        else
        {
            ppSorted[sorted_ind++] = ppArray[right_ind++];
        }
    }
    while (left_ind < mid)
    {
        ppSorted[sorted_ind++] = ppArray[left_ind++];
    }
    while (right_ind < right)
    {
        ppSorted[sorted_ind++] = ppArray[right_ind++];
    }

    for (int i = 0; i < sorted_ind; i++)
    {
        ppArray[left + i] = ppSorted[i];
    }
}
void templates::mergeSort(void **ppArray, int length, CompareSortType pCompareFunc)
{
    void **ppSorted = new void *[length];

    merge(ppArray, ppSorted, 0, length / 2, length, pCompareFunc);

    delete[] ppSorted;
    ppSorted = nullptr;
}