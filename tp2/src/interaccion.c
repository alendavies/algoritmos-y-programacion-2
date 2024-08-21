#include "estructuras.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_ACCION 1024
#define MAX_TIPO 5

int asignar_tipo_accion(char tipo)
{

	int accion_tipo = 0;

	if(tipo == 'd'){
		accion_tipo = DESCUBRIR_OBJETO;	
	}
	else if(tipo == 'r'){
		accion_tipo = REEMPLAZAR_OBJETO;	
	}
	else if(tipo == 'e'){
		accion_tipo = ELIMINAR_OBJETO;	
	}
	else if(tipo == 'm'){
		accion_tipo = MOSTRAR_MENSAJE;	
	}
	else if(tipo == 'g'){
		accion_tipo = ESCAPAR;	
	}
	else{
		accion_tipo = ACCION_INVALIDA;
	}
	return accion_tipo;
}

struct interaccion *interaccion_crear_desde_string(const char *string)
{	
	if(string == NULL){
		return NULL;
	}
	struct interaccion interaccion_tmp;
	struct accion accion;
	char tipo;

	int cantidad_leidos = sscanf(string, "%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]\n", interaccion_tmp.objeto, interaccion_tmp.verbo, interaccion_tmp.objeto_parametro, &tipo, accion.objeto, accion.mensaje);

	if(cantidad_leidos != 6){
		return NULL;
	}
	if(strcmp(interaccion_tmp.objeto_parametro, "_") == 0){
		interaccion_tmp.objeto_parametro[0] = 0;
	}	
	if(strcmp(accion.objeto, "_") == 0){
		accion.objeto[0] = 0;
	}
	accion.tipo = asignar_tipo_accion(tipo);
	
	interaccion_tmp.accion = accion;

	struct interaccion *interaccion = malloc(sizeof(struct interaccion));
	if(interaccion == NULL){
		return NULL;
	}
	*interaccion = interaccion_tmp;

	return interaccion;
}
