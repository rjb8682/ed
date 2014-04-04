// Hears a comment
#include <stdlib.h>

/// The struct that represents a node in the list. Each node
/// consists of the data at this node, the previous node, and
/// the next node. The data is of type void * and the next/previous
/// is of type struct node.
typedef struct node {

	void * data;
	struct node * previous;
	struct node * next;

} Node;

// This implementation of the struct consists of the current or curser node,
// the current index or 'currIndex' of the current node in the list, the last
// node in the list, and the size of the list.
struct dListStruct {

	Node * current;
	size_t currIndex;
	Node * last;
	size_t size;

};

typedef struct dListStruct * DlList_T;

#define _DLL_IMPL_
#include <stdio.h>
#include <assert.h>
#include "dlList.h"

/// Takes the contents of a node and creates a Node * to a new node.
/// @param data the data for the node
/// @param prev the previous node to this node.
/// @param next the next node to this node.
/// @return a newly allocated Node * with the contents from the parameters
static Node * makeNode(void * data, Node * prev, Node * next) {

	Node * new = (Node *) malloc(sizeof(Node));
	new->data = data;
	new->previous = prev;
	new->next = next;

	return new;

}

// Creates and allocates memory for a new DlList_T
DlList_T dll_create( void ) {

	DlList_T new;
	new = (DlList_T) malloc(sizeof(struct dListStruct));

	if (new != 0) {

		new->current = 0;
		new->currIndex = 0;
		new->last = 0;
		new->size = 0;

	}

	return new;

}

// Loops through and frees all of the ndoes then frees the list itself.
void dll_destroy( DlList_T lst ) {

	assert(lst != 0);

	lst->current = lst->last;

	while (lst->current->previous) {

		lst->current = lst->current->previous;
		free(lst->current->next);
	}

	free(lst->current);
	free(lst);

}

// Frees the nodes in the list and sets the contents to null.
void dll_clear( DlList_T lst ) {

	assert(lst != 0);

	while (lst->current->previous) {

		lst->current = lst->current->previous;
		free(lst->current->next);
	}

	free(lst->current);
	lst->current = 0;
	lst->currIndex = 0;
	lst->last = 0;
	lst->size = 0;

}

// Moves the cursor to the indexed node in the list. Returns true
// if move is successful, false otherwise.
bool dll_move_to( DlList_T lst, int indx ) {

	if (indx < 0 || indx >= lst->size) { return false; }

	int direction = -1;

	if (indx > lst->currIndex) {
		direction = 1;
	}

	while(lst->currIndex != indx) {

		if (direction == 1) {
			lst->current = lst->current->next;
		} else {
			lst->current = lst->current->previous;
		}

		lst->currIndex += direction;

	}

	return true;

}

// Checks if the current node in the list is null.
int dll_has_next( DlList_T lst ) {

	return lst->currIndex >= 0 && lst->currIndex < lst->size;

}

// returns the data of the current node THEN moves the cursor for the current node
// to the next node in the list.
void * dll_next( DlList_T lst ) {
	
	Node * current = lst->current;
	lst->current = lst->current->next;
	lst->currIndex++;

	return current->data;

}

// returns the data of the current node THEN moves the cursor for the current node
// to the previous node in the list.
void * dll_prev( DlList_T lst ) {
	
	Node * current = lst->current;
	lst->current = lst->current->previous;
	lst->currIndex--;

	return current->data;

}

// returns the size of the list.
int dll_size( DlList_T lst ) {

	return lst->size;

}

// Adds a new node to the end of the list.
void dll_append( DlList_T lst, void *data ) {

	Node * toAdd = makeNode(data, 0, 0);
	toAdd->previous = lst->last;

	lst->last->next = toAdd;
	lst->current = toAdd;
	lst->last = lst->current;
	lst->size += 1;

}

// If index is valid, it inserts a new node at that index in the list.
void dll_insert_at( DlList_T lst, int indx, void *data ) {

	int index = dll_size(lst) - 1;

	while (index >= 0) {

		if (index == indx) {

			Node * newPrevious = lst->current->previous;
			Node * newNext = lst->current;

			lst->current = makeNode(data, newPrevious, newNext);
			lst->size++;

		}

		lst->current = lst->current->previous;

	}

}

// returns the data at the node specified by the index given.
void * dll_get( DlList_T lst, int indx ) {

	if (indx >= lst->size || indx < 0) {

		return (void*) 0;

	}

	int index = lst->size - 1;

	Node * current = lst->current;
	while (index >= 0) {

		if (index == indx) {

			return current->data;

		} 

		index--;
		current = current->previous;

	}

	return (void*) 0;
}

// creates a new node for the given data and inserts it at the index given.
// Returns the data of the old node that it replaced.
void * dll_set( DlList_T lst, int indx, void *data ) {

	Node * newNode = makeNode(data, 0, 0);

	int index = lst->size - 1;

	Node * current = lst->current;
	while (index >= 0) {

		if (index == indx) {

			Node * newPrevious = current->previous;
			Node * newNext = current-> next;

			newNode->previous = newPrevious;
			newNode->next = newNext;

			free(lst->current);

			lst->current = newNode;

			return current->data;

		} 

		index--;
		current = current->previous;

	}

	return (void*) 0;
}

// Removes the item at the given index and returns its data value.
void * dll_pop( DlList_T lst, int indx ) {

	void * toReturn = dll_get(lst, indx);

	int index = lst->size - 1;

	Node * current = lst->current;
	while (index >= 0) {

		if (index == indx) {

			lst->size--;
			free(current);
			return toReturn;

		} 

		index--;
		current = current->previous;

	}

	return (void *) 0;

}

// returns the index of the node which has the same data as the one given.
int dll_index( DlList_T lst, void *data ) {
	int toReturn = lst->size - 1;

	Node * current = lst->current;
	while (toReturn >= 0) {

		if (current->data == data) {

			return toReturn;

		}

		toReturn--;

	}

	return -1;
}

/// Prints the list to stdout.
/// @param lst the already created list.
void printList(DlList_T lst) {

	printf("Null, ");

	for (int i = 0; i < lst->size; i++) {

		printf("%d, ", (int)dll_get(lst, i));

	}

	printf("Null");

}

// returns true if lst->size == 0, false otherwise
bool dll_empty( DlList_T lst ) {

	if (dll_size(lst)) {
		return false;
	}

	return true;
}

int main(void) {

	DlList_T lst = dll_create();

	printf( "Initial list is %s\n", dll_empty(lst) ? "empty" : "not empty" );

	dll_append(lst, (void *)1);
	dll_append(lst, (void *)2);
	dll_append(lst, (void *)3);
	dll_append(lst, (void *)4);

	printList(lst);

	dll_insert_at(lst, 2, (void *)6);

	printList(lst);

	printf( "List is %s\n", dll_empty(lst) ? "empty" : "not empty" );

	dll_destroy(lst);

	printList(lst);

	return 1;

}
