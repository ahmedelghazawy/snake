#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


//Defining the node for the linedlist
struct Node
{	
	int data;
	Node* next;
};


Node* insertLast( Node* h, int data )	//can also be called push_back
{
	//Creates the linkedlist if it is not created 
	if(h == NULL )
	{
		h = (Node*)malloc (sizeof(Node));	//Allocate memory for the new node
		h->data = data;	//Insert the required data into the new node
		h->next = NULL;	//Make sure the next pointer is pointing to NULL
		return h;	//return the recently created node as the new header
	}

	Node *it = h;	//create an iterator (pointer) starting from the header
	
	//Position the iterator on the last node
	while( it->next != NULL)
		it = it->next;

	//Create the new node (to be inserted)
	Node* tmp = (Node*)malloc( sizeof(Node) );
	tmp->next = NULL;
	tmp->data = data;

	//Attach the new node to the original linkedlist
	it->next = tmp;

	//return the address of the modified linkedlist
	return h;

}

Node* insertFirst( Node* h, int data )	//can also be called push_front
{
	//Creates the linkedlist if it is not created 
	if(h == NULL )
	{
		h = (Node*)malloc (sizeof(Node));	//Allocate memory for the new node
		h->data = data;	//Insert the required data into the new node
		h->next = NULL;	//Make sure the next pointer is pointing to NULL
		return h;	//return the recently created node as the new header
	}

	//Create the new node (to be inserted)
	Node* tmp = (Node*)malloc( sizeof(Node) );
	tmp->data = data;
	tmp->next = h;	//attach its next pointer to the header of the original linkedList

	h = tmp;	//make sure the the header points to the first Node (recently inserted)

	return h;	//return the address of the modified header

	
}

Node* removeLast( Node* h, int *removedData )
{
	//No LinkedList (user error )
	if(h == NULL)
		return NULL;

	//only a single node exists
	if(h->next == NULL)
	{
		*removedData = h->data;
		free( h );
		return NULL;	//return NULL, which means the LinkedList is destroyed and became empty
	}

	Node* it = h;
	
	//position the iterator on the node behind the last one
	while( it->next->next != NULL)
		it = it->next;

	*removedData = it->next->data;	//take a copy of the data that will be removed
	free( it->next );	//free the node (delete it)
	it->next = NULL;	//make sure the last node's next pointer is pointing to NULL

	return h;

}

Node* removeFirst( Node* h, int *removedData )
{
	//No LinkedList (user error )
	if(h == NULL)
		return NULL;

	//only a single node exists
	if(h->next == NULL)
	{
		*removedData = h->data;
		free( h );
		return NULL;	//return NULL, which means the LinkedList is destroyed and became empty
	}

	Node* tmp = h->next;	//take a copy of the 2nd node's address
	*removedData = h->data;	//take a copy of the data that will be removed

	free( h );	//free the first node (delete it)
	
	h = tmp;	//make sure that the header points to the correct node (2nd one) after removing the first node !

	return h;

}

void printLinkedList( Node* h )
{
	//if the linkedList does not exist, then, stop the function
	if(h == NULL)
		return ;	

	Node* it = h;
	while( it != NULL)
	{
		printf("%d -> ", it->data);
		it = it->next;
	}
	printf("NULL\n");
}

int getLinkedListSize( Node* h )
{
	if(h == NULL)
		return 0;

	int count = 0;
	Node* it = h;
	while( it != NULL)
	{
		count++;
		it = it->next;
	}
	return count;
}

Node* findNode( Node* h, int reqData )
{
	if(h == NULL)
		return NULL;
	Node* it = h;
	while( it != NULL )
	{
		if(it->data == reqData)
			return it;	//it data matches, return the node's address
		it = it->next;
	}
	return NULL;
}

Node* deleteNode( Node* h, Node *dataToDelete, bool *success )
{
	if(h == NULL)
		return NULL;

	//special case, if the header is the node to be deleted
	if(h == dataToDelete)
	{
		Node* tmp = h->next;
		free(h);
		h = tmp;
		*success = true;
		return h;
	}

	Node* it = h;
	while( it->next != NULL )
	{
		if( it->next == dataToDelete )
		{
			Node* tmp = it->next->next;
			free(it->next);
			it->next = tmp;
			*success = true;
			return h;
		}
		it = it->next;
	}
	*success = false;
	return h;
}

