#include "Extendable_Table.h"

/*********************************************************************** PART I  *****************************************************************/


/*Initialization of extendable*/
void initialization(int * n, int **key_table, int ** valid_vector) {

	printf("\nEnter initial size of set of keys: ");					//set dimension
	do {
		scanf("%d", n);
		if (*n <= 0) printf("You entered an incorrect value. Repeat the input: ");
	} while (*n <= 0);

	int f;																	//extension factor
	printf("\nEnter the extension factor for extendable table: ");
	do {
		scanf("%d", &f);
		if (f < 0) printf("You entered an incorrect value. Repeat the input: ");
	} while (f < 0);

	*n *= f;

	*key_table = calloc(*n, sizeof(int));
	*valid_vector = calloc(*n, sizeof(int));


	int tmp;
	printf("\nEnter initial set of keys:\n");
	for (int i = 0; i < *n; i += f) {

		int p = 0;

		scanf("%d", &tmp);
		for (int j = 0; j < i; j += f) {
			if ((*key_table)[j] == tmp) {
				p = 1;
				break;
			}
		}
		if (p) {
			printf("Key already in table.\n");
			i -= f;
		}
		else {
			(*key_table)[i] = tmp;
			(*valid_vector)[i] = 1;

		}

	}

	for (int i = 0; i < *n - f; i += f) {
		for (int j = i + f; j < *n; j += f) {
			if ((*key_table)[i] > (*key_table)[j]) {
				tmp = (*key_table)[i];
				(*key_table)[i] = (*key_table)[j];
				(*key_table)[j] = tmp;
			}
		}
	}

	for (int i = 0; i < *n; i++) {
		if ((*valid_vector)[i] == 0)
			(*key_table)[i] = tmp;
		else
			tmp = (*key_table)[i];
	}
}

void print_table(int n, int * K, int * V) {

	printf("\nExtendable table:\n\n");
	printf("   index   |  validity_vector  |   key_table\n");
	for (int i = 0; i < n; i++) {
		printf("   %3d     |        %3d        |      %3d\n", i, V[i], K[i]);
	}
}
/*print array with labeled index*/
void print_array(int n, int *arr, int index) {
	for (int i = 0; i < n; i++)
		if (i == index)
			printf("[%d] ", i);
		else
			printf("%3d ", i);
	putchar('\n');

	for (int i = 0; i < n; i++)
		if (i == index)
			printf("[%d] ", arr[i]);
		else
			printf("%3d ", arr[i]);
	putchar('\n');


}
/*Search, unknown vector size method implemented*/
int binary_search(int key, int n, int * K, int * valid_vector) {

	int low, high, mid;
	int i = 0;


	while (i < n && key > K[i]) {							/*Deciding high & low*/
		if (i == 0)
			i++;
		else
			i <<= 1;				//Times 2
	}

	i >>= 1;						// Divided by 2
	low = i;
	high = (i << 1) < n ? i << 1 : n;

	while (low <= high) {
		mid = (low + high) >> 1;			// Divided by 2

		if (key == K[mid])
			break;
		else
			if (key > K[mid])
				low = mid + 1;
			else
				high = mid - 1;
	}

	if (key != K[mid]) return -1;

	if (valid_vector[mid] == 0) {
		while (mid >= 0 && !valid_vector[mid]) {
			mid--;
		}
		if (mid < 0 || key != K[mid]) mid = -1;

	}

	return mid;

}

void delete_key(int n, int *K, int *valid_vector) {
	int key;
	printf("Enter a key which needs to be deleted: ");
	scanf("%d", &key);

	int pos = binary_search(key, n, K, valid_vector);

	if (pos == -1)
		printf("The key isn't present in the table.\n");
	else {
		valid_vector[pos] = 0;
		printf("Key %d succsessfully deleted from the table.\n", key);
	}


}
/*Insert new key*/
int bin_search_next_larger(int key, int n, int *K) {
	int low, high, mid;
	int i = 0;


	while (i < n && key > K[i]) {
		if (i == 0)
			i++;
		else
			i <<= 1;
	}

	i >>= 1;
	low = i;
	high = (i << 1) < n ? i << 1 : n;

	while (low <= high) {
		mid = (low + high) >> 1;

		if (key == K[mid]) {
			while (mid < n && K[mid] == key)
				mid++;
			return mid;     // mid is either n or needed value
		}

		if (key < K[mid])
			high = mid - 1;
		else
			low = mid + 1;

	}

	if (high < 0)
		return 0;
	else
		if (low > n - 1)
			return n;
		else
			return low;

}
void insert_key(int *n, int ** K, int **V) {

	int key;
	printf("Enter a key that needs to be inserted:\n");
	scanf("%d", &key);

	if (binary_search(key, *n, *K, *V) != -1) {
		printf("The key is already in the table.\n");
		return;
	}

	int i = bin_search_next_larger(key, *n, *K);
	printf("\nKey succsessfully inserted in table.\n");

	/*Find suitable location*/
	if (i != 0 && (*V)[i - 1] == 0) {

		int step = 1;


		while (i - step >= 0 && (*V)[i - step] == 0)
			step++;
		step--;


		int j = (i - step + i - 1) >> 1;
		(*V)[j] = 1;

		for (; j < i; j++)
			(*K)[j] = key;
		return;
	}


	int sentinel;
	for (sentinel = i; sentinel < *n && (*V)[sentinel] == 1; sentinel++);

	if (sentinel != *n) {

		for (int j = sentinel - 1; j >= i; j--) {
			(*K)[j + 1] = (*K)[j];
			(*V)[j + 1] = (*V)[j];
		}
		(*K)[i] = key;
		(*V)[i] = 1;

	}
	else {
		for (sentinel = i - 1; sentinel >= 0 && (*V)[sentinel] == 1; sentinel--);

		if (sentinel >= 0) {
			for (int j = sentinel; j + 1 < i; j++) {
				(*K)[j] = (*K)[j + 1];
				(*V)[j] = (*V)[j + 1];
			}
			(*K)[i - 1] = key;
			(*V)[i - 1] = 1;
		}
		else {
			i <<= 1;
			*K = realloc(*K, *n * 2 * sizeof(int));
			*V = realloc(*V, *n * 2 * sizeof(int));

			for (int j = *n - 1; j >= 0; j--) {
				(*K)[2 * j] = (*K)[2 * j + 1] = (*K)[j];
				(*V)[2 * j] = 1; (*V)[2 * j + 1] = 0;
			}

			*n <<= 1;
			if (i != 0) {
				(*K)[i - 1] = key;
				(*V)[i - 1] = 1;
			}
			else {
				(*V)[1] = (*V)[0];
				(*K)[1] = (*K)[0];

				(*K)[0] = key;
			}


			return;
		}
	}

}
