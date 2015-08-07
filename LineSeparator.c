/**
* @file LineSeparator.c
* @author  Omri Kaplan
* @date 4 Aug 2015
*
* @brief todo
*
* @section DESCRIPTION
* todo
*/
// ------------------------------ includes ------------------------------
#include "LineSeparator.h"

// -------------------------- const definitions -------------------------


// ------------------------------ functions -----------------------------


// todo typedef struct vector
typedef struct vector {
	int label;
	double coordinates[MAX_VECTOR_LENGTH];
} vector;

// todo inner product of vectors
double vectorInnerProduct (vector, vector);

// todo addition of two vectors
vector vectorAddition(vector, vector);

// todo parse file
int parseFile(); // todo add parameters

/**
 * @brief The addition function of two vector structs.
 * @param vector1 the first vector.
 * @param vector2 the second vector.
 */
vector vectorAddition(vector vector1, vector vector2)
{

}