/*
 * Utilities.cpp
 *
 *  Created on: Jan 29, 2023
 *      Author: Palanath
 */

#include "Utilities.hpp"

#include <cstdlib>
#include <cstring>
#include <sstream>
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

