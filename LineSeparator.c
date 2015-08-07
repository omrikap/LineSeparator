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
	int _label;
	double _coordinates[MAX_VECTOR_LENGTH];
} vector;

/**
 * @brief The Standard Inner Product function of two vector structs.
 * @param vector1 the first vector.
 * @param vector2 the second vector.
 */
double vectorInnerProduct (vector, vector);

/**
 * @brief The addition function of two vector structs.
 * @param vector1 the first vector.
 * @param vector2 the second vector.
 */
vector vectorAddition(vector, vector);

// todo parse file
int parseFile(); // todo add parameters

vector vectorAddition(vector vector1, vector vector2)
{
	vector result = vector1;
	for (int i=0; i<MAX_VECTOR_LENGTH; ++i)
	{
		result._coordinates[i] = vector1._coordinates[i] + vector2._coordinates[i];
	}
	return result;
}

double vectorInnerProduct (vector vector1, vector vector2)
{
	double result = 0;
	for (int i=0; i<MAX_VECTOR_LENGTH; ++i)
	{
		result += vector1._coordinates[i] * vector2._coordinates[i];
	}
	return result;
}

int main()
{
	// todo -------------- functions driver. remove --------------------------
	vector a, b, c;
	a._coordinates[0] = 1.00;
	b._coordinates[0] = 2.3;
	c = vectorAddition(a, b);
	double d = vectorInnerProduct(b,c);
	printf("the inner product is: %f\n", d);
	 // todo ----------------------------------------------------------------
	return 0;
}
