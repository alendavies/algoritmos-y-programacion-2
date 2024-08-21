#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

void creo_una_pila_y_devuelve_una_pila_vacia_con_tope_nulo()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila != NULL, "La pila creada es válida");
	pa2m_afirmar(pila_tamanio(pila) == 0 && pila_vacia(pila), "La pila creada está vacía");
	pa2m_afirmar(pila_tope(pila) == NULL, "La pila creada tiene tope nulo");

	pila_destruir(pila);
}

void apilo_un_elemento_y_se_incrementa_el_tamanio_de_la_pila()
{
	pila_t *pila = pila_crear();
	int elemento1 = 5;
	int elemento2 = 7;

	pa2m_afirmar(pila_apilar(pila, &elemento1) == pila, "Puedo apilar un elemento en una pila vacía y se devuelve la pila");
	pa2m_afirmar(pila_tamanio(pila) == 1 && !pila_vacia(pila), "Al apilar un elemento el tamaño de la pila aumenta");
	pa2m_afirmar(pila_tope(pila) == &elemento1, "El tope de la pila es el correcto");

	pa2m_afirmar(pila_apilar(pila, &elemento2) == pila, "Puedo apilar un segundo elemento y se devuelve la pila");
	pa2m_afirmar(pila_tamanio(pila) == 2 && !pila_vacia(pila), "Al apilar otro elemento el tamaño de la pila aumenta");
	pa2m_afirmar(pila_tope(pila) == &elemento2, "El tope de la pila es el correcto");

	pila_destruir(pila);
}

void puedo_apilar_un_elemento_NULL()
{
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_apilar(pila, NULL) == pila, "Puedo apilar un elemento NULL");
	pa2m_afirmar(pila_tamanio(pila) == 1 && !pila_vacia(pila), "Al apilar un elemento NULL el tamaño de la pila es 1");
	pa2m_afirmar(pila_tope(pila) == NULL, "El tope de la pila es NULL");

	pila_destruir(pila);
}

void no_se_puede_apilar_en_una_pila_nula()
{
	int elemento = 8;
	pa2m_afirmar(pila_apilar(NULL, &elemento) == NULL, "No puedo apilar en una pila nula");
}

void no_se_puede_desapilar_en_una_pila_nula()
{
	pa2m_afirmar(pila_desapilar(NULL) == NULL, "No puedo desapilar en una pila nula");
}

void desapilo_un_elemento_y_disminuye_el_tamanio_de_la_pila()
{
	pila_t *pila = pila_crear();
	int elemento1 = 5;
	int elemento2 = 7;
	int elemento3 = 10;

	pila_apilar(pila, &elemento1);
	pila_apilar(pila, &elemento2);
	pila_apilar(pila, &elemento3);

	pa2m_afirmar(pila_desapilar(pila) == &elemento3, "Puedo desapilar un elemento y devuelve el elemento desapilado");
	pa2m_afirmar(pila_tamanio(pila) == 2 && !pila_vacia(pila), "Al desapilar un elemento en una pila con 3 elementos, el tamaño de la pila es 2");
	pa2m_afirmar(pila_tope(pila) == &elemento2, "El tope de la pila es el correcto");

	pa2m_afirmar(pila_desapilar(pila) == &elemento2, "Puedo desapilar un segundo elemento y devuelve el elemento desapilado");
	pa2m_afirmar(pila_tamanio(pila) == 1 && !pila_vacia(pila), "Al desapilar un elemento en una pila con 2 elementos, el tamaño de la pila es 1");
	pa2m_afirmar(pila_tope(pila) == &elemento1, "El tope de la pila es el correcto");

	pa2m_afirmar(pila_desapilar(pila) == &elemento1, "Puedo desapilar un tercer elemento y devuelve el elemento desapilado");
	pa2m_afirmar(pila_tamanio(pila) == 0 && pila_vacia(pila), "Al desapilar un tercer elemento en una pila con 1 elemento, el tamaño de la pila es 0");
	pa2m_afirmar(pila_tope(pila) == NULL, "El tope de la pila es el correcto");

	pila_destruir(pila);
}

