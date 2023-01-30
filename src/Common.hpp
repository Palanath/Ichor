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

#endif /* COMMON_H_ */
