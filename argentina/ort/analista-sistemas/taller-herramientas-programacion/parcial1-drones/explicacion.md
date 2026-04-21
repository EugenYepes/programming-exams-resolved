
# Resolución: Servicio de mensajería por drones

Este ejercicio corresponde al **Primer Parcial** de la materia **Taller de Herramientas de Programacion** y **Fundamentos de la programacion** (Carrera: Analista de Sistemas - ORT).

## Enunciado resumido
La empresa *Almagro Express* requiere procesar el rendimiento de drones en **10 ciudades**. Para cada ciudad se ingresa su nombre y los datos de los drones que operaron en ella hasta ingresar el código "**FIN**".

### Datos por dron:
* **Código identificador** (no vacío).
* **Cantidad de entregas** (entero ≥ 0).
* **Tiempo total de vuelo** (minutos entre 0 y 1440).

## Lógica de Resolución
El programa utiliza una estructura de **ciclos anidados**:
1. **Ciclo Externo (`for`):** Itera exactamente 10 veces para procesar cada ciudad2. **Ciclo Interno (`do-while`):** Permite la carga de una cantidad indeterminada de drones por ciudad, finalizando con la centinela "FIN".

### Estrategias aplicadas:
* **Validación de datos:** Se utilizan bucles `do-while` para asegurar que los nombres de ciudades y códigos de drones no estén vacíos, y que los valores numéricos respeten los rangos solicitados.
* **Acumuladores y Contadores:** Se utilizan para calcular el total de minutos de vuelo por ciudad y la cantidad de drones para obtener el promedio de entregas.
* **Búsqueda de Máximo:** Se implementó una lógica de máximo global para identificar el código del dron con mayor cantidad de entregas en toda la operación* **Manejo de Casos Especiales:** Si una ciudad no registra drones, el sistema emite el mensaje específico "Sin datos de entregas para..." cuando el contador de drones es 0 para la ciudad.

## Estadísticas calculadas
1. **Por ciudad:** Total de minutos de vuelo y promedio de entregas por dron.
2. **Global:** Total general de entregas entre todas las ciudades y el código del dron más productivo.

Si necesitas ayuda para entender este tipo de parciales o estás preparando un examen, no dudes en contactarme para tener clases 1 - 1 con ejemplos personalizados y explicaciones detalladas.

- [Superprof](https://www.superprof.com.ar/clases-programacion-java-algoritmos-punteros-objetos-finales-utn-uba-ort-uia-senior-dev-fintech-analista.html)
- [Preply](https://preply.in/EUGENIO4ES3402806710?ts=17746642) 

Contacto: eugenionyepes@gmail.com
