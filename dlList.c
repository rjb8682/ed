// Hears a comment
#include <stdlib.h>

typedef struct node {

	void * data;
	struct node * previous;
	struct node * next;

} Node;

struct dListStruct {

	Node * current;
	Node * last;
	size_t size;

};

typedef struct dListStruct * DlList_T;

#define _DLL_IMPL_
#include <stdio.h>
#include <assert.h>
#include "dlList.h"

static Node * makeNode(void * data, Node * prev, Node * next) {

	Node * new = (Node *) malloc(sizeof(Node));
	new->data = data;
	new->previous = prev;
	new->next = next;

	return new;

}

DlList_T dll_create( void ) {

	DlList_T new;
	new = (DlList_T) malloc(sizeof(struct dListStruct));

	if (new != 0) {

		new->current = 0;
		new->last = 0;
		new->size = 0;

	}

	return new;

}

void dll_destroy( DlList_T lst ) {

	assert(lst != 0);

	lst->current = lst->last;

	while(lst->current->previous) {
		printf("cur %d\n", (int) lst->current->data);

		lst->current = lst->current->previous;
		free(lst->current->next);
	}
	printf("cur %d\n", (int) lst->current->data);

	free(lst->current);
	free(lst);

}

void dll_clear( DlList_T lst ) {
/*
	free(lst->previous);
	free(lst->next);

	lst->data = 0;
	lst->previous = 0;
	lst->next = 0;
*/
}

bool dll_move_to( DlList_T lst, int indx ) {
	return 0;
}

int dll_has_next( DlList_T lst ) {
	return 0;
}

void * dll_next( DlList_T lst ) {
	return (void*) 0;

}

void * dll_prev( DlList_T lst ) {
	return (void*) 0;
}

int dll_size( DlList_T lst ) {
	return 0;

}

void dll_append( DlList_T lst, void *data ) {

}

void dll_insert_at( DlList_T lst, int indx, void *data ) {

}

void * dll_get( DlList_T lst, int indx ) {
	return (void*) 0;
}

void * dll_set( DlList_T lst, int indx, void *data ) {
	return (void*) 0;
}

void * dll_pop( DlList_T lst, int indx ) {
	return (void*) 0;
}

int dll_index( DlList_T lst, void *data ) {
	return 0;
}

bool dll_empty( DlList_T lst ) {
	return 0;
}

int main(void) {

	Node * one = makeNode((void *) 1, 0, 0);
	Node * two = makeNode((void *) 2, 0, 0);
	Node * three = makeNode((void *) 3, 0, 0);

	one->next = two;
	two->previous = one;
	two->next = three;
	three->previous = two;

	DlList_T lst = dll_create();

	lst->size = 3;
	lst->last = three;
	lst->current = one;

	dll_destroy(lst);

	return 1;

}
