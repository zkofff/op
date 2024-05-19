#include <stdio.h>
#include "file.h"
#include <malloc.h>
#include "libs/data_structures/string/string_.h"
#include "libs/data_structures/matrix/matrix.h"
#include <stdbool.h>
#include <assert.h>

//№1

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
    char *true_data[] ={"3\n", "1 4 7\n", "2 5 8\n", "3 6 9\n", "0\n", "2\n", "11 3\n", "15 70\n", "1\n", "54"};
            assert(assert_file("test.txt", true_data));
    }
    void test_file1(){
        test_make_matrix_storage_by_columns();
    }

    //№2

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

    //№3

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
            if ((*elements.words[1].begin == '+' || *elements.words[1].begin == '-') && (*elements.words[3].begin == '*' || *elements.words[3].begin == '/')) {
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

    //№4

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

    //№5

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

    //№6

    void remove_polynomials_if_x_sqrt_root(char *file_name, int *size, int x) {
        FILE *file;
        file = fopen(file_name, "rb");
        if (file == NULL) {
            perror(file_name);
            return;
        }
        polynomial polynomials[*size];
        fread(polynomials, sizeof(polynomial), *size, file);
        fclose(file);
        file = fopen(file_name, "wb");
        polynomial result[*size];
        int result_size = 0;
        for (size_t i = 0; i < *size; i++) {
            if (polynomials[i].coefficient * pow_(x, polynomials[i].power) != x*x ||
                polynomials[i].power == 0) {
                result[result_size].power = polynomials[i].power;
                result[result_size++].coefficient = polynomials[i].coefficient;
            }
        }
        fwrite(result, sizeof(polynomial), result_size, file);
        *size = result_size;
        fclose(file);
    }
    void test_remove_polynomials_if_x_sqrt_root() {
        polynomial polynomials[] = {{3, 2}, {2, 1}, {1, -2}, {0, 3}};
        int size = 4;
        int x = 3;
        FILE *test;
        test = fopen("test.bin", "wb");
        fwrite(polynomials, sizeof(polynomial), size, test);
        fclose(test);
        polynomial true_data[] = {{3, 2},{1, -2}, {0, 3}};
        remove_polynomials_if_x_sqrt_root("test.bin", &size, x);
        assert(size == 3);
        polynomial results[size];
        test = fopen("test.bin", "rb");
        fread(results, sizeof(polynomial), size, test);
        for (size_t i = 0; i < size; i++) {
            assert(results[i].power == true_data[i].power && results[i].coefficient == true_data[i].coefficient);
        }
    }

    //№7

    void sort_negative_after_positive(char *file_name, size_t size) {
        FILE *file;
        file = fopen(file_name, "rb");
        int elements[size];
        fread(elements, sizeof(int), size, file);
        fclose(file);
        int positive_elements[size];
        int negative_elements[size];
        size_t positive_elements_size = 0;
        size_t negative_elements_size = 0;
        for (size_t i = 0; i < size; i++) {
            if (elements[i] < 0) {
                negative_elements[negative_elements_size++] = elements[i];
            } else {
                positive_elements[positive_elements_size++] = elements[i];
            }
        }
        for (size_t i = 0; i < positive_elements_size; i++) {
            elements[i] = positive_elements[i];
        }
        for (size_t i = 0; i < negative_elements_size; i++) {
            elements[positive_elements_size + i] = negative_elements[i];
        }
        file = fopen(file_name, "wb");
        fwrite(elements, sizeof(int), size, file);
        fclose(file);
    }
    void test_sort_negative_after_positive() {
        int elements[10] = {1, 4, -4, -3, -64, 43, -5, 2, 3, -5};
        FILE *test;
        test = fopen("test.bin", "wb");
        fwrite(elements, sizeof(int), 10, test);
        fclose(test);
        sort_negative_after_positive("test.bin", 10);
        test = fopen("test.bin", "rb");
        fread(elements, sizeof(int), 10, test);
        fclose(test);
        int true_data[10] = {1, 4, 43, 2, 3, -4, -3, -64, -5, -5};

        for (size_t i = 0; i < 10; i++) {
            assert(true_data[i] == elements[i]);
        }
    }

    //№8

    void transpose_non_symmetric_matrices(char *file_name, size_t size) {
        FILE *file;
        matrix matrices[size];
        file = fopen(file_name, "rb");
        fread(matrices, sizeof(matrix), size, file);
        fclose(file);
        for (size_t i = 0; i < size; i++) {
            if (!isSymmetricMatrix(&matrices[i])) {
                transposeMatrix(&matrices[i]);
            }
        }
        file = fopen(file_name, "wb");
        fwrite(matrices, sizeof(matrix), size, file);
        fclose(file);
    }
    void test_transpose_non_symmetric_matrices() {
        matrix matrix_1 = createMatrixFromArray((int[]) {1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
        matrix matrix_2 = createMatrixFromArray((int[]) {1, 2, 2, 1}, 2, 2);
        matrix matrices[] = {matrix_1, matrix_2};
        FILE *test;
        test = fopen("test.txt", "wb");
        fwrite(matrices, sizeof(matrix), 2, test);
        fclose(test);
        transposeMatrix(&matrix_1);
        matrix true_data[] = {matrix_1, matrix_2};
        transpose_non_symmetric_matrices("test.txt", 2);
        test = fopen("test.txt", "rb");
        fread(matrices, sizeof(matrix), 2, test);
        fclose(test);
        for (size_t i = 0; i < 2; i++) {
            assert(areTwoMatricesEqual(&matrices[i], &true_data[i]));
        }
    }

    //№9

    void sort_sportsmen(sportsman sportsmen[], size_t size) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < i; j++) {
                if (sportsmen[i].best_result > sportsmen[j].best_result) {
                    sportsman temp = sportsmen[i];
                    sportsmen[i] = sportsmen[j];
                    sportsmen[j] = temp;
                }
            }
        }
    }
    void make_team(char *file_name, size_t size, size_t players_need) {
        if (size > players_need) {
            FILE *file;
            sportsman sportsmen[size];
            file = fopen(file_name, "rb");
            fread(sportsmen, sizeof(sportsman), size, file);
            fclose(file);
            sort_sportsmen(sportsmen, size);
            sportsman team[players_need];
            for (size_t i = 0; i < players_need; i++) {
                team[i] = sportsmen[i];
            }
            file = fopen(file_name, "wb");
            fwrite(team, sizeof(sportsman), players_need, file);
            fclose(file);
        }
    }
    void test_make_team() {
        sportsman sportsmen[] = {{"sportsman 1", 13}, {"sportsman 2", 15}, {"sportsman 3", 12}, {"sportsman 4", 17}, {"sportsman 5", 16}};
        FILE *test;
        test = fopen("test.bin", "wb");
        fwrite(sportsmen, sizeof(sportsman), 5, test);
        fclose(test);
        make_team("test.bin", 5, 3);
        sportsman team[3];
        test = fopen("test.bin", "rb");
        fread(team, sizeof(sportsman), 3, test);
        fclose(test);
        sportsman true_data[] = {{"sportsman 4", 17}, {"sportsman 5", 16}, {"sportsman 2", 15}};

        for (size_t i = 0; i < 3; i++) {
            assert(true_data[i].FIO == team[i].FIO && true_data[i].best_result == team[i].best_result);
        }
    }

    //№10

