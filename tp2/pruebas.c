#include "pa2mm.h"
#include "src/estructuras.h"
#include "src/sala.h"
#include "src/objeto.h"
#include "src/interaccion.h"
#include "string.h"
#include "src/lista.h"
#include <stdbool.h>

struct sala {
	lista_t *objetos;
	lista_t *interacciones;
	lista_t *conocidos;
	lista_t *poseidos;
	bool escape_exitoso;
};

void pruebasCrearObjeto()
{
	pa2m_afirmar(objeto_crear_desde_string(NULL) == NULL,
		     "No puedo crear un objeto a partir de un string NULL");
	pa2m_afirmar(objeto_crear_desde_string("") == NULL,
		     "No puedo crear un objeto a partir de un string vacío");
	pa2m_afirmar(objeto_crear_desde_string("a;b") == NULL,
		     "\"a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;b") == NULL,
		     "\"a;;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;b") == NULL,
		     "\";a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;b;c") == NULL,
		     "\"a;b;c\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;true") == NULL,
		     "\"a;;true\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;false") == NULL,
		     "\";a;false\" no es un string objeto válido");

	struct objeto *objeto1 = objeto_crear_desde_string("nombre;desc;true");
	pa2m_afirmar(objeto1, "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0, "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0, "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}

void pruebasCrearInteracciones()
{
	pa2m_afirmar(interaccion_crear_desde_string(NULL) == NULL,
		     "No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(interaccion_crear_desde_string("") == NULL,
		     "No puedo crear una interacción a partir de un string vacío");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c:d:e") == NULL,
		     "\"a;b;c:d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d") == NULL,
		     "\"a;b;c;d\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d:e") == NULL,
		     "\"a;b;c;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;d:e") == NULL,
		     "\"a;b;_;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;de:f:g") == NULL,
		     "\"a;b;_;de:f:g\" no es un string interacción válido");

	struct interaccion *inter1 = interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0, "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0, "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0, "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0, "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 = interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1, "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0, "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0, "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0, "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");

	free(inter1);
	free(inter2);
}

void pruebas_crear_sala()
{
	pa2m_afirmar(sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd") == NULL,
		     "No puedo crear la sala a partír de archivos inexistentes");

	pa2m_afirmar(sala_crear_desde_archivos("", "arch_pruebas/int.csv") == NULL,
		     "No puedo crear la sala sin objetos");

	pa2m_afirmar(sala_crear_desde_archivos("arch_pruebas/obj.dat", "arch_pruebas/vacio.txt") == NULL,
		     "No puedo crear la sala sin interacciones");

	sala_t *sala = sala_crear_desde_archivos("arch_pruebas/obj.dat", "arch_pruebas/int.csv");

	pa2m_afirmar(sala != NULL, "Puedo crear la sala a partir de archivos no vacíos");

	/* pa2m_afirmar(sala->cantidad_objetos == 9, "Se leyeron 9 objetos");
	pa2m_afirmar(sala->cantidad_interacciones == 9, "Se leyeron 9 interacciones"); */

	pa2m_afirmar(sala->objetos->cantidad == 9, "Se leyeron 9 objetos");
	pa2m_afirmar(sala->interacciones->cantidad == 9, "Se leyeron 9 interacciones");

	sala_destruir(sala);
}

void pruebas_nombre_objetos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("arch_pruebas/obj.dat", "arch_pruebas/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir la lista de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir la lista de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos de la lista coincide con lo esperado");

	const char *esperados[] = { "habitacion",    "mesa",  "interruptor", "pokebola", "cajon",
				    "cajon-abierto", "llave", "anillo",	     "puerta" };

	int comparaciones_exitosas = 0;

	for (int i = 0; i < cantidad; i++)
		if (strcmp(objetos2[i], esperados[i]) == 0)
			comparaciones_exitosas++;

	pa2m_afirmar(comparaciones_exitosas == cantidad,
		     "Todos los nombres de objeto son los esperados");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("arch_pruebas/obj.dat", "arch_pruebas/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false, "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") == false, "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave", "cajon") == true, "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola", "") == true, "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "cajon-abierto", "") == true, "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") == false, "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") == false, "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo", "") == false, "No puedo examinar el techo");

	sala_destruir(sala);
}

