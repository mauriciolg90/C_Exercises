#include <stdio.h>

/* Function prototype */
int nIndirections(void *initial, unsigned int indirections);

int main(void) {
	int a = 3;
	int *a1 = &a;
	int **a2 = &a1;

	int result = nIndirections((void *)a2, 2);
	printf("The value stored in memory is: %d\n", result);

	return 0;
}

/** @brief Performs "n" indirections on the "initial" pointer.
 *
 *  @param initial Starting memory address as a pointer to void.
 *  @param indirections Amount of indirection to be performed on the pointer.
 *  @return int Value stored in memory.
 */
int nIndirections(void *initial, unsigned int indirections) {
	while(indirections > 1) {
		/*
		 * 1) *(int *)initial Dereferences a pointer to int.
		 * 2) (void *)(*(int *)initial) Casts the result to void pointer.
		 */
		initial = (void *)(*(int *)initial);
		--indirections;
	}
	return *(int *)initial;
}