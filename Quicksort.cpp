#include <mpi.h>
#include <iostream>
#include <algorithm>

void quicksort(int* data, int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = data[(left + right) / 2];

    while (i <= j) {
        while (data[i] < pivot)
            i++;
        while (data[j] > pivot)
            j--;
        if (i <= j) {
            tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            i++;
            j--;
        }
    };

    if (left < j)
        quicksort(data, left, j);
    if (i < right)
        quicksort(data, i, right);
}

int main(int argc, char** argv)
{
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int* data = nullptr;
    int n = 10000; // size of the data
    int subset_size = n / size;

    if (rank == 0) {
        // initialize the data
        data = new int[n];
        for (int i = 0; i < n; i++) {
            data[i] = rand();
        }

        // distribute the data to all processors
        for (int i = 1; i < size; i++) {
            MPI_Send(&data[i * subset_size], subset_size, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        // receive the data from processor 0
        data = new int[subset_size];
        MPI_Recv(data, subset_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // sort the subset of the data using Quicksort
    quicksort(data, 0, subset_size - 1);

    if (rank == 0) {
        // merge the sorted subsets
        for (int i = 1; i < size; i++) {
            MPI_Recv(&data[i * subset_size], subset_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
        std::sort(data, data + n);
    } else {
        // send the sorted subset back to processor 0
        MPI_Send(data, subset_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}