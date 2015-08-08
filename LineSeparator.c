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
 * A struct that represents a vector, with maximum 74 coordinates.
 */
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

double vectorInnerProduct (vector vector1, vector vector2)
{
	double result = 0;
	for (int i=0; i<MAX_VECTOR_LENGTH; ++i)
	{
		result += vector1._coordinates[i] * vector2._coordinates[i];
	}
	return result;
}

int parseFile(FILE *theFile)
{
	int dimension = 0;
	int trainingExamples = 0;
	char line[151];
	for (int i = 0; i < 2; ++i) // todo change logic
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
	int index = 0;
	while (fgets(line, 151, theFile) != NULL)
	{
		char *coordinate = NULL;
		coordinate = strtok(line, ",");
		puts("this is coordinate"); // todo remove
		puts(coordinate); // todo remove
//		strtod();
		while ((coordinate = strtok(NULL, ",")) != NULL)
		{
			puts("this is coordinate"); // todo remove
			puts(coordinate); // todo remove
			// todo continue
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	FILE * dataFile = fopen(argv[1], "r");
	parseFile(dataFile);
	/* fopen, fclose, fgets,atoi, atof, strtok */
	return 0;
}
