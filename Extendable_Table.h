#ifndef EXTENDABLE_TABLE_H
#define EXTENDABLE_TABLE_H
#include <stdio.h>
#include <stdlib.h>


/*********************************************************************** PART I  *****************************************************************/


void initialization(int * n, int **key_table, int ** valid_vector);

void print_table(int n, int * K, int * V);
void print_array(int n, int *arr, int index);

int binary_search(int key, int n, int * K, int * valid_vector);
void delete_key(int n, int *K, int *valid_vector);
int bin_search_next_larger(int key, int n, int *K);
void insert_key(int *n, int ** K, int **V);


#endif
