#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/** Cantidad máxima de clínicas que puede tener el hospital (dato del enunciado) */
#define CANT_CLINICAS 3

/**
 * El orden importa: se declaran de "adentro hacia afuera".
 * Paciente se declara primero porque Clinica lo contiene,
 * y Clinica se declara antes que Hospital por la misma razón.
 */

/**
 * Struct Paciente
 * Representa a un paciente internado en una clínica.
 */
typedef struct
{
	int dni;
	char nombre_paciente[50];
	char apellido_paciente[50];
} Paciente;

/**
 * Struct Clinica
 * Representa una clínica dentro del hospital.
 * - codigo: identificador único de la clínica
 * - cant_camas: capacidad máxima (define el tamaño del malloc de pacientes)
 * - cantPacientes: cantidad actual de pacientes internados
 * - pacientes: array dinámico asignado con malloc según cant_camas
 */
typedef struct
{
	int codigo;
	char nombreClinica[50];
	int cant_camas;
	int cantPacientes;	 /* Contador de pacientes actualmente internados */
	Paciente *pacientes; /* Array dinámico: se reserva con malloc */
} Clinica;

/**
 * Struct Hospital
 * Estructura principal que contiene toda la información del hospital.
 * - clinicas[]: array estático de tamaño CANT_CLINICAS (3)
 * - cantClinicas: cantidad de clínicas efectivamente cargadas
 */
typedef struct
{
	char nombreHospital[50];
	char direccion[50];
	Clinica clinicas[CANT_CLINICAS];
	int cantClinicas;
} Hospital;


void cargarHospital(Hospital *hospital);
void agregarClinica(Hospital *hospital);
void agregarPaciente(Hospital *hospital);
int buscarClinica(Hospital *hospital, int cantidad, int cod_clinica);
void mostrarDatos(Hospital *hospital);

int main()
{
	int opcion;

	/*
	 * Se reserva memoria dinámica para el hospital con malloc.
	 * Esto es un requisito del enunciado (uso de memoria dinámica).
	 * Se inicializa cantClinicas en 0 porque aún no se cargó ninguna.
	 */
	Hospital *hospital = (Hospital *)malloc(sizeof(Hospital));
	hospital->cantClinicas = 0;

	/*
	 * Menú interactivo con do-while:
	 * Se ejecuta al menos una vez y se repite hasta que el usuario elija salir.
	 * Se usa switch para direccionar cada opción a su función correspondiente.
	 */
	do
	{
		printf("\n---Sistema de gestion Hospitalaria---\n");
		printf("1.Cargar datos del Hospital\n");
		printf("2.Agregar Clinica (solo se permitira la carga de %d)\n", CANT_CLINICAS);
		printf("3.Agregar pacientes\n");
		printf("4.Mostrar datos de la clinica\n");
		printf("0.SALIR\n");
		printf("Opcion: ");
		scanf("%d", &opcion);

		switch (opcion)
		{
		case 1:
			cargarHospital(hospital);
			break;
		case 2:
			agregarClinica(hospital);
			break;
		case 3:
			agregarPaciente(hospital);
			break;
		case 4:
			mostrarDatos(hospital);
			break;
		case 0:
			printf("Gracias!\n");
			break;
		default:
			printf("Ingrese una opcion valida\n");
		}
	} while (opcion != 0);

	/*
	 * Liberar toda la memoria reservada.
	 * Primero se libera el array de pacientes de cada clínica (malloc interno).
	 * Si solo se hace free(hospital), los arrays de pacientes quedan sin liberar (memory leak).
	 */
	for (int i = 0; i < hospital->cantClinicas; i++)
	{
		free(hospital->clinicas[i].pacientes);
	}
	free(hospital);

	return 0;
}

/**
 * Solicita al usuario el nombre y la dirección del hospital.
 *
 * Se recibe un puntero a Hospital para modificar directamente la estructura
 * original (si se recibiera por valor, los cambios se perderían al salir).
 *
 * Nota: scanf con " %[^\n]" lee hasta el salto de línea, permitiendo
 * ingresar nombres con espacios (ej: "Hospital Central").
 * El espacio antes del % descarta whitespace pendiente en el buffer.
 */
void cargarHospital(Hospital *hospital)
{
	printf("Ingrese el nombre del hospital: \n");
	scanf(" %[^\n]", hospital->nombreHospital);
	printf("Ingrese la direccion: \n");
	scanf(" %[^\n]", hospital->direccion); //
}

/**
 * Registra una nueva clínica en el hospital.
 *
 * Validaciones:
 *   1. No se pueden agregar más de CANT_CLINICAS (3) clínicas.
 *   2. El código de clínica debe ser único (se busca con buscarClinica).
 *
 * Si la clínica es nueva, se reserva memoria dinámica con malloc para
 * el array de pacientes según la cantidad de camas ingresada.
 */
