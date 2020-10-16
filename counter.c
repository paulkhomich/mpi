#include <stdio.h>
#include <time.h>
#include <mpi.h>

#define ROOT    0
#define BUFINT  4

int main(int argc, char** argv) {
    time_t start, end;
    start = time(0);
    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (!rank) {
        int sum = 0;
        int buf[BUFINT];
        for (int i = 1; i < size; ++i) {
            MPI_Recv((void*)buf, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, (void*)0);
            sum += buf[0];
        }
        
        end = time(0);
        printf("Size of COMM_WORLD:\t%d\n", size);
        printf("Sum is done. Receive:\t%d\n", sum);
        printf("Time required:\t%f\n", difftime(start, end));
    } else {
        int buf[1] = { 1 };
        MPI_Send(buf, 1, MPI_INT, ROOT, MPI_ANY_TAG, MPI_COMM_WORLD);
    }
        
    MPI_Finalize();
    return 0;
}

