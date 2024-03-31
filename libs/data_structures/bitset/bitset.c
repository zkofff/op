#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include "bitset.h"
bitset bitset_create(unsigned maxValue){
    bitset result;
    result.values = 0;
    result.maxValue = maxValue;
    return result;
}
bool bitset_in(bitset set, unsigned int value){
    if (set.values & (1 << value) && value <= set.maxValue){
        return true;
    } else {
        return false;
    }
}
bool bitset_isEqual(bitset set1, bitset set2){
    if (set1.maxValue != set2.maxValue){
        return false;
    }
    for (int i = 0; i <= set1.maxValue; i++){
        if (bitset_in(set1, i) != bitset_in(set2, i)){
            return false;
        }
    }
    return true;
}
bool bitset_isSubset(bitset subset, bitset set){
    if (subset.values <= set.values && subset.maxValue <= set.maxValue){
        for (int i = 0; i <= subset.maxValue; i++) {
            if (bitset_in(subset, i) && !bitset_in(set, i)){
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
void bitset_insert(bitset *set, unsigned int value){
    if (value <= set->maxValue){
        set->values |= (1 << value);
    }
}
void bitset_deleteElement(bitset *set, unsigned int value){
    if (bitset_in(*set, value)){
        set->values &= ~(1 << value);
    }
}
bitset bitset_union(bitset set1, bitset set2){
    assert(set1.maxValue == set2.maxValue);
    bitset result = bitset_create(set1.maxValue);
    result.values = set1.values | set2.values;
    return result;
}
bitset bitset_intersection(bitset set1, bitset set2){
    assert(set1.maxValue == set2.maxValue);
    bitset result = bitset_create(set1.maxValue);
    result.values = set1.values & set2.values;
    return result;
}
bitset bitset_difference(bitset set1, bitset set2){
    assert(set1.maxValue == set2.maxValue);
    bitset result = bitset_create(set1.maxValue);
    result.values = set1.values & ~set2.values;
    return result;
}
bitset bitset_symmetricDifference(bitset set1, bitset set2){
    assert(set1.maxValue == set2.maxValue);
    bitset result = bitset_create(set1.maxValue);
    result.values = set1.values ^ set2.values;
    return result;
}
bitset bitset_complement(bitset set){
    bitset result = bitset_create(set.maxValue);
    result.values = ~set.values;
    return result;
}
void bitset_print(bitset set){
    printf("{");
    int is_empty = true;
    for (int i = 0; i <= set.maxValue; i++){
        if (bitset_in(set, i)){
            printf("%d, ", i);
            is_empty = false;
        }
    }
    if (is_empty){
        printf("}\n");
    } else {
        printf("\b\b}\n");
    }
}
void test_bitset_union1(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset result = bitset_union(set1, set2);
    bitset expected_set = bitset_create(10);
    bitset_insert(&expected_set, 1);
    bitset_insert(&expected_set, 4);
    bitset_insert(&expected_set, 6);
    assert(bitset_isEqual(result, expected_set));
}
void test_bitset_union2(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 2);
    bitset_insert(&set1, 4);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset result = bitset_union(set1, set2);
    bitset expected_set = bitset_create(10);
    bitset_insert(&expected_set, 2);
    bitset_insert(&expected_set, 4);
    bitset_insert(&expected_set, 6);
    assert(bitset_isEqual(result, expected_set));
}
void test_bitset_union(){
    test_bitset_union1();
    test_bitset_union2();
}
void test_bitset_in1(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset_insert(&set1, 6);
    assert(!bitset_in(set1, 5));
}
void test_bitset_in2(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset_insert(&set1, 6);
    assert(bitset_in(set1, 4));
}
void test_bitset_in(){
    test_bitset_in1();
    test_bitset_in2();
}
void test_bitset_isSubset1(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset_insert(&set1, 6);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    assert(bitset_isSubset(set2, set1));
}
void test_bitset_isSubset2(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset_insert(&set1, 6);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 5);
    bitset_insert(&set2, 6);
    assert(!bitset_isSubset(set2, set1));
}
void test_bitset_isSubset(){
    test_bitset_isSubset1();
    test_bitset_isSubset2();
}
void test_bitset_deleteElement(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 2);
    bitset_deleteElement(&set1, 1);
    bitset result = bitset_create(10);
    bitset_insert(&result, 2);
    assert(bitset_isEqual(set1, result));
}
void test_bitset_intersection1(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset result = bitset_intersection(set1, set2);
    bitset expected_set = bitset_create(10);
    bitset_insert(&expected_set, 4);
    assert(bitset_isEqual(result, expected_set));
}
void test_bitset_intersection2(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 2);
    bitset_insert(&set1, 3);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset result = bitset_intersection(set1, set2);
    bitset expected_set = bitset_create(10);
    assert(bitset_isEqual(result, expected_set));
}
void test_bitset_intersection(){
    test_bitset_intersection1();
    test_bitset_intersection2();
}
void test_bitset_difference1(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset result = bitset_difference(set1, set2);
    bitset expected_set = bitset_create(10);
    bitset_insert(&expected_set, 1);
    assert(bitset_isEqual(result, expected_set));
}
void test_bitset_difference2(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 2);
    bitset_insert(&set1, 3);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset result = bitset_difference(set1, set2);
    bitset expected_set = bitset_create(10);
    bitset_insert(&expected_set, 2);
    bitset_insert(&expected_set, 3);
    assert(bitset_isEqual(result, expected_set));
}
void test_bitset_difference(){
    test_bitset_difference1();
    test_bitset_difference2();
}
void test_bitset_symmetricDifference1(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset result = bitset_symmetricDifference(set1, set2);
    bitset expected_set = bitset_create(10);
    bitset_insert(&expected_set, 1);
    bitset_insert(&expected_set, 6);
    assert(bitset_isEqual(result, expected_set));
}
void test_bitset_symmetricDifference2(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 2);
    bitset_insert(&set1, 3);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset result = bitset_symmetricDifference(set1, set2);
    bitset expected_set = bitset_create(10);
    bitset_insert(&expected_set, 2);
    bitset_insert(&expected_set, 3);
    bitset_insert(&expected_set, 4);
    bitset_insert(&expected_set, 6);
    assert(bitset_isEqual(result, expected_set));
}
void test_bitset_symmetricDifference(){
    test_bitset_symmetricDifference1();
    test_bitset_symmetricDifference2();
}
void test_bitset_complement1(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 3);
    bitset_insert(&set1, 4);
    bitset_insert(&set1, 8);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 0);
    bitset_insert(&set2, 2);
    bitset_insert(&set2, 5);
    bitset_insert(&set2, 6);
    bitset_insert(&set2, 7);
    bitset_insert(&set2, 9);
    bitset_insert(&set2, 10);;
    bitset result = bitset_complement(set1);
    assert(bitset_isEqual(result, set2));
}
void test_bitset_complement2(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 2);
    bitset_insert(&set1, 3);
    bitset_insert(&set1, 4);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 6);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 8);
    bitset_insert(&set1, 9);
    bitset_insert(&set1, 10);
    bitset set2 = bitset_create(10);
    bitset_insert(&set2, 0);
    bitset result = bitset_complement(set1);
    assert(bitset_isEqual(result, set2));
}
void test_bitset_complement(){
    test_bitset_complement1();
    test_bitset_complement2();
}
void test_bitset(){
    test_bitset_union();
    test_bitset_in();
    test_bitset_isSubset();
    test_bitset_deleteElement();
    test_bitset_intersection();
    test_bitset_difference();
    test_bitset_symmetricDifference();
    test_bitset_complement();
}