void creo_una_cola_y_devuelve_una_cola_vacia_con_frente_nulo()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola != NULL, "La cola creada es válida");
	pa2m_afirmar(cola_tamanio(cola) == 0 && cola_vacia(cola), "La cola creada es de tamaño 0");
	pa2m_afirmar(cola_frente(cola) == NULL, "El elemento en el frente de la cola es nulo");

	cola_destruir(cola);
}

void encolo_un_elemento_y_se_incrementa_el_tamanio_de_la_cola()
{
	cola_t *cola = cola_crear();
	int elemento1 = 5;
	int elemento2 = 7;
	int elemento3 = 10;

	pa2m_afirmar(cola_encolar(cola, &elemento1) == cola, "Encolo un elemento en una cola vacía y me devuelve la cola");
	pa2m_afirmar(cola_tamanio(cola) == 1 && !cola_vacia(cola), "Al encolar un elemento el tamaño de la cola aumenta");
	pa2m_afirmar(cola_frente(cola) == &elemento1, "El frente de la cola es el correcto");

	pa2m_afirmar(cola_encolar(cola, &elemento2) == cola, "Encolo un segundo elemento y me devuelve la cola");
	pa2m_afirmar(cola_tamanio(cola) == 2 && !cola_vacia(cola), "Al encolar un segundo elemento el tamaño de la cola aumenta");
	pa2m_afirmar(cola_frente(cola) == &elemento1, "El frente de la cola es el correcto");

	pa2m_afirmar(cola_encolar(cola, &elemento3) == cola, "Encolo un tercer elemento y me devuelve la cola");
	pa2m_afirmar(cola_tamanio(cola) == 3 && !cola_vacia(cola), "Al encolar unn tercer elemento el tamaño de la cola aumenta");
	pa2m_afirmar(cola_frente(cola) == &elemento1, "El frente de la cola es el correcto");
	
	cola_destruir(cola);
}

void no_puedo_encolar_en_una_cola_nula()
{
	int elemento = 1;
	pa2m_afirmar(cola_encolar(NULL, &elemento) == NULL, "No puedo encolar en una cola nula");
}

void puedo_encolar_un_elemento_NULL()
{
	cola_t *cola = cola_crear();
	pa2m_afirmar(cola_encolar(cola, NULL) == cola, "Puedo encolar un elemento NULL");
	cola_destruir(cola);	
}

void no_puedo_desencolar_de_una_cola_vacia_o_nula()
{
	pa2m_afirmar(cola_desencolar(NULL) == NULL, "No puedo encolar en una cola nula");

	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_desencolar(cola) == NULL, "No puedo desencolar en una cola vacía");

	cola_destruir(cola);
}

void desencolo_un_elemento_y_disminuye_el_tamanio_de_la_cola()
{
	cola_t *cola = cola_crear();
	int elemento1 = 5;
	int elemento2 = 7;
	int elemento3 = 10;

	cola_encolar(cola, &elemento1);
	cola_encolar(cola, &elemento2);
	cola_encolar(cola, &elemento3);

	pa2m_afirmar(cola_desencolar(cola) == &elemento1, "Desencolo un elemento y me devuelve ese elemento");
	pa2m_afirmar(cola_tamanio(cola) == 2, "Al desencolar un elemento disminuye el tamaño de la cola");
	pa2m_afirmar(cola_frente(cola) == &elemento2, "Al desencolar un elemento, el nuevo frente de la cola es correcto");

	pa2m_afirmar(cola_desencolar(cola) == &elemento2, "Desencolo un elemento y me devuelve ese elemento");
	pa2m_afirmar(cola_tamanio(cola) == 1, "Al desencolar un elemento disminuye el tamaño de la cola");
	pa2m_afirmar(cola_frente(cola) == &elemento3, "Al desencolar un elemento, el nuevo frente de la cola es correcto");

	pa2m_afirmar(cola_desencolar(cola) == &elemento3, "Desencolo un elemento y me devuelve ese elemento");
	pa2m_afirmar(cola_tamanio(cola) == 0 && cola_vacia(cola), "Al desencolar el ultimo elemento de la cola, queda vacía");
	pa2m_afirmar(cola_frente(cola) == NULL, "Al desencolar el último elemento de la cola, el nuevo frente de la cola es NULL0");

	cola_destruir(cola);
}

