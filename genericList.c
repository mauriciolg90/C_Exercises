#include <stdio.h>
#include "genericList.h"

declare_list_type(int, ListOfInts);
declare_list_type(float, ListOfFloats);

int main(void) {
	ListOfInts *list01;
	ListOfFloats *list02;

	initList(int, ListOfInts, list01);
	addToList(int, ListOfInts, list01, 3);
	addToList(int, ListOfInts, list01, 5);

	printf("%d\n", (int)list01->data);
	printf("%d\n", (int)list01->nextNode->data);

	deleteList(int, ListOfInts, list01);

	printf("%d\n", (int)list01->data);

	return 0;
}