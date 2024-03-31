#ifndef INC_VECTORVOID_H
#define INC_VECTORVOID_H
#include <limits.h>
typedef struct vectorVoid {
    void *data; // указатель на нулевой элемент вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
    size_t baseTypeSize; // размер базового типа:

// например, если вектор хранит int -
// то поле baseTypeSize = sizeof(int)
// если вектор хранит float -
// то поле baseTypeSize = sizeof(float)

} vectorVoid;

vectorVoid createVectorV(size_t n, size_t baseTypeSize);

void reserveV(vectorVoid *v, size_t newCapacity);

void shrinkToFitV(vectorVoid *v);

void clearV(vectorVoid *v);

void deleteVectorV(vectorVoid *v);

bool isEmptyV(vectorVoid *v) {
    return v->size == 0 ? true : false;
}

bool isFullV(vectorVoid *v) {
    return v->size == v->capacity ? true : false;
}

void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void popBackV(vectorVoid *v) {
    if (isEmptyV(v)) {
        fprintf(stderr, "vector void is empty");
        exit(1);
    }

    (v->size)--;
}

void pushBackV(vectorVoid *v, void *source) {
    if (v->size == v->capacity) {
        size_t newCapacity = v->capacity*2;

        if (v->capacity == 0) {
            newCapacity = 1;
        }

        reserveV(v, newCapacity);
    }

    setVectorValueV(v, v->size++, source);
}

#endif