void creo_una_lista_y_me_devuelve_una_lista_vacía_con_principio_y_fin_nulos()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista != NULL, "La lista creada es válida");
	pa2m_afirmar(lista_tamanio(lista) == 0 && lista_vacia(lista), "La lista creada es de tamaño 0");
	pa2m_afirmar(lista_ultimo(lista) == NULL, "El último elemento de la lista es nulo");
	pa2m_afirmar(lista_primero(lista) == NULL, "El primer elemento de la lista es nulo");

	lista_destruir(lista);
}

void no_se_puede_insertar_en_una_lista_nula()
{
	char elemento = 'a';
	pa2m_afirmar(lista_insertar(NULL, &elemento) == NULL && lista_insertar_en_posicion(NULL, &elemento, 2) == NULL, "No puedo insertar en una lista nula");
}

void inserto_un_elemento_al_final_y_se_incrementa_el_tamanio_de_la_lista()
{
	lista_t *lista = lista_crear();

	char elemento1 = 'a';
	char elemento2 = 'b';

	pa2m_afirmar(lista_insertar(lista, &elemento1) == lista, "Puedo insertar un elemento al final de una lista vacía");
	pa2m_afirmar(lista_tamanio(lista) == 1 && !lista_vacia(lista), "Al insertar un elemento en una lista vacía el tamaño de la lista es 1");
	pa2m_afirmar(lista_ultimo(lista) == &elemento1 && lista_primero(lista) == &elemento1, "El último de la lista y el primero son el mismo elemento");

	pa2m_afirmar(lista_insertar(lista, &elemento2) == lista, "Puedo insertar un elemento al final de una lista con elementos");
	pa2m_afirmar(lista_tamanio(lista) == 2 && !lista_vacia(lista), "Al insertar un elemento al final de una lista el tamaño de la lista aumenta");
	pa2m_afirmar(lista_ultimo(lista) == &elemento2 && lista_primero(lista) == &elemento1, "El último de la lista y el primero son los correctos");

	lista_destruir(lista);
}

void inserto_un_elemento_y_se_incrementa_el_tamanio_de_la_lista()
{
	lista_t *lista = lista_crear();

	char elemento3 = 'c';
	char elemento4 = 'd';
	char elemento5 = 'e';
	char elemento6 = 'f';
	char elemento7 = 'g';
	
	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento6, 0) == lista, "Puedo insertar un elemento una lista vacia");
	pa2m_afirmar(lista_tamanio(lista) == 1 && !lista_vacia(lista), "Al insertar un elemento a el tamaño de la lista aumenta");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &elemento6, "El elemento en la posicion es el insertado");
	pa2m_afirmar(lista_ultimo(lista) == &elemento6 && lista_primero(lista) == &elemento6, "El último de la lista y el primero son los correctos");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento3, 1) == lista, "Puedo insertar un elemento en una lista con elementos");
	pa2m_afirmar(lista_tamanio(lista) == 2 && !lista_vacia(lista), "Al insertar un elemento en una lista el tamaño de la lista aumenta");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &elemento3, "El elemento en la posicion es el insertado");
	pa2m_afirmar(lista_ultimo(lista) == &elemento3 && lista_primero(lista) == &elemento6, "El último de la lista y el primero son los correctos");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento5, 2) == lista, "Puedo insertar otro elemento en una lista con elementos");
	pa2m_afirmar(lista_tamanio(lista) == 3 && !lista_vacia(lista), "Al insertar un elemento en el medio de una lista el tamaño de la lista aumenta");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &elemento5, "El elemento en la posicion es el insertado");
	pa2m_afirmar(lista_ultimo(lista) == &elemento5 && lista_primero(lista) == &elemento6, "El último de la lista y el primero son los correctos");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento4, 3) == lista, "Puedo insertar un elemento al final de una lista");
	pa2m_afirmar(lista_tamanio(lista) == 4 && !lista_vacia(lista), "Al insertar un elemento al final de una lista el tamaño de la lista aumenta");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == &elemento4, "El elemento en la posicion es el insertado");
	pa2m_afirmar(lista_ultimo(lista) == &elemento4 && lista_primero(lista) == &elemento6, "El último de la lista y el primero son los correctos");

	pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento7, 20) == lista && lista_ultimo(lista) == &elemento7, "Si la posicion no existe, se inserta al final");

	lista_destruir(lista);
}

