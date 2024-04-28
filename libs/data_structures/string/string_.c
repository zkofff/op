#include "string_.h"
#include <stdio.h>
#include <ctype.h>
#include <memory.h>
#include <assert.h>

size_t strlen_(const char *begin) {
    const char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char* find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char* findNonSpace(char *begin) {
    while (isspace(*begin) && *begin != '\0') {
        begin++;
    }
    return begin;
}
char* findSpace(char *begin) {
    while (!isspace(*begin) && *begin != '\0') {
        begin++;
    }
    return begin;
}
char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && isspace(*rbegin)) {
        rbegin--;
    }
    return rbegin;
}
char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && !isspace(*rbegin)) {
        rbegin--;
    }
    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs == *rhs && *lhs != '\0' && *rhs != '\0') {
        lhs++;
        rhs++;
    }
    return *lhs - *rhs;
}

char* copy(const char *beginSource, const char *endSource, char
*beginDestination) {
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);
    *(beginDestination + size) = '\0';
    return beginDestination + size;
}
char* copyIf(char *beginSource, const char *endSource, char *beginDestination,
             int (*f)(int)) {
    while (beginSource != endSource) {
        if (f( *beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }
    *beginDestination = '\0';
    return beginDestination;
}
char* copyIfReverse(char *rbeginSource, const char *rendSource, char
*beginDestination, int (*f)(int)) {
    char *beginDestination_ = beginDestination;
    while (rbeginSource >= rendSource) {
        if (f(*rbeginSource)) {
            *beginDestination_ = *rbeginSource;
            beginDestination_++;
        }
        rbeginSource--;
    }
    *beginDestination_ = '\0';
    return beginDestination_;
}
int is_h(char s) {
    return s == 'h' || s == 'w';
}

void test_find1() {
    char string[] = "hello";
    assert(find(string, string + 5, 'e') == string + 1);
}
void test_find2() {
    char string[] = "hello";
    assert(find(string, string + 5, 'h') == string);
}
void test_find3() {
    char string[] = "hello";
    assert(find(string, string + 5, 'o') == string + 4);
}
void test_find4() {
    char string[] = "hello";
    assert(find(string, string + 5, 'g') == string + 5);
}
void test_find_nonspace1() {
    char string[] = "hello";
    assert(findNonSpace(string) == string);
}
void test_find_nonspace2() {
    char string[] = " llo";
    assert(findNonSpace(string) == string + 2);
}
void test_find_nonspace3() {
    char string[] = " o";
    assert(findNonSpace(string) == string + 4);
}
void test_find_nonspace4() {
    char string[] = " ";
    assert(findNonSpace(string) == string + 5);
}
void test_find_space1() {
    char string[] = " ello";
    assert(findSpace(string) == string);
}
void test_find_space2() {
    char string[] = "he lo";
    assert(findSpace(string) == string + 2);
}
void test_find_space3() {
    char string[] = "hello";
    assert(findSpace(string) == string + 5);
}
void test_find_space4() {
    char string[] = "hell ";
    assert(findSpace(string) == string + 4);
}
void test_find_non_space_reverse1() {
    char string[] = "hello";
    assert(findNonSpaceReverse(string + 4, string) == string + 4);
}
void test_find_non_space_reverse2() {
    char string[] = "hel ";
    assert(findNonSpaceReverse(string + 4, string) == string + 2);
}
void test_find_non_space_reverse3() {
    char string[] = "h ";
    assert(findNonSpaceReverse(string + 4, string) == string);
}
void test_find_non_space_reverse4() {
    char string[] = " ";
    assert(findNonSpaceReverse(string + 4, string) == string - 1);
}
void test_find_space_reverse1() {
    char string[] = "hello";
    assert(findSpaceReverse(string + 4, string) == string - 1);
}
void test_find_space_reverse2() {
    char string[] = "hel ";
    assert(findSpaceReverse(string + 4, string) == string + 4);
}
void test_find_space_reverse3() {
    char string[] = "h o";
    assert(findSpaceReverse(string + 4, string) == string + 3);
}
void test_find_space_reverse4() {
    char string[] = " ello";
    assert(findSpaceReverse(string + 4, string) == string);
}
void test_strcmp1() {
    char string1[] = "Hello";
    char string2[] = "Hello";
    assert(strcmp(string1, string2) == 0);
}
void test_strcmp2() {
    char string1[] = "Hello";
    char string2[] = "Hallo";
    assert(strcmp(string1, string2) > 0);
}
void test_strcmp3() {
    char string1[] = "Hello";
    char string2[] = "Hellower";
    assert(strcmp(string1, string2) < 0);
}
void test_copy() {
    char string[] = "hahh";
    char new_string[4];
    copy(string, string + 3, new_string);
    char result[] = "hah";
    assert(strcmp(new_string, result) == 0);
}
void test_copyIf() {
    char string[] = "hahh";
    char new_string[4];
    copyIf(string, string + 3, new_string, (int (*)(int)) is_h);
    char result[] = "hh";
    assert(strcmp(new_string, result) == 0);
}
void test_copyIfReverse() {
    char string[] = "haw";
    char new_string[3];
    copyIfReverse(string + 3, string, new_string, (int (*)(int)) is_h);
    char result[] = "wh";
    assert(strcmp(new_string, result) == 0);
}
void tests_find_str() {
    test_find1();
    test_find2();
    test_find3();
    test_find4();
    test_find_nonspace1();
    test_find_nonspace2();
    test_find_nonspace3();
    test_find_nonspace4();
    test_find_space1();
    test_find_space2();
    test_find_space3();
    test_find_space4();
    test_find_non_space_reverse1();
    test_find_non_space_reverse2();
    test_find_non_space_reverse3();
    test_find_non_space_reverse4();
    test_find_space_reverse1();
    test_find_space_reverse2();
    test_find_space_reverse3();
    test_find_space_reverse4();
    test_strcmp1();
    test_strcmp2();
    test_strcmp3();
    test_copy();
    test_copyIf();
    test_copyIfReverse();
}

void removeNonLetters(char *s) {
    char *endSource = s + strlen_(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}
void assertString(const char *expected, char *got, char const *fileName, char
const *funcName, int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}
void test_removeNonLetters() {
    char s1[] = "hel lo";
    char s2[] = "hello";
    removeNonLetters(s1);
    ASSERT_STRING(s1, s2);
}

void removeExtraSpaces(char *s) {
    if (strlen_(s) > 0) {
        char *endSource = s + strlen_(s);
        char *destination = copy_if_not_extra_spaces(s, endSource, s);
        *destination = '\0';
    }
}
void test_removeExtraSpaces_1() {
    char s1[] = "";
    char s2[] = "";
    removeExtraSpaces(s1);
    ASSERT_STRING(s1, s2);
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}
void digitToStart(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin,
                               isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}
void digitToEnd(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin,
                               isalpha);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isdigit);
}
void digitToEndAndReverse(WordDescriptor word) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *endStringBuffer = copy(word.begin, word.end,_stringBuffer);
    char *recPosition = copyIf(_stringBuffer, endStringBuffer, word.begin,
                               isalpha);
    copyIfReverse(endStringBuffer, _stringBuffer, recPosition, isdigit);
}
void digits_to_end(char *string) {
    WordDescriptor word;
    char *beginSearch = string;
    while (getWord(beginSearch, &word)) {
        digitToEnd(word);
        beginSearch = word.end;
    }
}
void digits_to_end_and_reverse(char *string) {
    WordDescriptor word;
    char *beginSearch = string;
    while (getWord(beginSearch, &word)) {
        digitToEndAndReverse(word);
        beginSearch = word.end;
    }
}
void letters_to_end(char *string) {
    WordDescriptor word;
    char *beginSearch = string;
    while (getWord(beginSearch, &word)) {
        digitToStart(word);
        beginSearch = word.end;
    }
}
void test_WordDescriptor() {
    char string1[] = "he13l3lo8";
    digits_to_end(string1);
    ASSERT_STRING("hello1338", string1);
    char string2[] = "he13l3lo8";
    digits_to_end_and_reverse(string2);
    ASSERT_STRING("hello8331", string2);
    char string3[] = "he13l3lo8";
    letters_to_end(string3);
    ASSERT_STRING(string3, "1338hello");
}

