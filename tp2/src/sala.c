#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CARACTERES 1024
#define CANT_OBJETOS 20
#define ERROR -1

typedef struct objeto objeto_t;
typedef struct interaccion interaccion_t;

struct sala {
	lista_t *objetos;
	lista_t *interacciones;
	lista_t *conocidos;
	lista_t *poseidos;
	bool escape_exitoso;
};

/*  
 * Compara el elemento con un contexto.
 * Devuelve 0 si son iguales o distinto de 0 si son distintos.
 */
int comparador(void *elemento, void *contexto)
{
	objeto_t *objeto = (objeto_t *)elemento;

	return strcmp(objeto->nombre, (const char *)contexto);
}

/* 
 * Devuelve una lista que contiene todos los objetos 
 * existentes en el archivo.
 * 
 * Devuelve NULL en caso de error.
 */
lista_t *crear_lista_objetos(FILE *archivo)
{
	char linea[MAX_CARACTERES];

	lista_t *lista_objetos = lista_crear();
	if (!lista_objetos){
		return NULL;
	}
	
	while (fgets(linea, MAX_CARACTERES, archivo) != NULL){
		
		objeto_t *objeto = objeto_crear_desde_string(linea);
		if (!objeto){
			lista_destruir(lista_objetos);
			return NULL;
		}
		lista_objetos = lista_insertar(lista_objetos, objeto);
		if (!lista_objetos){
			free(objeto);
			lista_destruir(lista_objetos);
			return NULL;
		}	
	}
	return lista_objetos;
}

/* 
 * Devuelve una lista que contiene todas las interacciones 
 * existentes en el archivo.
 * 
 * Devuelve NULL en caso de error.
 */
lista_t *crear_lista_interacciones(FILE *archivo)
{
	char linea[MAX_CARACTERES];
	
	lista_t *lista_interacciones = lista_crear();
	if (!lista_interacciones){
		return NULL;
	}
	
	while (fgets(linea, MAX_CARACTERES, archivo) != NULL){
		
		interaccion_t *interaccion = interaccion_crear_desde_string(linea);
		if (!interaccion){
			lista_destruir(lista_interacciones);
			return NULL;
		}
		lista_interacciones = lista_insertar(lista_interacciones, interaccion);
		if (!lista_interacciones){
			free(interaccion);
			lista_destruir(lista_interacciones);
			return NULL;
		}	
	}
	return lista_interacciones;
}

/* 
* Agrega el objeto a la lista de conocidos si cumple con lo siguiente:
* - El objeto no está en la lista de conocidos ni de poseídos.
* - El objeto está en la lista de objetos de la sala.
*
* Devuelve true si pudo agregar al objeto o false en caso de error.
*/
bool conocer_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto){
		return false;
	}
	objeto_t *objeto = NULL;

	objeto = lista_buscar_elemento(sala->conocidos, comparador, (void *)nombre_objeto);

	if (objeto){
		return false;
	}

	objeto = lista_buscar_elemento(sala->poseidos, comparador, (void *)nombre_objeto);

	if (objeto){
		return false;
	}

	objeto = lista_buscar_elemento(sala->objetos, comparador, (void *)nombre_objeto);

	if (objeto){
		lista_t *conocidos = lista_insertar(sala->conocidos, objeto);
		if (!conocidos){
			return false;
		}
		sala->conocidos = conocidos;

		return true;
	}

	return false;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{	
	if (!objetos || !interacciones){
		return NULL;
	}

	FILE *arch_objetos = fopen(objetos, "r");
	if (!arch_objetos){
        	return NULL;
	}

	FILE *arch_interacciones = fopen(interacciones, "r");
	if (!arch_interacciones){
		fclose(arch_objetos);
        	return NULL;
	}

	sala_t *sala = calloc(1, sizeof(struct sala));
	if (!sala){
		fclose(arch_objetos);
		fclose(arch_interacciones);
		return NULL;
	}

	lista_t *lista_objetos = crear_lista_objetos(arch_objetos);
	if (!lista_objetos){
		fclose(arch_objetos);
		fclose(arch_interacciones);
		sala_destruir(sala);
		return NULL;
	}
	fclose(arch_objetos);

	lista_t *lista_interaccion = crear_lista_interacciones(arch_interacciones);
	if (!lista_interaccion){
		fclose(arch_interacciones);
		sala_destruir(sala);
		return NULL;
	}
	fclose(arch_interacciones);

	lista_t *lista_conocidos = lista_crear();
	if (!lista_conocidos){
		sala_destruir(sala);
		return NULL;
	}

	lista_t *lista_poseidos = lista_crear();
	if (!lista_poseidos){
		sala_destruir(sala);
		return NULL;
	}

	sala->objetos = lista_objetos;
	sala->interacciones = lista_interaccion;
	sala->conocidos = lista_conocidos;
	sala->poseidos = lista_poseidos;
	sala->escape_exitoso = false;

	if (sala->interacciones->cantidad == 0 || sala->objetos->cantidad == 0){
		sala_destruir(sala);
		return NULL;
	}

	if (!conocer_objeto(sala, sala->objetos->nodo_inicio->elemento)){
		return NULL;
	}
	
	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (!sala){
		*cantidad = ERROR;
		return NULL;
	}

	if (!cantidad){
		int i = 0;
		cantidad = &i;
	}

	*cantidad = (int)sala->objetos->cantidad;
	char **nombres_objetos = malloc((unsigned)(*cantidad) * (sizeof(char *)));

	if (!nombres_objetos) {
		*cantidad = ERROR;
		return NULL;
	}

	for(int i = 0; i < *cantidad; i++){
		objeto_t *objeto = (objeto_t*)lista_elemento_en_posicion(sala->objetos, (size_t)i);
		if (!objeto){
			free(nombres_objetos);
			return NULL;
		}
		nombres_objetos[i] = objeto->nombre;
	}

	return nombres_objetos;
}