void no_se_puede_quitar_en_una_lista_nula_o_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_quitar(NULL) == NULL && lista_quitar_de_posicion(NULL, 2) == NULL, "No puedo quitar elementos de una lista nula");

	pa2m_afirmar(lista_quitar(lista) == NULL && lista_quitar_de_posicion(lista, 2) == NULL, "No puedo quitar elementos de una lista vacía");

	lista_destruir(lista);
}

void quito_un_elemento_y_disminuye_el_tamanio_de_la_lista()
{
	lista_t *lista = lista_crear();

	char elemento1 = 'a';
	char elemento2 = 'b';
	char elemento3 = 'c';
	char elemento4 = 'd';

	lista_insertar(lista, &elemento1);
	lista_insertar(lista, &elemento2);
	lista_insertar(lista, &elemento3);
	lista_insertar(lista, &elemento4);

	pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == &elemento3, "Puedo quitar un elemento del medio de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 3, "Al quitar un elemento, el tamaño de la lista disminuye");
	pa2m_afirmar(lista_primero(lista) == &elemento1 && lista_ultimo(lista) == &elemento4, "El primero y el ultimo de la lista son los correctos");

	pa2m_afirmar(lista_quitar(lista) == &elemento4, "Puedo quitar un elemento del final de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 2, "Al quitar un elemento, el tamaño de la lista disminuye");
	pa2m_afirmar(lista_primero(lista) == &elemento1 && lista_ultimo(lista) == &elemento2, "El primero y el ultimo de la lista son los correctos");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == &elemento1, "Puedo quitar un elemento del principio de la lista");
	pa2m_afirmar(lista_tamanio(lista) == 1, "Al quitar un elemento, el tamaño de la lista disminuye");
	pa2m_afirmar(lista_primero(lista) == &elemento2 && lista_ultimo(lista) == &elemento2, "El primero y el ultimo de la lista son los correctos");

	lista_destruir(lista);
}

void creo_un_iterador_y_me_devuelve_un_iterador_valido()
{
	lista_t *lista = lista_crear();
	char elemento = 'a';
	lista_insertar(lista, &elemento);

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_crear(NULL) == NULL, "No se puede crear un iterador de una lista nula");
	pa2m_afirmar(iterador != NULL && iterador->corriente == lista->nodo_inicio && iterador->lista == lista, "Creo un iterador y me devuelve un iterador válido");

	pa2m_afirmar(lista_iterador_elemento_actual(iterador) == lista->nodo_inicio->elemento, "Al crear un iterador, el elemento actual es el primer elemento de la lista");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void no_se_puede_avanzar_el_iterador_en_lista_vacia_o_nula()
{
	lista_t *lista = lista_crear();

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == false && lista_iterador_avanzar(iterador) == false, "No se puede avanzar un iterador en una lista vacia");	

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void no_se_puede_avanzar_en_un_iterador_nulo()
{
	pa2m_afirmar(lista_iterador_avanzar(NULL) == false, "No se puede avanzar en un iterador nulo");
}

