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
	Problem *problem = genProblem(rand() % 3 + 3);

	// Generate randoms.
	short firstVar = rand() % 39 - 7, secondVar = rand() % 39 - 7;
	char firstVarName = rand() % 26 + 'a', secondVarName = rand() % 25 + 'a';
	if (secondVarName >= firstVarName)
		secondVarName++;

	short options[problem->optionCount];
	options[0] = firstVar * 2 + secondVar;
	fillUniqueRand<short>(1, problem->optionCount, -30, 100,
			(short (*)[]) &options);

	// Generate questions.
	std::stringstream q;
	q << "What is the value of the variable, " << secondVarName
			<< ", when the following code finishes executing?";
	problem->question = flush(&q);

	q << "int " << firstVarName << " = " << firstVar << ';' << std::endl;
	q << "int " << secondVarName << " = " << firstVarName << " + " << secondVar
			<< ';' << std::endl;
	q << secondVarName << " += " << firstVarName << "++;" << std::endl;
	problem->code = flush(&q);
	for (unsigned i = 0; i < problem->optionCount; i++) {
		q << options[i];
		problem->options[i] = flush(&q);
	}

	return problem;
}

struct Problem* genMathProblem2() {
	Problem *problem = genProblem(rand() % 2 + 4);
	//Generate random stuff.
}

struct Problem* StringGenerator::generateRandomProblem() {
	return genMathProblem1();
}

