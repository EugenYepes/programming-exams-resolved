# Parcial Resuelto – Sistema de Biblioteca

## Qué vas a aprender con este ejercicio

Este tipo de parcial aparece muy seguido en materias iniciales de programación.  
Evalúa si podés:
- Modelar un problema real.
- Separar lógica en funciones.
- Manejar arrays y estados.
- Búsqueda y procesamiento de datos.
- Lectura de archivos.

Si entendés bien este ejercicio, podés resolver la mayoría de los parciales similares.

## Explicación del enunciado
- Se debe crear un archivo respetando la estructura solicitada ej:
1001 501 2 1 3 4 1 2
donde el primer número es el id del socio, el segundo el id del libro y los últimos 6 la cantidad de ese libro prestada cada mes a ese socio.
- Se deben procesar estos datos y dado que el enunciado solo requiere la cantidad total de libros y no los libros prestados por mes, se acumulan todos los libros prestados en el semestre, por último, no se requiere saber qué libros pidió cada socio, sino cuántos. Las estructuras con los datos pasan a ser las siguientes. 
	1. socios
	2. cantidad préstamos del socio
	3. cantidad préstamos diferentes del socio

- Las estructuras datos, arrays, se relacionan a través de sus índices. El socio del índice 3 está relacionado con la cantidad de préstamos en el índice 3 etc.
- Hay que prestar atención al enunciado `No puede repetirse la dupla ID de socio y Código de libro.` esto simplifica completamente el procesamiento de los datos.

## Decisiones Clave

- **Modularizar el código**: Es requisito que el código esté modularizado. Evitar funciones que resuelvan múltiples problemas no relacionados.
- **Lectura separada**: Leer todo el archivo primero en arrays, luego procesar. Esto mantiene el código modular, pero gasta más memoria y tiempo de procesamiento.
- **Procesamiento por socio**: Agrupar datos en un loop aparte, usando búsqueda lineal para evitar duplicados.
- **Empates en búsqueda**: Para el socio con menos libros, elegir el último en caso de igualdad, usando `<=` en la comparación.
- **Búsquedas lineales**: Se recorren los arrays para encontrar los socios, contar la cantidad de libros etc. Siempre el mismo algoritmo, bucle con condición de corte cuando encuentra.

## Puntos de Dolor Comunes en Estos Parciales

Estos exámenes suelen enfocarse en habilidades básicas:
- **Indexación de múltiples arrays**: Mantener sincronizados arrays paralelos (ej: `socios[i]` con `prestamos[i]`) es propenso a errores.
- **Búsqueda y procesamiento en arrays**: Buscar elementos (como `obtenerIndiceSocio`) requiere loops manuales y control de los índices para evitar fallos de segmentación.
- **Lectura de datos desde archivo**: Parsear líneas con `fscanf` y manejar formatos variables es complicado, especialmente con datos numéricos.

## Mejoras de Eficiencia Posibles

Para hacerlo mejor (fuera de las restricciones):
- **Leer y procesar junto**: Integrar la lógica en el loop de lectura para no almacenar todo de golpe.
- **Memoria dinámica**: Usar `malloc` para arrays que crezcan según los datos reales.
- **Structs**: Agrupar datos relacionados (ej: struct Socio con id, total, libros) para código más limpio y seguro.

Si necesitas ayuda para entender este tipo de parciales o estás preparando un examen no dudes en contactarme para tener clases 1 - 1 con ejemplos personalizados y explicaciones detalladas.

- [Superprof](https://www.superprof.com.ar/clases-programacion-java-algoritmos-punteros-objetos-finales-utn-uba-ort-uia-senior-dev-fintech-analista.html)
- [Preply](https://preply.in/EUGENIO4ES3402806710?ts=17746642) 

Contacto: eugenionyepes@gmail.com