void update_products_information(char *products_file_name, size_t *products_size,
                                 char *orders_file_name, size_t orders_size) {
    FILE *file;
    product products[*products_size];
    order orders[orders_size];
    size_t products_left_size = 0;
    product products_left[*products_size];
    file = fopen(products_file_name, "rb");
    fread(products, sizeof(product), *products_size, file);
    fclose(file);
    file = fopen(orders_file_name, "rb");
    fread(orders, sizeof(order), orders_size, file);
    fclose(file);
    for (size_t j = 0; j < *products_size; j++) {
        for (size_t i = 0; i < orders_size; i++) {
            if (products[j].name == orders[i].name) {
                if (products[j].quantity > orders[i].quantity) {
                    products_left[products_left_size].name = orders[i].name;
                    products_left[products_left_size].unit_price =
                            products[j].unit_price;
                    products_left[products_left_size].quantity =
                            products[j].quantity - orders[i].quantity;
                    products_left[products_left_size].total_price =
                            products_left[products_left_size].unit_price *
                            products_left[products_left_size].quantity;
                    products_left_size++;
                }
            }
        }
    }
    *products_size = products_left_size;
    file = fopen(products_file_name, "wb");
    fwrite(products_left, sizeof(product), products_left_size, file);
    fclose(file);
}
void test_update_products_information() {
    product products[] = {{"long sword", 15, 7, 105},
                          {"battle axe", 10, 5, 50},
                          {"long spear", 10, 8, 80},
                          {"long bow",   50, 4, 200}};
    size_t products_size = 4;
    order orders[] = {{"long sword", 4},
                      {"battle axe", 5},
                      {"long spear", 3},
                      {"long bow",   5}};
    FILE *test;
    test = fopen("test.bin", "wb");
    fwrite(products, sizeof(product), 4, test);
    fclose(test);
    test = fopen("test2.bin", "wb");
    fwrite(orders, sizeof(order), 4, test);
    fclose(test);
    update_products_information("test.bin", &products_size, "test2.bin", 4);
    test = fopen("test.bin", "rb");
    product products_left[products_size];
    product true_data[] = {{"long sword", 15, 3, 45},
                           {"long spear", 10, 5, 50}};
    fread(products_left, sizeof(product), products_size, test);
    fclose(test);
    assert(products_size == 2);
    for (size_t i = 0; i < products_size; i++) {
        assert(products_left[i].name == true_data[i].name &&
               products_left[i].quantity == true_data[i].quantity &&
               products_left[i].total_price == true_data[i].total_price);
    }
}

