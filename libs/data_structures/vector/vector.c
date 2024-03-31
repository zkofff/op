#include <stdio.h>
#include "vector.h"
#include <malloc.h>
#include <stdbool.h>
#include <assert.h>

vector createVector(size_t n) {
    vector result;
    result.data = malloc(sizeof(int)*n);
    if (!result.data) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    result.size = 0;
    result.capacity = n;
    printf("Vector created\n");
    return result;
}

void reserve(vector *v, size_t newCapacity) {
    v->data = realloc(v->data, sizeof(int)*newCapacity);
    if (!v->data) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    v->capacity = newCapacity;
    v->size = newCapacity < v->size ? newCapacity : v->size;
    printf("Memory has been successfully reallocated\n");
}

void clear(vector *v) {
    v->size = 0;
}

void shrinkToFit(vector *v) {
    v->data = realloc(v->data, sizeof(int)*v->size);
}

void deleteVector(vector *v) {
    v->size = 0;
    v->capacity = 0;
    free(v->data);
}
