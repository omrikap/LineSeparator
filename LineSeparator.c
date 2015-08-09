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

/**
 * @brief todo
 */
vector scalarMultiplication(vector, double);

/**
 * @brief The function that calculates the position of the hyper-...
 * todo complete
 */
void updateVector(vector, vector, int);

vector lineToVector(char*, int);

// todo parse file
int parseFile(FILE*);

vector vectorAddition(vector vector1, vector vector2)
{
	vector result = vector1;
	for (int i=0; i<MAX_VECTOR_LENGTH; ++i)
	{
		result._coordinates[i] = vector1._coordinates[i] + vector2._coordinates[i];
	}
	return result;
}

vector scalarMultiplication(vector theVector, double scalar) // todo test
{
	vector result = theVector;
	for (int i = 0; i < MAX_VECTOR_LENGTH; ++i)
	{
		result._coordinates[i] = theVector._coordinates[i] * scalar;
	}
	return result;
}

double vectorInnerProduct(vector vector1, vector vector2)
{
	double result = 0;
	for (int i=0; i<MAX_VECTOR_LENGTH; ++i)
	{
		result += vector1._coordinates[i] * vector2._coordinates[i];
	}
	return result;
}

vector lineToVector(char* line, int dimension)
{
	vector x;
	int index = 0;
	x._coordinates[index] = atof(strtok(line, COORDINATE_SEPARATOR));
	printf("%d'th coordinate: %f\n", index, x._coordinates[index]);
	++index;
	for (; index < dimension; ++index)
	{
		x._coordinates[index] = atof(strtok(NULL, COORDINATE_SEPARATOR));
		printf("%d'th coordinate: %f\n", index, x._coordinates[index]);
	}
	x._label = atoi(strtok(NULL, COORDINATE_SEPARATOR));
	return x;
}

void updateVector( vector separator, vector dataVector, int tag) // todo change dataVector name,
// implement
{

}

int trainingSession(FILE *pFile, int dimension, int trainingExamples, vector separator)
{
	char line[151];
	puts("here"); // todo remove
	for (int lineNumber = 0; lineNumber < trainingExamples; ++lineNumber)
	{
		fgets(line, 151, pFile);
		vector dataVector = lineToVector(line, dimension);
//		updateVector(separator, dataVector, dataVector._label);
		printf("dataVector._label: %d\n", dataVector._label);
	}
//	puts("returning"); // todo remove
	return 0;
}

int parseFile(FILE *theFile)
{
	int dimension = 0;
	int trainingExamples = 0;
	char line[151];
	for (int i = 0; i < 2; ++i) // todo improve logic
	{
		fgets(line, 151, theFile);
		if (i == 0)
		{
			sscanf(line, "%d", &dimension);
		}
		else if (i == 1)
		{
			sscanf(line, "%d", &trainingExamples);
		}
	}
	vector w; // todo where to put?
	vector x;
	trainingSession(theFile, dimension, trainingExamples, w);
	while (fgets(line, 151, theFile) != NULL)
	{
		x = lineToVector(line, dimension);
	}
//	for (int j = 0; j < MAX_VECTOR_LENGTH; ++j) // todo remove
//	{
//		printf("%f\n", x._coordinates[j]);
//	}
	return 0;
}

int main(int argc, char* argv[])
{
	FILE * dataFile = fopen(argv[1], "r");
	parseFile(dataFile);
	/* fopen, fclose, fgets,atoi, atof, strtok */
	return 0;
}
