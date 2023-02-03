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

	unsigned short n1 = rand() % 7, n2 = rand() % 7;
	if (n2 == n1)
		n2 = (n2 + 1) % 7;
	n1++; // Shift range up from 0-7 to 1-8.
	n2++; // ^
	char var1 = rand() % 26, var2 = (var1 + 1) % 26;
	var1 += 'a';
	var2 += 'a';

	std::stringstream q;
	q << "What is the value of the expression (" << var1 << " + " << var2
			<< ") after the following code executes?";
	problem->question = flush(&q);
	q << "int " << var1 << " = 0, " << var2 << " = 0;" << std::endl << '('
			<< var1 << ", " << var2 << ") = (" << n1 << ", " << n2 << ");";

	problem->code = flush(&q);
	q << n2;
	problem->options[0] = flush(&q);
	q << "0";
	problem->options[1] = flush(&q);
	q << n1;
	problem->options[2] = flush(&q);
	q << n1 + n2;
	problem->options[3] = flush(&q);

	return problem;
}
/*
 * Picks a random type suitable for use in FunctionCallProblem1 based on the specified value.
 * The void type is selected using the argument 0. The largest acceptable input value for this function is 14, which will return long double.
 * Values above that will all return char.
 */
const char* pickPrimitiveType(unsigned type) {
	switch (type) {
	case 0:
		return "void";
	case 1:
		return "int";
	case 2:
		return "short";
	case 3:
		return "char";
	case 4:
		return "bool";
	case 5:
		return "float";
	case 6:
		return "double";
	case 7:
		return "signed char";
	case 8:
		return "unsigned char";
	case 9:
		return "unsigned int";
	case 10:
		return "short int";
	case 11:
		return "long int";
	case 12:
		return "unsigned short int";
	case 13:
		return "unsigned long int";
	case 14:
		return "long double";
	}
	return "char";
}
struct Problem* genFunctionCallProblem1() {
	Problem *p = genProblem(5);
	std::stringstream q;
	q
			<< "Which of the following declares a function that CANNOT be called like so:";
	p->question = flush(&q);
	q << "// Function call:" << std::endl << "func(1);";
	p->code = flush(&q);

	// This problem is primarily meant to allow the user to learn that func() {} can take any number of args, whereas func(void) can't take any.

	bool returnTypeVaries = rand() % 2;
	unsigned types[5] = { 0 };
	fillUniqueRand<unsigned>(1, 5, 1, 15, types);

	for (unsigned i = 0; i < 5; ++i) {

		// Ret type
		if (returnTypeVaries)
			q << pickPrimitiveType(rand() % 15);
		else
			q << "void";
		// Param type
		q << " func(" << pickPrimitiveType(types[i]) << ");";
		p->options[i] = flush(&q);
	}
	q
			<< "Note that function definitions have bodies (e.g. void f(int x) {}), whereas function declarations do not (e.g. void f(int);).";
	p->footnote = flush(&q);
	return p;
}

struct Problem* genFunctionCallProblem2() {
	Problem *p = genProblem(5);
	std::stringstream q;
	q
			<< "Which of the following declares a function that can be called like so:";
	p->question = flush(&q);
	q << "// Function call:" << std::endl << "func(1, \"2\", short(3));";
	p->code = flush(&q);

	q << "void func();";
	p->options[0] = flush(&q);
	q << "void func(void);";
	p->options[1] = flush(&q);

	unsigned types[3];
	fillUniqueRand<unsigned>(0, 3, 1, 15, types);
	for (unsigned i = 0; i < 3; ++i) {
		q << pickPrimitiveType(rand() % 15) << " func("
				<< pickPrimitiveType(types[i]) << ", "
				<< pickPrimitiveType(types[i]) << ", "
				<< pickPrimitiveType(types[i]) << ");";
		p->options[i + 2] = flush(&q);
	}

	return p;
}

// The following 2 functions need to be updated when a new problem is added.
// pickProblem needs to have another case (1 greater than the last value is fine)
// generateRandomProblem() needs to call pickProblem with a larger random range (so rand() % x needs to be changed to rand() % (x+1) in the call to pickProblem; e.g. rand() % 5 becomes rand() % 6).
struct Problem* StringGenerator::pickProblem(unsigned problemID) {
	switch (problemID) {
	case 0:
		return genMathProblem1();
	case 1:
		return genCharLiteralProblem1();
	case 2:
		return genCommaOpTrick1();
	case 3:
		return genFunctionCallProblem1();
	case 4:
		return genFunctionCallProblem2();
	}
	return genMathProblem1();
}
struct Problem* StringGenerator::generateRandomProblem() {
	return StringGenerator::pickProblem(rand() % 5);
}

