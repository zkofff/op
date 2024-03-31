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

bool isEmpty(vector *v) {
    return v->size == 0 ? true : false;
}

bool isFull(vector *v) {
    return v->size == v->capacity ? true : false;
}

int getVectorValue(vector *v, size_t i) {
    return i < v->size ? v->data[i] : -1;
}

void pushBack(vector *v, int x) {
    if (v->size == v->capacity) {
        size_t newCapacity = v->capacity*2;
        if (v->capacity == 0) {
            newCapacity = 1;
        }
        reserve(v, newCapacity);
    }
    v->data[v->size++] = x;
}

void test_pushBack_emptyVector() {
    vector v = createVector(0);
    pushBack(&v, 1);
    assert(v.size == 1);
    assert(v.capacity == 1);
    assert(v.data[0] == 1);
    deleteVector(&v);
}

void test_pushBack_fullVector() {
    vector v = createVector(1);
    pushBack(&v, 1);
    pushBack(&v, 2);
    assert(v.capacity == 2);
    assert(v.size == 2);
    assert(v.data[1] == 2);
    deleteVector(&v);
}

void popBack(vector *v) {
    if (isEmpty(v)) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    v->data[v->size--] = 0;
}