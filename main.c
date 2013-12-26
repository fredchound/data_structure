#include<stdio.h>
#include<stdlib.h>

#include "linked_list.h"
#include "stack_queue.h"
#include "hash_table.h"   // after linked list


/******  main test ******/

void test_LinkedList(void)
{

	printf("Linked list implementation test: \n\n");
	
	List * list = list_CreateList();
	printf("New list node created at %p \n", list);
	
	list_printList(list);

	printf("Inserting new value -1 to head: \n");
	list_InsertValueToHead(list, -1);	
	printf("New list is: \n");
	list_printList(list);

	Node* node = list_CreateNode(-3);
	printf("Inserting new node (-3) to head: \n");
	list_InsertNodeToHead(list, node);	
	printf("New list is: \n");
	list_printList(list);

	printf("Inserting new value 1 to tail: \n");
	list_InsertValueToTail(list, 1);	
	printf("New list is: \n");
	list_printList(list);
	
	node = list_CreateNode(3);
	printf("Inserting new node (3) to tail: \n");
	list_InsertNodeToTail(list, node);	
	printf("New list is: \n");
	list_printList(list);

	printf("Searching for -1 ... \n");
	node = list_Search(list, -1);
	printf("Insert -2 before -1. \n");
	list_InsertValueBeforeNode(list, node, -2);
	printf("New list is: \n");
	list_printList(list);	
	
	printf("Searching for 2 ... \n");	
	printf(" %p \n", list_Search(list, 2));
	printf("Insert 2 after 1. \n");
	node = list_Search(list, 1);
	list_InsertValueAfterNode(list, node, 2);
	printf("New list is: \n");
	list_printList(list);

	printf("Delete head: ");
	list_DeleteHead(list);
	printf("New list is: \n");
	list_printList(list);

	printf("Delete tail: ");
	list_DeleteTail(list);
	printf("New list is: \n");
	list_printList(list);

	printf("Find 0 and delete \n");
	node = list_Search(list, 0);
	list_Delete(list, node);
	printf("New list is: \n");
	list_printList(list);

}

int main()
{
	
//	test_LinkedList();


// test hash table
	
	printf("Hash Table test: \n");

	int i = 0;

	int hashSize = 10; 

	printf("Creating Hash Table of size %d \n", hashSize);
	HashTable_t* hashTable = malloc(sizeof(HashTable_t));
	ht_Create(hashTable, hashSize);

	for (i=0; i<hashSize; i++){
		printf("Data of node %d is %d \n", i, 
			(hashTable->hTable+i)->data);
	}

	for (i=0; i<hashSize*2; i++){
		printf("Index of key %d is %d \n", i, 
				ht_HashFunction(hashTable, i));
	}
	
	return 1;

}
