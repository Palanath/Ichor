/*
 * Utilities.cpp
 *
 *  Created on: Jan 29, 2023
 *      Author: Palanath
 */

#include "Utilities.hpp"

#include <string>


char* flushraw(std::stringstream *stream) {
	auto size = stream->tellp();
	char *res = (char*) malloc(size);
	memcpy(res, stream->str().c_str(), size);
	stream->str("");
	return res;
}

char* flush(std::stringstream *stream) {
	(*stream) << std::ends;
	return flushraw(stream);
}

void clearConsole() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	system("cls");
#else
	system("clear");
#endif
}
