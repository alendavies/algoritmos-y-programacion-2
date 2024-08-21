#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERROR -1
#define MAX_STRING 100               

#define AZUL "\033[1;34m"
#define NORMAL "\033[0m"
#define AMARILLO "\033[1;33m"    
#define VERDE "\033[1;32m"   
#define VIOLETA "\033[1;35m"                       

void mostrar_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("\n%s\n\n", mensaje);
}

void imprimir_objetos_conocidos(sala_t *sala)
{
	int cantidad_conocidos = 0;

	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_conocidos);
	if(!conocidos || cantidad_conocidos == ERROR){
		printf("\nHubo un error al imprimir los objetos conocidos\n");
	}
	printf("\nObjetos conocidos:\n\n");
	
	for (int i = 0; i < cantidad_conocidos; i++) {
		printf("%i: %s\n\n", i, conocidos[i]);
	}

	free(conocidos);
}

void imprimir_inventario(sala_t *sala)
{
	int cantidad_poseidos = 0;
	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_poseidos);
	if(!poseidos || cantidad_poseidos == ERROR){
		printf("\nHubo un error al imprimir los objetos del inventario\n");
	}
	
	printf("\nInventario:\n\n");
	
	for (int i = 0; i < cantidad_poseidos; i++) {
		printf("%i: %s\n\n", i, poseidos[i]);
	}
	free(poseidos);
}

void imprimir_introduccion()
{
        printf("\nAbrís los ojos.\n");
        sleep(2);
        printf("\nEstá todo oscuro.\n");
        sleep(2);
        printf("\nNo sabés dónde estás.\n");
        sleep(2);
        printf("\nEstás confundido y mareado.\n");
        sleep(2);
        printf("\nSeguro te la re pusiste en la pera anoche y estás tirado en algún callejón.\n");
        sleep(2);
        printf("\n\nAl prestar más atención, te das cuenta que estás en una especie de habitación.\n");
        sleep(2);
        printf("\nTe incorporas y miras a tu alrededor, en la oscuridad. Llegas a discernir lo que parece una pared.\n");
        sleep(2);
        printf("\nQuizás sea buena idea >examinar< con más detalle la habitación.\n\n\n");

        printf("(I) Inventario\t\t (C) Objetos descubiertos \t\t (A) Ayuda\n\n");

        printf("=================================================================================================================================================================\n\n");
}

int validar_opcion(sala_t *sala, char *comando, char *objeto1, char *objeto2, bool *ganado)
{
	if(!strcmp(comando, "A") || !strcmp(comando, "a")){

		printf("\nEstos son los comandos disponibles:\n\n");
		printf("\t-Para ver los objetos en el inventario ingresá (I).\n");
		printf("\t-Para ver los objetos con los que podes interactuar ingresá (C).\n");
		printf("\t-Para agarrar un objeto de la sala, ingresá 'agarrar' seguido del objeto.\n");
		printf("\t-Para ver la descripcion de un objeto, ingresá 'descripcion' seguido del objeto.\n");
		printf("\t-Para salir del juego ingresá 'salir'.\n");
		printf("\n\tTambién podés realizar las siguientes acciones seguidas de los objetos conocidos de la sala: \n\n\t\t-Examinar.\n\t\t-Usar.\n\t\t-Abrir.\n\t\t-Salir.\n\n");
	}

	else if(!strcmp(comando, "agarrar")){

		if(sala_agarrar_objeto(sala, objeto1)){
			printf("\nNuevo objeto en el inventario: %s\n\n", objeto1);
		}
		else{
			printf("\nNo se puede agarrar ese objeto\n\n");
		}				
	}

	else if(!strcmp(comando, "describir") && strcmp(objeto1, "") != 0){
		char *descripcion = sala_describir_objeto(sala, objeto1);
		if(descripcion){
			printf("\n%s\n", descripcion);
		}
		else{
			printf("\nNo se puede obtener la descripcion de ese objeto\n\n");
		}
	}

	else if(!strcmp(comando, "salir") && !strcmp(objeto1, "")){
		system("clear");
		return -1;
	}

	else if((!strcmp(comando, "I") || !strcmp(comando, "i")) && !strcmp(objeto1, "")){
		imprimir_inventario(sala);
	}

	else if((!strcmp(comando, "C") || !strcmp(comando, "c")) && !strcmp(objeto1, "")){
		imprimir_objetos_conocidos(sala);
	}

	else if(strcmp(comando, "") != 0 && strcmp(objeto1, "") != 0){
		int cantidad = 0;
		cantidad = sala_ejecutar_interaccion(sala, comando, objeto1, objeto2, mostrar_mensaje, NULL);
		if(cantidad == 0){
			printf("\nNo se pudo realizar esa interacción, probá con otra\n\n");
		}
	}

	if(sala_escape_exitoso(sala)){
                system("clear"); 
		printf(AZUL"\n \
   _____          _   _           _____ _______ ______  \n \
  / ____|   /\\   | \\ | |   /\\    / ____|__   __|  ____| \n \
 | |  __   /  \\  |  \\| |  /  \\  | (___    | |  | |__   \n \
 | | |_ | / /\\ \\ | . ` | / /\\ \\  \\___ \\   | |  |  __|  \n \
 | |__| |/ ____ \\| |\\  |/ ____ \\ ____) |  | |  | |____ \n \
  \\_____/_/    \\_\\_| \\_/_/    \\_\\_____/   |_|  |______|\n \
                                                        \n"NORMAL);   
							                 
		*ganado = true;
		return -1;
	}

	return 0;
}

