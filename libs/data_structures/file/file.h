#ifndef ОП_FILE_H
#define ОП_FILE_H

#define MAX_STRINGS_NUMBER 100
#define MAX_STRING_LENGTH 100
#define MAX_ELEMENTS_NUMBER 100

#include <stdio.h>
#include <stdbool.h>

typedef struct polynomial {
    int power;
    int coefficient;
} polynomial;

typedef struct sportsman {
    char *FIO;
    int best_result;
} sportsman;

typedef struct product {
    char *name;
    int unit_price;
    int quantity;
    int total_price;
} product;

typedef struct order {
    char *name;
    int quantity;
} order;

bool assert_file(char *file_name, char **true_data);

void make_matrix_storage_by_columns(char *file_name);

void test_make_matrix_storage_by_columns();

#endif