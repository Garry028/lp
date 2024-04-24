#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = new int[n1];
    int *R = new int[n2];

    for (i = 0; i < n1; ++i)
    {
        L[i] = arr[l + 1];
    }

    for (j = 0; j < n2; ++j)
    {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                mergeSort(arr, l, m);
            }
#pragma omp section
            {
                mergeSort(arr, m + 1, r);
            }
        }
        merge(arr, l, m, r);
    }
}

int main()
{

    int n;
    cout << "Enter the size of the array: ";
    cin >> n;

    int *arr = new int[n];

    srand(time(0));

    for (int i = 0; i < n; ++i)
    {
        arr[i] = rand() % 100;
    }

    clock_t start = clock();
#pragma omp parallel
    {
#pragma omp single
        {
            mergeSort(arr, 0, n - 1);
        }
    }
    clock_t end = clock();
    double parallelMergeTime = double(end - start) / CLOCKS_PER_SEC;

    // Performance measurement
    cout << "Parallel Merge Sort Time: " << parallelMergeTime << " seconds" << endl;

    delete[] arr;

    return 0;
}