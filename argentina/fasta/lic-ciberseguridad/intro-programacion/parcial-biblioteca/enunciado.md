# Enunciado del Parcial: Biblioteca Universitaria

## Descripción del Problema

Una biblioteca universitaria registra los préstamos de libros realizados durante el primer semestre en un archivo de texto llamado **data.txt**.

## Formato del Archivo

Cada línea del archivo contiene:

**ID de socio** (entero positivo)

**Código de libro** (entero positivo)

**Cantidad de préstamos por mes del semestre** (6 valores enteros, de enero a junio)

*Un mismo socio puede aparecer repetido, ya que puede haber pedido distintos libros.*

*Un mismo libro también puede aparecer repetido, ya que pudo haber sido prestado a varios socios.*

*No puede repetirse la dupla ID de socio y Código de libro.*

*El archivo no está ordenado por ningún criterio.*

## Requisitos del Programa

Se pide desarrollar un programa en lenguaje **C**, claro, eficiente y correctamente modularizado, que lea el archivo y almacene solamente la información necesaria en estructuras adecuadas para luego resolver las siguientes consignas:

### a) Resumen por Socio

Para cada **id de socio** registrado, informar: el total de préstamos del semestre (sumando todos los libros), y una etiqueta de préstamos según el total:

**"SOCIO FRECUENTE"**: más de 150 préstamos

**"MEDIO"**: más de 80 préstamos

**"BAJO"**: menos de 20 préstamos

**"REGULAR"**: cualquier otro caso

### b) Socio con Menor Alcance + Proporción de Socios No Frecuentes

Determinar el **ID de socio** que haya pedido la menor cantidad de libros distintos.

*Si hay empate, informar el último ID que aparezca.*

Calcular e informar el porcentaje de socios que hayan pedido menos de 3 libros distintos.

## Aclaraciones Importantes

Considerar únicamente las estructuras de almacenamiento y sentencias del lenguaje vistas en la asignatura hasta el momento del segundo parcial; el uso de otras estructuras y sentencias resultarán en la automática desaprobación del examen.
