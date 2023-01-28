//============================================================================
// Name        : Ichor.cpp
// Author      : Palanath
// Version     :
// Copyright   : Palanath
// Description : Ichor in C++, Ansi-style
//============================================================================

#include <ctime>
#include "DirectGenerator.h"



int main() {
	srand(time(0));

	struct Problem *prob = generateRandomProblem();
	printf("%s", printProblem(prob, 5, "\n```\n", 4, "```\n"));

	return 0;
}
