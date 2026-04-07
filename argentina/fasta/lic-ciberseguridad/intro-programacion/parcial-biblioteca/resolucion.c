#include <stdio.h>
#include <string.h>

// Constantes para límites y umbrales
#define MAX_REGISTROS 100
#define MESES 6
#define CANT_PRESTAMOS_SOCIO_FRECUENTE 150
#define CANT_PRESTAMOS_SOCIO_MEDIO 80
#define CANT_PRESTAMOS_SOCIO_BAJO 20

/*
 * Inicio del programa.
 * Lee el archivo de préstamos, procesa los registros para obtener datos por socio,
 * y muestra los resultados requeridos: resumen por socio y socio con menor alcance.
 */
int main()
{
	// Arrays para almacenar datos leídos del archivo
	int idSocios[MAX_REGISTROS] = {0}, idLibros[MAX_REGISTROS] = {0}, totPrestamosSemestreRegistro[MAX_REGISTROS] = {0};
	int ret = leerArchivo(idSocios, idLibros, totPrestamosSemestreRegistro);

	// Arrays para almacenar datos procesados por socio único
	int sociosProcesados[MAX_REGISTROS] = {0};
	int cantidadPrestamos[MAX_REGISTROS] = {0};
	int cantidadLibrosDiferentes[MAX_REGISTROS] = {0};
	int sociosProcesadosCont = 0;

	if (ret >= 0)
	{
		// Procesar registros para agrupar por socio
		procesarRegistros(idSocios, idLibros, totPrestamosSemestreRegistro, ret, sociosProcesados, cantidadPrestamos, cantidadLibrosDiferentes, &sociosProcesadosCont);
		
		// a) Mostrar resumen por socio con etiquetas
		mostrarSociosEtiqueta(sociosProcesados, cantidadPrestamos, sociosProcesadosCont);

		// b) Encontrar socio con menor cantidad de libros distintos
		int indexMenor = buscarIndexMenor(cantidadLibrosDiferentes, sociosProcesadosCont);
		printf("Socio con menos libros distintos: %d pidió %d libros diferentes\n", sociosProcesados[indexMenor], cantidadLibrosDiferentes[indexMenor]);

		// b) Calcular porcentaje de socios con menos de 3 libros distintos
		int cantidadSociosMenosLibros = cantLibrosDistintosMenorA(cantidadLibrosDiferentes, sociosProcesadosCont, 3);
		printf("Porcentaje de socios con menos de 3 libros diferentes: %.2f%%\n", (float)cantidadSociosMenosLibros/sociosProcesadosCont*100);
	}
	else
	{
		printf("Error al leer el archivo\n");
	}

	return 0;
}

/*
 * Lee el archivo data.txt y almacena los datos en los arrays proporcionados.
 * Parámetros:
 *   - idSocios: array para IDs de socios
 *   - idLibros: array para códigos de libros
 *   - totPrestamosSemestre: array para total de préstamos por registro (suma de 6 meses)
 * Retorna: número de registros leídos, o -1 si error al abrir archivo
 */
int leerArchivo(int idSocios[], int idLibros[], int totPrestamosSemestre[])
{
	FILE *f = fopen("data.txt", "r");
	int i = 0, j = 0;
	int auxCantLibrosMes = 0;

	if (f == NULL)
		return -1;

	// Leer cada línea: ID socio, ID libro, y 6 valores de préstamos por mes
	while (i < MAX_REGISTROS && fscanf(f, "%d %d", &idSocios[i], &idLibros[i]) == 2)
	{
		// Sumar los 6 valores de préstamos mensuales para este registro
		while (j < MESES && fscanf(f, "%d", &auxCantLibrosMes) == 1)
		{
			totPrestamosSemestre[i] += auxCantLibrosMes;
			j++;
		}
		j = 0; // Resetear contador de meses para el próximo registro
		i++;
	}

	fclose(f);
	return i;
}

/*
 * Procesa los registros para agrupar datos por socio único.
 * Actualiza los arrays de socios procesados, cantidad de préstamos totales y cantidad de libros diferentes.
 * Parámetros:
 *   - idSocios, idLibros, totPrestamosSemestre: datos de registros
 *   - tam: cantidad de registros
 *   - sociosProcesados, cantidadPrestamos, cantidadLibrosDiferentes: arrays a actualizar
 *   - sociosProcesadosCont: contador de socios únicos (pasado por referencia)
 */