void replace_digits_with_spaces(char *string) {
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *end = string + strlen_(string);
    char *readBuffer = _stringBuffer;
    copy(string, end, readBuffer);
    while (*readBuffer != '\0') {
        if (isalpha(*readBuffer)) {
            *string++ = *readBuffer;
        } else {
            while (isdigit(*readBuffer) && *readBuffer != '0') {
                *string++ = ' ';
                (*readBuffer)--;
            }
        }
        readBuffer++;
    }
    *string = '\0';
}
void test_replace_digits_with_spaces() {
    char string_1[] = "";
    replace_digits_with_spaces(string_1);
    ASSERT_STRING("", string_1);
    char string_2[] = "hl";
    replace_digits_with_spaces(string_2);
    ASSERT_STRING("hl", string_2);
    char string_3[] = "h12l";
    replace_digits_with_spaces(string_3);
    ASSERT_STRING("h l", string_3);
}

bool are_two_words_equal(WordDescriptor a, WordDescriptor b) {
    char *readBuffer1 = a.begin;
    char *readBuffer2 = b.begin;
    while ((*readBuffer1 != ' ' || *readBuffer2 != ' ') && (*readBuffer1 !=
                                                            '\0' && *readBuffer2 != '\0')) {
        if (*readBuffer1 != *readBuffer2 != '\0') {
            return 0;
        }
        readBuffer1++;
        readBuffer2++;
    }
    return readBuffer1 == a.end && readBuffer2 == b.end;
}
void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    WordDescriptor word;
    char _stringBuffer[MAX_STRING_SIZE + 1];
    char *readPtr, *recPtr;
    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, source + strlen_(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }
    while (getWord(readPtr, &word)) {
        WordDescriptor res = word2;
        if (!are_two_words_equal(word, word1)) {
            res = word;
        }
        for (char *cp = res.begin; cp != res.end; cp++) {
            *recPtr++ = *cp;
        }
        *recPtr++ = ' ';
        readPtr = word.end;
    }
    *(recPtr - 1) = '\0';
}
void test_replace() {
    char string[] = "0/15/2 who? -=-";
    replace(string, "who?", "Yasuo");
    ASSERT_STRING("0/15/2 Yasuo -=-", string);
    char string2[] = "0/15/2 x -=- x";
    replace(string2, "x", "Yasuo");
    ASSERT_STRING("0/15/2 Yasuo -=- Yasuo", string2);
}

