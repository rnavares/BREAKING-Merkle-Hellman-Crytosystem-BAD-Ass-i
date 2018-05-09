/*
 * cript.h
 *
 *  Created on: May 6, 2018
 *      Author: ricardo
 */

#ifndef CRIPT_H_
#define CRIPT_H_

int knapsack_problem(int *a, int N, int S, int *indices);
int knapsack_problem_superincreasing(int *A_si, int N, int S, int *indices);
int *to_bin(int number);
int* encrypt(void * msg, int long_msg, int *public_key);
int random_gen(int min, int max);
int gcd (int n, int m); /* greatest common divisor */
int euclides_ext(int u, int n, int *X, int *Y);
void *decrypt(int *cod, int n_cod, int *A_si, int n, int u);
void *break_encryption(int *cod, int n_cod, int *B);


#endif /* CRIPT_H_ */
