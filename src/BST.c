#include "BST.h"



/************************************* BST FORM *************************************/

void import_in_arr(int n, int * K, int * V, int *k, int ** arr) {
	int i;
	*k = 0;
	*arr = NULL;

	for (i = 0; i < n; i++) {
		if (V[i]) {

			(*arr) = realloc(*arr, (*k + 1) * sizeof(int));
			(*arr)[*k] = K[i];
			(*k)++;

		}
	}

}


Pointer create_BST(int n, int * arr) {
	printf("Generating tree...\n");
	Stack_Ptr s = NULL;
	int low, high, mid;
	Pointer root, next;

	/*Initial part*/
	low = 0;
	high = n - 1;
	mid = (low + high) >> 1;

	root = malloc(sizeof(Node));
	root->key = arr[mid];
	next = root;

	Stack_Info tmp_stack_info;
	tmp_stack_info = create_tmp_stack_info(next, mid + 1, high);
	push(&s, tmp_stack_info);

	high = mid - 1;

	while (low <= high) {
		mid = (low + high) >> 1;

		next->left = malloc(sizeof(Node));
		next = next->left;

		next->key = arr[mid]; next->extra = 0;


		tmp_stack_info = create_tmp_stack_info(next, mid + 1, high);
		push(&s, tmp_stack_info);

		printf("Stack status: ");
		Stack_Ptr p = s;
		while (p) {
			printf("%d ", p->info.tmp->key);
			p = p->next;
		}
		putchar('\n');


		high = mid - 1;
	}

	next->left = NULL;

	while (!stack_empty(s)) {
		tmp_stack_info = pop(&s);
		next = tmp_stack_info.tmp;
		low = tmp_stack_info.low;
		high = tmp_stack_info.high;





		printf("Stack status: ");
		Stack_Ptr p = s;
		while (p) {
			printf("%d ", p->info.tmp->key);
			p = p->next;
		}
		putchar('\n');

		if (low <= high) {
			mid = (low + high) >> 1;

			next->right = malloc(sizeof(Node));
			next = next->right;

			next->key = arr[mid]; next->extra = 0;


			tmp_stack_info = create_tmp_stack_info(next, mid + 1, high);
			push(&s, tmp_stack_info);

			printf("Stack status: ");
			Stack_Ptr p = s;
			while (p) {
				printf("%d ", p->info.tmp->key);
				p = p->next;

			}
			putchar('\n');

			high = mid - 1;

			while (low <= high) {
				mid = (low + high) >> 1;

				next->left = malloc(sizeof(Node));
				next = next->left;

				next->key = arr[mid]; next->extra = 0;

				tmp_stack_info = create_tmp_stack_info(next, mid + 1, high);
				push(&s, tmp_stack_info);
				high = mid - 1;

				printf("Stack status: ");

				Stack_Ptr p = s;
				while (p) {
					printf("%d ", p->info.tmp->key);
					p = p->next;

				}
				putchar('\n');

			}
			next->left = NULL;
		}
		else
			next->right = NULL;


	}
	printf("Tree succsessfully generated.\n");
	return root;

}


void print_tree(Pointer root, int balance_mode) {
	printf("\033[0;36m");
	printf("\n___________________ Generated Tree ____________________\n\n");


	Stack_Ptr s = NULL;
	Stack_Info tmp_stack_info;

	Pointer next = root;

	int level = 0;

	while (1) {
		while (next != NULL) {
			tmp_stack_info = create_tmp_stack_info(next, level, 0);

			push(&s, tmp_stack_info);

			level++;

			next = next->right;
		}


		if (!stack_empty(s)) {
			tmp_stack_info = pop(&s);

			next = tmp_stack_info.tmp;
			level = tmp_stack_info.low;


			if (!balance_mode && (next->extra == 1))
				printf("\033[1;36m");               //bolded

			for (int i = 0; i < 10 * level; i++) {
				if (i + 10 > 10 * level) {
					_setmode(_fileno(stdout), _O_U16TEXT);
					wprintf(L"\x2550");
					_setmode(_fileno(stdout), _O_TEXT);

				}

				else
					if (i + 10 == 10 * level) {
						_setmode(_fileno(stdout), _O_U16TEXT);

						if (s != NULL && top(s).tmp->right == next)
							wprintf(L"\x2554");
						else
							wprintf(L"\x255A");


						_setmode(_fileno(stdout), _O_TEXT);
					}
					else
						putchar(' ');
			}

			if (!balance_mode) {

				printf("%d", next->key);


			}
			else {
				printf("%d", next->extra);

				next->extra = 0;
			}



			printf("\033[0;36m");  //Not bolded


			putchar('\n');

			next = next->left;
			level++;
		}
		else
			break;

	}
	printf("\n________________________________________________________");
	printf("\033[1;36m");
}


