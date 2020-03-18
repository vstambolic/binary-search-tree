#include "Queue.h"

/*queue operations */
int queue_empty(Queue_Ptr q) {
	if (q == NULL)
		return 1;
	else
		return 0;
}

void insert_in_queue(Queue_Ptr *q, Pointer x) {

	Queue_Ptr tmp;
	tmp = malloc(sizeof(Queue_Field));
	tmp->node = x;
	tmp->next = NULL;

	if (*q == NULL) {
		*q = tmp;
	}
	else {
		Queue_Ptr ptr = *q;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = tmp;
	}
}
Pointer delete_from_queue(Queue_Ptr *q) {

	if (queue_empty(*q)) {
		printf("ERROR: Underflow\n");
		exit(EXIT_FAILURE);
	}

	Pointer tmp = (*q)->node;

	*q = (*q)->next;


	return tmp;
}
