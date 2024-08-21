#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES 1024
#define CANT_OBJETOS 20
#define ERROR -1

struct objeto **crear_vector_objetos(FILE *archivo, int *tope)
{
	char linea[MAX_CARACTERES];
	struct objeto **vector_objeto = NULL;
	
	while(fgets(linea, MAX_CARACTERES, archivo) != NULL){
	
		if(*tope == 0){
			
			vector_objeto = malloc(sizeof(struct objeto*));
		}
		else{
			vector_objeto = realloc(vector_objeto, (unsigned)((*tope)+1)*sizeof(struct objeto*));
		}
		if(vector_objeto == NULL){
			return NULL;
		}
		struct objeto *objeto = objeto_crear_desde_string(linea);
		if(objeto == NULL){
			free(vector_objeto);
			return NULL;
		}
		vector_objeto[*tope] = objeto;
		(*tope)++;	
	}
	return vector_objeto;
}

struct interaccion **crear_vector_interaccion(FILE *archivo, int *tope)
{
	char linea[MAX_CARACTERES];
	struct interaccion **vector_interaccion = NULL;

	while(fgets(linea, MAX_CARACTERES, archivo) != NULL){
	
		if(*tope == 0){
			
			vector_interaccion = malloc(sizeof(struct interaccion*));
		}
		else{
			vector_interaccion = realloc(vector_interaccion, (unsigned)((*tope)+1)*sizeof(struct interaccion*));
		}
		if(vector_interaccion == NULL){
			return NULL;
		}	
		struct interaccion *interaccion = interaccion_crear_desde_string(linea);
		if(interaccion == NULL){
			free(vector_interaccion);
			return NULL;
		}
		vector_interaccion[*tope] = interaccion;
		(*tope)++;	
	}
	return vector_interaccion;
}

sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{	
	FILE *arch_objetos = fopen(objetos, "r");
	if(!arch_objetos){
        	return NULL;
	}

	FILE *arch_interacciones = fopen(interacciones, "r");
	if(!arch_interacciones){
		fclose(arch_objetos);
        	return NULL;
	}

	sala_t *sala = malloc(sizeof(struct sala));
	if(!sala){
		fclose(arch_objetos);
		fclose(arch_interacciones);
		return NULL;
	}
	
	int tope_objetos = 0;
	struct objeto **vector_objeto = crear_vector_objetos(arch_objetos, &tope_objetos);
	if(!vector_objeto){
		fclose(arch_objetos);
		fclose(arch_interacciones);
		free(sala);
		return NULL;
	}
	sala->objetos = vector_objeto;
	sala->cantidad_objetos = tope_objetos;
	fclose(arch_objetos);

	int tope_interaccion = 0;
	struct interaccion **vector_interaccion = crear_vector_interaccion(arch_interacciones, &tope_interaccion);
	if(!vector_interaccion){
		fclose(arch_interacciones);
		for(int i = 0; i < sala->cantidad_objetos; i++){
			free(sala->objetos[i]);
		}
		free(sala->objetos);
		free(sala);
		return NULL;
	}
	sala->interacciones = vector_interaccion;
	sala->cantidad_interacciones = tope_interaccion;
	fclose(arch_interacciones);
	
	return sala;
}

char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if(sala == NULL){
		if(cantidad == NULL){
			return NULL;
		}
		else{
			*cantidad = ERROR;
			return NULL;
		}
	}
	char **nombres_objetos = malloc((unsigned) sala->cantidad_objetos*sizeof(char *));
	
	if(!nombres_objetos){
		if(cantidad == NULL){
			return NULL;
		}
		else{
			*cantidad = ERROR;
			return NULL;
		}
	}
	if(cantidad != NULL && sala->cantidad_objetos != 0){
		*cantidad = sala->cantidad_objetos;
	}
	int tope = 0;
	while(tope < sala->cantidad_objetos){
			
		nombres_objetos[tope] = sala->objetos[tope]->nombre;
		tope++;	
	}
	return nombres_objetos;
}

bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1, const char *objeto2)
{	
	bool es_valida = false;
	if(verbo!= NULL && objeto1 != NULL && objeto2 != NULL){

		for(int i = 0; i < sala->cantidad_interacciones; i++){

			if(strcmp(sala->interacciones[i]->verbo, verbo) == 0 && 
			strcmp(sala->interacciones[i]->objeto, objeto1) == 0 && 
			strcmp(sala->interacciones[i]->objeto_parametro, objeto2) == 0){

				es_valida = true;
			}
		}
	}
	return es_valida;
}

void sala_destruir(sala_t *sala)
{	
	for(int i = 0; i < sala->cantidad_objetos; i++){
		free(sala->objetos[i]);
	}
	free(sala->objetos);

	for(int j = 0; j < sala->cantidad_interacciones; j++){
		free(sala->interacciones[j]);
	}
	free(sala->interacciones);

	free(sala);
}
