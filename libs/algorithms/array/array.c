#include <assert.h>
#include "array.h"
#include <stdbool.h>
#include <malloc.h>
#include "unordered_array_set.h"
static void unordered_array_set_shrinkToFit(unordered_array_set *a){
    if (a->size != a->capacity){
        a->data = (int*)realloc(a->data, sizeof(int)*a->size);
        a->capacity = a->size;
    }
}
unordered_array_set unordered_set_create(size_t capacity){
    int *data = malloc(sizeof(int) * capacity);
    if (data == NULL){
        fprintf(stderr, "Fail memory allocated in
        unordered_array_set_create.\n");
        exit(-1);
    }
    return (unordered_array_set) {data, 0, capacity};
}
unordered_array_set unordered_array_set_create_from_array(const int *a, size_t
size){
    unordered_array_set result = unordered_array_set_create(size);
    for (size_t i = 0; i < size; i++) {
        unordered_array_set_insert(&result, a[i]);
    }
    unordered_array_set_shrinkToFit(&result);
    return result;
}
size_t unordered_array_set_in(unordered_array_set set, int value){
    return linearSearch_(set.data, set.size, value);
}
size_t unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set){
    if (subset.size > set.size){
        return set.size;
    }
    size_t coincidence = 0;
    for (size_t i = 0; i < set.size; i++){
        for (size_t j = 0; j < subset.size; j++){
            if (subset.data[j] == set.data[i + j]){
                coincidence++;
            } else {
                coincidence = 0;
                break;
            }
            if (coincidence == subset.size){
                return i;
            }
        }
    }
    return set.size;
}
bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2){
    if (set1.size != set2.size){
        return false;
    }
    size_t coincidence = 0;
    for (size_t i = 0; i < set1.size; i++){
        if (unordered_array_set_in(set2, set1.data[i]) != set2.size){
            coincidence++;
        }
    }
    if (coincidence == set1.size){
        return true;
    } else{
        return false;
    }
}
void unordered_array_set_isAbleAppend(unordered_array_set *set){
    assert(set->size < set->capacity);
}
void unordered_array_set_insert(unordered_array_set *set, int value){
    if (unordered_array_set_in(*set, value) == set->size){
        unordered_array_set_isAbleAppend(set);
        set->data[set->size++] = value;
    }
}
void unordered_array_set_deleteElement(unordered_array_set *set, int value){
    size_t value_index = unordered_array_set_in(*set, value);
    if (value_index == set->size){
        return;
    } else{
        for (int i = value_index; i < set->size - 1; i++){
            set->data[i] = set->data[i + 1];
        }
        set->size--;
        unordered_array_set_shrinkToFit(set);
    }
}
unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2){
    unordered_array_set result = unordered_array_set_create(set1.size +set2.size);

    for (size_t i = 0; i < set1.size; i++){
        unordered_array_set_insert(&result, set1.data[i]);
    }
    for (size_t i = 0; i < set2.size; i++){
        if (unordered_array_set_in(set1, set2.data[i]) == set1.size){
            unordered_array_set_insert(&result, set2.data[i]);
        }
    }
    unordered_array_set_shrinkToFit(&result);
    return result;
}
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2){
    size_t size = set1.size < set2.size ? set1.size : set2.size;
    unordered_array_set result = unordered_array_set_create(size);
    for (size_t i = 0; i < set1.size; i++){
        if (unordered_array_set_in(set2, set1.data[i]) != set2.size){
            unordered_array_set_insert(&result, set1.data[i]);
        }
    }
    unordered_array_set_shrinkToFit(&result);
    return result;
}
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2){
    unordered_array_set result = unordered_array_set_create(set1.size);
    for (size_t i = 0; i < set1.size; i++){
        if (unordered_array_set_in(set2, set1.data[i]) == set2.size){
            unordered_array_set_insert(&result, set1.data[i]);
        }
    }
    unordered_array_set_shrinkToFit(&result);
    return result;
}
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet){
    unordered_array_set result = unordered_array_set_create(universumSet.size);
    for (size_t i = 0; i < universumSet.size; i++){
        if (unordered_array_set_in(set, universumSet.data[i]) == set.size){
            unordered_array_set_insert(&result, universumSet.data[i]);
        }
    }
    unordered_array_set_shrinkToFit(&result);
    return result;
}
unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2){
    unordered_array_set difference1 = unordered_array_set_difference(set1, set2);
    unordered_array_set difference2 = unordered_array_set_difference(set2, set1);
    unordered_array_set result = unordered_array_set_union(difference1, difference2);
    return result;
}
void unordered_array_set_print(unordered_array_set set){
    outputArray_(set.data, set.size);
}
void unordered_array_set_delete(unordered_array_set *set){
    free(set->data);
    set->size = 0;
    set->capacity = 0;
}
void test_unordered_array_set_union1 (){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_union (set1, set2);
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {1, 2, 3}, 3);
    assert ( unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_union2 (){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2, 3}, 3) ;
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {}, 0) ;
    unordered_array_set resSet = unordered_array_set_union (set1, set2);
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {1, 2, 3}, 3);
    assert ( unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_union(){
    test_unordered_array_set_union1();
    test_unordered_array_set_union2();
}
void test_unordered_array_set_in1(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2, 3}, 3);
    size_t result = unordered_array_set_in(set1, 2);
    assert(result == 1);
    unordered_array_set_delete(&set1);
}
void test_unordered_array_set_in2(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2, 3}, 3);
    size_t result = unordered_array_set_in(set1, 4);
    assert(result == 3);
    unordered_array_set_delete(&set1);
}
void test_unordered_array_set_in(){
    test_unordered_array_set_in1();
    test_unordered_array_set_in2();
}
void test_unordered_array_set_isSubset1(){
    unordered_array_set set1 = unordered_array_set_create_from_array (( int []) {1, 2, 3}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int []) {1, 2, 3, 4}, 4);
    size_t result = unordered_array_set_isSubset(set1, set2);
    assert(result == 0);
    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
}
void test_unordered_array_set_isSubset2(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2, 7}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array((int []) {1, 2, 3, 4}, 4);
    size_t result = unordered_array_set_isSubset(set1, set2);
    assert(result == 4);
    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&set2);
}
void test_unordered_array_set_isSubset(){
    test_unordered_array_set_isSubset1();
    test_unordered_array_set_isSubset2();
}
void test_unordered_array_set_insert(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2, 7}, 3);
    set1.capacity++;
    unordered_array_set_insert(&set1, 4);
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {1, 2, 7, 4}, 4) ;
    assert ( unordered_array_set_isEqual (set1, expectedSet));
    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&expectedSet);
}
void test_unordered_array_set_deleteElement(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2, 7}, 3);
    unordered_array_set_deleteElement(&set1, 7);
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {1, 2}, 2);
    assert ( unordered_array_set_isEqual (set1, expectedSet));
    unordered_array_set_delete(&set1);
    unordered_array_set_delete(&expectedSet);
}
void test_unordered_array_set_intersection1() {
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_intersection (set1, set2)
    ;
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {2}, 1);
    assert ( unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_intersection2(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 4}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_intersection (set1, set2)
    ;
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {}, 0);
    assert ( unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_intersection(){
    test_unordered_array_set_intersection1();
    test_unordered_array_set_intersection2();
}
void test_unordered_array_set_difference1(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_difference (set1, set2);
    unordered_array_set expectedSet = unordered_array_set_create_from_array((int []) {1}, 1);
    assert ( unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_difference2(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {2, 3}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_difference (set1, set2 );
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {}, 0);
    assert (unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_difference(){
    test_unordered_array_set_difference1();
    test_unordered_array_set_difference2();
}
void test_unordered_array_set_symmetricDifference1(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {2, 3}, 2);
    unordered_array_set resSet = unordered_array_set_symmetricDifference (set1, set2);
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {1, 3}, 2);
    assert (unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_symmetricDifference2(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2}, 2);
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {4, 5}, 2);
    unordered_array_set resSet = unordered_array_set_symmetricDifference (set1, set2);
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {1, 2, 4, 5}, 4);
    assert ( unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_symmetricDifference(){
    test_unordered_array_set_symmetricDifference1();
    test_unordered_array_set_symmetricDifference2();
}
void test_unordered_array_set_complement1(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {1, 2, 4}, 3);
    unordered_array_set set2 = unordered_array_set_create_from_array ((int []) {1, 2 , 3, 4, 5}, 5);
    unordered_array_set resSet = unordered_array_set_complement (set1, set2);
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {3, 5}, 2);
    assert ( unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_complement2(){
    unordered_array_set set1 = unordered_array_set_create_from_array ((int []) {2, 3, 1, 4, 5}, 5);
    unordered_array_set set2 = unordered_array_set_create_from_array (( int []) {1, 2, 3, 4, 5}, 5);
    unordered_array_set resSet = unordered_array_set_complement ( set1, set2 );
    unordered_array_set expectedSet = unordered_array_set_create_from_array ((int []) {}, 0);
    assert ( unordered_array_set_isEqual (resSet, expectedSet));
    unordered_array_set_delete (&set1);
    unordered_array_set_delete (&set2);
    unordered_array_set_delete (&resSet);
    unordered_array_set_delete (&expectedSet);
}
void test_unordered_array_set_complement(){
    test_unordered_array_set_complement1();
    test_unordered_array_set_complement2();
}
void test_unordered_array_set(){
    test_unordered_array_set_union();
    test_unordered_array_set_in();
    test_unordered_array_set_isSubset();
    test_unordered_array_set_insert();
    test_unordered_array_set_deleteElement();
    test_unordered_array_set_intersection();
    test_unordered_array_set_difference();
    test_unordered_array_set_symmtricDifference();
    test_unordered_array_set_complement();
}
