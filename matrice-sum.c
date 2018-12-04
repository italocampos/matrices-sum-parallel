//#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ORDEM 100

int main(int argc, char** argv) {
	// Inicia o ambiente do MPI
	//MPI_Init(NULL, NULL);

	// Captura o número de processos que serão utilizados na execução
	//int world_rank;
	//MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Captura o número total de processos
	//int world_size;
	//MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int matrixA[ORDEM][ORDEM];
	//int matrixB[ORDEM][ORDEM];
	//int matrixC[ORDEM][ORDEM];
	
	// Povoa a matriz com 1's
	for (int i = 0; i < ORDEM;  i++) {
		for (int j = 0; j < ORDEM; j++) {
			matrixA[i][j] = 1;
			//matrixB[i][j] = 1;
		}	
	}

	// Verifica o número de processos
	//if(world_size != 4) {
	//	fprintf(stderr, "Two proccess are needed only\n");
	//	MPI_Abort(MPI_COMM_WORLD, 1);
	//}

	for (int i = 1; i < ORDEM;  i+=4) {
		for (int j = 1; j < ORDEM; j+=4) {
			printf("%d ", matrixA[i][j]);
			//matrixB[i][j] = 1;
		}
		printf("\n");
	}

	/*if(world_rank == 0) {
		vector[0] = 1;
		vector[1] = 2;
		vector[2] = 3;
		MPI_Send(&vector, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
	}
	else {
		if (world_rank == 1) {
			MPI_Recv(&pointer, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Process 1 received arg from process 0\n");
			int i;
			for(i = 0; i < 3; pointer++)
				printf("%d ", *pointer);
		}
	}*/

	 
	// Para executar essas tarefas existem quatro ranks
	/*if (world_rank != 0) {
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
	}*/
	//MPI_Finalize();
}
