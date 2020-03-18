#ifndef NODE_H
#define NODE_H



typedef struct node {
	struct node * left;
	struct node * right;
	int key;
	int height;
	int extra;
} Node;

typedef Node * Pointer;

#endif