char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if  (!sala) {
		*cantidad = ERROR;
		return NULL;
	}

	if  (!cantidad) {
		int i = 0;
		cantidad = &i;
	}

	*cantidad = (int)sala->conocidos->cantidad;

	char **conocidos = malloc((unsigned)(*cantidad) * (sizeof(char *)));

	if  (!conocidos){
		*cantidad = ERROR;
		return NULL;
	}

	for(int i = 0; i < *cantidad; i++){
		
		objeto_t *objeto = (objeto_t*)lista_elemento_en_posicion(sala->conocidos, (size_t)i);
		conocidos[i] = objeto->nombre;
	}

	return conocidos;
}

char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if  (!sala) {
		*cantidad = ERROR;
		return NULL;
	}

	if  (!cantidad) {
		int i = 0;
		cantidad = &i;
	}

	*cantidad = (int)sala->poseidos->cantidad;
	char **poseidos = malloc((unsigned)(*cantidad) * (sizeof(char *)));

	if (!poseidos){
		*cantidad = ERROR;
		return NULL;
	}

	for(int i = 0; i < *cantidad; i++){
		objeto_t *objeto = lista_elemento_en_posicion(sala->poseidos, (size_t)i);
		if (!objeto){
			return NULL;
		}
		poseidos[i] = objeto->nombre;
	}

	return poseidos;
}

/* 
 * Devuelve true si el verbo, objeto1 y objeto2 coinciden con los campos de la interacción.
 * Sino devuelve false.
*/
bool interaccion_correcta(interaccion_t *interaccion, const char *verbo, const char *objeto1, const char *objeto2)
{
	if (strcmp(interaccion->verbo, verbo) == 0 && 
	strcmp(interaccion->objeto, objeto1) == 0 && 
	strcmp(interaccion->objeto_parametro, objeto2) == 0){
		return true;
	}

	return false;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1, const char *objeto2)
{
	if (!sala || !verbo || !objeto1 || !objeto2){
		return NULL;
	}

	for(int i = 0; i < sala->interacciones->cantidad; i++){

		interaccion_t *interaccion = lista_elemento_en_posicion(sala->interacciones, (size_t)i);
		if (!interaccion){
			return false;
		}

		if (interaccion_correcta(interaccion, verbo, objeto1, objeto2)){
		 	return true;
		}	
	}

	return false;
}
 
 /* 
  * Quita de la lista y le aplica la funcion destructora a un elemento 
  * que coincida con el contexto utilizando el comparador. 
  * 
  * Devuelve la lista en caso de exito o NULL en caso de error.
  */
lista_t *lista_quitar_elemento(lista_t *lista, int (*comparador)(void *, void *), void *contexto, void (*funcion)(void *))
{
	if  (!lista || !comparador || lista_vacia(lista)){
		return NULL;
	}

	for (size_t i = 0; i < lista_tamanio(lista); i++) {

		objeto_t *objeto = lista_elemento_en_posicion(lista, i);
		if (!objeto){
			return NULL;
		}

		if (comparador(objeto, contexto) == 0){
			objeto = lista_quitar_de_posicion(lista, i);
			
			if (objeto && funcion){
				funcion(objeto);
			}
		}
	}

	return lista;
}

bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto){
		return false;
	}

	objeto_t *objeto = lista_buscar_elemento(sala->poseidos, comparador, (void *)nombre_objeto);

	if (objeto){
		return false;
	}

	objeto = lista_buscar_elemento(sala->conocidos, comparador, (void *)nombre_objeto);

	if (!objeto){
		return false;
	}

	if (!objeto->es_asible){
		return false;
	}

	lista_quitar_elemento(sala->conocidos, comparador, objeto, NULL);

	lista_insertar(sala->poseidos, objeto);

	return true;
}

