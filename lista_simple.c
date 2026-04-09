#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_simple.h"

#define invalidAddIndex(i, n)	( i < 0 || i >  n )
#define invalidIndex(i, n)	( i < 0 || i >= n )


// Nodos
Node* newAuxNode() {
	Node* n = (Node*) malloc(sizeof(Node));

	if(n) *n = (Node) {NULL, 0, NULL, NULL};

	return n;
}

Node* nodeGet(List* l, int index);
Node* nodeGetH(Node* n, int index);
Node* nodeGetT(Node* n, int index);

Node* newNode(void* data, size_t size) {
	Node* n = (Node*) malloc(sizeof(Node));
	void* d = malloc(size);
	
	if(!n || !d) {
		free(n);
		free(d);

		return NULL;
	}
	memcpy(d, data, size);
	*n = (Node) {d, size, NULL, NULL};

	return n;
}

void deleteNode(Node* n) {
	if(n)	free(n->data);
	free(n);	
}

bool modifyNode(Node* n, void* data, size_t size) {
	if(!n)	return false;

	if(size != n->data_size) {
		void *tmp = realloc(n->data, size);

		if(!tmp)	return false;
		n->data = tmp;
	}
	memcpy(n->data, data, size);

	return true;
}

Node* nodeGet(List* l, int index) {
	int indexR = l->length - index;

	return (index <= indexR) ? nodeGetH(l->head, index) : nodeGetT(l->tail, indexR + 1);
}

Node* nodeGetH(Node* n, int index) {
	Node *aux = n;
	for(int i = 0; i < index; i++)
		aux = aux->next;
	
	return aux;
}

Node* nodeGetT(Node* n, int index) {
	Node *aux = n;
	for(int i = 0; i < index; i++)
		aux = aux->last;
	
	return aux;
}

// Crear / estado
List* newList() {
	List* l = (List*) malloc(sizeof(List));
	if(!l) return NULL;

	Node* h = newAuxNode();
	Node* t = newAuxNode();

	if(!h || !t) {
		deleteNode(h);
		deleteNode(t);
		deleteList(l);
		
		return NULL;
	}
	h->next = h->last = t;
	t->next = t->last = h;	

	*l = (List) {h, t, 0};

	return l;
}

void deleteList(List* l) {
	if(!listIsEmpty(l))	listEmpty(l);

	if(l) {
		deleteNode(l->head);
		deleteNode(l->tail);
	}
	
	free(l);
}	


// Inserciones
bool listAdd(List* l, void* data, size_t size, int index) {
	Node* n;

	if(invalidAddIndex(index, l->length))	return false;
	if(!(n = newNode(data, size)))		return false;

	Node* aux = nodeGet(l, index);

	n->next = aux->next;
	n->last = aux;
	n->next->last = aux->next = n;
		
	(l->length)++;

	return true;
} 

bool listAddFirst(List* l, void* data, size_t size) {
	return listAdd(l, data, size, 0);
}

bool listAddLast(List* l, void* data, size_t size) {
	return listAdd(l, data, size, l->length);
}


// Eliminaciones
bool listRemove(List* l, int index) {
	if(invalidIndex(index, l->length))	return false;

	Node* n = nodeGet(l, index);
	Node* aux = n->next;

	n->next = aux->next;
	aux->next->last = n;

	deleteNode(aux);
	(l->length)--;

	return true;
}

bool listRemoveFirst(List* l) {
	return listRemove(l, 0);
}

bool listRemoveLast(List* l) {
	return listRemove(l, l->length);
}

bool listRemoveElement(List* l, void* data, bool (*cmpFunc)(void*, void*)) {
	if(!listIsEmpty(l))			return false;

	// Añadir remove

	return true;
}


// Búsquedas
void* listGet(List* l, int index) {
	if(invalidIndex(index, l->length))	return NULL;

	Node* n = nodeGet(l, index);

	return n->data;
}

int listSearch(List* l, void* data, bool (*cmpFunc)(void*, void*));

// Modificar
void listModifyElement(List* l, int index, void* dato, size_t size);

// Utilidad
void listPrint(List* l, void (*printFunc)(void*)) {
	if(!l)	return;
	if(listIsEmpty(l)) {
		puts("[]");
		return;
	}

	printf("[");

	Node* tmp = l->head;
	while((tmp = tmp->next) != l->tail)
		printFunc(tmp->data);

	puts("\b\b]");
}

void listEmpty(List* l) {
	if(!l || listIsEmpty(l))	return;

	Node* tmp = l->head->next;
	while(tmp != l->tail) {
		Node* ntr = tmp;
		tmp = tmp->next;

		free(ntr);
	}

	l->head->next = l->tail;
	l->tail->last = l->head;

	l->length = 0;
}

