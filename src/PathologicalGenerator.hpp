/*
 * StringstreamGenerator.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Palanath
 */

#ifndef PATHOLOGICALGENERATOR_H_
#define PATHOLOGICALGENERATOR_H_
struct Problem;

class PathologicalGenerator final: public ProblemGenerator {
	struct Problem* generateProblem();
	struct Problem* pickProblem(unsigned);
};

#endif /* PATHOLOGICALGENERATOR_H_ */
