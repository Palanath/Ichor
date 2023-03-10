/*
 * Common.h
 *
 *  Created on: Jan 30, 2023
 *      Author: Palanath
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>

struct Problem {
	unsigned optionCount;
	char *question, *code, *footnote = nullptr, *options[];
};

class ProblemGenerator {
public:
	virtual Problem* generateProblem() = 0;
	virtual ~ProblemGenerator() = default;
};

/*
 * Mallocs a Problem struct that has the specified number of options.
 * The footnote member, which is does not need to be specified, is set to nullptr, and the struct's optionCount member is set to the specified optionCount.
 *
 * All other members are uninitialized and will need to be initialized by the caller.
 */
struct Problem* genProblem(unsigned optionCount);

template<typename Printable> void prompt(Printable *output, struct Problem *p) {
	*output << p->question << std::endl << p->code << std::endl << std::endl;
	if (p->footnote != nullptr)
		*output << p->footnote << std::endl;
}

void delProblem(struct Problem*);

#endif /* COMMON_H_ */
