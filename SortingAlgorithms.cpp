#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h> 
#include <string>
#include <stdlib.h>

#include "SortingAlgorithms.h"

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
void insertionSort(int arr[], int n, double& running_time, unsigned int& count_compare) {
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
void selectionSort(int arr[], int n, double& running_time, unsigned int& count_compare) {
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
void bubbleSort(int arr[], int n, double& running_time, unsigned int& count_compare) {
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

//-------------------------->Shaker Sort

//-------------------------->Shaker Sort

//-------------------------->Shell Sort
void shellSort(int* arr, int n, double &running_time,unsigned int &count_compare)
{
    clock_t start, end;

    start = clock();
    for (int gap = n / 2;++count_compare && gap > 0; gap /= 2)
    {
        for (int i = gap;++count_compare && i < n; i++)
        {
            int temp = arr[i];
            int j;
            for (j = i; (++count_compare && j >= gap) && (++count_compare && arr[j - gap] > temp); j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }

    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Shell Sort


//-------------------------->Heap Sort
void sift(int arr[], int left, int right, double& running_time, unsigned int& count_compare) {
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

void createHeap(int arr[], int n, double& running_time, unsigned int& count_compare) {
    //Make the array into a heap
    int left = (n - 1) / 2;
    while ((++count_compare) && left > -1) {
        sift(arr, left, n - 1, running_time, count_compare);
        left--;
    }
}

void heapSort(int arr[], int n, double& running_time, unsigned int& count_compare) {
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
//-------------------------->Merge Sort

//-------------------------->Merge Sort

//-------------------------->Quick Sort
// int partition(int arr[], int low, int high, int& count_compare)
// {
//     int pivot = arr[high];
//     int left = low;
//     int right = high - 1;

//     while (true)
//     {
//         while (((++count_compare) &&left <= right )&& (++count_compare && arr[left] < pivot)){
//             left++;
//         }

//         while (((++count_compare) && right >= left )&& (++count_compare && arr[right] > pivot)){
//             right--;
//         }

//         if (++count_compare && left >= right)
//             break;

//         swap(arr[left], arr[right]);
//         left++;
//         right--;
//     }

//     swap(arr[left], arr[high]);
//     return left;
// }

int partition(int arr[], int low, int high, unsigned int& count_compare)
{
    int pivot = arr[(low + high) / 2];
	int i = low;
	int j = high;
	int tmp;
	while (++count_compare &&i <= j)
	{
		while (++count_compare && arr[i] < pivot)
			i++;
		while (++count_compare && arr[j] > pivot)
			j--;
		if (++count_compare && i <= j) {
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
	return i;
}

void Sort(int arr[], int low, int high, unsigned int& count_compare)
{
    if (++count_compare && low < high)
    {
        int pi = partition(arr, low, high, count_compare);

        Sort(arr, low, pi - 1, count_compare);
        Sort(arr, pi + 1, high, count_compare);
    }
}

void quickSort(int arr[], int n, double& running_time,unsigned int& count_compare)
{
    clock_t start, end;
    start = clock();

    Sort(arr, 0, n - 1, count_compare);

    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Quick Sort

//-------------------------->Counting Sort
void countingSort(int arr[], int n, double& time_use,unsigned int& count_compare)
{
    clock_t start, end;
    start = clock();

    int *a_fake = new int [n];
    int max = arr[0];
    int min = arr[0];
    int i;
    for (i = 1; ++count_compare && i < n; i++)
    {
        if (++count_compare && arr[i] > max)
            max = arr[i];
        else if (++count_compare && arr[i] < min)
            min = arr[i];
    }

    int* count_array = new int[max - min + 1];
    for (i = 0;++count_compare && i < (max - min + 1); i++)
        count_array[i] = 0;

    for (i = 0;++count_compare && i < n; i++)
        count_array[arr[i] - min]++;

    for (i = 1; ++count_compare && i < (max - min + 1); i++)
        count_array[i] += count_array[i - 1];

    for (i = 0;++count_compare && i < n; i++)
    {
        a_fake[count_array[arr[i] - min] - 1] = arr[i];
        count_array[arr[i] - min]--;
    }

    for (i = 0;++count_compare && i < n; i++)
        arr[i] = a_fake[i];

    delete[] a_fake;
    delete[] count_array;
    end = clock();
    time_use = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Counting Sort

//-------------------------->Radix Sort
void radixSort(int a[], int n, double& running_time,unsigned int& count_compare)
{
    clock_t start, end;
    start = clock();
    //Find maximum value in a[]
    int maxValue = a[0];
    for (int i = 1; ++count_compare && i < n; i++)
    {
        if (a[i] > maxValue)
            maxValue = a[i];
    }
    // Do counting sort for every digit. Note that instead
    // of passing digit number, j is passed. j is 10^i
    // where i is current digit number
    for (int j = 1; ++count_compare && maxValue / j > 0; j *= 10)
    {
        //Created Aftersorted to cout;
        int* Aftersorted = new int[n];
        int k = 0;
        int count[10] = { 0 };
        // Store count of occurrences in count[]
        for (int k = 0; ++count_compare && k < n; k++)
        {
            count[(a[k] / j) % 10]++;
        }
        // Change count[k] so that count[k] now contains actual
        //  position of this digit in output[]
        for (k = 1; ++count_compare && k < 10; k++)
        {
            count[k] += count[k - 1];
        }
        // Build the Aftersorted array
        for (k = n - 1; ++count_compare && k >= 0; k--) {
            Aftersorted[count[(a[k] / j) % 10] - 1] = a[k];
            count[(a[k] / j) % 10]--;
        }
        // Copy the output array to a[], so that a[] now
        // contains sorted numbers according to current digit
        for (k = 0;++count_compare && k < n; k++)
            a[k] = Aftersorted[k];
    }
    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Radix Sort

//-------------------------->Flash Sort
void flashSort(int arr[],int n,double& running_time, unsigned int& count_compare){
    clock_t start, end;
    start = clock();

    int m = int(0.45*n);

    //------->Find min value and max index
    int minVal = 0;
    int maxVal = 0;
    int i = 0;
    if(++count_compare && n % 2 == 0){
        if(++count_compare && arr[0] < arr[1]){
            minVal = arr[0];
            maxVal = arr[1];
        }
        else{
            minVal = arr[1];
            maxVal = arr[0];
        }
        i = 2;
    }
    else{
        minVal = arr[0];
        maxVal = arr[0];
        i = 1;
    }
    while(++count_compare && i < n - 1){
        if(++count_compare && arr[i] < arr[i+1]){
           if(++count_compare && arr[i] < minVal){
               minVal = arr[i];
           }
           if(++count_compare && arr[i+1] > maxVal){
               maxVal = arr[i+1];
           }
        }
        else{
            if(++count_compare && arr[i] > maxVal){
                maxVal = arr[i];
            }
            if(++count_compare && arr[i+1] < minVal){
                minVal = arr[i+1];
            }
        }
        i+=2;
    }
    //------->Find min value and max index

    int *L = new int [m];
    for(int i = 0;++count_compare &&  i < m ; i++){
        L[i] = 0;
    }

    double tmp = (m - 1)*1.0/(maxVal - minVal);

    for(int i = 0; ++count_compare && i < n; i++){
        int k = tmp * (arr[i] - minVal) ;
        L[k]++;
    }

    for(int i = 1;++count_compare && i < m; i++){
        L[i] = L[i - 1] + L[i]; 
    }

    int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (++count_compare && nmove < n - 1)
	{
		while (++count_compare && j > L[k] - 1)
		{
			j++;
			k = int(tmp*(arr[j] - minVal));
		}
		flash = arr[j];
		if (++count_compare && k < 0) break;
		while (++count_compare && j != L[k])
		{
			k = int(tmp*(flash - minVal));
			int hold = arr[t = --L[k]];
			arr[t] = flash;
			flash = hold;
			++nmove;
		}
	}

    delete[] L;
    insertionSort(arr,n,running_time,count_compare);

    end = clock();
    running_time = (double)(end - start) / CLOCKS_PER_SEC;
}
//-------------------------->Flash Sort


