/*
 * StringstreamGenerator.h
 *
 *  Created on: Jan 27, 2023
 *      Author: Palanath
 */

#ifndef STRINGSTREAMGENERATOR_H_
#define STRINGSTREAMGENERATOR_H_

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

struct String;

struct Problem {
	unsigned optionCount;
	char *question, *code, *footnote, *options[];
};

/*
 * malloc()s a char[] and copies the contents of the specified stream to it, then clears the stream.
 */
char* flushraw(std::stringstream *stream) {
	auto size = stream->tellp();
	char *res = (char*) malloc(size);
	memcpy(res, stream->str().c_str(), size);
	stream->str("");
	return res;
}

/*
 * This function appends the null-terminator to the specified stream, malloc()s a new char[], and copies the contents of the specified stream to it, then clears the stream.
 *
 * This implementation appends std::ends to the stream (via (*stream)<<std::ends;) and then calls and returns the result of flushraw(stream);.
 */
char* flush(std::stringstream *stream) {
	(*stream) << std::ends;
	return flushraw(stream);
}

struct Problem* generateRandomProblem() {
	int options = rand() % 3 + 3;
	Problem *problem = (Problem*) malloc(
			sizeof(struct Problem) + sizeof(char*) * options);
	problem->optionCount = options;

	// Generate randoms.
	int firstVar = rand() % 39 - 7, secondVar = rand() % 39 - 7;
	char firstVarName = rand() % 26 + 'a', secondVarName = rand() % 25 + 'a';
	if (secondVarName >= firstVarName)
		secondVarName++;

	// Calculate sizes.
	std::stringstream q;
	q << "What is the value of the variable, " << secondVarName
			<< ", when the following code finishes executing?";
	problem->question = flush(&q);

	q << "int " << firstVarName << " = " << firstVar << ';' << std::endl;
	q << "int " << secondVarName << " = " << firstVarName << " + " << secondVar
			<< ';' << std::endl;
	q << secondVarName << " += " << firstVarName << "++;" << std::endl;
	problem->code = flush(&q);

	return problem;
}

#endif /* STRINGSTREAMGENERATOR_H_ */
