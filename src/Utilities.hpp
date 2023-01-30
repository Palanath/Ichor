/*
 * Utililties.h
 *
 *  Created on: Jan 29, 2023
 *      Author: Palanath
 */

#ifndef UTILILTIES_H_
#define UTILILTIES_H_

#include <cstdlib>
#include <iostream>
#include <sstream>

struct Problem;

/*
 * This function appends the null-terminator to the specified stream, malloc()s a new char[], and copies the contents of the specified stream to it, then clears the stream.
 *
 * This implementation appends std::ends to the stream (via (*stream)<<std::ends;) and then calls and returns the result of flushraw(stream);.
 */
char* flush(std::stringstream *stream);
/*
 * malloc()s a char[] and copies the contents of the specified stream to it, then clears the stream.
 */
char* flushraw(std::stringstream *stream);

template<class T> char* printArray(unsigned size, T (*arr)[]) {
	std::stringstream b;
	b << '[';
	if (size) {
		for (unsigned i = 0; i < size - 1; ++i)
			b << (*arr)[i] << ", ";
		b << (*arr)[size - 1];
	}
	b << ']' << std::endl;
	return flush(&b);
}

/*
 * Generates count distinct random numbers, within the range specified by min and max, and returns a pointer to an array containing the values.
 * Note that the random numbers will be returned in sorted order.
 *
 * If the range max-min is greater than RAND_MAX, then the results of an invocation of this function are undefined.
 */
template<class T> void fillWithDistinctRandoms(unsigned startpos,
		unsigned count, int min, int max, T (*arr)[]) {
	for (unsigned int i = 0; i < count; ++i) {
		(*arr)[i] = rand() % (max - min - i) + min;

		bool shifted;
		for (unsigned int j = 0; j < i; ++j)
			if ((*arr)[j] >= (*arr)[i]) {
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

#endif /* UTILILTIES_H_ */
