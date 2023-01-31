/*
 * StringstreamGenerator.cpp
 *
 *  Created on: Jan 30, 2023
 *      Author: Palanath
 */

#include "StreamGenerator.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "../Common.hpp"
#include "../Utilities.hpp"

struct Problem* genMathProblem1() {
	unsigned optionCount = rand() % 3 + 3;
	Problem *problem = (Problem*) malloc(
			sizeof(struct Problem) + sizeof(char*) * optionCount);
	problem->optionCount = optionCount;

	// Generate randoms.
	short firstVar = rand() % 39 - 7, secondVar = rand() % 39 - 7;
	char firstVarName = rand() % 26 + 'a', secondVarName = rand() % 25 + 'a';
	if (secondVarName >= firstVarName)
		secondVarName++;

	short options[optionCount];
	std::cout << options[optionCount - 1];
	options[0] = firstVar * 2 + secondVar;
	fillUniqueRand<short>(1, optionCount, -30, 100, (short (*)[]) &options);

	// Calculate sizes.
	std::stringstream q;
	q << "What is the value of the variable, " << secondVarName
			<< ", when the following code finishes executing?";
	problem->question = flush(&q);

	q << "int " << firstVarName << " = " << firstVar << ';' << std::endl;
	q << "int " << secondVarName << " = " << firstVarName << " + " << secondVar
			<< ';' << std::endl;
	q << secondVarName << " += " << firstVarName << "++;" << std::endl;
	problem->code = flush(&q);
	for (unsigned i = 0; i < optionCount; i++) {
		q << options[i];
		problem->options[i] = flush(&q);
	}

	return problem;
}

struct Problem* StringGenerator::generateRandomProblem() {
	return genMathProblem1();
}

