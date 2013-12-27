/* 
* Implements harsh table data structure
*/


// data structure for hash table
// follows from linked list structs


//hash node holds <key, value> pair
typedef struct hash_node {
	DataType key;
	DataType value;
	struct hash_node* next;
}__attribute__((packed)) HashNode;

typedef struct hash_table {
	int hashSize; 
	HashNode* htNodeHead; // point to node head for each list of ht entry
} HashTable;


// create a hash node 
HashNode* ht_CreateNode(DataType key, DataType value)
{
	HashNode* node = malloc(sizeof(HashNode));
	node-> key = key;
	node-> value = value;
	node-> next = NULL;
	return node;
}


// create hash table given table size

void ht_Create(HashTable* hashTable, int hashSize)
{	
	int i; 	
	HashNode* p = malloc(hashSize*sizeof(HashNode));

	printf("HashTable allocated at %p \n", p);
	printf("Size_HashNode %d = size_NodePtr %d + 2*size_Data %d \n", 
		sizeof(HashNode), sizeof(HashNode*), 2*sizeof(DataType) );
		
	hashTable->hashSize = hashSize;
	hashTable->htNodeHead = p; // node head for first list in HT
	
	for(i = 0; i<hashSize; i++){
		p = (HashNode*)(hashTable->htNodeHead+i);
		p->next = NULL;
		p->key = NULL;  // TODO: first node is always dummy now.
		p->value = NULL; 
		printf("Initializing node %d at %p \n", i, p);
	}

}

// hash function: given key, find index
static unsigned int ht_HashFunction(HashTable* hashTable, DataType key)
{
	unsigned int index = key % hashTable->hashSize; 

	return index;
}


typedef struct hash_list{
	HashNode* listHead;
} HashList;

// given a hash node, create hash list
HashList* hashList_CreateList(HashNode* hashNode)
{	
	HashList* hashList = malloc(sizeof(HashList));
	hashList->listHead = hashNode;
	return hashList;
}

// get the last node of the hash list
HashNode* hashList_GetTail(HashList* hashList)
{	
	HashNode* p = hashList->listHead;	
	while (p->next!=NULL){
		p = p->next;
	}
	return p;	
}
// insert value into tail of hash list
void hashList_Add(HashList* hashList, DataType key, DataType value)
{	
	HashNode* newNode = ht_CreateNode(key, value);
	HashNode* p = hashList_GetTail(hashList);	
	p->next = newNode;
}


// print the entire list
void hashList_PrintList(HashList* list)
{	
	HashNode* p = list->listHead;
	int i = 0;
	while (p!=NULL){

		printf("Node %d key: %d   value: %d   ", i, p->key, p->value);
		printf("---Node %d address: %p \n", i, p);
		p = p->next;
		i++;	
	}

}

// insert into table: given <key, value>, insert into hash table.
void ht_Insert(HashTable* hashTable, DataType key, DataType value)
{
	unsigned int index = ht_HashFunction(hashTable, key);
	
	HashNode* p = (hashTable->htNodeHead+index); 

	// here we append new data directly to linked list created
	HashList* hashList = hashList_CreateList(p);

	hashList_Add(hashList, key, value);

	printf("\nData with key %d is inserted to %dth list. \n", key, index);
	hashList_PrintList(hashList);	
}




// search for an element: given key, return pt to element


// free table




