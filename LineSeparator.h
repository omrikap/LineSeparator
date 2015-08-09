

#ifndef LINESEPARATOR_LINESEPARATOR_H
#define LINESEPARATOR_LINESEPARATOR_H
// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -------------------------- const definitions -------------------------

#define MAX_VECTOR_LENGTH 74
#define COORDINATE_SEPARATOR ","

/**
 * A struct that represents a vector, with maximum 74 coordinates.
 */
typedef struct vector {
	int _label;
	double _coordinates[MAX_VECTOR_LENGTH];
} vector;

// ------------------------------ functions -----------------------------

/**
 *
 */
int trainingSession(FILE*, int, int, vector);

/**
 *
 */
int separatingSession(FILE*);

/**
 *
 */
int sortData(FILE*); // todo maybe change to char*
#endif //LINESEPARATOR_LINESEPARATOR_H
