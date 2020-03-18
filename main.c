#include "BST.h"

void print_menu(void) {
	printf("\033[0;36m");
	printf(" ____________________________________________________________________________________________________________\n");
	printf("|                                                     MENU                                                   |\n");
	printf("|                                                                                                            |\n");
	printf("| 1. Initialize Extendable Table                                                                             |\n");
	printf("| 2. Print Table                                                                                             |\n");
	printf("| 3. Find key in table                                                	                                     |\n");
	printf("| 4. Insert key in table                                                                                     |\n");
	printf("| 5. Delete key from table                                                                                   |\n");
	printf("|                                                                                                            |\n");
	printf("| ---------------------------------------------------------------------------------------------------------  |\n");
	printf("|                                                                                                            |\n");
	printf("| 6. Create Binary Search Tree (BST) from the table                                                          |\n");
	printf("| 7. Print tree                                                                                              |\n");
	printf("| 8. Find key in tree                                                                                        |\n");
	printf("| 9. Insert key in tree                                                                                      |\n");
	printf("| 10. Delete tree                                                                                            |\n");
	printf("| 11. Check AVL balance                                                                                      |\n");
	printf("|                                                                                                            |\n");
	printf("| 0. Exit                                                                                                    |\n");
	printf("|____________________________________________________________________________________________________________|\n");
	printf("\033[1;36m");


	printf("\nChoose any option: ");

}


void main(void) {
	/*first part variables*/
	printf("\033[1;36m");

	int * key_table = NULL;
	int * valid_vector = NULL;
	int n;
	int key;
	
	

	/*second part variables*/
	int * arr;
	int dim;
	Pointer root=NULL;

	print_menu();
	putchar('\n');
	while (1) {

		int x;
		scanf("%d", &x);
		putchar('\n');
		switch (x)
		{
		/*First part */
		case 1: {

			free(key_table);										//Memory management
			free(valid_vector);
			initialization(&n, &key_table, &valid_vector);
			
			printf("\033[0;36m");
			print_table(n, key_table, valid_vector);				
			printf("\033[1;36m");

			break;
		}
		case 2: {
			if (key_table == NULL) {
				printf("First of all enter option ( 1 ) to initialize the table.\n");
				break;
			}
			printf("\033[0;36m");
			print_table(n, key_table, valid_vector);
			printf("\033[1;36m");

			break;
		}
		case 3: {

			if (key_table == NULL) {
				printf("First of all enter option ( 1 ) to initialize the table.\n");
				break;
			}



			printf("Enter a key: ");
			scanf("%d", &key);

			int pos = binary_search(key, n, key_table, valid_vector);

			if (pos != -1) {
				printf("The key is located at the position: [%d]\n", pos);
				print_array(n, key_table, pos);
			}
			else
				printf("Search unsuccsessful (the key isn't present in the table).\n");

			break;
		}
		case 4: {
			if (key_table == NULL) {
				printf("First of all enter option ( 1 ) to initialize the table.\n");
				break;
			}

			insert_key(&n, &key_table, &valid_vector);
			break;
		}
		case 5: {
			delete_key(n, key_table, valid_vector);
			break;
		}

		/*PART II*/
		/*Create BST*/
		case 6: {
			import_in_arr(n, key_table, valid_vector, &dim, &arr);
			if (root == NULL) {
				root = create_BST(dim, arr);
			}
			else
				for (int i = 0; i < dim; i++) {
					insert_in_tree(&root, arr[i]);
				}

			print_tree(root,0);

			break;
		}

		/*Print BST*/
		case 7: {                                                                                  
			if (root == NULL) {
				printf("First of all enter option ( 6 ) to initialize the tree.\n");
				break;
			}
			
			print_tree(root,0);
			

			
			break;
		}
		case 8: {
			if (root == NULL) {
				printf("First of all enter option ( 6 ) to initialize the tree.\n");
				break;
			}
			printf("Enter a key that needs to be found: ");
			scanf("%d", &key);
			search_tree(root, key);
			break;
		}
		case 9: {
			printf("Enter a key that needs to be inserted: kljuc koji treba insertovati:\n");
			scanf("%d", &key);
			insert_in_tree(&root,key);
			print_tree(root,0);
			break;
		}
		case 10: {
			if (root == NULL) {
				printf("First of all enter option ( 6 ) to initialize the tree.\n");
				break;
			}
			printf("Deleting the tree...\n");
			delete_tree(root);
			printf("Tree succsessfully deleted.\n");

			root = NULL;
			break;
		}

		case 11: {
			if (root == NULL) {
				printf("First of all enter option ( 6 ) to initialize the tree.\n");
				break;
			}
			AVL_balance_check(root);

			break;
		}

		case 0:
			free(key_table);
			free(valid_vector);
			delete_tree(root);
			printf("Goodbye.\n");
			exit(EXIT_SUCCESS);
		default: printf("Invalid option chosen. Repeat the input: "); continue;
		}

		printf("\nPress any key to continue.\n");
		getch();

		putchar('\n');
		print_menu();

	}

}