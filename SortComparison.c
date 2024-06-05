//
// Created by KaguraSora on 2024/3/13.
//
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int *randomData(int number, int arr[]);

double bubbleSort(int number, int arr[]);

double insertSort(int number, int arr[]);

double selectionSort(int number, int arr[]);

int quickSort(int *a, int low, int high);

void initial(int number, int origin[], int copy[]);

void merge(int *arr1, int *arr2, int result[], int length, int length2);

void mergeSort(int *arr, int *re, int startIndex, int endIndex);


int main() {
    int number = 6000;
    int arr[number];
    int arrCopy[number];
    randomData(number, arr);
    initial(number, arr, arrCopy);
    double bubbleTime = bubbleSort(number, arrCopy);
    initial(number, arr, arrCopy);
    double insertTime = insertSort(number, arrCopy);
    initial(number, arr, arrCopy);
    double selectionTime = selectionSort(number, arrCopy);\
    //快排
    initial(number, arr, arrCopy);
    struct timeb startTime1, endTime1;
    ftime(&startTime1);
    quickSort(arrCopy, 0, number - 1);
    ftime(&endTime1);
    double quickTime = ((double) (endTime1.time - startTime1.time) +
                        (double) (endTime1.millitm - startTime1.millitm) / 1000);
    //归并
    struct timeb startTime2, endTime2;
    initial(number, arr, arrCopy);
    int re[number];
    ftime(&startTime2);
    mergeSort(arrCopy, re, 0, number - 1);
    ftime(&endTime2);
    double mergeTime = ((double) (endTime2.time - startTime2.time) +
                        (double) (endTime2.millitm - startTime2.millitm) / 1000);
    printf("\n\n\n");
    printf("%s%.3lf\n", "bubbleTime:", bubbleTime);
    printf("%s%.3lf\n", "insertTime:", insertTime);
    printf("%s%.3lf\n", "selectionTime:", selectionTime);
    printf("%s%.3lf\n", "quickTime:", quickTime);
    printf("%s%.3lf\n", "mergeTime:", mergeTime);

}

void initial(int number, int *origin, int *copy) {
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

double bubbleSort(int number, int arr[]) {
    struct timeb startTime, endTime;
    ftime(&startTime);
    for (int i = 0; i < number; ++i) {
        for (int j = 0; j < number - i - 1; ++j) {
            if (arr[j] >= arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    ftime(&endTime);
    return ((double) (endTime.time - startTime.time) + (double) (endTime.millitm - startTime.millitm) / 1000);
}

double insertSort(int number, int arr[]) {
    struct timeb startTime, endTime;
    ftime(&startTime);
    for (int i = 1; i < number; ++i) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            } else {
                break;
            }
        }
    }
    ftime(&endTime);
    return ((double) (endTime.time - startTime.time) + (double) (endTime.millitm - startTime.millitm) / 1000);
}

double selectionSort(int number, int arr[]) {
    struct timeb startTime, endTime;
    ftime(&startTime);
    for (int i = 0; i < number - 1; i++) {
        for (int j = i + 1; j < number; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    ftime(&endTime);
    return ((double) (endTime.time - startTime.time) + (double) (endTime.millitm - startTime.millitm) / 1000);
}

int quickSort(int *a, int low, int high) {
    int i = low;    //第一位
    int j = high;    //最后一位
    int key = a[i]; //将第一个数作为基准值-- 先找到一个基准值

    while (i < j) {
        while (i < j && a[j] >= key) {
            j--;
        }
        a[i] = a[j];

        while (i < j && a[i] <= key) {
            i++;
        }
        a[j] = a[i];
    }
    a[i] = key;
    if (i - 1 > low) {
        quickSort(a, low, i - 1);
    }
    if (i + 1 < high) {
        quickSort(a, i + 1, high);
    }
    return 0;
}

void mergeSort(int *arr, int *re, int startIndex, int endIndex) {
    //递归分组
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

