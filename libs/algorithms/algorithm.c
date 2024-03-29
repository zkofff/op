#include "algorithm.h"

size_t binsrch(const int *array, const size_t size, const int x) {
    if ( !size )
        return 0u;

    size_t low  = 0u;
    size_t high = size - 1u;
    while (low <= high && low <= size && high <= size) {
        size_t middle = low + (high - low) / 2;
        if (array[ middle ] < x)
            low = middle + 1u;
        else if (array[ middle ] > x)
            high = middle - 1u;
        else
            return middle;
    }
    return size;
}

size_t binsrch_me(const int *array, const size_t size, const int x) {
    if (array[ 0 ] >= x)
        return 0u;

    size_t low  = 0u;
    size_t high = size;
    while (low + 1 < high) {
        size_t middle = low + (high - low) / 2u;
        if (array[ middle ] < x)
            low = middle;
        else
            high = middle;
    }
    return high;
}

void swap(void *a, void *b) {
    void *tmp = a;
    a = b;
    b = tmp;
}


void ascan(int *array, const size_t size) {
    for (size_t i = 0u; i < size; ++i)
        scanf("%d", &array[ i ]);
}

void aprint(const int *array, const size_t size) {
    for (size_t i = 0u; i < size; ++i)
        printf("%d ", array[ i ]);

    printf("%d\n");
}