void pruebas_nombre_conocidos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos_conocidos(NULL, &cantidad) == NULL, "No puedo obtener los objetos conocidos de una sala NULL");

	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("arch_pruebas/obj.dat", "arch_pruebas/int.csv");

	char **objetos = sala_obtener_nombre_objetos_conocidos(sala, NULL);
	pa2m_afirmar(objetos != NULL, "Puedo pedir la lista de objetos conocidos a la sala pasando cantidad NULL");


	char **objetos2 = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL, "Puedo pedir la lista de objetos conocidos a la sala pasando cantidad no NULL");

	char **vector = NULL;

	pa2m_afirmar((vector = sala_obtener_nombre_objetos_conocidos( sala, &cantidad)), "Puedo obtener los nombres de los objetos conocidos");

	pa2m_afirmar(cantidad == 1, "Inicialmente solo se conoce un objeto");

	pa2m_afirmar(strcmp(vector[0], "habitacion") == 0, "El elemento conocido es la habitación");

	free(vector);

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_nombre_poseidos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos_poseidos(NULL, &cantidad) == NULL, "No puedo obtener los objetos poseidos de una sala NULL");

	pa2m_afirmar(cantidad == -1, "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("arch_pruebas/obj.dat", "arch_pruebas/int.csv");

	char **objetos = sala_obtener_nombre_objetos_poseidos(sala, NULL);
	pa2m_afirmar(objetos != NULL, "Puedo pedir la lista de objetos poseidos a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos_poseidos(sala, &cantidad);

	pa2m_afirmar(objetos2 != NULL, "Puedo pedir la lista de objetos poseidos a la sala pasando cantidad no NULL");
	char **vector = NULL;

	pa2m_afirmar((vector = sala_obtener_nombre_objetos_poseidos(sala, &cantidad)), "Puedo obtener los nombres de los objetos conocidos");

	pa2m_afirmar(cantidad == 0, "El jugador no posee ningún objeto");

	free(vector);

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}

void pruebas_agarrar()
{
	sala_t *sala = sala_crear_desde_archivos("arch_pruebas/objeto.txt", "arch_pruebas/interaccion.txt");

	pa2m_afirmar(sala_agarrar_objeto(NULL, "pokebola") == false, "No puedo agarrar un objeto de una sala NULL");
	pa2m_afirmar(sala_agarrar_objeto(sala, NULL) == false, "No puedo agarrar un objeto NULL");

	pa2m_afirmar(sala_agarrar_objeto(sala, "llave") == false, "No puedo agarrar un objeto no conocido");
	pa2m_afirmar(sala_agarrar_objeto(sala, "puerta") == false, "No puedo agarrar un objeto no asible");

	sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL,  NULL);

	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola") == true, "Puedo agarrar un objeto conocido y asible");
	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola") == false, "No puedo agarrar un objeto ya poseído");

	sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", NULL,  NULL);

	pa2m_afirmar(sala_agarrar_objeto(sala, "llave") == true, "Puedo agarrar otro objeto conocido y asible");

	sala_destruir(sala);
}

void pruebas_describir()
{
	sala_t *sala = sala_crear_desde_archivos("arch_pruebas/objeto.txt", "arch_pruebas/interaccion.txt");

	pa2m_afirmar(sala_describir_objeto(NULL, "pokebola") == NULL, "No puedo describir un objeto de una sala NULL");
	pa2m_afirmar(sala_describir_objeto(sala, NULL) == NULL, "No puedo describir un objeto NULL");

	pa2m_afirmar(sala_describir_objeto(sala, "puerta") == NULL, "No puedo obtener la descripción un objeto no conocido o poseído");

	pa2m_afirmar(sala_describir_objeto(sala, "habitacion") != NULL, "Puedo obtener la descripción de un objeto conocido");

	sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL,  NULL);
	sala_agarrar_objeto(sala, "pokebola");

	pa2m_afirmar(sala_describir_objeto(sala, "pokebola") != NULL, "Puedo obtener la descripción de un objeto poseido");

	sala_destruir(sala);
}

void pruebas_escape()
{
	sala_t *sala = sala_crear_desde_archivos("arch_pruebas/objeto.txt", "arch_pruebas/interaccion.txt");

	pa2m_afirmar(sala_escape_exitoso(sala) == false, "Inicialmente la sala no está escapada");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "salir", "puerta", "", NULL, NULL) == 0, "La puerta no está abierta, no puedo salir de la sala");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL, NULL) == 2, "Examino la habitacion y se ejecutan dos interacciones");

	sala_agarrar_objeto(sala, "pokebola");
	sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", NULL,  NULL);
	sala_agarrar_objeto(sala, "llave");
	sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", NULL,  NULL);
	sala_ejecutar_interaccion(sala, "salir", "puerta-abierta", "", NULL,  NULL);

	pa2m_afirmar(sala_escape_exitoso(sala) == true, "Ahora la sala fue escapada exitosamente");

	sala_destruir(sala);
}

int main()
{
	pa2m_nuevo_grupo("=============Pruebas del TP1=============");

	pa2m_nuevo_grupo("Pruebas de creación de objetos");
	pruebasCrearObjeto();

	pa2m_nuevo_grupo("Pruebas de creación de interacciones");
	pruebasCrearInteracciones();

	pa2m_nuevo_grupo("Pruebas de creación de sala");
	pruebas_crear_sala();

	pa2m_nuevo_grupo("Pruebas de la lista de nombres");
	pruebas_nombre_objetos();

	pa2m_nuevo_grupo("Pruebas de interacciones");
	pruebas_interacciones();

	pa2m_nuevo_grupo("=============Pruebas del TP2===============");

	pa2m_nuevo_grupo("Pruebas de la lista de conocidos");
	pruebas_nombre_conocidos();

	pa2m_nuevo_grupo("Pruebas de la lista de poseidos");
	pruebas_nombre_poseidos();

	pa2m_nuevo_grupo("Pruebas de agarrar objetos");
	pruebas_agarrar();

	pa2m_nuevo_grupo("Pruebas de describir objetos");
	pruebas_describir();

	pa2m_nuevo_grupo("Pruebas de escape");
	pruebas_escape();

	return pa2m_mostrar_reporte();
}
