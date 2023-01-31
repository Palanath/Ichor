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

int main() {
	srand(time(0));

	RESTRT: clearConsole();
	Problem *p = StringGenerator::generateRandomProblem();
	std::cout << p->question << std::endl << p->code << std::endl << std::endl;
	for (unsigned i = 0; i < p->optionCount; ++i)
		std::cout << '(' << (char) ('A' + i) << ".) " << p->options[i]
				<< std::endl;

	std::cout << std::endl << "You may use number keys 1-"
			<< (p->optionCount > 9 ? 9 : p->optionCount)
			<< " or letter keys to select an answer:" << std::endl;

	unsigned correctAnswerPos = 0;

	int c = getchar();
	for (; !(c <= '9' && c >= '1') && !(c <= 'z' && c >= 'a') && c != EOF; c =
			getchar())
		;
	if (c <= '9' && c >= '1')
		c -= '1';
	else
		c -= 'a';
	if (c != EOF) {
		clearConsole();
		std::cout << p->question << std::endl << p->code << std::endl
				<< std::endl;
		for (unsigned i = 0; i < p->optionCount; ++i) {
			if (i == correctAnswerPos)
				std::cout << CONSOLE_GREEN;
			std::cout << '(' << (char) ('A' + i) << ".) " << p->options[i];
			if (i == correctAnswerPos)
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
	if (c != EOF)
		goto RESTRT;
	return 0;
}