bool are_two_words_ordered(WordDescriptor word1, WordDescriptor word2) {
    char *string1 = word1.begin;
    char *string2 = word2.begin;
    while (*string1 != '\0' || *string1 != ' ') {
        if (*string2 - 'a' < *string1 - 'a' || *string2 == '\0' || *string2
                                                                   == ' ') {
            return false;
        } else if (*string2 - 'a' > *string1 - 'a') {
            return true;
        }
        string1++;
        string2++;
    }
    return true;
}
bool are_words_ordered(char *string) {
    WordDescriptor word1, word2;
    if (getWord(string, &word1)) {
        word2 = word1;
        char *string_ = word1.end;
        while (getWord(string_, &word1)) {
            if (!are_two_words_ordered(word2, word1)) {
                return false;
            }
            word2 = word1;
            string_ = word1.end;
        }
        return true;
    } else {
        return true;
    }
}
void test_are_words_ordered() {
    char string1[] = "";
    assert(are_words_ordered(string1));
    char string2[] = "zero one two";
    assert(!are_words_ordered(string2));
    char string3[] = "one two zero";
    assert(are_words_ordered(string3));
}

void getBagOfWords(BagOfWords *bag, char *s) {
    bag->size = 0;
    WordDescriptor word;
    char *beginSearch = s;
    while (getWord(beginSearch, &word)) {
        bag->words[bag->size].begin = word.begin;
        bag->words[bag->size].end = word.end;
        bag->size++;
        beginSearch = word.end;
    }
}
void print_words_in_reversed_order(char *string) {
    getBagOfWords(&_bag, string);
    char word[MAX_WORD_SIZE];
    for (size_t i = _bag.size; i > 0; i--) {
        copy(_bag.words[i - 1].begin, _bag.words[i - 1].end, word);
        printf("%s\n", word);
    }
}
void test_print_words_in_reversed_order() {
    char string_1[] = "";
    print_words_in_reversed_order(string_1);
    char string_2[] = "One Two Three";
    print_words_in_reversed_order(string_2);
}

