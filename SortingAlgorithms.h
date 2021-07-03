
#ifndef _SORTING_ALGORITHMS_H
#define _SORTING_ALGORITHMS_H
//---------------FUNCTION
void swap(int& a, int& b);
void printArray(int* arr, int n);

//---------------ALGORITHM SORTING
void insertionSort(int arr[], int n, double& running_time, int& count_compare);
void selectionSort(int arr[], int n, double& running_time, int& count_compare);
void bubbleSort(int arr[], int n, double& running_time, int& count_compare);

//-------------------------->Heap Sort
void sift(int arr[], int left, int right, double& running_time, int& count_compare);
void createHeap(int arr[], int n, double& running_time, int& count_compare);
void heapSort(int arr[], int n, double& running_time, int& count_compare);
//-------------------------->Heap Sort

//-------------------------->Quick Sort
int partition(int arr[], int low, int high, int& count_compare);
void Sort(int arr[], int low, int high, int& count_compare);
void QuickSort(int arr[], int n, double& time_use, int& count_compare);
//-------------------------->Quick Sort
#endif