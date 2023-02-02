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
	fillUniqueRand<short>(1, problem->optionCount, -30, 100, options);

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
	fillUniqueRand(0, problem->optionCount / 2, 'a', char('z' + 1), arr);
	char varname = rand() % 26 + 'a';

	// Populate problem.
	std::stringstream q;
	for (unsigned i = 0; i < problem->optionCount / 2; ++i) {
		q << (int) arr[i];
		problem->options[i * 2] = flush(&q);
		q << arr[i];
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

struct Problem* genCommaOpTrick1() {
	Problem *problem = genProblem(4);
	// TODO Make n1 and n2 always different. (This is required o/w two answer choices will be the same.)
	unsigned short n1 = rand() % 7, n2 = rand() % 7;
	char var1 = rand() % 26, var2 = (var1 + 1) % 26;
	var1 += 'a';
	var2 += 'a';

	const char question[] =
			"What is the value of the expression (x + y) after the following code executes?";
	problem->question = (char*) malloc(sizeof(question));
	strcpy(problem->question, question);
	std::stringstream q;
	// Generate random data needed.
	q << "int " << var1 << " = 0, " << var2 << " = 0;" << std::endl << '('
			<< var1 << ", " << var2 << ") = (" << n1 << ", " << n2 << ");";

	problem->options[1] = flush(&q);
	q << "C. " << n2;
	problem->code = flush(&q);
	q << "A. 0";
	problem->options[0] = flush(&q);
	q << "B. " << n1;
	problem->options[2] = flush(&q);
	q << "D. " << n1 + n2;
	problem->options[3] = flush(&q);

	return problem;
}

struct Problem* StringGenerator::generateRandomProblem() {
	switch (rand() % 3) {
	case 0:
		return genMathProblem1();
	case 1:
		return genCharLiteralProblem1();
	case 2:
		return genCommaOpTrick1();
	}
	return rand() % 2 ? genMathProblem1() : genCharLiteralProblem1();
}

