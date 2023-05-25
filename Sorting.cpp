#include <iostream>
#include <chrono>
#include <omp.h>
using namespace std;
using namespace std::chrono;
void bubbleSort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void parallel_bubbleSort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		#pragma omp parallel
		
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void merge(int arr[], int l, int m, int r)
{
	int k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	int i = 0;
	int j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}

		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void parallel_merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;
	int L[n1], R[n2];
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	i = 0;
	j = 0;
	k = l;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}

		k++;
	}

	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

void parallel_mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		int m = l + (r - l) / 2;
		#pragma omp parallel sections num_threads(2)
		{
			#pragma omp section
			{
				parallel_mergeSort(arr, l, m);
			}
			#pragma omp section
			{
				parallel_mergeSort(arr, m + 1, r);
			}
		}

		parallel_merge(arr, l, m, r);
	}
}

int main()
{
	cout << "No. of elements = ";
	int N, a, ch;
	cin >> N;
	int arr[N] = { 0
	}, arr1[N] = { 0 };

	for (int i = 0; i < N; i++)
	{
		a = rand() % N;
		arr[i] = a;
		arr1[i] = a;
	}

	cout << "UnSorted array: \n";
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}

	cout << "\nOption (1.bubbleSort, 2.mergeSort)= ";
	cin >> ch;
	switch (ch)
	{
		case 1:
			{
				auto t1 = high_resolution_clock::now();
				bubbleSort(arr, N);
				auto t2 = high_resolution_clock::now();
				auto duration = (t2 - t1) *1e-6;
				cout << "\nTime taken by function: " << duration.count() << " microseconds \n " << endl;
				t1 = high_resolution_clock::now();
				parallel_bubbleSort(arr1, N);
				t2 = high_resolution_clock::now();
				duration = (t2 - t1) *1e-6;
				cout << "\nTime taken by parallel_function: " << duration.count() << " microseconds \n " << endl;
				break;
			}

		case 2:
			{
				auto t1 = high_resolution_clock::now();
				mergeSort(arr, 0, N - 1);
				auto t2 = high_resolution_clock::now();
				auto duration = (t2 - t1) *1e-6;
				cout << "\nTime taken by function: " << duration.count() << " microseconds \n " << endl;
				t1 = high_resolution_clock::now();
				parallel_mergeSort(arr1, 0, N - 1);
				t2 = high_resolution_clock::now();
				duration = (t2 - t1) *1e-6;
				cout << "\nTime taken by parallel_function: " << duration.count() << " microseconds \n " << endl;
				break;
			}

		default:
			cout << "Invalid option\n";
	}

	cout << "Sorted array: \n";
	for (int i = 0; i < N; i++)
	{
		cout << arr[i] << " ";
	}

	return 0;
}

//OUTPUT