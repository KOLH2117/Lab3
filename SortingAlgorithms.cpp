#include "SortingAlgorithms.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h> 
#include <string>
#include <stdlib.h>
using namespace std;

void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//-------------------------->Insertion Sort
void insertionSort(int arr[], int n, double& running_time, int& count_compare) {
    clock_t start, end;
    start = clock();

    int key, j;
    for (int i = 1; (++count_compare) && i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (((++count_compare) && j >= 0) && ((++count_compare) && arr[j] > key)) {
            //count_compare += 2;
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }

    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Insertion Sort

//-------------------------->Slection Sort
void selectionSort(int arr[], int n, double& running_time, int& count_compare) {
    clock_t start, end;
    start = clock();
    for (int i = 0; (++count_compare) && i <= n - 2; i++) {
        int iMin = i;
        for (int j = i + 1; (++count_compare) && j < n; j++) {
            if ((++count_compare) && arr[j] < arr[iMin]) {
                iMin = j;
            }
        }
        swap(arr[i], arr[iMin]);
    }
    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Slection Sort

//-------------------------->Bubble Sort
void bubbleSort(int arr[], int n, double& running_time, int& count_compare) {
    clock_t start, end;
    start = clock();

    for (int i = 0; (++count_compare) && i < n - 1; i++) {
        for (int j = 0; (++count_compare) && j < n - i - 1; j++) {
            if ((++count_compare) && arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }

    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Bubble Sort

//-------------------------->Heap Sort
void sift(int arr[], int left, int right, double& running_time, int& count_compare) {
    int i = left;
    int j = 2 * i;
    int x = arr[i];

    while ((++count_compare) && j <= right) {
        if ((++count_compare) && j < right)
            if ((++count_compare) && arr[j] > arr[j + 1])
                j++;
        if ((++count_compare) && x <= arr[j])
            break;
        arr[i] = arr[j];
        i = j;
        j = 2 * i;
    }

    arr[i] = x;
}

void createHeap(int arr[], int n, double& running_time, int& count_compare) {
    //Make the array into a heap

    int left = (n - 1) / 2;
    while ((++count_compare) && left > -1) {
        sift(arr, left, n - 1, running_time, count_compare);
        left--;
    }
}

void heapSort(int arr[], int n, double& running_time, int& count_compare) {
    clock_t start, end;
    start = clock();

    createHeap(arr, n, running_time, count_compare);

    int right = n - 1;

    while ((++count_compare) && right > 0) {
        swap(arr[0], arr[right]);
        right--;
        sift(arr, 0, right, running_time, count_compare);
    }

    for (int i = 0; (++count_compare) && i < n / 2; i++) {
        swap(arr[i], arr[n - 1 - i]);
    }

    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Heap Sort

//-------------------------->Quick Sort
int partition(int arr[], int low, int high, int& count_compare)
{
    int pivot = arr[high];
    int left = low;
    int right = high - 1;
    while (true)
    {
        while ((++count_compare && left <= right) && (++count_compare && arr[left] < pivot))
        {
            left++;
        }

        while ((++count_compare && right >= left) && (++count_compare && arr[right] > pivot))
        {
            right--;
        }


        if (++count_compare && left >= right)
            break;

        swap(arr[left], arr[right]);
        left++;
        right--;
    }
    swap(arr[left], arr[high]);
    return left;
}

void Sort(int arr[], int low, int high, int& count_compare)
{
    if (++count_compare && low < high)
    {
        int pi = partition(arr, low, high, count_compare);

        Sort(arr, low, pi - 1, count_compare);
        Sort(arr, pi + 1, high, count_compare);
    }
}

void QuickSort(int arr[], int n, double& time_use, int& count_compare)
{
    count_compare = 0;
    time_use = 0;

    clock_t start, end;

    start = clock();

    Sort(arr, 0, n - 1, count_compare);

    end = clock();

    time_use = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Quick Sort
