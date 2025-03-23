#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>

// 冒泡排序
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    int swapped;
    for (i = 0; i < n-1; i++) {
        swapped = 0;
        for (j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) break;
    }
}

// 快速排序分区
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    
    for (int j = low; j <= high-1; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

// 快速排序
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 堆调整
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        int swap = arr[i];
        arr[i] = arr[largest];
        arr[largest] = swap;
        heapify(arr, n, largest);
    }
}

// 堆排序
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n-1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        wprintf(L"%d ", arr[i]);
    wprintf(L"\n");
    fflush(stdout);
}

int main() {
    // 设置控制台编码和本地化
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "zh_CN.UTF-8");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    wprintf(L"原始数组: ");
    printArray(arr, n);

    // 冒泡排序
    bubbleSort(arr, n);
    wprintf(L"冒泡排序: ");
    printArray(arr, n);
    
    // 快速排序
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    wprintf(L"\n原始数组: ");
    printArray(arr2, n);
    
    quickSort(arr2, 0, n-1);
    wprintf(L"快速排序: ");
    printArray(arr2, n);
    
    // 堆排序
    int arr3[] = {64, 34, 25, 12, 22, 11, 90};
    wprintf(L"\n原始数组: ");
    printArray(arr3, n);
    
    heapSort(arr3, n);
    wprintf(L"堆排序: ");
    printArray(arr3, n);
    
    return 0;
}