Node* mergeLinkedList( Node* h1, Node* h2 )
{
	if( h1 == NULL || h2 == NULL)	//if any of the LinkedLists don't exist, return h1 as the new list (even it is NULL !!!)
		return h1;
	
	Node* it = h1;

	//Skip to the end of the first linkedList
	while( it->next != NULL)
		it = it->next;
	//attach it to the 2nd linkedList
	it->next = h2;

	return h1;	//return the address of the modified linkedList (1st one)

}
bool isCyclic( Node* h )
{
	if( h == NULL || h->next == NULL )
		return false;

	Node* slowIt = h;
	Node* fastIt = h;

	while( fastIt != NULL)
	{
		if(fastIt->next == NULL)
			return false;

		fastIt = fastIt->next->next;
		slowIt = slowIt->next;

		if(fastIt == slowIt)
			return true;
	}
	return false;
}
void main()
{

	//Create two empty linked Lists
	Node* linkedList1 = NULL;	//the linkedlist's header must be pointing to NULL (initialization)
	Node* linkedList2 = NULL;
	int tmp;	//variable to be used later

	printf("Inserting data into the FIRST linked list...\n");
	//insert some data into the linked list
	linkedList1 = insertLast( linkedList1, 1);
	linkedList1 = insertLast( linkedList1, 2);
	linkedList1 = insertLast( linkedList1, 3);
	linkedList1 = insertLast( linkedList1, 4);
	linkedList1 = insertLast( linkedList1, 5);
	linkedList1 = insertLast( linkedList1, 6);
	linkedList1 = insertLast( linkedList1, 7);
	linkedList1 = insertLast( linkedList1, 8);

	printf("Inserting data into the SECOND linked list...\n");
	//insert some data into the linked list
	linkedList2 = insertLast( linkedList2, 10);
	linkedList2 = insertLast( linkedList2, 20);
	linkedList2 = insertLast( linkedList2, 30);
	linkedList2 = insertLast( linkedList2, 40);


	printf("Printing the FIRST linked list...\n");
	printLinkedList( linkedList1 );

	printf("Printing the SECOND linked list...\n");
	printLinkedList( linkedList2 );

	printf("Removing the LAST two elements from the FIRST linked list...\n");
	linkedList1 = removeLast(linkedList1, &tmp);	
	linkedList1 = removeLast(linkedList1, &tmp);	

	printf("Printing the FIRST linked list...\n");
	printLinkedList( linkedList1 );

	printf("Removing the FIRST element from the SECOND linked list...\n");
	linkedList2 = removeFirst(linkedList2, &tmp);	

	printf("Printing the SECOND linked list...\n");
	printLinkedList( linkedList2 );

	printf("Printing the size of both linked lists...\n");
	printf("The size for the FIRST linked list is %d\n", getLinkedListSize(linkedList1) );
	printf("The size for the SECOND linked list is %d\n", getLinkedListSize(linkedList2) );

	printf("Merging the two linked lists (will only modify the FIRST linked list, the second one will remain intact)...\n");
	linkedList1 = mergeLinkedList( linkedList1, linkedList2);

	printf("Printing the FIRST linked list...\n");
	printLinkedList( linkedList1 );
	printf("Printing the SECOND linked list...\n");
	printLinkedList( linkedList2 );

	printf("Enter data to look for inside the FIRST linked list: ");
	scanf("%d", &tmp);

	if(findNode(linkedList1, tmp) != NULL)
		printf("Data found !!!\n");
	else
		printf("Data not found !!!\n");
	
	printf("Enter data to delete from the first Linked List: ");
	scanf("%d", &tmp);
	Node* dNode = findNode(linkedList1, tmp);
	bool success;
	linkedList1 = deleteNode( linkedList1, dNode, &success); 
	if(success == true )
		printf("%d deleted !!!\n", tmp);
	else
		printf("%d is not found !!!\n", tmp);

	printf("Printing the FIRST linked list...\n");
	printLinkedList( linkedList1 );
	


	printf("Creating an intentional cycle in linked list 1...\n");
	linkedList1->next->next = linkedList1->next;
	
	
 	printf("Linked List 1 Cyclic ? (1=YES, 0=NO)   :   , %d\n", isCyclic(linkedList1) );
	printf("Linked List 2 Cyclic ? (1=YES, 0=NO)   :   , %d\n", isCyclic(linkedList2) );
	

	getch();

	

}