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

	for (int i = 0; i < 10; ++i) {
		unsigned int size = 25;
		int arr[size];
		fillUniqueRand(0, size, 0, 25, (int (*)[]) &arr);
		std::cout << "List " << i + 1 << ": "
				<< printArray(size, (int (*)[]) &arr) << std::endl;
	}
	return 0;
}

