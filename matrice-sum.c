#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ORDER 500
#define JUMP 4

// Função que povoa uma matriz qualquer, de uma ordem qualquer, com um valor qualquer
void start_matrix(int matrix[ORDER][ORDER], int valor) {
	for (int i = 0; i < ORDER;  i++) {
		for (int j = 0; j < ORDER; j++) {
			matrix[i][j] = valor;
			matrix[i][j] = valor;
		}	
	}
}

// Função que imprime uma dada matriz
void print_matrix(int matrix[ORDER][ORDER]) {
	for (int i = 1; i < ORDER;  i++) {
		for (int j = 1; j < ORDER; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

// Função de soma das matrizes
void sum(int matrix_A[ORDER][ORDER], int matrix_B[ORDER][ORDER], int matrix_C[ORDER][ORDER], int token) {
	for(int i = token; i < ORDER; i+=JUMP) {
		for (int j = 0; j < ORDER; j++) {
			matrix_C[j][i] = matrix_A[j][i] + matrix_B[j][i];
		}
	}
}

// Função que povoa uma coluna da matriz
void set_column(int matrix[ORDER][ORDER], int column, int value) {
	for(int i = 0; i < ORDER; i++)
		matrix[i][column] = value;
}

// Função que junta matrizes
void merge_matrix(int matrix_A[ORDER][ORDER], int matrix_B[ORDER][ORDER], int token) {
	for(int i = token; i < ORDER; i+=JUMP) {
		for (int j = 0; j < ORDER; j++) {
			matrix_A[j][i] = matrix_B[j][i];
		}
	}
}

// Função que inicia uma matriz com valores aleatórios
void start_matrix_random(int matrix[ORDER][ORDER]) {
	srand(time(NULL));
	for (int i = 0; i < ORDER;  i++) {
		for (int j = 0; j < ORDER; j++) {
			matrix[i][j] = rand() % 100;
		}	
	}
}

int main(int argc, char** argv) {
	// Inicia o ambiente do MPI
	MPI_Init(NULL, NULL);

	// Captura o número de processos que serão utilizados na execução
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	// Captura o número total de processos
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);

	int matrixA[ORDER][ORDER];
	int matrixB[ORDER][ORDER];
	int matrixC[ORDER][ORDER];

	// Insere os valores iniciais
	for(int j = 0; j < ORDER; j++)
		set_column(matrixA, j, j+10);
	for(int j = ORDER-1; j >= 0; j--)
		set_column(matrixB, j, j+5);
	start_matrix(matrixC, 0);

	// Verifica o número de processos
	if(world_size != 4) {
		fprintf(stderr, "Four proccess are needed to run\n");
		MPI_Abort(MPI_COMM_WORLD, 1);
	}

	if(world_rank == 0) {
		// Mostra as matrizes A, B e C
		printf("MATRIZ A: \n");
		print_matrix(matrixA);
		printf("MATRIZ B: \n");
		print_matrix(matrixB);
		printf("MATRIZ C: \n");
		print_matrix(matrixC);

		// Envia coluna de onde deve iniciar cada subprocesso
		int token = 0;
		MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		token++;
		MPI_Send(&token, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
		token++;
		MPI_Send(&token, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);

		// Soma o que sobrou da matriz
		token++;
		sum(matrixA, matrixB, matrixC, token);

		// Aguarda mensagem dos processos que estão somando a matriz
		int matrix_temp[ORDER][ORDER];
		MPI_Recv(&matrix_temp, ORDER*ORDER, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("0: Recebi matriz do processo 1.\n");
		token = 0;
		merge_matrix(matrixC, matrix_temp, token);

		MPI_Recv(&matrix_temp, ORDER*ORDER, MPI_INT, 2, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("0: Recebi matriz do processo 2.\n");
		token++;
		merge_matrix(matrixC, matrix_temp, token);

		MPI_Recv(&matrix_temp, ORDER*ORDER, MPI_INT, 3, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("0: Recebi matriz do processo 3.\n");
		token++;
		merge_matrix(matrixC, matrix_temp, token);

		// Mostra os resultados na matriz C
		printf("MATRIZ C: \n");
		print_matrix(matrixC);
	}
	else {
		int token;
		printf("%d: I received job from proccess 0\n", world_rank);
		MPI_Recv(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("%d: My token is %d\n", world_rank, token);
		sum(matrixA, matrixB, matrixC, token);
		MPI_Send(matrixC, ORDER*ORDER, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	// Finaliza e limpa o ambiente MPI
	MPI_Finalize();
}