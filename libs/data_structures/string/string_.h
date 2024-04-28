#ifndef ОП_STRING__H
#define ОП_STRING__H
#include <stdio.h>

size_t strlen_(const char *begin);

char* find(char *begin, char *end, int ch);

char* findNonSpace(char *begin);

char* findSpace(char *begin);

char* findNonSpaceReverse(char *rbegin, const char *rend);

char* findSpaceReverse(char *rbegin, const char *rend);

int strcmp(const char *lhs, const char *rhs);

char* copy(const char *beginSource, const char *endSource, char *beginDestination);

char* copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));

char* copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int));

void test_find1();

void test_find2();

void test_find3();

void test_find4();

void test_find_nonspace1();

void test_find_nonspace2();

void test_find_nonspace3();

void test_find_nonspace4();

void test_find_space1();

void test_find_space2();

void test_find_space3();

void test_find_space4();

void test_find_non_space_reverse1();

void test_find_non_space_reverse2();

void test_find_non_space_reverse3();

void test_find_non_space_reverse4();

void test_find_space_reverse1();

void test_find_space_reverse2();

void test_find_space_reverse3();

void test_find_space_reverse4();

void tests_find_str();

void test_strcmp1();

void test_strcmp2();

void test_strcmp3();

void test_copy();

void test_copyIf();

void test_copyIfReverse();

void removeNonLetters(char *s);

void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line);

void test_removeNonLetters();

char* copy_if_not_extra_spaces(char *beginSource, const char *endSource, char *beginDestination);

void removeAdjacentEqualLetters(char *s);

void test_removeAdjacentEqualLetters();

void removeExtraSpaces(char *s);

void test_removeExtraSpaces_1();

void test_removeExtraSpaces_2();

void test_removeExtraSpaces_3();

int getWord(char *beginSearch, WordDescriptor *word);

void digitToStart(WordDescriptor word);

void digitToEnd(WordDescriptor word);

void digitToEndAndReverse(WordDescriptor word);

void digits_to_end(char *string);

void digits_to_end_and_reverse(char *string);

void letters_to_end(char *string);

void test_WordDescriptor();

void replace_digits_with_spaces(char *string);

void test_replace_digits_with_spaces();

bool are_two_words_equal(WordDescriptor a, WordDescriptor b);

void replace(char *source, char *w1, char *w2);

void test_replace();

void getBagOfWords(BagOfWords *bag, char *s);

void print_words_in_reversed_order(char *string);

void test_print_words_in_reversed_order();

int is_palindrome(char *begin, char *end);

int count_palindromes(char *string);

void test_count_palindromes();

void join_strings(char *string1, char *string2, char *result);

void test_join_strings();

void reverse_words_order(char *string);

void test_reverse_words_order();

void printWordBeforeFirstWordWithA(char *s);

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w);

void test_getWordBeforeFirstWordWithA();

void wordDescriptorToString(WordDescriptor word, char *destination);

char* getLastWordInFirstStringInSecondString(char *s1, char *s2);

void test_getLastWordInFirstStringInSecondString();

bool has_same_words(char *string);

void test_has_same_words();

bool has_words_with_similar_characters(char *string);

bool are_two_words_with_similar_characters(char *s1, char *s2);

void test_has_words_with_similar_characters();

void get_string_without_words_like_last_word(char *string, char *result);

void test_get_string_without_words_like_last_word();

WordPrecedingFirstCommonWordReturnCode get_word_preceding_first_common_word(char *s1, char *s2, WordDescriptor *word);

void test_get_word_preceding_first_common_word();

void delete_palindromes(char *string);

void test_delete_palindromes();

void complement_smaller_string(char *string1, char *string2);

void test_complement_smaller_string();

bool is_string_contain_all_letter(char *string, char *word);

void test_is_string_contain_all_letter();

bool are_two_words_ordered(WordDescriptor word1, WordDescriptor word2);

bool are_words_ordered(char *string);

void test_are_words_ordered();

#endif
