# Explicación de Decisiones en la Resolución

## Restricciones del Parcial

Este parcial de Introducción a la Programación tenía reglas estrictas: **no se podían usar memoria dinámica ni structs**. Todo debía ser arrays fijos, sin agrupar datos en estructuras personalizadas. Por eso se resuelve con múltiples arrays paralelos para manejar la info de socios y préstamos, lo que complica el código pero cumple con las reglas.

## Decisiones Clave

- **Lectura separada**: Leer todo el archivo primero en arrays, luego procesar. Esto mantiene el código modular, pero gasta más memoria.
- **Procesamiento por socio**: Agrupar datos en un loop aparte, usando búsqueda lineal para evitar duplicados.
- **Empates en búsqueda**: Para el socio con menos libros, elegir el último en caso de igualdad, usando `<=` en la comparación.

## Puntos de Dolor Comunes en Estos Parciales

Estos exámenes suelen enfocarse en habilidades básicas que duelen:
- **Indexación de múltiples arrays**: Mantener sincronizados arrays paralelos (ej: `socios[i]` con `prestamos[i]`) es propenso a errores.
- **Búsqueda y procesamiento en arrays**: Buscar elementos (como `obtenerIndiceSocio`) requiere loops manuales y control de los indices para evitar segmentations faults.
- **Lectura de datos desde archivo**: Parsear líneas con `fscanf` y manejar formatos variables es complicado, especialmente con datos numéricos.

## Mejoras de Eficiencia Posibles

Para hacerlo mejor (fuera de las restricciones):
- **Leer y procesar junto**: Integrar la lógica en el loop de lectura para no almacenar todo de golpe.
- **Memoria dinámica**: Usar `malloc` para arrays que crezcan según los datos reales.
- **Structs**: Agrupar datos relacionados (ej: struct Socio con id, total, libros) para código más limpio y seguro.

Si necesitas ayuda para entender este tipo de parciales, no dudes en contactarme para tener clases 1 - 1

- [Superprof](https://www.superprof.com.ar/clases-programacion-java-algoritmos-punteros-objetos-finales-utn-uba-ort-uia-senior-dev-fintech-analista.html)
- [Preply](https://preply.in/EUGENIO4ES3402806710?ts=17746642) 

Contacto: eugenionyepes@gmail.com
