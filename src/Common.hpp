/*
 * Common.h
 *
 *  Created on: Jan 30, 2023
 *      Author: Palanath
 */

#ifndef COMMON_H_
#define COMMON_H_

struct Problem {
	unsigned optionCount;
	char *question, *code, *footnote = nullptr, *options[];
};

/*
 * Mallocs a Problem struct that has the specified number of options.
 * The footnote member, which is does not need to be specified, is set to nullptr, and the struct's optionCount member is set to the specified optionCount.
 *
 * All other members are uninitialized and will need to be initialized by the caller.
 */
struct Problem* genProblem(unsigned optionCount);

#endif /* COMMON_H_ */
