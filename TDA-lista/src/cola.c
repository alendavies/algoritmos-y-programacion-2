#include "cola.h"
#include "lista.h"

struct _cola_t{
	nodo_t *principio;
	nodo_t *fin;
	size_t cantidad;
};

cola_t *cola_crear()
{
	cola_t *cola = calloc(1, sizeof(cola_t));
	if(!cola){
		return NULL;
	}
	return cola;
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	if(!cola){
		return NULL;
	}
	nodo_t *nuevo_nodo = malloc(sizeof(struct nodo));
	if(!nuevo_nodo){
		return NULL;
	}
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = cola->fin;
	
	if(cola_vacia(cola)){
		cola->principio = nuevo_nodo;
	}
	else{
		cola->fin->siguiente = nuevo_nodo;
	}
	cola->fin = nuevo_nodo;

	cola->cantidad++;

	return cola;
}

void *cola_desencolar(cola_t *cola)
{
	if(!cola || cola_vacia(cola)){
		return NULL;
	}
	void* elemento_a_desencolar = cola_frente(cola);
	nodo_t *nuevo_inicio = cola->principio->siguiente;

	free(cola->principio);

	cola->principio = nuevo_inicio;

	cola->cantidad--;

	return elemento_a_desencolar;
}

void *cola_frente(cola_t *cola)
{
	if(cola_vacia(cola)){
		return NULL;
	}
	return cola->principio->elemento;
}

size_t cola_tamanio(cola_t *cola)
{
	if(!cola){
		return 0;
	}
	return cola->cantidad;
}

bool cola_vacia(cola_t *cola)
{
	if(!cola || cola_tamanio(cola) == 0){
		return true;
	}
	return false;
}

void cola_destruir(cola_t *cola)
{
	if(!cola){
		return;
	}
	while(!cola_vacia(cola)){
		cola_desencolar(cola);
	}
	free(cola);
}
