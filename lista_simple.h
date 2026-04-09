#ifndef __NOTY_LISTA_PRACTICA_H__

	#define __NOTY_LISTA_PRACTICA_H__

	#include <stddef.h>
	#include <stdbool.h>

	typedef struct Node {
		void*	data;
		size_t	data_size;

		struct Node* next;
		struct Node* last;
	}Node;

	typedef struct {
		Node* head;
		Node* tail;

		size_t length;
	}List;


	// Nodos
	Node* newNode(void* data, size_t size);
	void deleteNode(Node* n);
	bool modifyNode(Node* n, void* data, size_t size);


	// Crear / estado
	List* newList();
	void deleteList(List* l);
	
	static inline bool listIsEmpty(List* l) {
		return l->length == 0;
	}


	// Inserciones
	bool listAdd(List* l, void* data, size_t size, int index);
	bool listAddFirst(List* l, void* data, size_t size);
	bool listAddLast(List* l, void* data, size_t size);


	// Eliminaciones
	bool listRemove(List* l, int index);
	bool listRemoveFirst(List* l);
	bool listRemoveLast(List* l);
	bool listRemoveElement(List* l, void* data, bool (*cmpFunc)(void*, void*));


	// Búsquedas
	void* listGet(List* l, int index);
	int listSearch(List* l, void* data, bool (*cmpFunc)(void*, void*));


	// Modificar
	void listModifyElement(List* l, int index, void* dato, size_t size);


	// Utilidad
	void listPrint(List* l, void (*printFunc)(void*));
	void listEmpty(List* l);

#endif
