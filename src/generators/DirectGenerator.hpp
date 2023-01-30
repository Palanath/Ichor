/*
 * DirectGenerator.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Palanath
 */

#ifndef DIRECTGENERATOR_H_
#define DIRECTGENERATOR_H_

namespace DirectGenerator {

struct Problem* generateRandomProblem();

char* printProblem(const struct Problem *problem, const int openCodeBlockSize,
		const char *openCodeBlock, const int closeCodeBlockSize,
		const char *closeCodeBlock);

}  // namespace DirectGenerator

#endif /* DIRECTGENERATOR_H_ */