int is_palindrome(char *begin, char *end) {
    end--;
    while (end > begin) {
        if (*begin != *end) {
            return 0;
        }
        begin++;
        end--;
    }
    return 1;
}
int count_palindromes(char *string) {
    char *begin = findNonSpace(string);
    char *end = string + strlen_(string);
    char *new_word = find(begin, end, ',');
    bool is_last_word = *new_word == '\n';
    size_t result = 0;
    while (*new_word != '\0' || is_last_word) {
        result += is_palindrome(begin, new_word);
        if (is_last_word) {
            break;
        }
        begin = findNonSpace(new_word + 1);
        new_word = find(begin, end, ',');
        is_last_word = *new_word == '\0';
    }
    return result;
}
void test_count_palindromes() {
    char string_1[] = "";
    assert(count_palindromes(string_1) == 0);
    char string_2[] = "pudge, zazaz";
    assert(count_palindromes(string_2) == 1);
}

void join_strings(char *string1, char *string2, char *result) {
    WordDescriptor word1, word2;
    bool isW1Found, isW2Found;
    char *beginSearch1 = string1, *beginSearch2 = string2;
    while ((isW1Found = getWord(beginSearch1, &word1)), (isW2Found =
                                                                 getWord(beginSearch2, &word2)), isW1Found || isW2Found) {
        if (isW1Found && isW2Found) {
            for (char *s = word1.begin; s != word1.end; s++) {
                *result++ = *s;
            }
            *result++ = ' ';
            for (char *s = word2.begin; s != word2.end; s++) {
                *result++ = *s;
            }
            beginSearch1 = word1.end;
            beginSearch2 = word2.end;
            if ((isW1Found = getWord(beginSearch1, &word1)), (isW2Found =
                                                                      getWord(beginSearch2, &word2)), isW1Found || isW2Found) {
                *result++ = ' ';
            }
        } else if (isW1Found) {
            for (char *s = word1.begin; s != beginSearch1 +
                                             strlen_(beginSearch1); s++) {
                *result++ = *s;
            }
            return;
        } else {
            for (char *s = word2.begin; s != beginSearch2 +
                                             strlen_(beginSearch2); s++) {
                *result++ = *s;
            }
            return;
        }
    }
}
void test_join_strings() {
    char result1[MAX_STRING_SIZE];
    join_strings("", "", result1);
    ASSERT_STRING(result1, "");
    char result2[MAX_STRING_SIZE];
    join_strings("one three", "two four", result2);
    ASSERT_STRING(result2, "one two three four");
    char result3[MAX_STRING_SIZE];
    join_strings("one three five", "two four", result3);
    ASSERT_STRING(result3, "one two three four five");
    char result4[MAX_STRING_SIZE];
    join_strings("one three", "two four five", result4);
    ASSERT_STRING(result4, "one two three four five");

    void reverse_words_order(char *string) {
        getBagOfWords(&_bag, string);
        char result[MAX_STRING_SIZE + 1];
        int size = 0;
        for (int i = _bag.size; i > 0; i--) {
            for (char *s = _bag.words[i - 1].begin; s != _bag.words[i - 1].end;
                 s++) {
                result[size++] = *s;
            }
            if (i != 1) {
                result[size++] = ' ';
            }
        }
        result[size++] = '\0';
        copy(result, result + size, string);
    }
    void test_reverse_words_order() {
        char string1[] = "";
        reverse_words_order(string1);
        ASSERT_STRING(string1, "");
        char string2[] = "one";
        reverse_words_order(string2);
        ASSERT_STRING(string2, "one");
        char string3[] = "one two three";
        reverse_words_order(string3);
        ASSERT_STRING(string3, "three two one");
    }

    void printWordBeforeFirstWordWithA(char *s) {
        WordDescriptor word;
        WordBeforeFirstWordWithAReturnCode code = getWordBeforeFirstWordWithA(s,
                                                                              &word);
        if (code == EMPTY_STRING) {
            printf("The string is empty.\n");
        } else if (code == NOT_FOUND_A_WORD_WITH_A) {
            printf("The letter 'a' or 'A' was not founded.\n");
        } else if (code == FIRST_WORD_WITH_A) {
            printf("The letter 'a' or 'A' was founded in first word.\n");
        } else {
            char *beginSearch = s;
            char result[MAX_WORD_SIZE];
            while (getWord(beginSearch, &word)) {
                copy(word.begin, word.end, result);
                getWord(word.end, &word);
                if (find(word.begin, word.end, 'A') != word.end ||
                    find(word.begin, word.end, 'a') != word.end) {
                    printf("%s\n", result);
                    return;
                }
                beginSearch = word.begin;
            }
        }
    }
    WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s,
                                                                   WordDescriptor *w) {
        if (*s == '\0') {
            return EMPTY_STRING;
        } else if (find(s, s + strlen_(s), 'A') != s + strlen_(s) || find(s, s +
                                                                             strlen_(s), 'a') != s + strlen_(s)) {
            char *beginSearch = s;
            getWord(beginSearch, w);
            if (find(w->begin, w->end, 'A') != w->end || find(w->begin, w->end,
                                                              'a') != w->end) {
                return FIRST_WORD_WITH_A;
            } else {
                return WORD_FOUND;
            }
        } else {
            return NOT_FOUND_A_WORD_WITH_A;
        }
    }
    void test_getWordBeforeFirstWordWithA() {
        WordDescriptor word;
        char s1[] = "";
        printWordBeforeFirstWordWithA(s1);
        assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);
        char s2[] = "ABC";
        printWordBeforeFirstWordWithA(s2);
        assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);
        char s3[] = "BC DSS A DS AD";
        printWordBeforeFirstWordWithA(s3);
        assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);
        char s4[] = "B Q WE YR OW IUWR";
        printWordBeforeFirstWordWithA(s4);
        assert(getWordBeforeFirstWordWithA(s4, &word) ==
               NOT_FOUND_A_WORD_WITH_A);
    }

    void wordDescriptorToString(WordDescriptor word, char *destination) {
        copy(word.begin, word.end, destination);
    }
    char* getLastWordInFirstStringInSecondString(char *s1, char *s2) {
        getBagOfWords(&_bag, s1);
        getBagOfWords(&_bag2, s2);
        char result[MAX_WORD_SIZE + 1];
        for (int i = _bag.size; i > 0; i--) {
            for (int j = _bag2.size; j > 0; j--) {
                if (are_two_words_equal(_bag.words[i - 1], _bag2.words[j - 1])) {
                    wordDescriptorToString(_bag.words[i - 1], result);
                    return result;
                }
            }
        }
        return "";
    }
    void test_getLastWordInFirstStringInSecondString() {
        char s1_1[] = "";
        char s1_2[] = "";
        ASSERT_STRING(getLastWordInFirstStringInSecondString(s1_1, s1_2), "");
        char s2_1[] = "One Two Zero Three";
        char s2_2[] = "One Zero Five";
        ASSERT_STRING(getLastWordInFirstStringInSecondString(s2_1, s2_2),
                      "Zero");
        char s3_1[] = "One Three Five";
        char s3_2[] = "Two Four";
        ASSERT_STRING(getLastWordInFirstStringInSecondString(s3_1, s3_2), "");
    }

    void wordDescriptorToString(WordDescriptor word, char *destination) {
        copy(word.begin, word.end, destination);
    }
    char* getLastWordInFirstStringInSecondString(char *s1, char *s2) {
        getBagOfWords(&_bag, s1);
        getBagOfWords(&_bag2, s2);
        char result[MAX_WORD_SIZE + 1];
        for (int i = _bag.size; i > 0; i--) {
            for (int j = _bag2.size; j > 0; j--) {
                if (are_two_words_equal(_bag.words[i - 1], _bag2.words[j - 1])) {
                    wordDescriptorToString(_bag.words[i - 1], result);
                    return result;
                }
            }
        }
        return "";
    }
    void test_getLastWordInFirstStringInSecondString() {
        char s1_1[] = "";
        char s1_2[] = "";
        ASSERT_STRING(getLastWordInFirstStringInSecondString(s1_1, s1_2), "");
        char s2_1[] = "One Two Zero Three";
        char s2_2[] = "One Zero Five";
        ASSERT_STRING(getLastWordInFirstStringInSecondString(s2_1, s2_2),
                      "Zero");
        char s3_1[] = "One Three Five";
        char s3_2[] = "Two Four";
        ASSERT_STRING(getLastWordInFirstStringInSecondString(s3_1, s3_2), "");
    }
