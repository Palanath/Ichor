/*
 * PathologicalGenerator.cpp
 *
 *  Created on: Jan 30, 2023
 *      Author: Palanath
 */

#include <cstdlib>
#include <iostream>

#include "Common.hpp"
#include "PathologicalGenerator.hpp"
#include "Utilities.hpp"

struct Problem* genMathProblem1() {
	Problem *problem = genProblem(rand() % 3 + 3);

	// Generate randoms.
	short firstVar = rand() % 39 - 7, secondVar = rand() % 39 - 7;
	char firstVarName = rand() % 26 + 'a', secondVarName = rand() % 25 + 'a';
	if (secondVarName >= firstVarName)
		secondVarName++;

	short options[problem->optionCount];
	options[0] = firstVar * 2 + secondVar;
	fillUniqueRand<short>(0, 1, problem->optionCount, -30, 100, options);

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

struct Problem* genLoopProblem1() {

	bool ival = rand() % 2, includeNoneInOptions = rand() % 2;

	Problem *p = genProblem(4 + includeNoneInOptions);
	std::stringstream q;
	q << "How many times does the body of this loop run?";
	p->question = flush(&q);

	q << "for (int i = " << ival << ", j = 10; (i - j) && j > -100; ++i, j--)"
			<< std::endl << "\t;// ...";
	p->code = flush(&q);

	q << std::boolalpha << (ival ? 110 : 10);
	p->options[0] = flush(&q);
	int res[3];
	fillUniqueRand(0, 3, 0, 6, res);
	for (unsigned i = 0; i < 3; ++i) {
		switch (res[i]) {
		case 0:
			q << (ival ? 10 : 110);
			break;
		case 1:
			q << 9;
			break;
		case 2:
			q << 100;
			break;
		case 3:
			q << 99;
			break;
		case 4:
			q << 101;
			break;
		case 5:
			q << 111;
		}
		p->options[i + 1] = flush(&q);
	}
	if (includeNoneInOptions) {
		q << "None";
		p->options[4] = flush(&q);
	}

	return p;

}

struct Problem* genComparisonOperatorPrecedenceProblem1() {
	bool eq = rand() % 2;
	int x = rand() % 20, y = rand() % 20, z = rand() % 20;

	Problem *p = genProblem(2);
	std::stringstream q;
	q
			<< "What is the value of the variable p after the code finishes executing?";
	p->question = flush(&q);
	q << "int x = " << x << ", y = " << y << ", z = " << z << ';' << std::endl
			<< "int p = (x <";
	if (eq)
		q << '=';
	q << " y != y >";
	if (eq)
		q << '=';
	q << " z);";
	p->code = flush(&q);

	bool predicate = x <= y != y >= z;
	q << predicate; // Print as number (since x, in the question, is of type int).
	p->options[0] = flush(&q);
	q << !predicate;
	p->options[1] = flush(&q);

	return p;
}

struct Problem* genSwitchProblem1() {
	Problem *p = genProblem(2);
	std::stringstream q;

	unsigned y = rand() % 15 + 1, trigger = rand() % 3;
	bool shortDecl = rand() % 2;

	q << "Does the following code print anything?";
	p->question = flush(&q);
	q << "int y = " << y;
	if (shortDecl)
		q << ", trigger = ";
	else
		q << ';' << std::endl << "int trigger = ";
	q << trigger << ';' << std::endl << std::endl << "switch (trigger)"
			<< std::endl << "case 0: if (y >= 5) {" << std::endl
			<< "case 1: if (y < 10) {" << std::endl << "case 2:" << std::endl
			<< "\tstd::cout << \"PRINTED\" << std::endl;" << std::endl << "}}";
	p->code = flush(&q);

	bool prints = trigger == 2
			|| y < 10 && (trigger == 1 || trigger == 0 && y >= 5);

