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
* This file holds macros, include statements and the signature of the central function in the
 * implementation of the Perceptron algorithm.
*/

#ifndef LINESEPARATOR_LINESEPARATOR_H
#define LINESEPARATOR_LINESEPARATOR_H

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// -------------------------- const definitions -------------------------
#define MAX_VECTOR_LENGTH 74
#define MAX_LINE_LENGTH 151
#define MINIMAL_DIMENSION 2
#define COORDINATE_SEPARATOR ","
#define EPSILON 0.00001

// ------------------------------ functions -----------------------------

/**
 * @brief A function that produce a separator for specific vectors according to given input
 * examples, and than separate an unlimited amount of that vectors.
 * @param An address of a command file containing the training and data needed.
 * @return 0 if the process ended successfully, or 1 if got illegal dimension.
 */
int trainAndSeparateData(char *fileName);

#endif //LINESEPARATOR_LINESEPARATOR_H
