#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>

// ð������
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

// �����������
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

// ��������
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// �ѵ���
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

// ������
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

// ��ӡ����
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        wprintf(L"%d ", arr[i]);
    wprintf(L"\n");
    fflush(stdout);
}

int main() {
    // ���ÿ���̨����ͱ��ػ�
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "zh_CN.UTF-8");
    
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    wprintf(L"ԭʼ����: ");
    printArray(arr, n);

    // ð������
    bubbleSort(arr, n);
    wprintf(L"ð������: ");
    printArray(arr, n);
    
    // ��������
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    wprintf(L"\nԭʼ����: ");
    printArray(arr2, n);
    
    quickSort(arr2, 0, n-1);
    wprintf(L"��������: ");
    printArray(arr2, n);
    
    // ������
    int arr3[] = {64, 34, 25, 12, 22, 11, 90};
    wprintf(L"\nԭʼ����: ");
    printArray(arr3, n);
    
    heapSort(arr3, n);
    wprintf(L"������: ");
    printArray(arr3, n);
    
    return 0;
}
