#include <stdio.h>
#include "file.h"
#include <malloc.h>
#include "libs/data_structures/string/string_.h"
#include "libs/data_structures/matrix/matrix.h"
#include <stdbool.h>
#include <assert.h>

bool assert_file(char *file_name, char **true_data){
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL){
        perror(file_name);
        fclose(file);
        return false;
    }
    size_t size = 0;
    while (!feof(file)){
        char string[MAX_STRING_LENGTH];
        fgets(string, MAX_STRING_LENGTH, file);
        if (strcmp(string, true_data[size]) != 0){
            fclose(file);
            return false;
        }
        size++;
    }
    fclose(file);
    return true;
}
void make_matrix_storage_by_columns(char *file_name){
    FILE *file;
    file = fopen(file_name, "r");
    if (file == NULL){
        perror(file_name);
        return;
    }
    char strings[MAX_STRINGS_NUMBER][MAX_STRING_LENGTH];
    size_t size = 0;
    while (!feof(file)){
        fgets(strings[size], MAX_STRING_LENGTH, file);
        size++;
    }
    fclose(file);
    file = fopen(file_name, "w");
    for (size_t i = 0; i < size; i++){
        int matrix_size = atoi(strings[i]);
        if (i == 0){
            fprintf(file, "%d", matrix_size);
        } else{
            fprintf(file, "\n%d", matrix_size);
        }
        BagOfWords elements[matrix_size];
        for (size_t j = 0; j < matrix_size; j++){
            getBagOfWords(&elements[j], strings[i + j + 1]);
        }
        for (size_t j = 0; j < matrix_size; j++){
            for (size_t g = 0; g < matrix_size; g++){
                int element = atoi(elements[g].words[j].begin);
                if (g == 0){
                    fprintf(file, "\n%d", element);
                } else{
                    fprintf(file, " %d", element);
                }
            }
        }
        i += matrix_size;
    }
    fclose(file);
}
void test_make_matrix_storage_by_columns(){
    FILE *test;
    test = fopen("test.txt", "w");
    fprintf(test, "3\n1 2 3\n4 5 6\n7 8 9\n0\n2\n11 15\n3 70\n1\n54");
    fclose(test);
    make_matrix_storage_by_columns("test.txt");
    char *true_data[] ={"3\n", "1 4 7\n", "2 5 8\n", "3 6 9\n", "0\n", "2\n", "11
            3\n", "15 70\n", "1\n", "54"};
            assert(assert_file("test.txt", true_data));
    }
    void test_file1(){
        test_make_matrix_storage_by_columns();
    }

    void represent_as_floating_point_numbers(char *file_name) {
        FILE *file;
        file = fopen(file_name, "r");
        double numbers[MAX_STRINGS_NUMBER];
        size_t size = 0;
        while (fscanf(file, "%lf", &numbers[size]) != EOF) {
            size++;
        }
        fclose(file);
        file = fopen(file_name, "w");
        for (size_t i = 0; i < size; i++) {
            if (i == 0) {
                fprintf(file, "%.2f", numbers[i]);
            } else {
                fprintf(file, "\n%.2f", numbers[i]);
            }
        }
        fclose(file);
    }
    void test_represent_as_floating_point_numbers() {
        FILE *test;
        test = fopen("test.txt", "w");
        fprintf(test, "12343.3\n332.253\n4322.32\n2.32523");
        fclose(test);
        represent_as_floating_point_numbers("test.txt");
        char *true_data[] = {"12343.30\n", "332.25\n", "4322.32\n", "2.33"};
        assert(assert_file("test.txt", true_data));
    }

    void calculate_expression(char *file_name) {
        FILE *file;
        file = fopen(file_name, "r");
        char expression[MAX_STRING_LENGTH];
        fgets(expression, MAX_STRING_LENGTH, file);
        fclose(file);
        double expression_result;
        BagOfWords elements;
        getBagOfWords(&elements, expression);
        if (elements.size == 3) {
            double a = atof(elements.words[0].begin);
            double b = atof(elements.words[2].begin);
            if (*elements.words[1].begin == '+') {
                expression_result = a + b;
            } else if (*elements.words[1].begin == '-') {
                expression_result = a - b;
            } else if (*elements.words[1].begin == '*') {
                expression_result = a * b;
            } else {
                expression_result = a / b;
            }
        } else {
            double a = atof(elements.words[0].begin);
            double b = atof(elements.words[2].begin);
            double c = atof(elements.words[4].begin);
            if ((*elements.words[1].begin == '+' || *elements.words[1].begin == '-')
                && (*elements.words[3].begin == '*' || *elements.words[3].begin == '/')) {
                if (*elements.words[3].begin == '*') {
                    expression_result = b * c;
                } else {
                    expression_result = b / c;
                }
                if (*elements.words[1].begin == '+') {
                    expression_result += a;
                } else {
                    expression_result = a - expression_result;
                }
            } else {
                if (*elements.words[1].begin == '+') {
                    expression_result = a + b;
                } else if (*elements.words[1].begin == '-') {
                    expression_result = a - b;
                } else if (*elements.words[1].begin == '*') {
                    expression_result = a * b;
                } else {
                    expression_result = a / b;
                }
                if (*elements.words[3].begin == '+') {
                    expression_result += c;
                } else if (*elements.words[3].begin == '-') {
                    expression_result -= c;
                } else if (*elements.words[3].begin == '*') {
                    expression_result *= c;
                } else {
                    expression_result /= c;
                }
            }
        }
        file = fopen(file_name, "a");
        fprintf(file, " = %.3lf", expression_result);
        fclose(file);
    }
    void test_calculate_expression() {
        FILE *test;
        test = fopen("test.txt", "w");
        fprintf(test, "3 + 2");
        fclose(test);
        calculate_expression("test.txt");
        char *true_data[1] = {"3 + 2 = 5.000"};
        assert(assert_file("test.txt", true_data));

        test = fopen("test.txt", "w");
        fprintf(test, "3 - 6");
        fclose(test);
        calculate_expression("test.txt");
        char *true_data_2[1] = {"3 - 6 = -3.000"};
        assert(assert_file("test.txt", true_data_2));

        test = fopen("test.txt", "w");
        fprintf(test, "2 * 2");
        fclose(test);
        calculate_expression("test.txt");
        char *true_data_3[1] = {"2 * 2 = 4.000"};
        assert(assert_file("test.txt", true_data_3));

        test = fopen("test.txt", "w");
        fprintf(test, "5 / 2");
        fclose(test);
        calculate_expression("test.txt");
        char *true_data_4[1] = {"5 / 2 = 2.500"};
        assert(assert_file("test.txt", true_data_4));

        test = fopen("test.txt", "w");
        fprintf(test, "2 + 5 - 3");
        fclose(test);
        calculate_expression("test.txt");
        char *true_data_5[1] = {"2 + 5 - 3 = 4.000"};
        assert(assert_file("test.txt", true_data_5));

        test = fopen("test.txt", "w");
        fprintf(test, "2 * 2 - 1");
        fclose(test);
        calculate_expression("test.txt");
        char *true_data_6[1] = {"2 * 2 - 1 = 3.000"};
        assert(assert_file("test.txt", true_data_6));

        test = fopen("test.txt", "w");
        fprintf(test, "2 * 2 * 2");
        fclose(test);
        calculate_expression("test.txt");
        char *true_data_7[1] = {"2 * 2 * 2 = 8.000"};
        assert(assert_file("test.txt", true_data_7));

        test = fopen("test.txt", "w");
        fprintf(test, "2 + 2 * 2");
        fclose(test);
        calculate_expression("test.txt");
        char *true_data_8[1] = {"2 + 2 * 2 = 6.000"};
        assert(assert_file("test.txt", true_data_8));
    }

    void save_only_words_with_sequence(char *file_name, char *sequence) {
        FILE *file;
        file = fopen(file_name, "r");
        size_t sequence_size = strlen_(sequence);
        char strings[MAX_STRINGS_NUMBER][MAX_STRING_LENGTH];
        size_t size = 0;
        while (!feof(file)) {
            fgets(strings[size], MAX_STRING_LENGTH, file);
            size++;
        }
        fclose(file);
        file = fopen(file_name, "w");
        bool is_first_saved_word = true;
        for (size_t i = 0; i < size; i++) {
            size_t word_size = strlen_(strings[i]);
            for (size_t j = 0; j < word_size - sequence_size; j++) {
                char *word = strings[i] + j;
                if (*sequence == *word) {
                    int coincidences = 0;
                    for (char *s1 = sequence, *s2 = word; *s1 != '\0'; s1++, s2++) {
                        if (*s1 == *s2) {
                            coincidences++;
                        }
                    }
                    if (coincidences == sequence_size) {
                        char string[MAX_STRING_LENGTH];
                        copy(strings[i], strings[i] + strlen_(strings[i]) - 1,
                             string);
                        if (is_first_saved_word) {
                            fprintf(file, "%s", string);
                            is_first_saved_word = false;
                        } else {
                            fprintf(file, "\n%s", string);
                        }
                    }
                }
            }
        }
        fclose(file);
    }
    void test_save_only_words_with_sequence() {
        FILE *test;
        test = fopen("test.txt", "w");
        fprintf(test, "zero\nerror\nhero\nhouse");
        fclose(test);
        save_only_words_with_sequence("test.txt", "ero");
        char *true_data[] = {"zero\n", "hero"};
        assert(assert_file("test.txt", true_data));
    }

    void save_only_longest_word_in_string(char *file_name) {
        FILE *file;
        file = fopen(file_name, "r");
        if (file == NULL) {
            perror(file_name);
            return;
        }
        char strings[MAX_STRINGS_NUMBER][MAX_STRING_LENGTH];
        size_t size = 0;
        while (!feof(file)) {
            fgets(strings[size], MAX_STRING_LENGTH, file);
            size++;
        }
        fclose(file);
        file = fopen(file_name, "w");
        for (size_t i = 0; i < size; i++) {
            BagOfWords words;
            getBagOfWords(&words, strings[i]);
            size_t max_len = 0;
            char longest_word[MAX_STRING_LENGTH];
            for (size_t j = 0; j < words.size; j++) {
                char word[MAX_STRING_LENGTH];
                wordDescriptorToString(words.words[j], word);
                size_t len = strlen_(word);
                if (len > max_len) {
                    max_len = len;
                    copy(word, word + len, longest_word);
                }
            }
            if (i == 0) {
                fprintf(file, "%s", longest_word);
            } else {
                fprintf(file, "\n%s", longest_word);
            }
        }
        fclose(file);
    }
    void test_save_only_longest_word_in_string() {
        FILE *test;
        test = fopen("test.txt", "w");
        fprintf(test, "one two three eleven\nkeyboard button switch\nHello
        Goodbye\naboba");
        fclose(test);
        save_only_longest_word_in_string("test.txt");
        char *true_data[] = {"eleven\n", "keyboard\n", "Goodbye\n", "aboba"};
        assert(assert_file("test.txt", true_data));
    }

