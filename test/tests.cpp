// Copyright 2021 NNTU-CS

#include <time.h>
#include <stdlib.h>

#include "gtest/gtest.h"

#define ARRSIZE1 100000
#define ARRSIZE2 200000

int countPairs1(int *arr, int len, int value);
int countPairs2(int *arr, int len, int value);
int countPairs3(int *arr, int len, int value);

void generateSorted(int *arr, int min, int max, int len) {
    int value = 0, j = 0;
    for (int i = 0; i < len; i++) {
        value = min + rand() % (max - min + 1);
        j = i - 1;
        while (j >= 0 && arr[j] > value) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = value;
    }
}


TEST(lab2, test1) {
    int *arr = new int[ARRSIZE1];
    generateSorted(arr, 0, 100, ARRSIZE1);
    int count1 = countPairs1(arr, ARRSIZE1, 50);
    int count2 = countPairs2(arr, ARRSIZE1, 50);
    int count3 = countPairs3(arr, ARRSIZE1, 50);
    EXPECT_TRUE((count1 == count2) && (count1 == count3) && (count2 == count3));
    delete[] arr;
}
TEST(lab2, test2) {
    int *arr = new int[ARRSIZE2];
    generateSorted(arr, 0, 100, ARRSIZE2);
    int count1 = countPairs1(arr, ARRSIZE2, 50);
    int count2 = countPairs2(arr, ARRSIZE2, 50);
    int count3 = countPairs3(arr, ARRSIZE2, 50);
    EXPECT_TRUE((count1 == count2) && (count1 == count3) && (count2 == count3));
    delete[] arr;
}
TEST(lab2, test3) {
    clock_t begin1, end1, begin2, end2, begin3, end3;
    clock_t t1, t2, t3;
    int *arr = new int[ARRSIZE1];
    generateSorted(arr, 0, 100, ARRSIZE1);
    begin1 = clock();
    int count1 = countPairs1(arr, ARRSIZE1, 50);
    end1 = clock();
    begin2 = clock();
    int count2 = countPairs2(arr, ARRSIZE1, 50);
    end2 = clock();
    begin3 = clock();
    int count3 = countPairs3(arr, ARRSIZE1, 50);
    end3 = clock();
    t1 = end1 - begin1;
    t2 = end2 - begin2;
    t3 = end3 - begin3;
    EXPECT_TRUE(t2 < t3 && t3 < t1);
    delete[] arr;
}
