#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ORDEM 10

int main(int argc, char** argv) {
	// Inicia o ambiente do MPI
	MPI_Init(NULL, NULL);

	// Encontra o tamanho do rank
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	int matrixA[ORDEM][ORDEM];
	int matrixB[ORDEM][ORDEM];
	int matrixC[ORDEM][ORDEM];

	// Popula matrizes A e B
	for (int i = 0; i < ORDEM;  i++) {
		for (int j = 0; j < ORDEM; j++) {
			matrixA[i][j] = 1;
			matrixB[i][j] = 1;
		}	
	}
	 
	// Para executar essas tarefas existem quatro ranks
	if (world_rank == 0) {
		int c1[ORDEM/4][ORDEM/4];
		for (int i = 0; i < 24; i++) {
			for (int j = 0; j < 24; i++) {
				c1[i][j] = matrixA[i][j] + matrixB[i][j]; 			
			}
		}


		MPI_RECV();
	if (world_rank == 1) {
	}
	if (world_rank == 1) {
	}
	if (world_rank == 1) {
	}
	MPI_Finalize();
}
