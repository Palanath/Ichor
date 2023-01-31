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

struct Problem* genCharLiteralProblem1() {
	Problem *problem = genProblem((rand() % 2 + 2) * 2);

	//Generate random stuff.
	char arr[problem->optionCount / 2];
	fillUniqueRand(0, 3, 'a', 'z', (char (*)[]) &arr);
	char varname = rand() % 26 + 'a';

	// Populate problem.
	std::stringstream q;
	for (unsigned i = 0; i < problem->optionCount / 2; ++i) {
		q << arr[i * 2];
		problem->options[i * 2] = flush(&q);
		q << (int) arr[i * 2];
		problem->options[i * 2 + 1] = flush(&q);
	}
	q
			<< "Which of the following is printed as a result of running the following code?";
	problem->question = flush(&q);
	q << "auto " << varname << " = +'" << arr[0] << "';" << std::endl
			<< "cout << " << varname << ';';
	problem->code = flush(&q);
	return problem;
}

struct Problem* StringGenerator::generateRandomProblem() {
	return rand() % 2 ? genMathProblem1() : genCharLiteralProblem1();
}

