#pragma once
#ifndef _SORTING_ALGORITHMS_H_
#define _SORTING_ALGORITHMS_H_
//---------------FUNCTION
void swap(int& a, int& b);
void printArray(int* arr, int n);
//---------------ALGORITHM SORTING
void insertionSort(int arr[], int n, double& running_time, unsigned int& count_compare);
void selectionSort(int arr[], int n, double& running_time, unsigned int& count_compare);
void bubbleSort(int arr[], int n, double& running_time, unsigned int& count_compare);

//-------------------------->Heap Sort
void sift(int arr[], int left, int right, double& running_time, unsigned int& count_compare);
void createHeap(int arr[], int n, double& running_time, unsigned int& count_compare);
void heapSort(int arr[], int n, double& running_time, unsigned int& count_compare);
//-------------------------->Heap Sort

//-------------------------->Quick Sort
int partition(int arr[], int low, int high, unsigned int& count_compare);
void Sort(int arr[], int low, int high, unsigned int& count_compare);
void quickSort(int arr[], int n, double& time_use, unsigned int& count_compare);
//-------------------------->Quick Sort

//-------------------------->Flash Sort
void flashSort(int arr[], int n, double& running_time, unsigned int& count_compare);
//-------------------------->Flash Sort
#endif