#include <stdio.h>

void produce_results(int *actual, int *expected, char *testing) {
    printf("Testing: %s\n", testing); // not sure if can actually do printf from core
    int wrong = 0;
    for (int i = 0; i < 50; i++) {
        if (actual[i] != expected[i]) {
            printf("Value for i = %d is %d, but should be %d.\n", i, actual[i], expected[i]); 
            wrong++;
        }
    }
    if (wrong == 0) {
        printf("All tests in %s successful\n", testing);
    }
}

int main() {
    int actual[50];
    int expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49};
    for (int i = 0; i < 50; i++) {
        actual[i] = i;
        expected[i] = i;
    }
    produce_results(actual, expected, "Set values");

    int expected2[] = {3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39, 41, 43, 45, 47, 49, 51, 53, 55, 57, 59, 61, 63, 65, 67, 69, 71, 73, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93, 95, 97, 48, 49};
    for (int i = 0; i < 48; i++) {
        actual[i] = actual[i+1] + actual[i+2];
    }
    produce_results(actual, expected2, "Adding");

    int expected3[] = {3, 5, 2, -3, -5, -2, 3, 5, 2, -3, -5, -2, 3, 5, 2, -3, -5, -2, 3, 5, 2, -3, -5, -2, 3, 5, 2, -3, -5, -2, 3, 5, 2, -3, -5, -2, 3, 5, 2, -3, -5, -2, 3, 5, 2, -3, -5, -2, 3, 5};
    for (int i = 2; i < 50; i++) {
        actual[i] = actual[i-1] - actual[i-2];
    }
    produce_results(actual, expected3, "Subtracting");

    int expected4[] = {10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 10, -6, 15, 3, 5};
    for (int i = 0; i < 48; i++) {
        actual[i] = actual[i+1] * actual[i+2];
    }
    produce_results(actual, expected4, "Multiplying");
}