	q << "No";
	p->options[prints] = flush(&q);
	q << "Yes";
	p->options[!prints] = flush(&q);
	return p;

}

struct Problem* genIntegralPromotionOfBoolProblem1() {
	Problem *p = genProblem(rand() % 3 + 5);
	std::stringstream q;

	unsigned numb = rand() % 30;
	q << "What does the following code print?";
	p->question = flush(&q);
	q << "bool a = " << numb << ';' << std::endl
			<< "int array[] = {a, a * 2, a * 3, a * 4, a * 5};" << std::endl
			<< "std::cout << array[a];";
	p->code = flush(&q);
	q << (numb ? 2 : 0);
	p->options[0] = flush(&q);

	unsigned arr[p->optionCount - 1];
	fillUniqueRand<unsigned>(0, p->optionCount - 1, 2, 30, arr);
	for (unsigned i = 0; i < p->optionCount - 1; ++i) {
		q << (arr[i] == 2 ? 1 : arr[i]);
		p->options[i + 1] = flush(&q);
	}

	return p;
}

struct Problem* genCommaOperatorProblem1() {
	Problem *p = genProblem(2);
	unsigned values[2];
	fillUniqueRand<unsigned>(0, 2, 3, 13, values);

	std::stringstream q;
	q << "What does the following code print?";
	p->question = flush(&q);
	q << "unsigned a = " << values[0] << ", b = " << values[1] << ';'
			<< std::endl << "std::cout << a, b;";
	p->code = flush(&q);
	q << values[0];
	p->options[0] = flush(&q);
	q << values[1];
	p->options[1] = flush(&q);

	return p;
}

struct Problem* genStringLiteralConcatenationProblem1() {
	unsigned opc = rand() % 7 + 3;

	Problem *p = genProblem(opc);

	std::stringstream q;
	q << "What does the following code print?";
	p->question = flush(&q);
	q << "std::cout << ";
	unsigned short count = 0;
	for (short literals = rand() % 7 + 3; literals >= 0; --literals)
		q << (rand() % 2 ? ++count, "\"\\\"\"" : "\"\"");
	q << ';';
	p->code = flush(&q);

	unsigned arr[opc];
	arr[0] = count;
	fillUniqueRand<unsigned>(0, 1, opc, 1, 15, arr);
	for (unsigned i = 0; i < opc; ++i) {
		for (unsigned j = 0; j < arr[i]; ++j)
			q << '"';
		p->options[i] = flush(&q);
	}

	return p;
}

struct Problem* genCommaOperatorProblem2() {
	bool rescount = rand() % 2, unflipped = rand() % 2;
	Problem *p = genProblem(5 + rescount);
	std::stringstream q;
	q << "What is the value of the variable x?";
	p->question = flush(&q);

	if (rescount) {
		if (unflipped)
			// Invokes a buggy warning on G++ (5 "unused").
			q << "int x = (0, 1 ? 2, 3 : 4, 5);";
		else
			q << "int x = (5, 4 ? 3, 2 : 1, 0)";

		p->code = flush(&q);
		for (unsigned short i = 0; i < 6; ++i) {
			q << (unflipped ? 5 - i : i);
			p->options[i] = flush(&q);
		}
	} else {
		if (unflipped)
			q << "int x = (0, 1 ? 2, 3 : 4);";
		else
			q << "int x = (4, 3 ? 2, 1 : 0);";

		std::cout << "TESTING!!!!!!!" << std::endl;

		p->code = flush(&q);
		q << 1 + unflipped * 2; // Correct answer (fourth number from the left in expression).
		p->options[0] = flush(&q);
		for (unsigned short i = 1; i < 5; ++i) {
			q << (i <= 1 + unflipped * 2 ? i - 1 : i);
			p->options[i] = flush(&q);
		}
	}

	return p;
}

struct Problem* genOperatorSyntaxAmbiguityProblem1() {
	Problem *p = genProblem(4);
	std::stringstream q;
	q << "What is the value of the variable z?";
	p->question = flush(&q);

