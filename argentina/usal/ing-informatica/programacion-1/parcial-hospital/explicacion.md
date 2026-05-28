
# Resolución: Sistema de Gestión Hospitalaria

Este ejercicio corresponde al **Parcial** de la materia **Programación 1** (Carrera: Ingeniería Informática - USAL).

## Enunciado resumido
El Hospital Central necesita una aplicación en C para gestionar clínicas y pacientes internados. El sistema debe permitir cargar datos del hospital, agregar hasta 3 clínicas (cada una con una cantidad de camas definida por el usuario), y registrar pacientes respetando la disponibilidad de camas.

### Modelo de datos:
* **Hospital:** nombre, dirección, array de 3 clínicas.
* **Clínica:** código único, nombre, cantidad de camas, array dinámico de pacientes.
* **Paciente:** DNI, nombre, apellido.

### Restricciones del enunciado:
* Máximo 3 clínicas (constante).
* Código de clínica único.
* No se pueden agregar pacientes si no hay camas disponibles.
* Los pacientes se almacenan con `malloc` según la cantidad de camas.

## Lógica de Resolución

El programa utiliza **structs anidados** para modelar la jerarquía Hospital → Clínica → Paciente, y un **menú interactivo** con `do-while` + `switch`.

### Flujo principal:
1. **Menú con do-while:** Se ejecuta al menos una vez, repitiendo hasta que el usuario elija salir.
2. **Switch para opciones:** Cada opción del menú llama a una función específica, manteniendo el `main` limpio.
3. **Punteros:** Todas las funciones reciben `Hospital *hospital` para modificar la estructura original.

### Estrategias aplicadas:

* **Structs anidados:** Se declaran en orden de dependencia (Paciente → Clínica → Hospital). Clínica contiene un puntero a Paciente, no un array estático, porque el tamaño se define en tiempo de ejecución.
* **malloc/free:** Se usa `malloc` para dos cosas: el Hospital en sí (en `main`) y el array de pacientes de cada clínica (en `agregarClinica`). Al salir, se libera todo en orden inverso: primero los arrays internos, después el hospital.
* **Validaciones de negocio:**
  - Límite de 3 clínicas → se verifica `cantClinicas >= CANT_CLINICAS` antes de agregar.
  - Código único → `buscarClinica` retorna -1 si no existe; si ya existe, se rechaza.
  - Camas disponibles → se compara `cantPacientes < cant_camas` antes de internar.
* **Búsqueda lineal:** `buscarClinica` recorre el array de clínicas comparando el código. Retorna el índice o -1. Es el mismo patrón que se usa en la mayoría de los parciales de Programación 1.
* **Campo `cantPacientes`:** Agregado al struct `Clinica` para rastrear cuántos pacientes hay realmente internados (vs. cuántas camas tiene). Sin este campo, no se puede saber dónde almacenar el próximo paciente ni si hay lugar.

## Errores comunes que hacen desaprobar

1. **No almacenar el paciente:** Crear una variable local `Paciente nuevo`, cargar datos, pero nunca copiarla al array. El paciente se pierde al terminar la función.
2. **No asignar el código a la clínica:** Leer el código del usuario en una variable pero no guardarlo en `nuevo.codigo`. Después `buscarClinica` nunca lo encuentra.
3. **Buscar en `CANT_CLINICAS` en vez de `cantClinicas`:** Si solo hay 1 clínica cargada pero se busca en las 3 posiciones, se lee basura en las posiciones 1 y 2.
4. **No validar camas disponibles:** Si la clínica tiene 2 camas y ya hay 2 pacientes, agregar un tercero escribe fuera del array reservado con malloc (comportamiento indefinido, posible segmentation fault).
5. **No validar límite de clínicas:** Agregar una 4ta clínica accede fuera del array `clinicas[3]` que tiene tamaño 3.
7. **Memory leak:** Hacer `free(hospital)` sin liberar antes los arrays de pacientes de cada clínica. Primero se debe liberar la memoria de las estructuras internas.

## Mejoras posibles (fuera del alcance del parcial)
* **Función para liberar memoria:** Crear `liberarHospital(Hospital *h)` para encapsular la lógica de `free`.
* **Usar realloc para los pacientes** Utilizar realocación de memoria para los pacientes de una clinica.

Si necesitas ayuda para entender este tipo de parciales o estás preparando un examen, no dudes en contactarme para tener clases 1 - 1 con ejemplos personalizados y explicaciones detalladas.

- [Superprof](https://www.superprof.com.ar/clases-programacion-java-algoritmos-punteros-objetos-tdas-preparacion-finales-utn-uba-ort-senior-software.html)
- [Preply](https://preply.in/EUGENIO4ES3402806710?ts=17746642) 

Contacto: eugenionyepes@gmail.com
