#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1

void imprimir_objetos_sala(sala_t *sala){

	int cantidad_objetos = 0;

	char **nombre_objetos = sala_obtener_nombre_objetos(sala, &cantidad_objetos);

	if(nombre_objetos == NULL || cantidad_objetos == ERROR){
		printf("Hubo un error al imprimir los objetos de la sala\n");
	}

	printf("\nObjetos...\n");

	for(int i = 0; i < cantidad_objetos; i++){
		printf("%i: %s\n", i, nombre_objetos[i]);
	}
	
	free(nombre_objetos);
}

void imprimir_interacciones_sala(sala_t *sala){

	printf("\nInteracciones...\n");

	printf("Examinar habitación: ");
	sala_es_interaccion_valida(sala, "examinar", "habitacion", "") ? printf("Válido\n") : printf("Inválido\n");

	printf("Abrir pokebola: ");
	sala_es_interaccion_valida(sala, "abrir", "pokebola", "") ? printf("Válido\n") : printf("Inválido\n");

	printf("Usar llave en el cajon: ");
	sala_es_interaccion_valida(sala, "usar", "llave", "cajon") ? printf("Válido\n") : printf("Inválido\n");

	printf("Quemar la mesa: ");
	sala_es_interaccion_valida(sala, "quemar", "mesa", "") ? printf("Válido\n") : printf("Inválido\n");
}

int main(int argc, char *argv[])
{
	if(argc != 3){
		return ERROR;
	}
	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (sala == NULL) {
		printf("Error al crear la sala de escape\n");
		return ERROR;
	}

	imprimir_objetos_sala(sala);

	imprimir_interacciones_sala(sala);

	sala_destruir(sala);

	return 0;
}