void agregarClinica(Hospital *hospital)
{
	Clinica nuevo;
	int cod_clinica;

	/*
	 * Valida que no se supere el límite de clínicas.
	 * El array clinicas[] tiene tamaño CANT_CLINICAS; si se intenta agregar
	 * una más, se accedería fuera del array (comportamiento indefinido).
	 * No se usa realloc: el enunciado dice que son 3 clínicas fijas.
	 */
	if (hospital->cantClinicas >= CANT_CLINICAS)
	{
		printf("No se pueden agregar mas clinicas (maximo %d)\n", CANT_CLINICAS);
		return;
	}

	printf("Ingrese el codigo de la clinica:\n");
	scanf("%d", &cod_clinica);

	/*
	 * Se busca si ya existe una clínica con ese código.
	 * IMPORTANTE: se busca en cantClinicas (las cargadas), NO en CANT_CLINICAS.
	 * Si se buscara en CANT_CLINICAS, se leería basura de posiciones no inicializadas.
	 */
	int indice = buscarClinica(hospital, hospital->cantClinicas, cod_clinica);

	if (indice < 0)
	{
		nuevo.codigo = cod_clinica;

		printf("Ingrese el nombre de la clinica: \n");
		scanf(" %[^\n]", nuevo.nombreClinica);

		printf("Ingrese cantidad de camas: \n");
		scanf("%d", &nuevo.cant_camas);

		// Inicializar el contador de pacientes en 0
		nuevo.cantPacientes = 0;

		// Copiar la clínica al array del hospital
		hospital->clinicas[hospital->cantClinicas] = nuevo;

		/*
		 * Reservar memoria dinámica para los pacientes.
		 * Se usa malloc con cant_camas * sizeof(Paciente) porque la cantidad
		 * máxima de pacientes está limitada por la cantidad de camas.
		 */
		hospital->clinicas[hospital->cantClinicas].pacientes =
			(Paciente *)malloc(nuevo.cant_camas * sizeof(Paciente));

		hospital->cantClinicas++;
		printf("Clinica agregada exitosamente.\n");
	}
	else
	{
		printf("Clinica ya ingresada (codigo %d ya existe)\n", cod_clinica);
	}
}

/**
 * Registra un nuevo paciente en una clínica existente.
 *
 * Validaciones:
 *   1. La clínica debe existir (se busca por código).
 *   2. La clínica debe tener camas disponibles (cantPacientes < cant_camas).
 *
 * El paciente se almacena en la posición cantPacientes del array dinámico
 * y luego se incrementa el contador.
 */
void agregarPaciente(Hospital *hospital)
{
	Paciente nuevo;
	int indice;
	int cod_clinica;

	printf("Ingrese el codigo de la clinica:\n");
	scanf("%d", &cod_clinica);

	indice = buscarClinica(hospital, hospital->cantClinicas, cod_clinica);

	if (indice >= 0)
	{
		// Verifica disponibilidad de camas antes de agregar.
		Clinica *clinica = &hospital->clinicas[indice];

		if (clinica->cantPacientes >= clinica->cant_camas)
		{
			printf("No hay camas disponibles en la clinica '%s'\n", clinica->nombreClinica);
			return;
		}

		printf("Ingrese su nombre: \n");
		scanf(" %s", nuevo.nombre_paciente);
		printf("Ingrese su apellido: \n");
		scanf(" %s", nuevo.apellido_paciente);
		printf("Ingrese su DNI: \n");
		scanf("%d", &nuevo.dni);

		// Almacena el paciente en el array dinámico de la clínica.
		clinica->pacientes[clinica->cantPacientes] = nuevo;
		clinica->cantPacientes++;
		printf("Paciente agregado exitosamente.\n");
	}
	else
	{
		printf("Clinica no encontrada\n");
	}
}

/**
 * Busca lineal de una clínica por su código dentro del array de clínicas del hospital.
 *
 * Parámetros:
 *   hospital    - puntero al hospital
 *   cantidad    - cantidad de clínicas a recorrer
 *   cod_clinica - código a buscar
 *
 * Retorna:
 *   El índice de la clínica si la encuentra, -1 si no la encuentra.
 */
int buscarClinica(Hospital *hospital, int cantidad, int cod_clinica)
{
	int i;
	for (i = 0; i < cantidad; i++)
	{
		if (hospital->clinicas[i].codigo == cod_clinica)
		{
			return i;
		}
	}
	return -1;
}

/**
 * Muestra toda la información del hospital: clínicas y sus pacientes.
 */
void mostrarDatos(Hospital *hospital)
{
	printf("\n========== DATOS DEL HOSPITAL ==========\n");
	printf("Hospital: %s\n", hospital->nombreHospital);
	printf("Direccion: %s\n", hospital->direccion);
	printf("=========================================\n");

	for (int i = 0; i < hospital->cantClinicas; i++)
	{
		Clinica *clinica = &hospital->clinicas[i];

		printf("\n--- Clinica: %s (Codigo: %d) ---\n", clinica->nombreClinica, clinica->codigo);
		printf("Camas totales: %d | Ocupadas: %d | Disponibles: %d\n",
			   clinica->cant_camas,
			   clinica->cantPacientes,
			   clinica->cant_camas - clinica->cantPacientes);

		if (clinica->cantPacientes == 0)
		{
			printf("  (Sin pacientes internados)\n");
		}

		/**
		 * Se itera hasta cantPacientes (pacientes realmente cargados),
		 * NO hasta cant_camas. Iterar hasta cant_camas mostraría basura en
		 * las posiciones del array que no fueron inicializadas.
		 */
		for (int j = 0; j < clinica->cantPacientes; j++)
		{
			printf("  Paciente %d: %s %s, DNI: %d\n",
				   j + 1,
				   clinica->pacientes[j].nombre_paciente,
				   clinica->pacientes[j].apellido_paciente,
				   clinica->pacientes[j].dni);
		}
	}
}
