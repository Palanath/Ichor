/*
 * Common.cpp
 *
 *  Created on: Jan 30, 2023
 *      Author: Palanath
 */

#include "Common.hpp"

#include <stdlib.h>

struct Problem* genProblem(unsigned optionCount) {
	Problem *p = (Problem*) malloc(
			sizeof(Problem) + sizeof(char*) * optionCount);
	p->optionCount = optionCount;
	p->footnote = nullptr;
	return p;
}

void delProblem(struct Problem *p) {
	for (unsigned i = 0; i < p->optionCount; ++i)
		free(p->options[i]);
	free(p->question);
	free(p->code);
	if (p->footnote != nullptr)
		free(p->footnote);
	free(p);
}
