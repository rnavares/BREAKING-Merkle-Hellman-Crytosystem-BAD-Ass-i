#include "cript.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>

int knapsack_problem(int *a, int N, int S, int *indices)

{

  int **matrix = NULL;
  int i = 0, j = 0;
  int value = 1, count = 0;
  int sum = 0;

  if (a == NULL){
    printf("Error in knapsack_problem: no elements in array\n");
    return -1;
  }

  if (N < 0) {
    printf("Error in knapsack_problem: wrong number of elementes\n");
    return -1;
  }



  matrix = (int **) malloc ((N + 2) * sizeof (int *));
  if (matrix == NULL){
    printf("Error in knapsack_problem: no memory\n");
    return -1;
  }

  
  for (i = 0; i < N + 1; i++)  {
      matrix[i] = (int *) malloc ((S + 2) * sizeof(int));
      if (matrix[i] == NULL){
    	  printf("Error in knapsack_problem: no memory\n");

	  for (j = 0; j < i; j++)
    		  free(matrix[j]);

    	  if (matrix) free(matrix);

    	  return -1;
      }
    }

  /* initialization */
  for (i = 0; i < N; i++)
    indices[i] = -1;

  /* first columns and row as 0 sum */
  for (i = 0; i < S; i++)
    matrix[0][i] = 0;

  for (i = 0; i < N; i++)
    matrix[i][0] = 0;

  
  /* build matrix knapsack_problemo*/
  for (i = 1; i < N + 1; i++){
      for (j = 1; j < S + 1; j++){
	if (j < a[i - 1]){
	  matrix[i][j] = matrix[i - 1][j];
	} else if (matrix[i - 1][j] > (matrix[i - 1][j - a[i - 1]] + value)) {
	    matrix[i][j] = matrix[i - 1][j];
	} else {
	  matrix[i][j] = matrix[i - 1][j - a[i - 1]] + value;
	}
       }
   }

  
  
  /* inspect matrix */
  i = N;
  j = S;

  while ((i > 0) && (j > 0)){
    if ( j < a[i - 1])
      	i--;
    else if (matrix[i-1][j] > matrix[i-1][j-a[i-1]] + value)
       	i--;
    else {
	indices[count] = i - 1;
	count++;
	j = j - a[i - 1];
	i--;
    }

  }


  /* free memory */
  for(i = 0; i < N + 1; i++){
      free(matrix[i]);
  }

  if(matrix) free(matrix);

  /* check if solution exists */
  for(i = 0; i < count; i++)
    sum = sum + a[indices[i]];

  if (sum != S) return 0;

  return 1;
}


int knapsack_problem_superincreasing(int *A_si, int N, int S, int *indices)

{

  int control = 0, i = 0, count = 0;

  if (A_si == NULL){
    printf("Error knapsack_problem_superincreasing: no superincreasing serie\n");
    return -1;
  }

  if ( N < 0 ) {
    printf("Error knapsack_problem_superincreasing: wrong num elements\n");
    return -1;
  }

  for (i = 0; i < N; i++)
    indices[i] = -1;

  control = S;
  i = N;

  while ( (i > 0) && (control != 0))

    {
      if (A_si[i-1] <= control){
	indices[count] = i-1;
	control = control - A_si[i-1];
	count++;
      }

      i--;
    }

  if (control == 0)
    return 1;

  return 0;

}

int *to_bin(int number)
{

  int *n_binary = NULL;
  int i = 0, remainder = 0;

  n_binary = (int*) malloc (8 * sizeof (int));
  if (n_binary == NULL ){
      printf("Error to_bin: no memory\n");
      return NULL;
   }

  for (i = 0; i < 8; i++){
      remainder = number % 2;
      number = number / 2;
      n_binary[7-i] = remainder;

    }
  return n_binary;
}

int* encrypt(void * msg, int long_msg, int *public_key)
{

  int element = 0,i = 0,j = 0, sum = 0;
  int *num_bin = NULL, *encryption = NULL;
  unsigned char bits[256];

  if (msg == NULL)   {
    printf("Error encrypt: no msg\n");
    return NULL;
  }

  if (long_msg < 0)   {
    printf("Error encrypt: no long_msg\n");
    return NULL;
  }

  if (public_key == NULL)   {
    printf("Error encrypt: n public key\n");
    return NULL;
  }

  memcpy(bits,msg,long_msg);

  encryption = (int*) malloc (long_msg * sizeof (int));
  if (encryption == NULL){
      printf("Error encrypt: no memory for encryption\n");
      return NULL;
  }

  for (i = 0; i < long_msg; i++)
    {
      element =  bits[i];

      num_bin = to_bin(element);
      if (num_bin == NULL){
	printf("Error in encrypt: error in to_bin\n");
	free(encryption);
	return NULL;
      }

      sum = 0;
      for (j = 0; j < 8; j++)
	{
	  sum = sum + (num_bin[j] * public_key[j]);
	}

      encryption[i] = sum;

    }

  free(num_bin);
  return encryption;
}

