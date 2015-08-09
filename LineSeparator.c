/**
* @file LineSeparator.c
* @author  Omri Kaplan
* @date 9 Aug 2015
*
* @brief todo
*
* @section DESCRIPTION
* todo
*/
// ------------------------------ includes ------------------------------
#include "LineSeparator.h"

// -------------------------- const definitions -------------------------

/**
 * A struct that represents a vector, with maximum 74 coordinates.
 */
typedef struct vector {
	int _label;
	double _coordinates[MAX_VECTOR_LENGTH];
} vector;

// ------------------------------ functions -----------------------------

/**
 * @brief The Standard Inner Product function of two vector structs.
 * @param vector1 the first vector.
 * @param vector2 the second vector.
 */
double vectorInnerProduct (vector, vector, int);

/**
 * @brief The addition function of two vector structs.
 * @param vector1 the first vector.
 * @param vector2 the second vector.
 */
vector vectorAddition(vector, vector, int);

/**
 * @brief todo
 */
vector scalarMultiplication(vector, double, int);

/**
 * @brief The function that calculates the position of the hyper-plane.
 * todo complete
 */
vector updateVector(const vector, const vector, const int);

/**
 *
 */
vector lineToVector(char*, int);

/**
 *
 */
int getSign(double);

/**
 *
 */
int trainingSession(FILE*, vector*);

/**
 *
 */
int separatingSession(FILE*, vector*, int);

vector vectorAddition(vector vector1, vector vector2, int dimension)
{
	vector result = vector1;
	for (int i=0; i < dimension; ++i)
	{
		result._coordinates[i] = vector1._coordinates[i] + vector2._coordinates[i];
	}
	return result;
}

vector scalarMultiplication(vector theVector, double scalar, int dimension) // todo test
{
	vector result = theVector;
	for (int i = 0; i < dimension; ++i)
	{
		result._coordinates[i] = theVector._coordinates[i] * scalar;
	}
	return result;
}

double vectorInnerProduct(vector vector1, vector vector2, int dimension)
{
	double result = 0;
	for (int i=0; i < dimension; ++i)
	{
		result += vector1._coordinates[i] * vector2._coordinates[i];
	}
	return result;
}

int getSign(double innerProductValue)
{
	if (fabs(innerProductValue) < EPSILON)
	{
		return -1;
	}
	else
	{
		return (int) (fabs(innerProductValue)/innerProductValue);
	}
}

vector lineToVector(char* line, int dimension)
{
	vector x = {0};
	int index = 0;
	x._coordinates[index] = atof(strtok(line, COORDINATE_SEPARATOR));
	++index;
	for (; index < dimension; ++index)
	{
		x._coordinates[index] = atof(strtok(NULL, COORDINATE_SEPARATOR));
	}
	char *label = strtok(NULL, COORDINATE_SEPARATOR);
	if (label != NULL)
	{
		x._label = atoi(label);
	}
	return x;
}

vector updateVector( vector separator, vector dataVector, int dimension) // todo change dataVector
{
	double innerProduct = getSign(vectorInnerProduct(dataVector, separator, dimension));
	if (innerProduct != dataVector._label)
	{
		separator = vectorAddition(separator, scalarMultiplication(dataVector, dataVector
				._label, dimension), dimension);
	}
	return separator;
}

int trainingSession(FILE *pFile, vector *separator)
{
	int dimension = 0;
	int trainingExamples = 0;
	char line[151];
	for (int i = 0; i < 2; ++i) // todo improve logic
	{
		fgets(line, 151, pFile);
		if (i == 0)
		{
			sscanf(line, "%d", &dimension);
		}
		else if (i == 1)
		{
			sscanf(line, "%d", &trainingExamples);
		}
	}
	for (int lineNumber = 0; lineNumber < trainingExamples; ++lineNumber)
	{
		fgets(line, 151, pFile);
		vector dataVector = lineToVector(line, dimension);
		*separator = updateVector(*separator, dataVector, dimension);
	}
	return dimension;
}

int separatingSession(FILE *pFile, vector *separator, int dimension)
{
	char line[151];
	while (fgets(line, 151, pFile) != NULL)
	{
		vector dataVector = lineToVector(line, dimension); // todo change 0 to dimension variable
		double point = vectorInnerProduct(dataVector, *separator, dimension);
		if (fabs(point) < EPSILON || point <= 0)
		{
			puts("-1");
		}
		else
		{
			puts("1");
		}
	}
	return 0;
}

int trainAndSeparateData(char *fileName)
{
	FILE *pFile = fopen(fileName, "r");
	vector separator = {0};
	int dimension = trainingSession(pFile, &separator);
	separatingSession(pFile, &separator, dimension);
	return 0;
}

int main(int argc, char* argv[])
{
	trainAndSeparateData(argv[1]);
	return 0;
}
