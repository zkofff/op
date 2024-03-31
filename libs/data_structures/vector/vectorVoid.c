#include <stdio.h>
#include "vectorVoid.h"
#include <malloc.h>
#include <stdbool.h>
#include <memory.h>

vectorVoid createVectorV(size_t n, size_t baseTypeSize) {
    vectorVoid result;
    result.data = malloc(sizeof(int)*n);
    if (!result.data) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    result.size = 0;
    result.capacity = n;
    result.baseTypeSize = baseTypeSize;
    printf("Vector void has been successfully initialized\n");
    return result;
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    v->data = realloc(v->data, sizeof(int)*newCapacity);
    if (!v->data) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    v->capacity = newCapacity;
    v->size = newCapacity < v->size ? newCapacity : v->size;
    printf("Memory has been successfully reallocated\n");
}
void clearV(vectorVoid *v) {
    v->size = 0;
}
void shrinkToFitV(vectorVoid *v) {
    v->data = realloc(v->data, sizeof(int)*v->size);
}
void deleteVectorV(vectorVoid *v) {
    v->size = 0;
    v->capacity = 0;
    v->baseTypeSize = 0;
    free(v->data);
}
