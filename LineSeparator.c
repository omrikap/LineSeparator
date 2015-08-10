/**
* @file LineSeparator.c
* @author  Omri Kaplan
* @date 9 Aug 2015
*
* @brief A Perceptron implementation.
*
* @section DESCRIPTION
* Perceptron is a machine learning algorithm that can decide if an input belongs to a certain
* group or to a different group.
* This file holds the implementation of the function declared in LineSeparator.h.
*/
// ------------------------------ includes ------------------------------
#include <assert.h>
#include "LineSeparator.h"

// -------------------------- const definitions -------------------------

#define ILLEGAL_DIMENSION 1
#define SUCCESS 0
#define ONE_ARGUMENT 1
#define FIRST_LINE 0
#define FIRST_COORDINATE 0
#define NEGATIVE_SIGN -1
#define DIMENSION_AND_TRAINING_LINES 2
#define DIMENSION_LINE 0
#define TRAINING_LINE 1

/**
 * @brief A struct that represents a vector, with maximum 74 coordinates.
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
 * @return The dot product of the two vectors that were given.
 */
double vectorInnerProduct(const vector vector1, const vector vector2, const int dimension);

/**
 * @brief The addition function of two vector structs.
 * @param vector1 the first vector.
 * @param vector2 the second vector.
 * @return A new vector, the sum of tow vectors that were given.
 */
vector vectorAddition(const vector vector1, const vector vector2, const int dimension);

/**
 * @brief Multiply each coordinate of a vector by a specific scalar.
 * @param The vector to be multiplied.
 * @param The scalar to multiply the vector by.
 * @param The length of the vectors.
 */
vector scalarMultiplication(const vector theVector, const double scalar, const int dimension);

/**
 * @brief The function that calculates the position of the hyperplane.
 * @param The vector that represents the hyperplane.
 * @param The vector we update the hyperplane by.
 * @param The length of the vectors.
 * @return the updated separator vector.
 */
vector updateVector(vector separator, const vector dataVector, const int dimension);

/**
 * @brief This method get a line from the file, and parse it to a new vector.
 * @param the line to parse.
 * @param the vector length.
 * @return A vector.
 */
vector lineToVector(char* line, const int dimension);

/**
 * @brief Takes an inner product value, and returns it's sign with accuracy determined by the
 * macro EPSILON.
 * @param The value of an inner product.
 * @return 1 if the value is positive, -1 if the value is zero or negative.
 */
int getSign(const double innerProductValue);

/**
 * @brief A function that produce a separator vector out of a training set of vectors written in
 * a command file.
 * @param A command file, where the training session is written.
 * @param A pointer to the separator vector, that will be updated during the training.
 * @return the dimension of the vector space, i.e. the length of the vectors that we test.
 */
int trainingSession(FILE *pFile, vector *separator);

/**
 * @brief This function separate input according to a given hyperplane separator.
 * @param A file containing the data to be separated.
 * @param The hyperplane separator.
 * @param The dimension of the vector space, i.e. the length of the vectors.
 * @return 0 if the process ended successfully. Else undefined.
 */
int separatingSession(FILE *pFile, const vector *separator, const int dimension);

// ------------------- function implementations --------------------------

vector vectorAddition(const vector vector1, const vector vector2, const int dimension)
{
	vector result = vector1;
	for (int i=FIRST_COORDINATE; i < dimension; ++i)
	{
		result._coordinates[i] = vector1._coordinates[i] + vector2._coordinates[i];
	}
	return result;
}

vector scalarMultiplication(const vector theVector, const double scalar, const int dimension)
{
	vector result = theVector;
	for (int i = FIRST_COORDINATE; i < dimension; ++i)
	{
		result._coordinates[i] = theVector._coordinates[i] * scalar;
	}
	return result;
}

double vectorInnerProduct(const vector vector1, const vector vector2, const int dimension)
{
	double result = 0;
	for (int i=FIRST_COORDINATE; i < dimension; ++i)
	{
		result += vector1._coordinates[i] * vector2._coordinates[i];
	}
	return result;
}

int getSign(const double innerProductValue)
{
	if (fabs(innerProductValue) < EPSILON)
	{
		return NEGATIVE_SIGN;
	}
	else
	{
		return (int) (fabs(innerProductValue)/innerProductValue);
	}
}

vector lineToVector(char* line, const int dimension)
{
	vector x = {0};
	int index = 0;
	x._coordinates[index] = atof(strtok(line, COORDINATE_SEPARATOR));
	++index;
	for (; index < dimension; ++index)
	{
		x._coordinates[index] = atof(strtok(NULL, COORDINATE_SEPARATOR));
		assert(&x._coordinates[index] != NULL); // detect bad formatted input.
	}
	char *label = strtok(NULL, COORDINATE_SEPARATOR);
	if (label != NULL)
	{
		x._label = atoi(label);
	}
	return x;
}

vector updateVector(vector separator, const vector dataVector, const int dimension)
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
	char line[MAX_LINE_LENGTH];
	for (int lineCounter = FIRST_LINE; lineCounter < DIMENSION_AND_TRAINING_LINES; ++lineCounter)
	{
		fgets(line, MAX_LINE_LENGTH, pFile);
		if (lineCounter == DIMENSION_LINE)
		{
			sscanf(line, "%d", &dimension);
		}
		else if (lineCounter == TRAINING_LINE)
		{
			sscanf(line, "%d", &trainingExamples);
		}
	}
	for (int lineNumber = FIRST_LINE; lineNumber < trainingExamples; ++lineNumber)
	{
		fgets(line, MAX_LINE_LENGTH, pFile);
		vector dataVector = lineToVector(line, dimension);
		*separator = updateVector(*separator, dataVector, dimension);
	}
	return dimension;
}

int separatingSession(FILE *pFile, const vector *separator, const int dimension)
{
	char line[MAX_LINE_LENGTH];
	while (fgets(line, MAX_LINE_LENGTH, pFile) != NULL)
	{
		vector dataVector = lineToVector(line, dimension);
		int vectorLabel = getSign(vectorInnerProduct(dataVector, *separator, dimension));
		printf("%d\n", vectorLabel);
	}
	return SUCCESS;
}

int trainAndSeparateData(char *fileName)
{
	FILE *pFile = fopen(fileName, "r");
	vector separator = {0};
	int dimension = trainingSession(pFile, &separator);
	assert(dimension >= MINIMAL_DIMENSION);
	if (dimension < MINIMAL_DIMENSION)
	{
		return ILLEGAL_DIMENSION;
	}
	int endStatement = separatingSession(pFile, &separator, dimension);
	fclose(pFile);
	return endStatement;
}

int main(int argc, char* argv[])
{
	assert(argc != ONE_ARGUMENT);
	return trainAndSeparateData(argv[1]);
}
