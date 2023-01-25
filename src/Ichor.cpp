//============================================================================
// Name        : Ichor.cpp
// Author      : Palanath
// Version     :
// Copyright   : Palanath
// Description : Ichor in C++, Ansi-style
//============================================================================

#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <ctime>
#include <iostream>

using namespace std;

struct Problem {
	/*
	 * Used to keep track of the number of options.
	 */
	unsigned optionCount;
	char *question, *code, *footnote,
	// The correct answer is always stored in the first element.
			*options[];
};

struct Problem* generateRandomProblem() {
	int randomVar = rand() % 26;
	char randomVarLetter = randomVar + 'a', nextLetter = (randomVar + 1) % 26
			+ 'a';
	short randomIntegralValue = rand() % 32 + 3;

	char *code = (char*) malloc(
			(randomIntegralValue >= 10 ? 26 : 27) * sizeof(char));
	sprintf(code, "int %c = %d;\nint %c;\n%c = %c++;", randomVarLetter,
			randomIntegralValue, nextLetter, nextLetter, randomVarLetter);

	char *question = (char*) malloc(72 * sizeof(char));
	sprintf(question,
			"What is the value of the variable, %c, when the code finishes executing?",
			nextLetter);

	unsigned optionCount = rand() % 3 + 2;
	struct Problem *problem = (struct Problem*) malloc(
			sizeof(struct Problem) + sizeof(char*) * optionCount);
	problem->code = code;
	problem->optionCount = optionCount;
	problem->question = question;
	int results[optionCount] = { randomIntegralValue };
	for (unsigned short i = 1; i < optionCount; i++) {
		short randomNumb = rand() % (randomIntegralValue * 3 / 2);
		for (short j = 0; j < i; j++)
			if (randomNumb == results[j]) {
				randomNumb = rand() % (randomIntegralValue * 3 / 2);
				j = -1;
			}
		results[i] = randomNumb;
		problem->options[i] = (char*) malloc(
				sizeof(char) * (1 + (randomNumb >= 10 ? 3 : 2)));
		sprintf(problem->options[i], "%d", randomNumb);
	}

	return problem;
}



int main() {
	srand(time(0));

	struct Problem *prob = generateRandomProblem();

	return 0;
}
