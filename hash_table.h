/* 
* Implements harsh table data structure
*/

// TODO: how to handle redundant key
// TODO: how about double linked list for hash list?


// data structure for hash table
// each key is mapped to a linked list


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

typedef struct hash_list{
	HashNode* listHead;
} HashList;

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
		p->key = 0;  // TODO: first node is always dummy now.
		p->value = 0; 
		printf("Initializing node %d at %p \n", i, p);
	}

}

// hash function: given key, find index
static unsigned int ht_HashFunction(HashTable* hashTable, DataType key)
{
	unsigned int index = key % hashTable->hashSize; 

	return index;
}

// given a hash node, create hash list
static HashList* hashList_CreateList(HashNode* hashNode)
{	
	HashList* hashList = malloc(sizeof(HashList));
	hashList->listHead = hashNode;
	return hashList;
}

// get the last node of the hash list
static HashNode* hashList_GetTail(HashList* hashList)
{	
	HashNode* p = hashList->listHead;	
	while (p->next!=NULL){
		p = p->next;
	}
	return p;	
}

// insert value into tail of hash list
static void hashList_Add(HashList* hashList, DataType key, DataType value)
{	
	HashNode* newNode = ht_CreateNode(key, value);
	HashNode* p = hashList_GetTail(hashList);	
	p->next = newNode;
}


// print the entire list
static void hashList_PrintList(HashList* list)
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

	printf("\nData with <key, val> <%d, %d> is inserted to %dth list. \n", 
                   key, value, index);
	hashList_PrintList(hashList);	
}

// search for an element: given key, return pt to hash node
HashNode* ht_Search(HashTable* hashTable, DataType key)
{
	unsigned int index = ht_HashFunction(hashTable, key);
	
	HashNode* p = (hashTable->htNodeHead+index); 
	HashNode* result = NULL;
    
    p = p->next;
    while(p){
        if(p->key==key) {
            result = p;
            break;
        }    
        p = p->next;                               
    }
    
    if(result)
        printf("Data with key %d is found with value %d. \n", 
                   key, result->value);
    else printf("Key %d not found. \n", key);
    
    return result;
}

// delete tail node of list corresponding to key
static void hashList_DeleteTail(HashTable* hashTable, DataType key)
{
	unsigned int index = ht_HashFunction(hashTable, key);
	
	printf("Deleting tail node. \n");
	
	HashNode* prev = (hashTable->htNodeHead+index);   
    HashNode* p = prev->next;
    while(p->next){
             prev = p;
             p = p->next;
    }
    prev->next = NULL;
    free(p);          
}

// Delete a node given its key: return TRUE if node found and deleted
int ht_Delete(HashTable* hashTable, DataType key)
{
	
	HashNode* p;
    HashNode* q;
    
    q = ht_Search(hashTable, key);// note that q can never be the dummy list head
    
    if(q) {
  	
	    p = q->next;    
	    if(p){
              // not tail node
	          q->key = p->key;
	          q->value = p->value;
	          q->next = p->next;
	          free(p);
        } else{ 
              // tail node of list
              hashList_DeleteTail(hashTable, key);
        }   
        printf("Node with key %d deleted.\n", key);          
        return 1;
        
    } else {
         printf("Key %d not found. \n", key);
         return 0;
    }
}

// print entire hash table
void ht_PrintTable(HashTable* hashTable, DataType key)
{
    unsigned int index = ht_HashFunction(hashTable, key);
	
	HashNode* p = (hashTable->htNodeHead+index); 

    printf("List correspoding to key %d", key);
    while(p){
        printf("-<%d, %d>-", p->key, p->value);
        p = p->next;                               
    }
    printf("\n");   
}

