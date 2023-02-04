/*
 * StringstreamGenerator.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Palanath
 */

#ifndef STRINGSTREAMGENERATOR_H_
#define STRINGSTREAMGENERATOR_H_
struct Problem;

namespace StringGenerator {

struct Problem* generateRandomProblem();
struct Problem* pickProblem(unsigned);

}  // namespace StringstreamGenerator

#endif /* STRINGSTREAMGENERATOR_H_ */
