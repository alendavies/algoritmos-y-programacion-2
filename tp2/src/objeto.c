#include "objeto.h"
#include "estructuras.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_LETRAS 10

struct objeto *objeto_crear_desde_string(const char *string)
{	
	if(string == NULL){
		return NULL;
	}
	char es_asible[MAX_LETRAS];
	struct objeto objeto_temporal;

	int cantidad_leidos = sscanf(string, "%[^;];%[^;];%[^\n]\n", objeto_temporal.nombre, objeto_temporal.descripcion, es_asible);

	if(cantidad_leidos != 3){
		return NULL;
	}
	if(strcmp(es_asible, "true") == 0){
		objeto_temporal.es_asible = true;
	}
	else if(strcmp(es_asible, "false") == 0){
		objeto_temporal.es_asible = false;
	}
	else{
		return NULL;
	}
	struct objeto *objeto = malloc(sizeof(struct objeto));
	if(objeto == NULL){
		return NULL;
	}
	*objeto = objeto_temporal;

	return objeto;
}
