#include "pila.h"
#include "lista.h"

struct _pila_t{
	nodo_t *tope;
	size_t cantidad;
};

pila_t *pila_crear()
{
	pila_t *pila = calloc(1, sizeof(pila_t));
	if(!pila){
		return NULL;
	}
	return pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{	
	if(!pila){
		return NULL;
	}
	nodo_t *nuevo_nodo = malloc(sizeof(struct nodo));
	if(!nuevo_nodo){
		return NULL;
	}
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = pila->tope;

	pila->tope = nuevo_nodo;
	pila->cantidad++;

	return pila;
}

void *pila_desapilar(pila_t *pila)
{
	if(!pila){
		return NULL;
	}
	nodo_t *nuevo_tope = pila->tope->siguiente;
	void* elemento_a_desapilar = pila_tope(pila);

	free(pila->tope);

	pila->tope = nuevo_tope;

	pila->cantidad--;

	return elemento_a_desapilar;
}

void *pila_tope(pila_t *pila)
{
	if(pila_vacia(pila)){
		return NULL;
	}
	return pila->tope->elemento;
}

size_t pila_tamanio(pila_t *pila)
{
	if(!pila){
		return 0;
	}
	return pila->cantidad;
}

bool pila_vacia(pila_t *pila)
{
	if(!pila || pila_tamanio(pila) == 0){
		return true;
	}
	return false;
}

void pila_destruir(pila_t *pila)
{
	if(!pila){
		return;
	}
	while(!pila_vacia(pila)){
		pila_desapilar(pila);
	}
        free(pila);
}
