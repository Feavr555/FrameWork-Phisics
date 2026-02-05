#pragma once
#include <stdlib.h>
#include <string.h>

#define VECTOR_INIT_CAPACITY 4

/**
 * @struct Vector
 * @brief Estructura que implementa un vector dinámico genérico (array dinámico)
 * 
 * Esta estructura permite almacenar elementos de cualquier tipo mediante
 * el uso de punteros void* y aritmética de punteros. El vector crece
 * automáticamente cuando se llena su capacidad actual.
 * 
 * @member data      Puntero al bloque de memoria que almacena los elementos
 * @member size      Número actual de elementos almacenados en el vector
 * @member capacity  Capacidad total actual (número máximo de elementos que puede almacenar sin redimensionar)
 * @member elem_size Tamaño en bytes de cada elemento (permite almacenar cualquier tipo de dato)
 */
typedef struct {
	void *data;
	unsigned int size;
	unsigned int capacity;
	size_t elem_size;
} Vector;

/**
 * @brief Inicializa un nuevo vector dinámico
 * 
 * Esta función reserva memoria para la estructura Vector y para el array
 * interno de datos. La capacidad inicial es 1 (aunque VECTOR_INIT_CAPACITY
 * está definida como 4, la implementación actual usa 1).
 * 
 * @param elem_size Tamaño en bytes de cada elemento que se almacenará
 * @return Puntero al vector inicializado, o NULL si falla la reserva de memoria
 * 
 * @note El vector debe ser liberado con Vector_destroy() cuando ya no se necesite
 * @warning La implementación actual usa capacidad inicial de 1, no VECTOR_INIT_CAPACITY
 */
Vector *Vector_init(size_t elem_size);

/**
 * @brief Añade un elemento al final del vector
 * 
 * Esta función inserta un nuevo elemento al final del vector. Si el vector
 * está lleno (size == capacity), redimensiona el vector duplicando su
 * capacidad antes de realizar la inserción.
 * 
 * @param vector Puntero al vector donde se insertará el elemento
 * @param element Puntero al elemento a insertar (debe tener tamaño elem_size)
 * 
 * @note Utiliza memcpy() para copiar los bytes del elemento al vector
 * @warning El puntero 'element' debe apuntar a memoria válida de al menos elem_size bytes
 */
void Vector_pushback(Vector *vector, void *element);

/**
 * @brief Obtiene un puntero a un elemento del vector por índice
 * 
 * Esta función devuelve un puntero al elemento en la posición especificada.
 * Permite acceso directo a los datos almacenados.
 * 
 * @param vector Puntero al vector
 * @param index Índice del elemento a recuperar (0-based)
 * @return Puntero al elemento, o NULL si el índice está fuera de rango
 * 
 * @note El puntero devuelto puede ser casteado al tipo apropiado
 * @warning El puntero devuelto apunta a memoria interna del vector, no debe ser liberado
 * @warning Modificar los datos a través de este puntero afecta directamente al vector
 */
void *Vector_getValue(Vector *vector, int index);

/**
 * @brief Redimensiona la capacidad del vector
 * 
 * Cambia la capacidad del vector a un nuevo valor. Si newReserve es menor
 * que el tamaño actual, los elementos excedentes se pierden (el tamaño
 * se ajusta a la nueva capacidad).
 * 
 * @param vector Puntero al vector a redimensionar
 * @param newReserve Nueva capacidad deseada (número de elementos)
 * 
 * @note Utiliza realloc() para redimensionar el array interno
 * @warning Si newReserve < vector->size, se perderán elementos del final
 * @warning Si realloc() falla, el vector queda en estado inconsistente
 */
void Vector_newsize(Vector *vector, int newReserve);

/**
 * @brief Libera toda la memoria asociada al vector
 * 
 * Esta función libera tanto el array interno de datos como la estructura
 * Vector. Después de llamar a esta función, el puntero al vector no debe
 * ser utilizado.
 * 
 * @param vector Puntero al vector a destruir
 * 
 * @note Equivalente a free() para estructuras Vector
 * @warning No libera memoria de elementos individuales si estos contienen punteros
 * @warning El puntero al vector se invalida después de esta llamada
 */
void Vector_destroy(Vector *vector);



/**
 * @example Ejemplo de uso básico:
 * 
 * // Crear vector de enteros
 * Vector *vec = Vector_init(sizeof(int));
 * 
 * // Añadir elementos
 * for(int i = 0; i < 10; i++) {
 *     Vector_pushback(vec, &i);
 * }
 * 
 * // Acceder a elementos
 * int *value = (int*)Vector_getValue(vec, 5);
 * if(value) printf("Elemento 5: %d\n", *value);
 * 
 * // Liberar memoria
 * Vector_destroy(vec);
 * 
 * 
 * @note Para tipos compuestos, asegurarse de que elem_size sea correcto:
 * typedef struct { float x, y; } Punto2D;
 * Vector *puntos = Vector_init(sizeof(Punto2D));
 */