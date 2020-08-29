#ifndef QUEUE_H
#define QUEUE_H
#include "BST.h"


/*Queue*/
typedef struct queue_field {
	Pointer node;
	struct queue_field * next;
} Queue_Field;
typedef Queue_Field * Queue_Ptr;


/*queue operations */
int queue_empty(Queue_Ptr q);
void insert_in_queue(Queue_Ptr *q, Pointer x);
Pointer delete_from_queue(Queue_Ptr *q);



#endif // !QUEUE_H
