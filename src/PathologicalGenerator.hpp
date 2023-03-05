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
	struct Problem* genMathProblem1();
	struct Problem* genCharLiteralProblem1();
	struct Problem* genCommaOpTrick1();
	struct Problem* genFunctionCallProblem1();
	struct Problem* genFunctionCallProblem2();
	struct Problem* genLoopProblem1();
	struct Problem* genComparisonOperatorPrecedenceProblem1();
	struct Problem* genSwitchProblem1();
	struct Problem* genIntegralPromotionOfBoolProblem1();
	struct Problem* genCommaOperatorProblem1();
	struct Problem* genStringLiteralConcatenationProblem1();
	struct Problem* genCommaOperatorProblem2();
	struct Problem* genOperatorSyntaxAmbiguityProblem1();
	struct Problem* genCharAdditionProblem1();
	struct Problem* genReturnByReferenceProblem1();
	const char* pickPrimitiveType(unsigned type);
public:
	struct Problem* generateProblem() override;
	struct Problem* pickProblem(unsigned);
};

#endif /* PATHOLOGICALGENERATOR_H_ */
