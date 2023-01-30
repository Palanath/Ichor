/*
 * SizedGenerator.cpp
 *
 *  Created on: Jan 30, 2023
 *      Author: Palanath
 */

#include "SizedGenerator.hpp"

#include <cstdlib>

#include "../Common.hpp"

struct String {
	char *contents;
	unsigned size;
};

struct Problem* SizedGenerator::generateRandomProblem() {
	int options = rand() % 3 + 3;
	struct Problem *problem = (struct Problem*) malloc(
			sizeof(struct Problem) + sizeof(struct String) * options);
	problem->optionCount = options;

	// Generate randoms.
	int firstVar = rand() % 39 - 7, secondVar = rand() % 39 - 7;
	char firstVarName = rand() % 26 + 'a', secondVarName = rand() % 25 + 'a';
	if (secondVarName >= firstVarName)
		secondVarName++;

	// Calculate sizes.
	char *question = "What is the value of %s when the code finishes executing?";

}