void no_se_puede_avanzar_el_iterador_en_la_ultima_posicion()
{
	lista_t *lista = lista_crear();

	char a = 'a', b = 'b', c = 'c';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	iterador->corriente = lista->nodo_fin;

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true && lista_iterador_avanzar(iterador) == false, "No puedo avanzar un iterador en la ultima posicion de la lista");	

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void si_tiene_siguiente_puedo_avanzar()
{
	lista_t *lista = lista_crear();

	char a = 'a', b = 'b', c = 'c';

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);

	lista_iterador_t *iterador = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true && lista_iterador_avanzar(iterador) == true, "Puedo avanzar un iterador si tiene siguiente");	

	lista_iterador_destruir(iterador);
	lista_destruir(lista);
}

void un_iterador_nulo_no_puede_tener_siguiente()
{
	pa2m_afirmar(lista_iterador_tiene_siguiente(NULL) == false, "Un iterador nulo no tiene siguiente");
}

int elemento_es_igual_a(void *_a, void *_b)
{
	char *a = _a;
	char *b = _b;

	if(a && b && *a == *b)
		return 0;

	return -1;
}

void no_puedo_buscar_un_elemento_en_una_lista_nula_o_vacia()
{	
	lista_t *lista = lista_crear();
	int elemento = 'a';

	pa2m_afirmar(lista_buscar_elemento(lista, elemento_es_igual_a, &elemento) == NULL, "No puedo buscar un elemento en una lista vacía");

	pa2m_afirmar(lista_buscar_elemento(NULL, elemento_es_igual_a, &elemento) == NULL, "No puedo buscar un elemento en una lista nula");

	pa2m_afirmar(lista_buscar_elemento(lista, NULL, &elemento) == NULL, "No puedo buscar un elemento en una lista con funcion nula");

	lista_destruir(lista);
}

void busco_un_elemento_que_esta_en_la_lista_y_lo_encuentra()
{
	lista_t *lista = lista_crear();
	int elemento1 = 10;
	int elemento2 = 5;
	int elemento3 = 8;
	lista_insertar(lista, &elemento1);
	lista_insertar(lista, &elemento2);
	lista_insertar(lista, &elemento3);

	pa2m_afirmar(lista_buscar_elemento(lista, elemento_es_igual_a, &elemento1) == &elemento1, "Busco el primer elemento de la lista y lo encuentra");
	pa2m_afirmar(lista_buscar_elemento(lista, elemento_es_igual_a, &elemento2) == &elemento2, "Busco un elemento de la lista y lo encuentra");
	pa2m_afirmar(lista_buscar_elemento(lista, elemento_es_igual_a, &elemento3) == &elemento3, "Busco el último elemento de la lista y lo encuentra");

	lista_destruir(lista);
}

void busco_un_elemento_que_no_esta_en_la_lista_y_no_lo_encuentra()
{
	lista_t *lista = lista_crear();
	int elemento = 'a';

	pa2m_afirmar(lista_buscar_elemento(lista, elemento_es_igual_a, &elemento) == NULL, "Busco un elemento que no está en la lista y no lo encuentra");

	lista_destruir(lista);
}

bool mostrar_elemento(void *elemento, void *contador)
{
	if (elemento && contador)
		return true;
	return false;
}

void no_se_puede_iterar_con_lista_nula_o_vacia()
{
	lista_t *lista = lista_crear();
	int contador = 0;

	pa2m_afirmar(lista_con_cada_elemento(lista, mostrar_elemento, (void *)&contador) == 0, "No se puede iterar una lista vacia");
	pa2m_afirmar(lista_con_cada_elemento(NULL, mostrar_elemento, (void *)&contador) == 0, "No se puede iterar una lista nula");

	pa2m_afirmar(lista_con_cada_elemento(lista, NULL, (void *)&contador) == 0, "No se puede iterar una lista con funcion nula");

	lista_destruir(lista);
}