	unsigned options[2];
	fillUniqueRand<unsigned>(0, 2, 1, 9, options);

	q << "int x = " << options[0] << ", y = " << options[1] << ';' << std::endl
			<< "int z = x +++ y;";
	p->code = flush(&q);

	q << options[0] + options[1];
	p->options[0] = flush(&q);
	q << options[0];
	p->options[1] = flush(&q);
	q << options[1];
	p->options[2] = flush(&q);
	q << options[0] + options[1] + 1;
	p->options[3] = flush(&q);

	return p;
}

struct Problem* genCharAdditionProblem1() {
	Problem *p = genProblem(3);
	std::stringstream q;
	q << "What is the type of the variable x?";
	p->question = flush(&q);

	bool aNumb = rand() % 2, bNumb = rand() % 2;
	q << "char a = ";
	(aNumb ? q << 1 : q << "'a'") << ", b = ";
	(bNumb ? q << 2 : q << "'b'") << ";" << std::endl << "auto x = a + b;";
	p->code = flush(&q);

	p->options[0] = mallocstr("int");
	p->options[1] = mallocstr("char");
	p->options[2] = mallocstr("short");

	return p;
}

struct Problem* genReturnByReferenceProblem1() {
	Problem *p = genProblem(6);

	p->question = mallocstr(
			"What set of numbers does the following code print?");

	int r = rand() % 32 + 3;

	const char *line =
			rand() % 2 ?
					"\tstd::cout << (++test()) << std::endl;" :
					"\tstd::cout << ++test() << std::endl;";
	std::stringstream q;
	q << "#include <iostream>" << std::endl << std::endl << "auto& test() {"
			<< std::endl << "\tstatic int x = " << r << ";" << std::endl
			<< "\treturn ++x;" << std::endl << '}' << std::endl << std::endl
			<< "int main() {" << std::endl << line << std::endl << line
			<< std::endl << line << std::endl << '}';
	p->code = flush(&q);

	q << r + 2 << ", " << r + 4 << ", " << r + 6;
	p->options[0] = flush(&q);
	q << r + 1 << ", " << r + 2 << ", " << r + 3;
	p->options[1] = flush(&q);
	q << r + 1 << ", " << r + 3 << ", " << r + 5;
	p->options[2] = flush(&q);
	q << r << ", " << r + 2 << ", " << r + 4;
	p->options[3] = flush(&q);
	q << r << ", " << r + 1 << ", " << r + 2;
	p->options[4] = flush(&q);
	q << r + 2 << ", " << r + 3 << ", " << r + 4;
	p->options[5] = flush(&q);

	return p;
}

// The following 2 functions need to be updated when a new problem is added.
// pickProblem needs to have another case (1 greater than the last value is fine)
// generateRandomProblem() needs to call pickProblem with a larger random range (so rand() % x needs to be changed to rand() % (x+1) in the call to pickProblem; e.g. rand() % 5 becomes rand() % 6).
struct Problem* PathologicalGenerator::pickProblem(unsigned problemID) {
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
	case 5:
		return genLoopProblem1();
	case 6:
		return genComparisonOperatorPrecedenceProblem1();
	case 7:
		return genSwitchProblem1();
	case 8:
		return genIntegralPromotionOfBoolProblem1();
	case 9:
		return genCommaOperatorProblem1();
	case 10:
		return genStringLiteralConcatenationProblem1();
	case 11:
		return genCommaOperatorProblem2();
	case 12:
		return genOperatorSyntaxAmbiguityProblem1();
	case 13:
		return genCharAdditionProblem1();
	case 14:
		return genReturnByReferenceProblem1();
	}
	return genMathProblem1();
}
struct Problem* PathologicalGenerator::generateRandomProblem() {
	return PathologicalGenerator::pickProblem(rand() % 15);
}

