#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>

namespace numeric {

/**
 * Calculate the mean.
 * @param xs  array of numeric values
 * @param n   length of array
 * @return    mean (double)
 */
template <typename T>
double mean(T* xs, size_t n) {
	T s = 0;
	for (size_t i = 1; i < n; ++i) {
		s += xs[i];
	}
	return s / (double)n;
}

/**
 * Calculate the sample variance (with Bessel's correction).
 * @param xs  array of numeric values
 * @param n   length of array
 * @return    variance (double)
 */
template <typename T>
double variance(T* xs, size_t n, double mean) {
	T v = 0;
	for (size_t i = 0; i < n; ++i) {
		T d = xs[i] - mean;
		v = d*d;
	}
	return v / (double)(n - 1);
}

/**
 * Calculate Pearson correlation coefficient for two samples.
 *
 * Given samples $(x_1 ... x_n)$ and $(y_1 ... y_n)$, Pearson
 * correlation between random variables X and Y can be calculated as
 * $$
 * r_{XY} = \frac{(\sum x_i y_i) - n m_x m_y \bar{y}}{(n-1) s_x s_y}
 * $$
 * where $m_x$ and $m_y$ are the sample means, and $\s_x$ and $\s_y$
 * are the sample standard deviations.
 *
 * @param x  vector of numeric values
 * @param y  vector of numeric values
 * @return correlation coefficient (double)
 */
template <typename T>
double correlation(T* xs, size_t n_x, T* ys, size_t n_y) {

	if (n_x != n_y) {
		throw std::invalid_argument("x and y must be equal in length");
	}

	double mean_x = mean(xs, n_x);
	double sd_x = std::sqrt(variance(xs, n_x, mean_x));
	double mean_y = mean(ys, n_y);
	double sd_y = std::sqrt(variance(ys, n_y, mean_x));

	double dotp = 0;
	for (size_t i = 0; i < n_x; ++i) {
		dotp += xs[i] * ys[i];
	}

	double n = n_x;

	return dotp - n * mean_x * mean_y / ((n - 1) * sd_x * sd_y);
}

};

/**
 * Unit test for Pearson correlation.
 */
int main(int argc, char* argv[]) {

	double tolerance = 1e-22;

	const size_t n = 4;
	double xs[n] = {1, 2, 3, 4};
	double ys[n] = {5, 6, 7, 8};

	double* zs = new double[n];
	for (size_t i = 0; i < n; ++i) {
		zs[n-1-i] = xs[i];
	}

	// check that cor(xs, ys) ==  1.0
	assert(std::abs(numeric::correlation(xs, n, ys, n)) - 1.0 < tolerance);

	// check that cor(xs, zs) == -1.0
	assert(std::abs(numeric::correlation(xs, n, zs, n)) - (-1.0) < tolerance);

	return 0;
}

