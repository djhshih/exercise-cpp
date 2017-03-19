#include <vector>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <iostream>

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
	for (size_t i = 0; i < n; ++i) {
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
		v += d*d;
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
	double sd_y = std::sqrt(variance(ys, n_y, mean_y));

	double dotp = 0;
	for (size_t i = 0; i < n_x; ++i) {
		dotp += xs[i] * ys[i];
	}
        
	double n = n_x;

	return (dotp - n * mean_x * mean_y) / ((n - 1) * sd_x * sd_y);
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
        
        //manually compute mean, variance and pearson correlations for xs 
        double mean_test = numeric::mean(xs, n);
        double v_test = 0;
        for (size_t i = 0; i < n; ++i) {
		double d_test = xs[i] - mean_test;
		v_test += d_test*d_test;
	}
	
	double variance_test = v_test / (double)(n - 1);
	double MANUAL_MEAN_XS = (double)(xs[0]+xs[1]+xs[2]+xs[3]) / n;
	double MANUAL_MEAN_YS = (double) (ys[0]+ys[1]+ys[2]+ys[3]) / n;
	
        //unit test for mean
        // computed mean value for ys =  6.5, computed mean value for xs = 2.5   
        assert(numeric::mean(xs, n) == MANUAL_MEAN_XS);
        
        //unit test for variance
        assert(numeric::variance(xs, n, mean_test) == variance_test);
         
	// check that cor(xs, ys) ==  1.0
        assert(std::abs(numeric::correlation(xs, n, ys, n)) - 1.0 < tolerance);

	// check that cor(xs, zs) == -1.0
	assert(numeric::correlation(xs, n, zs, n) - (-1.0) < tolerance);

	return 0;
}

