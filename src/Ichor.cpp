//============================================================================
// Name        : Ichor.cpp
// Author      : Palanath
// Version     :
// Copyright   : Palanath
// Description : Ichor in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Common.hpp"
#include "generators/StreamGenerator.hpp"

int main() {
	srand(time(0));

	Problem *p = StringstreamGenerator::generateRandomProblem();
	std::cout << p->question << std::endl << p->code << std::endl << std::endl;
	for (unsigned i = 0; i < p->optionCount; ++i) {
		std::cout << '(' << (char) ('A' + i) << ".) " << p->options[i]
				<< std::endl;
	}

	return 0;
}

