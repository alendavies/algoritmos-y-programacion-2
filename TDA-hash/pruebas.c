#include "src/hash.h"
#include "pa2m.h"
#include <stdlib.h>

void creo_un_hash_y_devuelve_un_hash_valido(){

	hash_t *hash = hash_crear(10);

	pa2m_afirmar(hash != NULL, "Creo un hash y me devuelve un hash no nulo");
	pa2m_afirmar(hash_cantidad(hash) == 0, "Creo un hash y está vacío");

	hash_destruir(hash);
}

void inserto_un_elemento_y_se_inserta_correctamente(){

	hash_t *hash = hash_crear(10);
	void *anterior = NULL;

	char *mariano = "Mariano";
	char *lucas = "Lucas";
	char *manu = "Manu";
	char *guido = "Guido";
	char *matias = "Matias";
	char *azul = "Azul";

	pa2m_afirmar(hash_insertar(hash, "AC123BD", mariano, &anterior) != NULL, "Inserto un elemento correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "El hash tiene un elemento.");

	pa2m_afirmar(hash_insertar(hash, "OPQ976", lucas, &anterior) != NULL, "Inserto un segundo elemento correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 2, "El hash tiene dos elementos.");

	pa2m_afirmar(hash_insertar(hash, "A421ACB", manu, &anterior) != NULL, "Inserto un tercer elemento correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 3, "El hash tiene tres elementos.");

	pa2m_afirmar(hash_insertar(hash, "AA442CD", guido, &anterior) != NULL, "Inserto un cuarto elemento correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El hash tiene cuatro elementos.");

	pa2m_afirmar(hash_contiene(hash, "AC123BD"), "Busco un elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "AC123BD") == mariano, "El elemento de la clave pasada es el correcto");

	pa2m_afirmar(hash_contiene(hash, "OPQ976"), "Busco un segundo elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "OPQ976") == lucas, "El elemento de la clave pasada es el correcto.");

	pa2m_afirmar(hash_contiene(hash, "A421ACB"), "Busco un tercer elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "A421ACB") == manu, "El elemento de la clave pasada es el correcto.");

	pa2m_afirmar(hash_contiene(hash, "AA442CD"), "Busco un cuarto elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "AA442CD") == guido, "El elemento de la clave pasada es el correcto.");

	pa2m_afirmar(hash_insertar(hash, "AA442CD", matias, &anterior) != NULL, "Inserto un elemento con clave repetida correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El hash sigue teniendo la misma cantidad de elementos.");

	pa2m_afirmar(hash_contiene(hash, "AA442CD"), "Busco el elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "AA442CD") == matias, "Se reemplazó el elemento de la clave repetida.");

	pa2m_afirmar(hash_insertar(hash, "A421ACB", azul, &anterior) != NULL, "Inserto otro elemento con clave repetida correctamente.");
	pa2m_afirmar(hash_cantidad(hash) == 4, "El hash sigue teniendo la misma cantidad de elementos.");

	pa2m_afirmar(hash_contiene(hash, "A421ACB"), "Busco el elemento por su clave y lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "A421ACB") == azul, "Se reemplazó el elemento de la clave repetida.");
	
	hash_destruir_todo(hash, NULL);
}

void quito_un_elemento_y_se_quita_correctamente(){

	hash_t *hash = hash_crear(10);
	void *anterior = NULL;

	char *mariano = "Mariano";
	char *lucas = "Lucas";
	char *manu = "Manu";
	char *matias = "Matias";

	pa2m_afirmar(hash_quitar(NULL, "AA442CD") == NULL, "No puedo quitar un en un hash nulo.");
	pa2m_afirmar(hash_quitar(hash, "AA442CD") == NULL, "No puedo quitar un en un hash sin elementos.");
	pa2m_afirmar(hash_quitar(hash, NULL) == NULL, "No puedo quitar con clave nula.");
	
	hash_insertar(hash, "AC123BD", mariano, anterior);
	hash_insertar(hash, "OPQ976", lucas, anterior);
	hash_insertar(hash, "A421ACB", manu, anterior);
	hash_insertar(hash, "AA442CD", matias, anterior);

	pa2m_afirmar(hash_quitar(hash, "AC123BD") == mariano, "Quito un elemento correctamente y lo devuelve.");
	pa2m_afirmar(hash_cantidad(hash) == 3, "Disminuye la cantidad de elementos en el hash.");

	pa2m_afirmar(hash_quitar(hash, "OPQ976") == lucas, "Quito un elemento correctamente y lo devuelve.");
	pa2m_afirmar(hash_cantidad(hash) == 2, "Disminuye la cantidad de elementos en el hash.");

	pa2m_afirmar(hash_quitar(hash, "A421ACB") == manu, "Quito un elemento correctamente y lo devuelve.");
	pa2m_afirmar(hash_cantidad(hash) == 1, "Disminuye la cantidad de elementos en el hash.");

	pa2m_afirmar(hash_quitar(hash, "AA442CD") == matias, "Quito un elemento correctamente y lo devuelve.");
	pa2m_afirmar(hash_cantidad(hash) == 0, "Disminuye la cantidad de elementos en el hash, el hash queda vacío.");

	pa2m_afirmar(hash_contiene(hash, "AC123BD") == false, "Busco un elemento por su clave que fue eliminado y no lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "AC123BD") == NULL, "El elemento de la clave pasada no existe");

	pa2m_afirmar(hash_contiene(hash, "OPQ976") == false,  "Busco un elemento por su clave que fue eliminado y no lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "OPQ976") == NULL, "El elemento de la clave pasada no existe.");

	pa2m_afirmar(hash_contiene(hash, "A421ACB") == false,  "Busco un elemento por su clave que fue eliminado y no lo encuentro.");
	pa2m_afirmar(hash_obtener(hash, "A421ACB") == NULL, "El elemento de la clave pasada no existe.");

	pa2m_afirmar(hash_contiene(hash,"AA442CD") == false,  "Busco un elemento por su clave que fue eliminado y no lo encuentro.");
	pa2m_afirmar(hash_obtener(hash,"AA442CD") == NULL, "El elemento de la clave pasada no existe.");
	
	pa2m_afirmar(hash_quitar(hash, "AA442CD") == NULL, "No puedo quitar un elemento que no está en el hash.");

	hash_destruir_todo(hash, NULL);
}

bool mostrar_clave(const char *clave, void *valor, void *aux)
{
	if (!clave)
		return false;

	aux = aux;

	return true;
}

void itero_y_me_devuelve_la_cantidad_de_claves(){

	hash_t *hash = hash_crear(20);
	void *anterior = NULL;

	pa2m_afirmar(hash_con_cada_clave(hash, mostrar_clave, NULL) == 0, "No se puede iterar un hash vacio");
	pa2m_afirmar(hash_con_cada_clave(NULL, mostrar_clave, NULL) == 0, "No se puede iterar un hash nulo");

	pa2m_afirmar(hash_con_cada_clave(hash, NULL, NULL) == 0, "No se puede iterar un hash con funcion nula");

	char *mariano = "Mariano";
	char *lucas = "Lucas";
	char *manu = "Manu";

	hash_insertar(hash, "AC123BD", mariano, &anterior);
	hash_insertar(hash, "OPQ976", lucas, &anterior);
	hash_insertar(hash, "A421ACB", manu, &anterior);

	pa2m_afirmar(hash_con_cada_clave(hash, mostrar_clave, NULL) == 3, "Puedo iterar en un hash y me devuelve la cantidad de elementos");

	hash_destruir_todo(hash, NULL);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creacion de hash");
	creo_un_hash_y_devuelve_un_hash_valido();

	pa2m_nuevo_grupo("Pruebas de insertar");
	inserto_un_elemento_y_se_inserta_correctamente();

	pa2m_nuevo_grupo("Pruebas de quitar");
	quito_un_elemento_y_se_quita_correctamente();

	pa2m_nuevo_grupo("Pruebas de iterador interno");
	itero_y_me_devuelve_la_cantidad_de_claves();

	return pa2m_mostrar_reporte();
}
