//============================================================================
// Name        : Ichor.cpp
// Author      : Palanath
// Version     :
// Copyright   : Palanath
// Description : Ichor in C++, Ansi-style
//============================================================================

#include <cstdlib>
#include <ctime>

#include "Utilities.hpp"

int main() {
	srand(time(0));

	for (int i = 0; i < 30; ++i) {
		unsigned int size = 5;
		int arr[5];
		fillWithDistinctRandoms(0, size, 5, 15, (int (*)[]) &arr);
		std::cout << printArray(size, (int (*)[]) &arr);
	}
	return 0;
}

