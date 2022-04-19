#include "lab02.h"
#include "unit_test_framework.h"

const int SIZE = 6;
const int MAX_SIZE = 1000;

void compare_arrays(const int test[], const int n1, const int exp[], const int n2)
{
    ASSERT_TRUE(n1 == n2);
    const int *ptr2 = exp;
    for (const int *ptr1 = test; ptr1 < (test + n1); ++ptr1) {
	   ASSERT_EQUAL(*ptr1, *ptr2);
	   ++ptr2;
    }
}

TEST(slideRight) {
    int test_arr[SIZE] = { 0, 1, 3, 5, 7, 9};
    const int expected_arr[SIZE] = { 9, 0, 1, 3, 5, 7};
    slideRight(test_arr, SIZE);
    compare_arrays(test_arr, SIZE, expected_arr, SIZE);
}

TEST(slideRight2) {
    int test_arr2[MAX_SIZE];
    int expected_arr2[MAX_SIZE];
    for (int i = 0; i < MAX_SIZE; ++i) {
	   test_arr2[i] = 0;
	   expected_arr2[i] = 0;
    }
    test_arr2[500] = 25;
    expected_arr2[501] = 25;

    slideRight(test_arr2, MAX_SIZE);
    compare_arrays(test_arr2, MAX_SIZE, expected_arr2, MAX_SIZE);
}

TEST(slideRight3) {
    int test_arr[1] = {99};
    const int expected_arr[1] = {99};
    slideRight(test_arr, 1);
    compare_arrays(test_arr, 1, expected_arr, 1);
}

TEST(slideRight4) {
    int test_arr[3] = { 1, 2, 3};
    const int expected_arr[3] = { 1, 2, 3 };
    slideRight(test_arr, 3);
    slideRight(test_arr, 3);
    slideRight(test_arr, 3);
    compare_arrays(test_arr, 3, expected_arr, 3);
}

TEST(flip) {
    int test_arr[SIZE] = { 2, 5, 6, 9, 10, 13};
    const int expected_arr[SIZE] = { 13, 10, 9, 6, 5, 2 };
    flip(test_arr, SIZE);
    compare_arrays(test_arr, SIZE, expected_arr, SIZE);
}

TEST(flip2) {
    int test_arr2[MAX_SIZE];
    int expected_arr2[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; ++i) { // Fill with '0'
	   test_arr2[i] = 0;
	   expected_arr2[i] = 0;
    }
    for (int j = 0; j < MAX_SIZE / 2; ++j) {	   // Fill first 500 with '1'
	   test_arr2[j] = 1;
    }
    for (int j = MAX_SIZE / 2; j < MAX_SIZE; ++j) { // Fill last 500 with '1'
	   expected_arr2[j] = 1;
    }
    flip(test_arr2, MAX_SIZE);
    compare_arrays(test_arr2, MAX_SIZE, expected_arr2, MAX_SIZE);
}

TEST(flip3) {
    int test_arr[1] = { 99 };
    const int expected_arr[1] = { 99 };
    flip(test_arr, 1);
    compare_arrays(test_arr, 1, expected_arr, 1);
}

TEST(flip4) {
    int test_arr[3] = { 1, 2, 3 };
    const int expected_arr[3] = { 3, 2, 1 };
    flip(test_arr, 3);
    flip(test_arr, 3);
    flip(test_arr, 3);
    compare_arrays(test_arr, 3, expected_arr, 3);
}

TEST_MAIN()