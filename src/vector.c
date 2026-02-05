#include <vector.h>




Vector *Vector_init(size_t elem_size) {
	Vector *vector = (Vector*)malloc(sizeof(Vector));
	vector->data = malloc(1*elem_size);
	vector->size = 0;
	vector->capacity = 1;
	vector->elem_size = elem_size;
	return vector;
}


void Vector_pushback(Vector *vector, void *element) {
	if (vector->size == vector->capacity) {
		Vector_newsize(vector, vector->capacity * 2);
	}
	memcpy((char*)vector->data+(vector->size*vector->elem_size),
			element,vector->elem_size);
	vector->size++;
}

void *Vector_getValue(Vector *vector, int index) {
	if (index < 0 || index >= vector->size) {
        return NULL; // Retorna NULL si el índice está fuera de límites
    }
	return (char*)vector->data+(index*vector->elem_size);
}

void Vector_newsize(Vector *vector, int newReserve) {
	vector->data = realloc(vector->data, newReserve*vector->elem_size);
	vector->capacity = newReserve;
}

void Vector_destroy(Vector *vector) {
	free(vector->data);
	free(vector);
}