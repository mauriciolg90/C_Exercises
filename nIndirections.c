#include <stdio.h>

/* Function prototype */
int nIndirections(void *initial, unsigned int indirections);

int main(void)
{
	int a = 3;
	int *a1 = &a;
	int **a2 = &a1;

	int result = nIndirections(a2, 2);
	printf("The value stored in memory is: %d\n", result);

	return 0;
}

/** @brief Performs "n" indirections on the "initial" pointer.
 *
 *  @param initial Starting memory address as a pointer to void.
 *  @param indirections Amount of indirection to be performed on the pointer.
 *  @return int Value stored in memory.
 */
int nIndirections(void *initial, unsigned int indirections)
{
	/*
	 * 1) (int **)initial Casts the void pointer to a pointer to pointer of type int.
	 * 2) *(int **)initial Obtains the address pointed to by the next pointer.
	 */
	for(; indirections > 1; --indirections) {
		initial = *(int **)initial;
	}

	return *(int *)initial;
}