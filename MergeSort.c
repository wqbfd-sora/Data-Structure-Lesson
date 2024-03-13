//
// Created by KaguraSora on 2024/3/13.
//

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int *randomData(int number, int arr[]);

void initial(int number, int origin[], int copy[]);

void merge(int *arr1, int *arr2, int result[], int length, int length2);

void mergeSort(int *arr, int *re, int startIndex, int endIndex);

int main() {

    int number = 10;
    int arr[number];
    int arrCopy[number];
    randomData(number, arr);
    //归并
    struct timeb startTime, endTime;
    initial(number, arr, arrCopy);
    int re[number];
    mergeSort(arrCopy, re, 0, number - 1);
    ftime(&startTime);
    ftime(&endTime);
    double mergeTime = ((double) (endTime.time - startTime.time) +
                        (double) (endTime.millitm - startTime.millitm) / 1000);
    printf("%.3lf\n", mergeTime);

}

void mergeSort(int *arr, int *re, int startIndex, int endIndex) {
    //递归分组
    printf("1 ");
    if (startIndex == endIndex) {
        re[0] = arr[startIndex];
        return;
    }
    int middle = (startIndex + endIndex) / 2;
    int in1[middle - startIndex + 1];
    mergeSort(arr, in1, startIndex, middle);
    int in2[endIndex - middle];
    mergeSort(arr, in2, middle + 1, endIndex);
    merge(in1, in2, re, middle - startIndex + 1, endIndex - middle);
}

void merge(int *arr1, int *arr2, int *result, int length1, int length2) {
    int point1 = 0;
    int point2 = 0;
    int resultPoint = 0;
    while (!(point1 == length1 && point2 == length2)) {
        if (point1 == length1) {
            result[resultPoint] = arr2[point2];
            point2++, resultPoint++;
            continue;
        }
        if (point2 == length2) {
            result[resultPoint] = arr1[point1];
            point1++, resultPoint++;
            continue;
        }
        if (arr1[point1] < arr2[point2]) {
            result[resultPoint] = arr1[point1];
            point1++, resultPoint++;
        } else {
            result[resultPoint] = arr2[point2];
            point2++, resultPoint++;
        }
    }
}

void initial(int number, int origin[], int copy[]) {
    for (int i = 0; i < number; ++i) {
        copy[i] = origin[i];
    }
}

int *randomData(int number, int arr[]) {
    srand((unsigned int) (time(NULL)));
    for (int i = 0; i < number; ++i) {
        arr[i] = rand();
    }
    return arr;
}
