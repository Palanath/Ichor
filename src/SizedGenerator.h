/*
 * SizedGenerator.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Palanath
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifndef SIZEDGENERATOR_H_
#define SIZEDGENERATOR_H_

struct String {
	char *contents;
	unsigned size;
};

struct Problem {
	unsigned optionCount;
	struct String question, code, footnote, options[];
};

struct Problem* generateRandomProblem() {
	int options = rand() % 3 + 3;
	Problem *problem = (Problem*) malloc(
			sizeof(struct Problem) + sizeof(struct String) * options);
	problem->optionCount = options;

	// Generate randoms.
	int firstVar = rand() % 39 - 7, secondVar = rand() % 39 - 7;
	char firstVarName = rand() % 26 + 'a', secondVarName = rand() % 25 + 'a';
	if (secondVarName >= firstVarName)
		secondVarName++;

	// Calculate sizes.
	char* question = "What is the value of %s when the code finishes executing?";


}

#endif /* SIZEDGENERATOR_H_ */
