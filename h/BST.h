#ifndef BST_H
#define BST_H

#include "Node.h"
#include "Stack.h"
#include "Queue.h"
#include "Extendable_Table.h"
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>



/************************************* BST FORM *************************************/
void import_in_arr(int n, int * K, int * V, int *k, int ** arr);
Pointer create_BST(int n, int * arr);
/************************************** BST Search **********************************/
void search_tree(Pointer root, int key);
/*********************************** BST Insert *************************************/
void insert_in_tree(Pointer *root, int key);

/*********************************** BST Delete *************************************/
void delete_tree(Pointer root);
/************************************** AVL Balance Check ***************************/
int AVL_balance_check(Pointer root);

#endif // !BST_H
