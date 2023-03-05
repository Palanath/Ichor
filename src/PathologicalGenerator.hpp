/*
 * StringstreamGenerator.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Palanath
 */

#ifndef PATHOLOGICALGENERATOR_H_
#define PATHOLOGICALGENERATOR_H_
struct Problem;

namespace PathologicalGenerator {

struct Problem* generateRandomProblem();
struct Problem* pickProblem(unsigned);

}  // namespace PathologicalGenerator

#endif /* PATHOLOGICALGENERATOR_H_ */
