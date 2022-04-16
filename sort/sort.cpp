#include "sort.h"

#include <cstdio>

void templates::simpleSort(void** ppArray, int length,
                           CompareSortType pCompareFunc) {
  for (size_t i = length - 1; i > 0; i--) {
    for (size_t j = 0; j < i; j++) {
      if (pCompareFunc(ppArray[j], ppArray[j + 1]) < 0) {
        void* ptr = ppArray[j];
        ppArray[j] = ppArray[j + 1];
        ppArray[j + 1] = ptr;
        ptr = nullptr;
      }
    }
  }
}