int random_gen(int min, int max)
{
    double range = max - min + 1;
    return min + (int)(range * rand() / (RAND_MAX + 1.0));
}


int gcd ( int n, int m)
{
  int remainder = 0, dividend = 0, divisor = 0;
  int count = 0;

  count = 1;
  dividend = n;
  divisor = m;
  remainder = n % m;

  while (count >= 0){
    if (dividend % divisor == 0){
      return divisor;
      count--;
    } else {
      remainder = dividend % divisor;
      dividend = divisor;
      divisor = remainder;
    }
  }
  return divisor;
}

int euclides_ext(int u, int n, int *X, int *Y)
{
  int mcd = 0;
  int Xtemp = 0, Ytemp = 0;

  if (n == 0){
    *X = 1;
    *Y = 0;
    return u;
  } else {
    mcd = euclides_ext(n, u%n, &Xtemp, &Ytemp);
    *X = Ytemp;
    *Y = Xtemp - floor(u / n) * Ytemp;
    return mcd;
  }
}

void *decrypt(int *cod, int n_cod, int *A_si, int n, int u)
{

  int D = 0, y = 0, i = 0, j = 0, value = 0, count = 0, sum = 0;
  int *indices = NULL;
  unsigned char *bits = NULL;

  
  if (cod == NULL){
    printf("Error en decrypt: input cod\n");
    return NULL;
  }

  if (A_si == NULL){
    printf("Error en decrypt: input SA_i\n");
    return NULL;
  }

  if (n_cod < 0){
    printf("Error en decrypt: input n_cod\n");
    return NULL;
  }

  if (n < 0){
    printf("Error en decrypt: input n\n");
    return NULL;
  }

  if (u < 0){
    printf("Error en decrypt: input u\n");
    return NULL;
  }
  
  /* check n greater than set sum */
  /* and A_si is superincreasing  */

  for (i = 0; i < 8; i++){
    if (A_si[i] > sum)
      sum = sum + A_si[i];
    else {
      printf("Error en decrypt: A_si is not superincreasing\n");
      return NULL;
    }
  }


  bits = (unsigned char *) malloc (n_cod * 8 * sizeof(unsigned char));
  if (bits == NULL){
    printf("Error decrypt: no memory\n");
    return NULL;
  }

  /* initialize bits */
  for (i = 0; i < n_cod * 8; i++)
    bits[i] = '0';

  indices = (int *) malloc ( 8 * sizeof(int));
  if (indices == NULL ){
    printf("Error decrypt: no memory\n");
    if(bits) free(bits);
    return NULL;
  }

  euclides_ext(u,n,&D,&y);
  if(D < 0)
    D = D + n;

  for (i = 0; i < n_cod; i++){
    value = (cod[i] * D) % n;

    if(knapsack_problem_superincreasing(A_si,8,value,indices) == -1){
      printf("Error decrypt: error inn knapsack_problem_superincreasing\n");
      if (indices) free(indices);
      if(bits) free(bits);
      return NULL;
    }

    /* check which indices to use */
    for (j = 0; j < 8; j++){
      if(indices[j] != -1)
	bits[count + indices[j]] = '1';
    }

    count = count + 8;
  }

  free(indices);

  return (void *) bits;

}

void *break_encryption(int *cod, int n_cod, int *B)
{

  unsigned char *bits = NULL;
  int *indices = NULL;
  int i = 0, j = 0, count = 0;

  if (cod == NULL){
    printf("Error break_encryption: input cod\n");
    return NULL;
  }

  if (B == NULL){
    printf("Error break_encryption: input B\n");
    return NULL;
  }

  if (n_cod < 0){
    printf("Error break_encryption: input n_cod\n");
    return NULL;
  }

  
  bits = (unsigned char *) malloc (n_cod * 8 * sizeof(unsigned char));
  if (bits == NULL ){
    printf("Error break_encryption: no memory\n");
    return NULL;
  }

  
  indices = (int *) malloc ( 8 * sizeof(int));
  if (indices == NULL )
    {
      printf("Error break_encryption: indices\n");
      if(bits) free(bits);
      return NULL;
    }

   for (i = 0; i < n_cod * 8; i++)
     bits[i] = '0';


  /* get encryption */
  for (i = 0; i < n_cod; i++){
    if( knapsack_problem(B,8,cod[i],indices) == -1){
      printf("Error break_encryption: knapsack_problem\n");
      if (indices) free(indices);
      if(bits) free(bits);
	  return NULL;
    }

    /* checks which indices to use */
    for (j = 0; j < 8; j++){
      if(indices[j] != -1)
      bits[count + indices[j]] = '1';
    }

    count = count + 8;
  }

  free(indices);

  return (void *) bits;

}



