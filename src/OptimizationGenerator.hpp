/*
 * OptimizationGenerator.hpp
 *
 *  Created on: Mar 4, 2023
 *      Author: Palanath
 */

#ifndef OPTIMIZATIONGENERATOR_HPP_
#define OPTIMIZATIONGENERATOR_HPP_

#include "Common.hpp"

class OptimizationGenerator final : public ProblemGenerator {
	struct Problem* genForLoopProblem1();
	struct Problem* genUnnecessaryCodeProblem1();
public:
	struct Problem* generateProblem() override;
};

#endif /* OPTIMIZATIONGENERATOR_HPP_ */
