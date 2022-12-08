#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h> 

#define CORE 4

#define MAX 5


pthread_t thread[MAX * 3];


int matA[MAX][MAX]; 
int matB[MAX][MAX]; 

int matSumResult[MAX][MAX];
int matDiffResult[MAX][MAX]; 
int matProductResult[MAX][MAX]; 

int step_i = 0;

void fillMatrix(int matrix[MAX][MAX]) {
  for(int i = 0; i<MAX; i++) {
    for(int j = 0; j<MAX; j++) {
      matrix[i][j] = rand()%10+1;
    }
  }
}

void printMatrix(int matrix[MAX][MAX]) {
  for(int i = 0; i<MAX; i++) {
    for(int j = 0; j<MAX; j++) {
      printf("%5d", matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}


void* computeSum(void* args) { 
  int x, y;
  intptr_t core = (intptr_t)args;

  
  for (x = core * MAX / 4; x < (core + 1) * MAX / 4; x++) {
    for (y = 0; y < MAX; y++) {
      matSumResult[x][y] = matA[x][y] + matB[x][y];
    }
  }  
  // free(args);
  return NULL;
}

void* computeDiff(void* args) { // pass in the number of the ith thread
  int x, y;
  intptr_t core = (intptr_t)args;

  // Each thread computes 1/4th of matrix difference
  for (x = core * MAX / 4; x < (core + 1) * MAX / 4; x++) {
    for (y = 0; y < MAX; y++) {
      matDiffResult[x][y] = matA[x][y] - matB[x][y];
    }
  }  
  // free(args);
  return NULL;
}


void* computeProduct(void* args) { // pass in the number of the ith thread
  int j, k, i = step_i++; //i denotes row number of resultant matC
   
  for (j = 0; j < MAX; j++) {
    for (k = 0; k < MAX; k++) {
      matProductResult[i][j] += matA[i][k] * matB[k][j];
    }
  }
      
  return NULL;
}


int main(char **args) {
    srand(time(0));  // Do Not Remove. Just ignore and continue below.
    
    int i, step = 0;

    // 0. Get the matrix size from the command line and assign it to MAX
    // MAX = atoi(args[1]);
    
    // 1. Fill the matrices (matA and matB) with random values.
    fillMatrix(matA);
    fillMatrix(matB);
    
    // 2. Print the initial matrices.
    printf("Matrix A:\n");
    printMatrix(matA);
    printf("Matrix B:\n");
    printMatrix(matB);
    
    // 3. Create pthread_t objects for our threads.
    
    // 4. Create a thread for each cell of each matrix operation.

    for (i = 0; i < MAX; i++) {
      if (pthread_create(&thread[i], NULL, &computeSum, (void *)(intptr_t)step) != 0) {
        perror("Failed to create thread!");
      }
      if (pthread_create(&thread[i + MAX], NULL, &computeDiff, (void *)(intptr_t)step) != 0) {
        perror("Failed to create thread!");
      }
      if (pthread_create(&thread[i + MAX * 2], NULL, &computeProduct, (void *)(intptr_t)step) != 0) {
        perror("Failed to create thread!");
      }
      step++;
    }

    // 
    // You'll need to pass in the coordinates of the cell you want the thread
    // to compute.
    // 
    // One way to do this is to malloc memory for the thread number i, populate the coordinates
    // into that space, and pass that address to the thread. The thread will use that number to calcuate 
    // its portion of the matrix. The thread will then have to free that space when it's done with what's in that memory.
    
    // 5. Wait for all threads to finish.
    // pthread_exit(NULL);
    for (i = 0; i < MAX * 3; i++) {
      pthread_join(thread[i], NULL);
    }
    
    // 6. Print the results.
    printf("Results:\n");
    printf("Sum:\n");
    printMatrix(matSumResult);
    printf("Difference:\n");
    printMatrix(matDiffResult);
    printf("Product:\n");
    printMatrix(matProductResult);
    return 0;
  
}