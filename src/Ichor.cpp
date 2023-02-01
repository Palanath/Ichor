//============================================================================
// Name        : Ichor.cpp
// Author      : Palanath
// Version     :
// Copyright   : Palanath
// Description : Ichor in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "Common.hpp"
#include "generators/StreamGenerator.hpp"
#include "Utilities.hpp"

void coutstrings(char (*strs)[]) {
}

int main() {
	srand(time(0));

	RESTRT: clearConsole();
	auto p = StringGenerator::generateRandomProblem();

	unsigned correctAnswerPos = 0;
	auto optionsCopy = copy(p->optionCount, (char*(*)[]) p->options);
	shuffle(p->optionCount, optionsCopy);

	std::cout << p->question << std::endl << p->code << std::endl << std::endl;
	for (unsigned i = 0; i < p->optionCount; ++i)
		std::cout << '(' << (char) ('A' + i) << ".) " << (*optionsCopy)[i]
				<< std::endl;

	std::cout << std::endl << "You may use number keys 1-"
			<< (p->optionCount > 9 ? 9 : p->optionCount)
			<< " or letter keys to select an answer:" << std::endl;

	int c = getchar();
	for (; !(c <= '9' && c >= '1') && !(c <= 'z' && c >= 'a') && c != EOF; c =
			getchar())
		;
	if (c <= '9' && c >= '1')
		c -= '1';
	else if (c != EOF)
		c -= 'a';
	if (c != EOF) {
		clearConsole();
		std::cout << p->question << std::endl << p->code << std::endl
				<< std::endl;
		for (unsigned i = 0; i < p->optionCount; ++i) {
			if (i == correctAnswerPos)
				std::cout << CONSOLE_GREEN;
			else if (i == c)
				std::cout << CONSOLE_RED;
			std::cout << '(' << (char) ('A' + i) << ".) " << (*optionsCopy)[i];
			if (i == correctAnswerPos || i == c)
				std::cout << CONSOLE_RESET;
			std::cout << std::endl;
		}
		std::cout << std::endl
				<< (c == correctAnswerPos ?
						"You answered right!" : "That's not correct...")
				<< std::endl << "Press ENTER to continue...";
		std::string s;
		getline(std::cin, s);
		getline(std::cin, s);
	}

	for (unsigned i = 0; i < p->optionCount; ++i)
		free(p->options[i]);
	free(p);
	free(optionsCopy);

	if (c != EOF)
		goto RESTRT;
	return 0;
}

