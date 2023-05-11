/*
 * OptimizationGenerator.cpp
 *
 *  Created on: Mar 5, 2023
 *      Author: Palanath
 */

#include "OptimizationGenerator.hpp"

#include <iostream>

#include "Utilities.hpp"

struct Problem* OptimizationGenerator::genForLoopProblem1() {
	bool correct = rand() % 2;
	Problem *p = genYesNoProblem(correct);
	p->question = mallocstr("Are the following two for loops equivalent?");
	std::stringstream q;
	q << "// Loop 1:" << std::endl << "for (int i = 0; i < len; i+=3) {"
			<< std::endl << "\tsum += arr[i]" << std::endl
			<< "\tsum += arr[i + 1]" << std::endl << "\tsum += arr[i + 2]"
			<< std::endl << '}' << std::endl << "// Loop 2:";
	if (correct)
		q << "for (int i = 0; i < len; i += 3)" << std::endl
				<< "\tsum += arr[i] + arr[i + 1] + arr[i + 2];";
	else
		switch (rand() % 3) {
		case 0:
			q << "for(int i = 0; i < len; i += 3)" << std::endl;
		}

	// TODO Complete
	return p;
}

struct Problem* OptimizationGenerator::genUnnecessaryCodeProblem1() {
	bool condtrue = rand() % 2, rettrue = rand() % 2, correct = rand() % 2;

	Problem *p = genYesNoProblem(correct);
	p->question = mallocstr("Are the following equivalent?");
	std::stringstream q;
	bool condeq = rand() % 2, retvar = rand() % 2;
	q << "// First" << std::endl << "if (";
	if (!(condeq || condtrue))
		q << '!';
	q << 'x';
	if (condeq)
		q << " == " << (condtrue ? "true" : "false");
	q << ") {" << std::endl << "\treturn "
			<< (retvar ? rettrue ? "x" : "!x":rettrue ? "true" : "false") << ";"
			<< std::endl << "} else {" << std::endl << "\treturn "
			<< (retvar ? rettrue ? "!x" : "x":rettrue ? "false" : "true")
			<< std::endl;
	q << std::endl;
	q << "// Second" << std::endl << "return "
			<< ((condtrue == rettrue) ^ correct ? "true" : "false")
			<< std::endl;

	return p;
}

struct Problem* OptimizationGenerator::generateProblem() {
	return genUnnecessaryCodeProblem1();
}
