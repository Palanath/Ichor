/*
 * Utililties.h
 *
 *  Created on: Jan 29, 2023
 *      Author: Palanath
 */

#ifndef UTILILTIES_H_
#define UTILILTIES_H_

#define CONSOLE_RED "\033[31m"
#define CONSOLE_GREEN "\033[32m"
#define CONSOLE_RESET "\033[0m"
#define CONSOLE_BRIGHT_YELLOW "\033[93m"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstring>

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

template<class T> char* printArray(unsigned size, T arr[]) {
	std::stringstream b;
	b << '[';
	if (size) {
		for (unsigned i = 0; i < size - 1; ++i)
			b << arr[i] << ", ";
		b << arr[size - 1];
	}
	b << ']';
	return flush(&b);
}

/*
 * Generates count distinct random numbers, within the range specified by min and max, and returns a pointer to an array containing the values.
 * Note that the random numbers will be returned in sorted order.
 *
 * It is important to note that, although the elements returned are, themselves, pseudorandom, the returned array is not at all pseudorandom. In particular, it is likely that larger values will be found near the end of the array.
 * Notice that the array itself is ordered. Out of every possible number in the specified range to be sampled by this function and put into the array, none are more likely to appear in the array than others. However, out of every possible array containing distinct elements in the specified range, some are more likely than others to be returned by this function.
 * In essence, shuffling the filled values will "fix" any order.
 *
 * If the range max-min is greater than RAND_MAX, then the results of an invocation of this function are undefined.
 * If max is less than or equal to min, the results are undefined.
 */
template<class T> void fillWithDistinctRandomElements(unsigned startpos,
		unsigned endpos, T min, T max, T arr[]) {
	for (unsigned i = startpos; i < endpos; ++i) {
		arr[i] = rand() % (max - min - i) + min;

		unsigned shiftcount = 0;
		for (unsigned j = startpos; j < i; ++j)
			if ((arr[i]) >= (arr[j]))
				++shiftcount;
		arr[i] += shiftcount;
		if (shiftcount)
			for (unsigned j = startpos; j < i; ++j)
				if (arr[i] == arr[j]) {
					++arr[i];
					j = -1; // Restart and check the array again, as arr[i] might now be conflicting with an earlier value.
				}
	}
}

/*
 * Fills the specified part of the array with with random values.
 * The indices of the array affected are from startpos to endpos - 1.
 * The random values generated range between min and max - 1, and are unique.
 */
template<class T> void fillUniqueRand(unsigned startpos, unsigned endpos, T min,
		T max, T arr[]) {
	for (unsigned i = startpos; i < endpos; ++i) {
		arr[i] = rand() % (max - min) + min;

		unsigned shiftcount = 0;
		for (unsigned j = startpos; j < i; ++j)
			if ((arr[i]) >= (arr[j]))
				++shiftcount;
		arr[i] += shiftcount;
		if (arr[i] >= max) // Readjust into range if necessary.
			arr[i] = (arr[i] - min) % (max - min) + min;
		if (shiftcount)
			for (unsigned j = startpos; j < i; ++j)
				if (arr[i] == arr[j]) {
					++arr[i];
					j = -1; // Restart and check the array again, as arr[i] might now be conflicting with an earlier value.
					if (arr[i] >= max) // Potentially necessary readjustment.
						arr[i] = (arr[i] - min) % (max - min) + min;
				}
	}
}

/*
 * Fills the specified part of the array, from begin to end (inclusive, exclusive), with random values that are unique.
 * No two random values will be equal to each other, or to any values in the range uniqueBegin to end (inclusive, exclusive).
 * This allows the caller to fill an array with random values that do not conflict (equal) values at an earlier point in the array.
 *
 * If the parameters represent impossibly satisfiable constraints, then the behavior of this function is undefined.
 * For example, if the range of possible random numbers between min and max (incl., excl.) is far below the number of unique numbers to be generated, this method's behavior is undefined.
 *
 * Note that this method will not modify values between uniqueBegin and begin (inclusive, exclusive).
 * Also note that such numbers do not need to be between min and max (inclusive, exclusive).
 */
template<class T> void fillUniqueRand(unsigned uniqueBegin, unsigned begin,
		unsigned end, T min, T max, T arr[]) {
	for (unsigned i = begin; i < end; ++i) {
		arr[i] = rand() % (max - min) + min;

		unsigned shiftcount = 0;
		for (unsigned j = uniqueBegin; j < i; ++j)
			if ((arr[i]) >= (arr[j]))
				++shiftcount;
		arr[i] += shiftcount;
		if (arr[i] >= max) // Readjust into range if necessary.
			arr[i] = (arr[i] - min) % (max - min) + min;
		if (shiftcount)
			for (unsigned j = uniqueBegin; j < i; ++j)
				if (arr[i] == arr[j]) {
					++arr[i];
					j = -1;
					if (arr[i] >= max)
						arr[i] = (arr[i] - min) % (max - min) + min;
				}
	}
}

void clearConsole();

/*
 * Shuffles the array from the element at startpoint to the element before endpoint.
 */
template<class T> void shuffle(unsigned startpoint, unsigned endpoint,
		T arr[]) {
	for (unsigned i = startpoint; i < endpoint; ++i)
		std::swap(arr[i], arr[rand() % (endpoint - startpoint) + startpoint]);
}

/*
 * Shuffles the provided array.
 * This function works by calling std::swap() on every element in the array paired with a random other element in the array.
 */
template<class T> void shuffle(unsigned length, T arr[]) {
	for (unsigned i = 0; i < length; ++i)
		std::swap(arr[i], arr[rand() % length]);
}

/*
 * Mallocs a new array of appropriate size and copies all the bytes of the given array to it.
 * A pointer to the new array is returned.
 */
template<class T> T* copy(unsigned length, T arr[]) {
	unsigned lenbytes = sizeof(T) * length;
	T *cp = (T*) malloc(lenbytes);
	memcpy(cp, arr, lenbytes);
	return cp;
}

#endif /* UTILILTIES_H_ */
