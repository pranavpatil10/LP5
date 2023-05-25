#include <iostream>
#include <omp.h>
#include <time.h>
#include <iomanip>
#include <limits>
#include <chrono>
using namespace std::chrono;
using namespace std;
int sum(int a[], int n)
{
	int sum = 0;
	#pragma omp parallel for reduction(+: sum)
	for (int i = 0; i < n; i++)
	{
		sum += a[i];
	}

	return sum;
}

int min(int a[], int n)
{
	int v = a[0];
	#pragma omp parallel for reduction(min: v)
	for (int i = 0; i < n; i++)
	{
		if (a[i] < v)
			v = a[i];
	}

	return v;
}

int max(int a[], int n)
{
	int v = a[0];
	#pragma omp parallel for reduction(max: v)
	for (int i = 0; i < n; i++)
	{
		if (a[i] > v)
			v = a[i];
	}

	return v;
}

float avg(int a[], int n)
{
	return sum(a, n) / n;
}

int main()
{
	int a[100];
	int cnt = 0;
	for (int i = 0; i < 100; i++)
	{
		a[i] = i + 6;
		cnt = cnt + 1;
	}

	cout << " Input data is :";
	for (int i = 0; i < cnt; i++)
		cout << " " << a[i];
	cout << "\n";

	auto start = high_resolution_clock::now();
	cout << " Sum of 100 numbers: " << sum(a, 100);
	cout << "\n";
	cout << " Minimum number from 100 numbers: " << min(a, 100);
	cout << "\n";
	cout << " Maximum number from 100 numbers: " << max(a, 100);
	cout << "\n";
	cout << " Average of 100 numbers: " << avg(a, 100);
	auto stop = high_resolution_clock::now();
	auto duration = (stop - start) *1e-6;

	cout << "\n";
	cout << "Time taken by function: " <<duration.count() << " microseconds" << endl;
	return 0;
}