/************************************** BST Search ***************************************/

void search_tree(Pointer root, int key) {
	Pointer * path = NULL;
	int k = 0;

	Pointer p = root;

	while (p != NULL && p->key != key) {
		k++;
		path = realloc(path, k * sizeof(Pointer));
		path[k - 1] = p;

		p->extra = 1;

		if (key < p->key)
			p = p->left;
		else
			p = p->right;

	}


	if (p == NULL) {
		printf("The key isn't present in tree\n\n");

		for (int i = 0; i < k; i++)
			path[i]->extra = 0;
		free(path);
		print_tree(root, 0);
	}
	else {
		p->extra = 1;
		k++;
		path = realloc(path, k * sizeof(Pointer));
		path[k - 1] = p;



		printf("Key succsessfully found.\n\n");
		print_tree(root, 0);
		for (int i = 0; i < k; i++)
			path[i]->extra = 0;
		free(path);

	}



}


/*********************************** BST Insert **************************************/
void insert_in_tree(Pointer *root, int key) {


	Pointer ptr = malloc(sizeof(Node));
	ptr->extra = 0;
	ptr->key = key;
	ptr->left = ptr->right = NULL;


	Pointer p = *root, q = NULL;


	while (p != NULL) {
		q = p;
		if (p->key == key) {
			printf("Key %d already present in tree\n", key);
			return;
		}
		else
			if (key < p->key)
				p = p->left;
			else
				p = p->right;
	}

	if (q == NULL) {
		(*root) = ptr;
	}
	else
		if (key < q->key)
			q->left = ptr;
		else
			q->right = ptr;
	printf("Key %d succsessfully inserted in tree.\n", key);



}



void delete_tree(Pointer root) {

	/*level-order*/
	if (root != NULL) {
		Queue_Ptr q = NULL;

		insert_in_queue(&q, root);
		while (!queue_empty(q)) {
			root = delete_from_queue(&q);
			if (root->left != NULL) insert_in_queue(&q, root->left);
			if (root->right != NULL) insert_in_queue(&q, root->right);
			free(root);
		}
	}

}


/************************************** AVL Balance Check *******************************/

int AVL_balance_check(Pointer root) {
	Pointer ptr = root;
	Stack_Ptr s = NULL;
	Stack_Info tmp_stack_info;
	int avl = 1;

	/*POSTORDER*/
	do {
		while (ptr != NULL) {
			if (ptr->right != NULL) {
				tmp_stack_info.tmp = ptr->right;
				push(&s, tmp_stack_info);
			}
			tmp_stack_info.tmp = ptr;
			push(&s, tmp_stack_info);

			ptr = ptr->left;


		}

		ptr = pop(&s).tmp;
		if (ptr->right != NULL && top(s).tmp == ptr->right) {
			pop(&s);
			tmp_stack_info.tmp = ptr;
			push(&s, tmp_stack_info);
			ptr = ptr->right;
		}
		else {
			int hl, hr;
			if (ptr->left != NULL)
				hl = ptr->left->height;
			else
				hl = -1;	//no children

			if (ptr->right != NULL)
				hr = ptr->right->height;
			else
				hr = -1;	//no children

			ptr->extra = hl - hr;

			if (ptr->extra > 1 || ptr->extra < -1) avl = 0;

			if (ptr->left == NULL && ptr->right == NULL) {
				ptr->height = 0;
			}
			else
				ptr->height = hl > hr ? hl + 1 : hr + 1;

			printf("Key: %2d          Height: %2d          Balance: [%2d]\n", ptr->key, ptr->height, ptr->extra);

			ptr = NULL;
		}

	} while (!stack_empty(s));


	if (avl) {
		printf("\nThe tree IS balanced by AVL criteria\n");
	}
	else
		printf("\nThe tree IS NOT balanced by AVL criteria\n");

	print_tree(root, 1);




	return avl;
}