char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto){
		return NULL;
	}

	objeto_t *objeto = lista_buscar_elemento(sala->poseidos, comparador, (void *)nombre_objeto);

	if (objeto){
		return objeto->descripcion;
	}

	objeto = lista_buscar_elemento(sala->conocidos, comparador, (void *)nombre_objeto);
	
	if (objeto){
		return objeto->descripcion;
	}

	return NULL;
}

/* 
 * Si el objeto se encuentra en las listas de la sala, lo elimina.
 *
 * Devuelve true en caso de que haya podido eliminar el objeto 
 * o false en caso de error.
 */
bool eliminar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (!sala || !nombre_objeto){
		return false;
	}

	lista_t *poseidos = lista_quitar_elemento(sala->poseidos, comparador, (void *)nombre_objeto, NULL);
	lista_t *conocidos = lista_quitar_elemento(sala->conocidos, comparador, (void *)nombre_objeto, NULL);
	lista_t *objetos = lista_quitar_elemento(sala->objetos, comparador, (void *)nombre_objeto, free);

	if (!poseidos && !conocidos && !objetos){
		return false;
	}

	if (poseidos){
		sala->poseidos = poseidos;
	}
	if (conocidos){
		sala->conocidos = conocidos;
	}
	if (objetos){
		sala->objetos = objetos;
	}

	return true;
}

/* 
 * Ejecuta el campo acción de la interacción.
 * 
 * Devuelve true en caso de éxito o false en caso de error.
 */
bool ejecutar_accion(sala_t *sala, interaccion_t *interaccion, const char *objeto1, const char *objeto2, void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux), void *aux){

	if (interaccion->accion.tipo == ACCION_INVALIDA){
		return false;
	}
	else if (interaccion->accion.tipo == MOSTRAR_MENSAJE){
		if (mostrar_mensaje){
			mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			return true;
		}
	}
	else if (interaccion->accion.tipo == ELIMINAR_OBJETO){
		if (eliminar_objeto(sala, objeto1)){
			if (mostrar_mensaje){
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			}
			return true;
		}
	}
	else if (interaccion->accion.tipo == DESCUBRIR_OBJETO){
		if (conocer_objeto(sala, interaccion->accion.objeto)){
			if (mostrar_mensaje){
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			}
			return true;
		}
	}
	else if (interaccion->accion.tipo == ESCAPAR){
		if (mostrar_mensaje){
			mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
		}
		sala->escape_exitoso = true;
		return true;
	}
	else if (interaccion->accion.tipo == REEMPLAZAR_OBJETO){
		if (eliminar_objeto(sala, objeto2) && conocer_objeto(sala, interaccion->accion.objeto)){
			if (mostrar_mensaje){
				mostrar_mensaje(interaccion->accion.mensaje, interaccion->accion.tipo, aux);
			}
			return true;
		}
	}

	return false;
}

int sala_ejecutar_interaccion(sala_t *sala, const char *verbo, const char *objeto1, const char *objeto2, void (*mostrar_mensaje)(const char *mensaje, enum tipo_accion accion, void *aux), void *aux)
{
	if (!sala || !verbo || !objeto1 || !objeto2){
		return 0;
	}

	objeto_t *objeto_conocidos = NULL;
	objeto_t *objeto_poseidos = NULL;

	objeto_conocidos = lista_buscar_elemento(sala->conocidos, comparador, (void *)objeto1);

	objeto_poseidos = lista_buscar_elemento(sala->poseidos, comparador, (void *)objeto1);

	if (!objeto_conocidos && !objeto_poseidos){
		return 0;
	}

	if (!sala_es_interaccion_valida(sala, verbo, objeto1, objeto2)){
		return 0;
	}

	if (objeto_conocidos && objeto_conocidos->es_asible && !objeto_poseidos){
                return 0;
        }
	
	int ejecutadas = 0;
	interaccion_t *interaccion = NULL;

	for(int i = 0; i < sala->interacciones->cantidad; i++){

		interaccion= lista_elemento_en_posicion(sala->interacciones, (size_t)i);
		if (!interaccion){
			return 0;
		}

		if (interaccion_correcta(interaccion, verbo, objeto1, objeto2)){
			
			if (ejecutar_accion(sala, interaccion, objeto1, objeto2, mostrar_mensaje, aux)){
				ejecutadas++;
			}
		}			
	}

	return ejecutadas;
}

bool sala_escape_exitoso(sala_t *sala)
{
	if (!sala){
		return false;
	}
	return sala->escape_exitoso;
}

void sala_destruir(sala_t *sala)
{
	if (!sala){
		return;
	}

	lista_destruir_todo(sala->objetos, free);
	lista_destruir_todo(sala->interacciones, free);
	lista_destruir(sala->conocidos);
	lista_destruir(sala->poseidos);
	free(sala);
}