void procesarRegistros(int idSocios[], int idLibros[], int totPrestamosSemestre[], int tam, int sociosProcesados[], int cantidadPrestamos[], int cantidadLibrosDiferentes[], int *sociosProcesadosCont)
{
	int socioId = -1;
	int socioIndex = -1;

	for (int i = 0; i < tam; i++) // Para cada registro, verificar si el socio ya fue procesado
	{
		socioId = idSocios[i];
		socioIndex = obtenerIndiceSocio(sociosProcesados, *sociosProcesadosCont, socioId);

		if (socioIndex != -1) // Socio ya procesado, actualizar datos
		{
			cantidadPrestamos[socioIndex] += totPrestamosSemestre[i];
			cantidadLibrosDiferentes[socioIndex] += 1; // Incrementar cantidad de libros diferentes
		}
		else
		{
			// Nuevo socio: agregar a la lista
			sociosProcesados[*sociosProcesadosCont] = idSocios[i];
			cantidadPrestamos[*sociosProcesadosCont] = totPrestamosSemestre[i];
			cantidadLibrosDiferentes[*sociosProcesadosCont] = 1;
			(*sociosProcesadosCont)++;
		}
	}
}

/*
 * Busca el índice de un socio en el array de socios procesados.
 * Parámetros:
 *   - idSocios: array de IDs de socios
 *   - tam: tamaño del array
 *   - socio: ID del socio a buscar
 * Retorna: índice si encontrado, -1 si no
 */
int obtenerIndiceSocio(int idSocios[], int tam, int socio)
{
	int i = 0;
	while (i < tam && idSocios[i] != socio)
	{
		i++;
	}
	return i < tam ? i : -1;
}

/*
 * Muestra el resumen por socio: ID, total de préstamos y etiqueta.
 * Parámetros:
 *   - idSocios: array de IDs de socios
 *   - cantidadPrestamos: array de totales de préstamos
 *   - tam: cantidad de socios
 */
void mostrarSociosEtiqueta(int idSocios[], int cantidadPrestamos[], int tam)
{
	for (int i = 0; i < tam; i++)
	{
		printf("Socio ID: %d, Prestamos Totales: %d  Etiqueta: %s\n", idSocios[i], cantidadPrestamos[i], obtenerEtiqueta(cantidadPrestamos[i]));
	}
}

/*
 * Determina la etiqueta de un socio basada en la cantidad de préstamos.
 * Parámetros:
 *   - cantidadPrestamos: total de préstamos del socio
 * Retorna: cadena con la etiqueta correspondiente
 */
char *obtenerEtiqueta(int cantidadPrestamos)
{
	if (cantidadPrestamos > CANT_PRESTAMOS_SOCIO_FRECUENTE)
	{
		return "SOCIO FRECUENTE";
	}
	else if (cantidadPrestamos >= CANT_PRESTAMOS_SOCIO_MEDIO)
	{
		return "SOCIO MEDIO"; // Nota: según enunciado, debería ser "MEDIO" sin "SOCIO"
	}
	else if (cantidadPrestamos >= CANT_PRESTAMOS_SOCIO_BAJO)
	{
		return "SOCIO REGULAR"; // Nota: enunciado dice "REGULAR" para el caso intermedio
	}
	else
	{
		return "SOCIO BAJO"; // Nota: enunciado dice "BAJO"
	}
}

/*
 * Encuentra el índice del socio con la menor cantidad de libros diferentes.
 * En caso de empate, retorna el último (mayor índice).
 * Parámetros:
 *   - cantidadLibrosDiferentes: array con cantidades por socio
 *   - cantSocios: cantidad de socios
 * Retorna: índice del socio con menor cantidad
 */
int buscarIndexMenor(int cantidadLibrosDiferentes[], int cantSocios)
{
	int menor = cantidadLibrosDiferentes[0];
	int indexMenor = 0;
	for (int i = 1; i < cantSocios; i++)
	{
		if (cantidadLibrosDiferentes[i] <= menor) // <= para tomar el último en caso de empate
		{
			menor = cantidadLibrosDiferentes[i];
			indexMenor = i;
		}
	}
	return indexMenor;
}

/*
 * Cuenta cuántos socios tienen menos de 'limite' libros diferentes.
 * Parámetros:
 *   - cantidadLibrosDiferentes: array con cantidades por socio
 *   - tam: cantidad de socios
 *   - limite: límite inferior (exclusivo)
 * Retorna: cantidad de socios que cumplen la condición
 */
int cantLibrosDistintosMenorA(int cantidadLibrosDiferentes[], int tam, int limite)
{
	int count = 0;
	// Cada índice de cantidadLibrosDiferentes corresponde a un socio procesado.
	for (int i = 0; i < tam; i++)
	{
		if (cantidadLibrosDiferentes[i] < limite)
		{
			count++;
		}
	}
	return count;
}
