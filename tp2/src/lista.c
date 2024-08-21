#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

lista_t *lista_crear()
{
	lista_t *lista = calloc(1, sizeof(lista_t));
	if(!lista){
		return NULL;
	}
	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if(!lista){
		return NULL;
	}
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo){
		free(lista);
		return NULL;
	}
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;

	if(lista_vacia(lista)){
		lista->nodo_inicio = nuevo_nodo;
	}
	else{
		lista->nodo_fin->siguiente = nuevo_nodo;
	}
	lista->nodo_fin = nuevo_nodo;
	lista->cantidad++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion)
{
	if(!lista){
		return NULL;
	}
	if(posicion >= lista_tamanio(lista) || lista_vacia(lista)){ //insertar al final
		return lista_insertar(lista, elemento);
	}

	nodo_t *nuevo_nodo = malloc(sizeof(struct nodo));
	if(!nuevo_nodo){
		free(lista);
		return NULL;
	}
	nuevo_nodo->elemento = elemento;

	if(posicion == 0){ //insertar al principio
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		if(lista_vacia(lista)){
			lista->nodo_fin = nuevo_nodo;
		}			
	}
	else{
		int i = 0;
		nodo_t *actual = lista->nodo_inicio;
		while( i < posicion-1){ //Insertar al medio 
			actual = actual->siguiente;
			i++;
		}
		nuevo_nodo->siguiente = actual->siguiente;
		actual->siguiente = nuevo_nodo;
	}
	lista->cantidad++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if(!lista || lista_vacia(lista)){
		return NULL;
	}
	void *elemento_a_quitar = lista->nodo_fin->elemento;

	if(lista_tamanio(lista) == 1){
		free(lista->nodo_fin);
		lista->nodo_fin = NULL;
		lista->nodo_inicio = NULL;
	}
	else{
		nodo_t *actual = lista->nodo_inicio;
		while(actual->siguiente != lista->nodo_fin){
			actual = actual->siguiente;
		}
		free(lista->nodo_fin);
		lista->nodo_fin = actual;
		lista->nodo_fin->siguiente = NULL;
	}
	lista->cantidad--;

	return elemento_a_quitar;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if(!lista || lista_vacia(lista)){
		return NULL;
	}
	void *elemento_a_quitar = NULL;

	if(posicion >= lista_tamanio(lista)-1){ //Quitar al final
		return lista_quitar(lista);
	}
	else if(posicion == 0){ //Quitar al inicio
		elemento_a_quitar = lista->nodo_inicio->elemento;
		nodo_t *nuevo_inicio = lista->nodo_inicio->siguiente;
		free(lista->nodo_inicio);
		lista->nodo_inicio = nuevo_inicio;
	}
	else{
		int i = 0;
		nodo_t *actual = lista->nodo_inicio;
		while( i < posicion-1){ //Quitar al medio 
			actual = actual->siguiente;
			i++;
		}
		elemento_a_quitar = actual->siguiente->elemento;
		nodo_t *nodo_a_quitar  = actual->siguiente;
		actual->siguiente = actual->siguiente->siguiente;
		free(nodo_a_quitar);
	}
	lista->cantidad--;
	return elemento_a_quitar;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if(!lista || lista_vacia(lista) || posicion >= lista_tamanio(lista)){
		return NULL;
	}
	void *elemento = NULL;

	if(posicion == 0){
		return lista_primero(lista);
	}
	else if(posicion == lista_tamanio(lista)-1){
		return lista_ultimo(lista);
	}
	else{
		int i = 0;
		nodo_t *actual = lista->nodo_inicio;
		while(i < posicion){
			actual = actual->siguiente;
			i++;
		}
		elemento = actual->elemento;
	}
	return elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *), void *contexto)
{
	if(!lista || lista_vacia(lista) || !comparador){
		return NULL;
	}
	size_t i = 0;
	while(i < lista_tamanio(lista)){
		if(comparador(lista_elemento_en_posicion(lista, i), contexto) == 0){
			return lista_elemento_en_posicion(lista, i);
		}
		i++;
	}
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if(!lista || lista_vacia(lista)){
		return NULL;
	}
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(!lista || lista_vacia(lista)){
		return NULL;
	}
	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	if(!lista || lista->cantidad == 0){
		return true;
	}
	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	if(!lista){
		return 0;
	}
	return lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	if(!lista){
		return;
	}
	int i = 0;
	nodo_t *aux = lista->nodo_inicio;
	while(i < lista_tamanio(lista)){
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		free(aux);
		aux = lista->nodo_inicio;
		i++;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if(!lista){
		return;
	}
	if(funcion){
		int i = 0;
		nodo_t *aux = lista->nodo_inicio;
		while(i < lista_tamanio(lista)){
			funcion(aux->elemento);
			aux = aux->siguiente;
			i++;
		}
	}
	lista_destruir(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if(!lista){
		return NULL;
	}
	lista_iterador_t *iterador = malloc(sizeof(struct lista_iterador));
	if(!iterador){
		return NULL;
	}
	iterador->corriente = lista->nodo_inicio;
	iterador->lista = lista;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if(!iterador || !iterador->corriente){
		return false;
	}
	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if(!iterador || !lista_iterador_tiene_siguiente(iterador)){
		return false;
	}
	
	iterador->corriente = iterador->corriente->siguiente;
	if(!iterador->corriente){
        	return false;
	}
	return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if(!iterador || !iterador->corriente || lista_vacia(iterador->lista)){
		return NULL;
	}
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if(!iterador){
		return;
	}
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *), void *contexto)
{
	if(!lista || lista_vacia(lista) || !funcion){
		return 0;
	}
	size_t cantidad = 0;
	nodo_t *actual = lista->nodo_inicio;
	while(actual != NULL && funcion(actual->elemento, contexto)){
		actual = actual->siguiente;
		cantidad++;
	}
	if(!actual){
		cantidad--;
	}
	return cantidad+1;
}
