#ifndef ОП_LB20_H
#define ОП_LB20_H

#include <stdio.h>
#include "E:\ОП\libs\data_structures\matrix\matrix.h"

typedef struct domain {
    int visits_number;
    char *name;
} domain;

typedef struct prefix {
    int size;
    int begin_index;
    int end_index;
} prefix;

int** task_1(int n, int query[][4], size_t size);

void test_task_1();

int count_living_neighboring_cells(int m, int n, int board[m][n], int i, int j);

void task_2(int m, int n, int board[m][n]);

void test_task_2();

void get_median(int filter, int matrix[filter][filter], int i, int j);

void task_3(int filter, int matrix[filter][filter]);

void test_task_3();









#endif
