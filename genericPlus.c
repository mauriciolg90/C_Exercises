#include <stdio.h>

/* Macro */
#define offsetOf(myStruct, structMember) (size_t)&(((myStruct *)0)->structMember)

/* Function prototype */
int genericPlus(const void *array, size_t structSize, size_t fieldOffset, size_t amountOfElements);

/* User structure */
struct S {
	int field1;
	float field2;
	char field3[10];
	char field4;
};

int main(void)
{
	int result;
	struct S *array[3];
	struct S myStruct1, myStruct2, myStruct3;

	array[0] = &myStruct1;
	array[1] = &myStruct2;
	array[2] = &myStruct3;

	array[0]->field1 = 11;
	array[1]->field1 = 22;
	array[2]->field1 = 33;

	result = genericPlus(array[0], sizeof(struct S), offsetOf(struct S, field1), sizeof(array)/sizeof(array[0]));
	printf("The result is: %d\n", result);

	return 0;
}

/** @brief Adds all specified fields within the structures.
 *
 *  @param array Pointer to user structures array.
 *  @param structSize Size of the structure.
 *  @param fieldOffset Offset of the desired field.
 *  @param amountOfElements Number of array elements.
 *  @return int Sum of the indicated fields.
 */
int genericPlus(const void *array, size_t structSize, size_t fieldOffset, size_t amountOfElements)
{
	size_t i;
	int result;

	/*
	 * 1) (size_t)array + fieldOffset Adds an offset to the beginning of the structure.
	 * 2) *(int *)((size_t)array + fieldOffset) Dereferences the pointer to the member.
	 * 3) (size_t)array + structSize Adds an size to point to the following structure.
	 */
	for (i = 0, result = 0; i < amountOfElements; ++i) {
		result = result + *(int *)((size_t)array + fieldOffset);
		array = (void *)((size_t)array + structSize);
	}

	return result;
}