int iniciar_juego(sala_t *sala)
{
	bool ganado = false;

	while(ganado == false){

		char input[MAX_STRING];
		char comando[MAX_STRING];
		strcpy(comando, "");
		char objeto1[MAX_STRING];
		strcpy(objeto1, "");
		char objeto2[MAX_STRING];
		strcpy(objeto2, "");

                printf("> ");

                scanf(" %[^\n]", input);

		sscanf(input, "%s %s %s", comando, objeto1, objeto2);

		int opcion = validar_opcion(sala, comando, objeto1, objeto2, &ganado);

		if(opcion == -1){
			return -1;
		}
	}
        return 0;
}

void mostrar_instrucciones()
{
	printf(VIOLETA"\n \
  _____ _   _  _____ _______ _____  _    _  _____ _____ _____ ____  _   _ ______  _____  \n \
 |_   _| \\ | |/ ____|__   __|  __ \\| |  | |/ ____/ ____|_   _/ __ \\| \\ | |  ____|/ ____|\n \
   | | |  \\| | (___    | |  | |__) | |  | | |   | |      | || |  | |  \\| | |__  | (___  \n \
   | | | . ` |\\___ \\   | |  |  _  /| |  | | |   | |      | || |  | | . ` |  __|  \\___ \\ \n \
  _| |_| |\\  |____) |  | |  | | \\ \\| |__| | |___| |____ _| || |__| | |\\  | |____ ____) |\n \
 |_____|_| \\_|_____/   |_|  |_|  \\_\\\\____/ \\_____\\_____|_____\\____/|_| \\_|______|_____/ \n \
                                                                                        \n\n"NORMAL);

	printf("Para jugar tenés que ingresar las interacciones que queres realizar con los objetos de la sala.\n");
	printf("Para agarrar un objeto debes ingresar 'agarrar' seguido del objeto.\n");
	printf("Para obtener la descripción de un objeto debes ingresar 'describir' seguido del objeto.\n");
	printf("Para obtener ayuda con los comandos que podés utilizar durante el juego podes ingresar 'ayuda'.\n");
	printf("Para ver los objetos del inventario del personaje podes ingresar 'I'.\n");
	printf("Para ver los objetos descubiertos con los que podés interactuar podes ingresar 'C'.\n");
	printf("Para salir del juego debes ingresar 'salir'.\n\n");

	printf("Presioná (B) para volver al menú principal\n");

	char opcion;
	scanf(" %c", &opcion);
	while(opcion != 'B' && opcion != 'b'){
		scanf(" %c", &opcion);
	}
	return;
}

void menu_principal(sala_t *sala)
{
	char opcion;
	printf(AMARILLO"\n \
  ______                            _____      _                               \n \
 |  ____|                          |  __ \\    | |                             \n \
 | |__   ___  ___ __ _ _ __   ___  | |__) |__ | | _____ _ __ ___   ___  _ __  \n \
 |  __| / __|/ __/ _` | '_ \\ / _ \\ |  ___/ _ \\| |/ / _ \\ '_ ` _ \\ / _ \\| '_ \\ \n \
 | |____\\__ \\ (_| (_| | |_) |  __/ | |  | (_) |   <  __/ | | | | | (_) | | | | \n \
 |______|___/\\___\\__,_| .__/ \\___| |_|   \\___/|_|\\_\\___|_| |_| |_|\\___/|_| |_| \n \
                      | |                                                     \n \
                      |_|                                                    \n \
		      \n\n"NORMAL);

	printf(VERDE"> Iniciar el juego (J)\n\n");
	printf("> Instrucciones del juego (I)\n\n");
	printf("> Salir del juego (S)\n\n"NORMAL);

	scanf(" %c", &opcion);

	while(opcion != 'J' && opcion != 'j' && opcion != 'I' && opcion != 'i' && opcion != 'S' && opcion != 's'){
		scanf(" %c", &opcion);
	}

	if(opcion == 'J' || opcion == 'j'){
		system("clear");
                imprimir_introduccion();
		int salir = iniciar_juego(sala);
                if(salir == -1){
                        return;
                }
		system("clear");
		menu_principal(sala);
	}
	else if(opcion == 'I' || opcion == 'i'){
		system("clear");
		mostrar_instrucciones();
		system("clear");
		menu_principal(sala);
	}
	else if(opcion == 'S' || opcion == 's'){

		printf("\nEstás seguro que querés salir del juego? (y/n): ");
		char opcion;
		scanf(" %c", &opcion);

		while(opcion != 'Y' && opcion != 'y' && opcion != 'N' && opcion != 'n'){
			printf("Ingrese una opción válida (y/n): ");
			scanf(" %c", &opcion);
		}
		if(opcion == 'Y' || opcion == 'y'){
			return;
		}
		else if(opcion == 'N' || opcion == 'n'){
			system("clear");
			menu_principal(sala);
		}	
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3){
		return ERROR;
	}
	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (!sala) {
		printf("\nError al crear la sala de escape\n");
		return ERROR;
	}

	menu_principal(sala);

	sala_destruir(sala);

	return 0;
}