#include <cstdlib>
#include <cmath>

/** Collection of functions for numeric computation.
 *  Missing values are not supported.
 */
namespace numeric {

	namespace impl {

		template <typename T>
		inline void swap(T& a, T& b) {
			T t = a; a = b; b = t;
		}

		/**
		 * Partition array around pivot indexed by k.
		 * After partitioning, xs is organized as three partitions:
		 * 1. partition with elements less than pivot (in any order)
		 * 2. pivot
		 * 3. partition with elements greater than pivot (in any order)
		 * and the index of the pivot is returned. The pivot is placed in
		 * the same position as it would be if the array was sorted; therefore,
		 * the returned index is the rank of the pivot element.
		 * @param xs  array
		 * @param i   index of pivot
		 * @param l   index of first element in xs
		 * @param r   index of last element in xs
		 * @return    rank of the pivot
		 */
		template <typename T>
		inline size_t partition(T* xs, size_t k, size_t l, size_t r) {
			// convert k from local to global index
			k += l;

			// move pivot to the first position
			swap(xs[l], xs[k]);

			// use first element as pivot
			T p = xs[l];

			// Partition xs into two partitions: less-than-p and greater-than-p.
			// Initially, the pivot is the first element, and
			// all other elements are in the greater-than-p partition, then
			// elements are moved into the less-than-p partition.
			// i and j are global indexes
			// j indexes the first element of the less-than-p partition
			// i indexes the first element of the greater-than-p partition
			size_t i = l + 1;
			for (size_t j = l + 1; j < r; ++j) {
				if (xs[j] < p) {
					// swap element j with the leftmost element in partition greater-than-p
					swap(xs[j], xs[i]);
					// increment i to include the new element in partition less-than-p
					++i;
				}
			}

			// move pivot to middle, swapping with rightmost element in the
			// less-than-p partition
			swap(xs[l], xs[i-1]);

			// convert index of pivot in its new position to local index
			return i - 1 - l;
		}

		/**
		 * Find the ith order statistic in a sub-array (help function).
		 * Side effect: elements in xs will be re-arranged.
		 * @param xs  array
		 * @param l   first element of the subarray
		 * @param r   end of subarray (one past the last element)
		 * @param i   index
		 */
		template <typename T>
		inline T select(T* xs, size_t l, size_t r, size_t i) {
			size_t n = r - l;
			if (n == 1) return xs[l];

			// choose pivot p from xs uniformly at random
			// and partition xs around p
			size_t j = partition(xs, std::rand() % n, l, r);

			if (j == i) {
				// convert index of pivot form local to global index and return element
				return xs[l+j];
			} else if (j > i) {
				// recurse on first half
				return select(xs, l, l+j, i);
			} else {
				// since j < i, recurse on second half
				++j;
				return select(xs, l+j, r, i-j);
			}
		}

		/**
		 * Find the ith order statistic.
		 * If multiple elements tie for the ith order statistic, an arbitrary one
		 * is chosen.
		 * Side effect: elements in xs will be re-arranged.
		 * @param xs  array
		 * @param i   index
		 * @param n   length of array
		 * @return {@code i}th ranked element
		 */
		template <typename T>
		inline T select(T* xs, size_t n, size_t i) {
			return select(xs, 0, n, i);
		}

	};

	/**
	 * Calculate the median.
	 * Side effect: elements in xs will be re-arranged.
	 * @param xs  array
	 * @param n   length of array
	 * @return median (double)
	*/
	template <typename T>
	inline double median(T* xs, size_t n) {
		if (n % 2 == 0) {
			// even number of elements: average middle elements
			T x = impl::select(xs, n, n/2 - 1);
			T y = impl::select(xs, n, n/2);
			return (x + y) / (double)2;
		} else {
			// odd number of elements: return middle element
			return impl::select(xs, n, n/2);
		}
	}

	/**
	 * Calculate the median absolute deviation.
	 * @param xs  array of numeric values
	 * @param n   length of array
	 * @return median absolute deviation (double)
	 */
	template <typename T>
	inline double mad(T* xs, size_t n) {
		double m = median(xs, n);
		double* deviations = new double[n];
		for (size_t i = 0; i < n; ++i) {
			deviations[i] = std::abs(xs[i] - m);
		}
		double y = median(deviations, n);
		delete [] deviations;
		return y;
	}

};
