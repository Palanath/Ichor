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
