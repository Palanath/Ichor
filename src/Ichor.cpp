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
#include <sstream>
#include <string>

#include "Common.hpp"
#include "generators/StreamGenerator.hpp"
#include "Utilities.hpp"

int main() {
	srand(time(0));

	int c = 0;
	while (c != EOF) {
		clearConsole();
		auto p = StringGenerator::generateRandomProblem();

		char **optionsCopy = copy(p->optionCount, p->options);
		shuffle(1, p->optionCount, optionsCopy); // Shuffle all but first element.
		unsigned correctAnswerPos = rand() % p->optionCount;
		std::swap(optionsCopy[0], optionsCopy[correctAnswerPos]);

		prompt(&std::cout, p);
		for (unsigned i = 0; i < p->optionCount; ++i)
			std::cout << '(' << (char) ('A' + i) << ".) " << optionsCopy[i]
					<< std::endl;

		std::cout << std::endl << "You may use number keys 1-"
				<< (p->optionCount > 9 ? 9 : p->optionCount)
				<< " or letter keys to select an answer:" << std::endl;

		int c = getchar();
		for (; !(c <= '9' && c >= '1') && !(c <= 'z' && c >= 'a') && c != EOF;
				c = getchar())
			;
		if (c != EOF) {
			if (c <= '9' && c >= '1')
				c -= '1';
			else if (c != EOF)
				c -= 'a';
			clearConsole();
			prompt(&std::cout, p);
			for (unsigned i = 0; i < p->optionCount; ++i) {
				if (i == correctAnswerPos)
					std::cout << CONSOLE_GREEN;
				else if (i == c)
					std::cout << CONSOLE_RED;
				std::cout << '(' << (char) ('A' + i) << ".) " << optionsCopy[i];
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

		delProblem(p);
		free(optionsCopy);
	}
	return 0;
}