void puedo_iterar_y_me_devuelve_la_cantidad_de_elementos()
{
	lista_t *lista = lista_crear();
	int contador = 0;
	char elemento1 = 'c';
	char elemento2 = 'd';
	char elemento3 = 'e';

	lista_insertar(lista, &elemento1);
	lista_insertar(lista, &elemento2);
	lista_insertar(lista, &elemento3);

	pa2m_afirmar(lista_con_cada_elemento(lista, mostrar_elemento, (void *)&contador) == 3, "Puedo iterar en una lista y me devuelve la cantidad de elementos");

	lista_destruir(lista);
}

int main() {

	pa2m_nuevo_grupo("Pruebas de creación de pila");
  	creo_una_pila_y_devuelve_una_pila_vacia_con_tope_nulo();

  	pa2m_nuevo_grupo("Pruebas de apilar");
	no_se_puede_apilar_en_una_pila_nula();
	puedo_apilar_un_elemento_NULL();
	apilo_un_elemento_y_se_incrementa_el_tamanio_de_la_pila();

	pa2m_nuevo_grupo("Pruebas de desapilar");
	no_se_puede_desapilar_en_una_pila_nula();
	desapilo_un_elemento_y_disminuye_el_tamanio_de_la_pila(); 

	pa2m_nuevo_grupo("Pruebas de creación de cola");
  	creo_una_cola_y_devuelve_una_cola_vacia_con_frente_nulo();

	pa2m_nuevo_grupo("Pruebas de encolar");
	no_puedo_encolar_en_una_cola_nula();
	puedo_encolar_un_elemento_NULL();
	encolo_un_elemento_y_se_incrementa_el_tamanio_de_la_cola();

	pa2m_nuevo_grupo("Pruebas de desencolar");
	no_puedo_desencolar_de_una_cola_vacia_o_nula();
	desencolo_un_elemento_y_disminuye_el_tamanio_de_la_cola();

	pa2m_nuevo_grupo("Pruebas de creación de lista");
	creo_una_lista_y_me_devuelve_una_lista_vacía_con_principio_y_fin_nulos();

	pa2m_nuevo_grupo("Pruebas de insertar al final en lista");
	no_se_puede_insertar_en_una_lista_nula();
	inserto_un_elemento_al_final_y_se_incrementa_el_tamanio_de_la_lista();

	pa2m_nuevo_grupo("Pruebas de insertar en posicion en lista");
	no_se_puede_insertar_en_una_lista_nula();
	inserto_un_elemento_y_se_incrementa_el_tamanio_de_la_lista();

	pa2m_nuevo_grupo("Pruebas de quitar al final en lista");
	no_se_puede_quitar_en_una_lista_nula_o_vacia();
	quito_un_elemento_y_disminuye_el_tamanio_de_la_lista();

	pa2m_nuevo_grupo("Pruebas de buscar elemento en lista");
	no_puedo_buscar_un_elemento_en_una_lista_nula_o_vacia();
	busco_un_elemento_que_esta_en_la_lista_y_lo_encuentra();
	busco_un_elemento_que_no_esta_en_la_lista_y_no_lo_encuentra();
	
	pa2m_nuevo_grupo("Pruebas de iterador externo");
	creo_un_iterador_y_me_devuelve_un_iterador_valido();
	un_iterador_nulo_no_puede_tener_siguiente();
	no_se_puede_avanzar_en_un_iterador_nulo();
	no_se_puede_avanzar_el_iterador_en_lista_vacia_o_nula();
	no_se_puede_avanzar_el_iterador_en_la_ultima_posicion();
	si_tiene_siguiente_puedo_avanzar();

	pa2m_nuevo_grupo("Pruebas de iterador interno");
	no_se_puede_iterar_con_lista_nula_o_vacia();
	puedo_iterar_y_me_devuelve_la_cantidad_de_elementos();

  	return pa2m_mostrar_reporte();
}
