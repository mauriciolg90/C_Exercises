#include <stdlib.h>

#ifndef GENERIC_LIST_H_
	#define GENERIC_LIST_H_
	#define declare_list_type(type, listName) \
				typedef struct listName {type *data; struct listName *nextNode;} listName
	#define initList(type, listName, list) \
				listName *headNode; \
				list = malloc(sizeof(listName)); \
				headNode = list
	#define addToList(type, listName, list, elem) \
				headNode->data = (type *)elem; \
				headNode->nextNode = malloc(sizeof(listName)); \
				headNode = headNode->nextNode
	#define deleteList(type, listName, list) \
				listName *temp = list; \
				while(temp->nextNode) {temp = list->nextNode; free(list); list = temp;}
#endif
