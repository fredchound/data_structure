/* 
* Implements harsh table data structure
*/


//TODO: implement in C++ class
//TODO: add error handling
//TODO: generalize to any data type


// data structure for hash table

typedef int Data_t; // need to generalize to any data type

typedef struct hash_node {
	Data_t data;
	struct hash_node* next;
} __attribute__((packed)) HashNode_t;

typedef struct hash_table {
	int hashSize; 
	HashNode_t* hTable;
} HashTable_t;


// create hash table given table size

void ht_Create(HashTable_t* hashTable,int hashSize)
{	
	int i; 	
	HashNode_t* p = malloc(hashSize*sizeof(HashNode_t));

	printf("HashTable allocated at %p \n", p);
	printf("Size of hash node = size of data_t %d + size of ptr %d = %d \n", 
		sizeof(Data_t), sizeof(struct hash_node*), sizeof(HashNode_t));
		
	hashTable->hashSize = hashSize;
	hashTable->hTable = p; 
	
	for(i = 0; i<hashSize; i++){
		//p = (HashNode_t*)(hashTable->hTable+ i*sizeof(HashNode_t));
		p = (HashNode_t*)(hashTable->hTable+i);
		p->next = NULL;
		p->data = i;  // testing
		printf("Initializing node %d at %p \n", i, p);
	}

}

// hash function: given key, find index
static unsigned int ht_HashFunction(HashTable_t* hashTable, Data_t key)
{
	unsigned int index = key % hashTable->hashSize; 

	return index;
}


// insert into table: given key, insert into hash table.
void ht_Insert(HashTable_t* hashTable, Data_t key)
{
     unsigned index = ht_HashFunction(hashTable, key);
     
     
}

// free table


// search for an element in table







