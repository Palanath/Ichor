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
	char *question, *code, *footnote = nullptr, *options[];
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

/*
 * Generates count distinct random numbers, within the range specified by min and max, and returns a pointer to an array containing the values.
 * Note that the random numbers will be returned in sorted order.
 *
 * If the range max-min is greater than RAND_MAX, then the results of an invocation of this function are undefined.
 */
template<class T> void fillWithDistinctRandoms(unsigned int startpos, unsigned int count, int min,
		int max, T (*arr)[]) {
	for (unsigned int i = 0; i < count; ++i) {
		(*arr)[i] = rand() % (max - min - i) + min;

		bool shifted;
		for (unsigned int j = 0; j < i; ++j)
			if ((*arr)[i] >= (*arr)[j]) {
				++(*arr)[i]; // Shift variable up because it's >= to a value earlier in list.
				shifted = true;
			}

		if (shifted)
			for (unsigned int j = 0; j < i; ++j)
				if ((*arr)[i] == (*arr)[j]) {
					++(*arr)[i];
					j = 0; // Restart and check the array again, as (*arr)[i] might now be conflicting with an earlier value.
				}

	}

}

struct Problem* generateRandomProblem() {

	int optionCount = rand() % 3 + 3;
	Problem *problem = (Problem*) malloc(
			sizeof(struct Problem) + sizeof(char*) * optionCount);
	problem->optionCount = optionCount;

	// Generate randoms.
	short firstVar = rand() % 39 - 7, secondVar = rand() % 39 - 7;
	char firstVarName = rand() % 26 + 'a', secondVarName = rand() % 25 + 'a';
	if (secondVarName >= firstVarName)
		secondVarName++;

	short options[optionCount] { firstVar * 2 + secondVar };
	for (unsigned short i = 1; i < optionCount; ++i) {
		// TODO generate random options and then print them below.
		options[i] = rand() % 39 - 7;
	}

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
