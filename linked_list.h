/* 
* Implements linked list operations
*/


typedef int DataType; //TODO: generalize to any data type 

typedef struct node{
	DataType data;  
	struct node *next;
} __attribute__((packed)) Node;


typedef struct list{
	Node* listHead;
} List;


// create a node in linked list
Node* list_CreateNode(DataType value)
{
	Node* node = malloc(sizeof(Node));
	node-> data = value;
	node-> next = NULL;
	return node;
}

// create a linked list: given node is list head
List* list_CreateList(Node* node)
{	
	List* list = malloc(sizeof(List));
	list->listHead = node;
	return list;
}


// print the entire list
void list_printList(List* list)
{	
	Node* p = list->listHead;
	int i = 0;
	while (p!=NULL){

		printf("Node %d data: %d   ", i, p->data);
		printf("---Node %d address: %p \n", i, p);
		p = p->next;
		i++;	
	}

}


// get the last node of the list
Node* list_GetTail(List* list)
{	
	Node* p = list->listHead;	
	while (p->next!=NULL){
		p = p->next;
	}
	return p;	
	
}


// search for a node 
Node* list_Search(List* list, DataType value)
{
	Node* p = list->listHead;
	while (p!=NULL){
		if(p->data == value)	
			return p;
		p = p->next;
	}
	// not found, return Null
	return NULL;
}



// insert new value to to the head of the list
void list_InsertValueToHead(List* list, DataType value)
{	
	Node* newNode = list_CreateNode(value);
	newNode->next = list->listHead;
	list->listHead = newNode; // update list head

}

// insert new value to the tail of the list
void list_InsertValueToTail(List* list, DataType value)
{	
	Node* newNode = list_CreateNode(value);
	Node* p = list_GetTail(list);	
	p->next = newNode;
}

// insert new value before a node
void list_InsertValueBeforeNode(List* list, Node* node, DataType value)
{	
	if (node == list->listHead) {
		list_InsertValueToHead(list, value);
	} else {
		Node* newNode = list_CreateNode(node->data);
		newNode->next = node->next;
		node->data = value;
		node->next = newNode;
	}

}


// insert new value after a node
void list_InsertValueAfterNode(List* list, Node* node, DataType value)
{	
	if(node->next == NULL){
		list_InsertValueToTail(list, value);	
	} else {
		Node* newNode = list_CreateNode(value);
		newNode->next = node->next;
		node->next = newNode;
	}	
}




// insert new node to to the head of the list
void list_InsertNodeToHead(List* list, Node * newNode)
{	
	newNode->next = list->listHead;
	list->listHead = newNode;
}


// insert new node to the tail of the list
void list_InsertNodeToTail(List* list, Node* newNode)
{	
	Node* p = list_GetTail(list);	
	p->next = newNode;
	newNode->next = NULL;
}


// insert newNode after a node location
void list_InsertNodeAfterNode(List* list, Node* nodeLocation, Node* newNode)
{
	if (nodeLocation->next == NULL)	{
		list_InsertNodeToTail(list, newNode);
	} else {
		newNode->next = nodeLocation->next;		
		nodeLocation->next = newNode;
	}
}


// insert newNode before a node location
void list_InsertNodeBeforeNode(List* list, Node* nodeLocation, Node* newNode)
{	
	if(nodeLocation == list->listHead) {
		list_InsertNodeToHead(list, newNode);
	} else {
		DataType temp = nodeLocation->data;
		nodeLocation->data = newNode->data;
		nodeLocation->next = newNode;
		newNode->data = temp; 
	}

}


// delete list head
void list_DeleteHead(List* list)
{
	if (list->listHead->next ==NULL){
		printf("List is empty after deletion! \n");
		free(list);		
		return;
	}

	Node* node = list->listHead;
	list->listHead = list->listHead->next;
	free(node);
}
	
// delete list tail
void list_DeleteTail(List* list)
{	

	Node* p1 = list->listHead; // slow runner
	Node* p2 = list->listHead->next; //fast runner

	if (p2 == NULL){
		printf("List is empty after deletion! \n");
		free(list);
		return;
	}

	while(p2->next!=NULL){
		p1 = p1->next;
		p2 = p2->next; 
		

	}
	free(p2); //p2 is tail
	p1->next = NULL; 
}


// delete from list a node given its pointer
void list_Delete(List* list, Node* node)
{	
	if (node == list->listHead){
		list_DeleteHead(list);
		return;
	}

	Node* p = list_GetTail(list);	
	if(node == p){
		list_DeleteTail(list);
		return;
	}

	p = node->next;
	node->data = node->next->data;
	node->next = node->next->next;
	free(p);	
}


