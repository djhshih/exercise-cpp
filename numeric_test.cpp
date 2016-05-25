#include <cassert>
#include <iostream>
#include <cmath>
using namespace std;

#include "numeric.hpp"
using namespace numeric;

int main(int argc, char* argv[]) {

	const double tol = 1e-22;

	const size_t n = 5;
	int x[n] = {6, 1, 2, 5, 9};

	assert((int)median(x, n) == 5);
	assert((int)mad(x, n) == 3);

	const size_t m = 4;
	int z[m] = {2, 1, 8, 6};
	//int z[m] = {3, 2, 2, 4};

	assert(abs(median(z, m) - 4.0) < tol);
	assert(abs(mad(z, m) - 2.5) < tol);

	return 0;
}
