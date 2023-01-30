/*
 * DirectGenerator.cpp
 *
 *  Created on: Jan 30, 2023
 *      Author: Palanath
 */

#include "DirectGenerator.hpp"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "../Common.hpp"

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

	unsigned optionCount = rand() % 3 + 3;
	struct Problem *problem = (struct Problem*) malloc(
			sizeof(struct Problem) + sizeof(char*) * optionCount);
	problem->code = code;
	problem->optionCount = optionCount;
	problem->question = question;
	int results[optionCount] = { randomIntegralValue };
	sprintf(
			(problem->options[0] = (char*) malloc(
					sizeof(char) * (1 + (randomIntegralValue >= 10 ? 3 : 2)))),
			"%d", randomIntegralValue);
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

char* printProblem(const struct Problem *problem, const int openCodeBlockSize,
		const char *openCodeBlock, const int closeCodeBlockSize,
		const char *closeCodeBlock) {
	unsigned int positions[3 + problem->optionCount] = { strlen(
			problem->question), strlen(problem->code),
			problem->footnote == NULL ? 0 : strlen(problem->footnote) }; // End positions of all strings.
	for (unsigned short i = 0; i < problem->optionCount; i++)
		positions[i + 3] = strlen(problem->options[i]) + 4; // Add extra 3 size for prefix (e.g., "A. "), and another 1 for line break, totaling 4.
	int total = 0;
	for (unsigned short i = 0; i < 3 + problem->optionCount; i++)
		total += positions[i];
	char *arr = (char*) malloc(
			sizeof(char)
					* (total + 1 + openCodeBlockSize + closeCodeBlockSize));
	memcpy(arr, problem->question, sizeof(char) * positions[0]);
	memcpy(arr + positions[0], openCodeBlock, sizeof(char) * openCodeBlockSize);
	memcpy(arr + positions[0] + openCodeBlockSize, problem->code,
			sizeof(char) * positions[1]);
	memcpy(arr + positions[0] + openCodeBlockSize + positions[1],
			closeCodeBlock, sizeof(char) * closeCodeBlockSize);
	total = positions[0] + openCodeBlockSize + positions[1]
			+ closeCodeBlockSize;
	if (problem->footnote) {
		memcpy(
				arr + positions[0] + openCodeBlockSize + closeCodeBlockSize
						+ positions[1], problem->footnote,
				sizeof(char) * positions[2]);
		total += positions[2];
	}
	for (unsigned short i = 0; i < problem->optionCount; i++) {
		arr[total] = 'A' + i;
		arr[total + 1] = '.';
		arr[total + 2] = ' ';
		memcpy(arr + total + 3, problem->options[i],
				sizeof(char) * positions[3 + i]);
		total += positions[3 + i];
		arr[total - 1] = '\n';
	}
	arr[total] = 0;
	return arr;
}

