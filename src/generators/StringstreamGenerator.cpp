/*
 * StringstreamGenerator.cpp
 *
 *  Created on: Jan 30, 2023
 *      Author: Palanath
 */

#include "StringstreamGenerator.hpp"

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "../Common.hpp"
#include "../Utilities.hpp"

struct Problem* StringstreamGenerator::generateRandomProblem() {

	int optionCount = rand() % 3 + 3;
	Problem *problem = (Problem*) malloc(
			sizeof(struct Problem) + sizeof(char*) * optionCount);
	problem->optionCount = optionCount;

	// Generate randoms.
	short firstVar = rand() % 39 - 7, secondVar = rand() % 39 - 7;
	char firstVarName = rand() % 26 + 'a', secondVarName = rand() % 25 + 'a';
	if (secondVarName >= firstVarName)
		secondVarName++;

	short options[optionCount] { firstVar * 2 + secondVar };
	for (unsigned short i = 1; i < optionCount; ++i) {
		// TODO generate random options and then print them below.
		options[i] = rand() % 39 - 7;
	}

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

	return problem;
}

