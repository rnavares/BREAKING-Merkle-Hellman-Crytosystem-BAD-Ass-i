/*
 * main.c
 *
 *  Created on: May 6, 2018
 *      Author: ricardo
 */

#include "cript.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{

  int *indices = NULL;
  int *a = NULL, *cod = NULL;
  int count = 0;
  int n, i, *b = NULL;
  char *encryption;

  /* TEST 1: Vanilla knapsack problem --------------------- */
  n = 4;
  a = (int*) malloc (n * sizeof(int));
  a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4;

  indices = (int*) malloc (n * sizeof (int));

  count = knapsack_problem(a, n, 6, indices);
  if (count == 0){
    free(indices);
    free(a);
    return 1;
  }

  printf("\n\n======= Test 1: Vanilla knapsack problem =====\n");
  printf("SUM = 6; a = [ ");
  for(count = 0; count < n; count++)
    printf("%d ",a[count]);
  printf("]\n");

  printf("indices to include = [ ");
  for(count = n - 1; count >= 0; count--)
    if (indices[count] >= 0)
      printf("%d ",indices[count]);
  printf("]\n");

  if (indices) free(indices);
  free(a);

  /* TEST 2: knapsack problem with superincreasing series ---------------- */

  n = 8;
  a = (int*) malloc (n * sizeof(int));
  a[0] = 1; a[1] = 3; a[2] = 6; a[3] = 14;
  a[4] = 27; a[5] = 60; a[6] = 150; a[7] = 300;
  
  indices = (int*) malloc (n * sizeof (int));

  count = knapsack_problem_superincreasing(a,n,483,indices);
  if (count==0){
    free(indices);
    free(a);
    return 1;
  }

  printf("\n======= Test 2: Knapsack with superincreasing series ======\n");
  printf("SUM = 483; a = [ ");
  for(count = 0; count < n; count++)
    printf("%d ",a[count]);
  printf("]\n");

  printf("indices to include = [ ");
  for(count = n - 1; count >= 0; count--)
    if (indices[count] >= 0)
      printf("%d ",indices[count]);
  printf("]\n");

  if (indices) free(indices);
  if(a) free(a);

  /* TEST 3: to_bin ---------------- */

  b = to_bin(88);
  if(b == NULL)
    return 0;

  printf("\n======= Test 3: to_bin ======\n");
  printf("dec = 88;  bin = ");

  for (i = 0; i < 8; i++)
    printf ("%d", b[i]);
  
  printf("\n");

  b = to_bin(1000);
  if(b == NULL)
    return 0;

  printf("dec = 1000;  bin = ");

  for (i = 0; i < 8; i++)
    printf ("%d", b[i]);
  
  printf("\n");

  if(b) free(b);

  /* TEST 4:  Meckl-Hellmann encryption ---------------- */
  a = (int*) malloc (8 * sizeof(int));

  a[0] = 1000; a[1] = 961; a[2] = 1922; a[3] = 1766;
  a[4] = 493; a[5] = 869; a[6] = 1153;  a[7] = 267;

  indices = encrypt("XYZXYZXYZ", 9, a);
  if (indices == NULL){
    free(indices);
    free(a);
    return 1;
  }

  printf("\n======= Test 4: Meckl-Hellmann encryption ======\n");
  printf("message = XYZXYZXYZ\nencryption = ");
  for(count = 0; count < 9; count++)
    printf(" %d",indices[count]);
  printf("\n");
  printf("public key = [");
  for(count = 0; count < 8; count++)
    printf(" %d",a[count]);
  printf(" ]\n");
  printf("private key = 9");
  printf("\n");

  if (indices) free(indices);
  if(a) free(a);
  
  /* TEST 5:  Meckl-Hellmann decryption ---------------- */
  a = (int*) malloc (8 * sizeof(int));
  a[0] = 1; a[1] = 3; a[2] = 6; a[3] = 14;
  a[4] = 27; a[5] = 60; a[6] = 150; a[7] = 300;

  n = 3;
  cod = (int*) malloc (n * sizeof(int));
  cod[0] = 3220; cod[1] = 3487; cod [2] = 4373;

  encryption = (char *) malloc (8 * sizeof(char));
  
  encryption = decrypt(cod, n, a, 2039, 1000);
  if (encryption == NULL){
    free(a);
    return 1;
  }

  printf("\n======= Test 5: Meckl-Hellmann decrypt ======\n");
  printf("coded message = [%d %d %d]\n",
	 cod[0], cod[1], cod[2]);
  printf("key generators: 2039, 1000\n");
  printf("original A_si = [ " );
  for(count = 0; count < 8; count++)
    printf("%d ",a[count]);
  printf("]\n" );
  printf("original message = XYZXYZXYZ\n");
  printf("decrypted = [ " );
  for(count = 0; count < 8; count++)
    printf("%d ",encryption[count]);
  printf("]\n" );

  if(encryption) free(encryption);
  if(a) free(a);
  if(cod) free(cod);


  /* TEST 6:  Break MH encryption ---------------- */

  b = (int*) malloc (8 * sizeof(int));
  b[0] = 1000; b[1] = 961; b[2] = 1922; b[3] = 1766;
  b[4] = 493; b[5] = 869; b[6] = 1153; b[7] = 267;
  
  cod = (int*) malloc (3 * sizeof(int));
  cod[0] = 3220; cod[1] = 3487; cod [2] = 4373;

  encryption = (char *) malloc (3 * 8 * sizeof(char));

  encryption = break_encryption(cod,3,b);
  if (encryption == NULL){
    free(b);
    free(cod);
    return 1;
  }

   printf("\n======= Test 6: Break Meckl-Hellmann encryption ======\n");
  printf("coded message = [%d %d %d]\n",
	 cod[0], cod[1], cod[2]);
  printf("public key: [ ");
  for(count = 0; count < 8; count++)
    printf("%d ",b[count]);
  printf("]\n" );
  printf("Breaking encryption...\n");
  printf("Message decoded: [ ");
  for(count = 0; count < 24; count++)
    printf("%d ",encryption[count]);
  printf("]\n");
  
  if(encryption) free(encryption);
  if(b) free(b);
  if(cod) free(cod);

  
  return 1;
  
}
