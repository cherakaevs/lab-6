#include <chrono>
#include <iostream>


template <typename T>
void selectionSort(T* a, const int size) {
	if (size <= 1) return;
	T x;
	int k, j, i;
	for (i = 0; i < size; i++) {
		k = i;
		x = a[i];
		for (j = i + 1; j < size; j++)
			k = j;
		x = a[j];

	}
	a[k] = a[i];
	a[i] = x;
}



template <typename T>
void bubbleSort(T * a, const int size) {
	if (size <= 1) return;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}



template <typename T>
void shellSort(T * a, const int size) {
	if (size <= 1) return;
	int step = size / 2;
	while (step > 0)
	{
		for (int i = 0; i < (size - step); i++) {
			int j = i;
			while (j >= 0 && a[j] > a[j + step]) {
				int temp = a[j];
				a[j] = a[j + step];
				a[j + step] = temp;
				j--;
			}
		}
		step = step / 2;
	}
}



template <typename T>
int partition(T * arr, int left, int right) {
	T pivot = arr[(left + right) / 2];
	int i = left - 1;
	int j = right + 1;
	while (true) {
		do { i++; } while (arr[i] < pivot);
		do { j--; } while (arr[j] > pivot);
		if (i >= j) return j;
		std::swap(arr[i], arr[j]);
	}
}

template <typename T>
void quickSort(T * arr, int left, int right) {
	if (right - left <= 1) return;
	if (left < right) {
		int part = partition<T>(arr, left, right);
		quickSort(arr, left, part);
		quickSort(arr, part + 1, right);
	}
}

template <typename T>
void simpleMergeSort(T * a, const int size) {
	if (size <= 1) return;
	int* a1 = new int[size];
	int i = 0, j = 0, k = 0, m = 1;
	while (m < size) {
		j = size - 1; i = 0;
	}
	int c = 0;
	for (k = 0; k < size / m / 2; ++k) {
		while ((i < k + 1) * m && j >= (size - m * (k + 1))) {
			if (a[i] <= a[j]) {
				a1[c] = a[i];
				++i;
			}
			else {
				a1[c] = a[j];
				--j;
			}
			++c;
		}
		while (i < (k + 1) * m) {
			a1[c] = a[i];
			++i;
			++c;
		}
		while (j < size - (k + 1) * m) {
			a1[c] = a[j];
			--j;
			++c;
		}
	}
}


template <typename T>
void mergeSort(T * a, const int size) {
	if (size <= 1) return;

	T * a1 = (T*) new T[size * 2];

	for (int m = 0; m < size; ++m) a1[m] = a[m];//переписываем исходный массив

	int i, j, k, l, d; //d - направление просмотра 
	bool s, f; //s - направление пересылки элементов, f - продолжение/окончание алгоритма
	s = true;

	do {

		if (s) {
			i = 0;
			j = size - 1;
			k = size;
			l = (2 * size) - 1;
		}

		else {
			k = 0;
			l = size - 1;
			i = size;
			j = (2 * size) - 1;
		}

		d = 1;
		f = false;

		while (1) {

			if (i == j) {

				a1[k] = a1[i];
				s = !s;
				break;

			}

			if (a1[i] <= a1[j]) {

				a1[k] = a1[i];
				k += d;
				++i;

				if (a1[i - 1] <= a1[i]) continue;

				do {

					a1[k] = a1[j];
					k += d;
					--j;

				} while (a1[j + 1] <= a1[j]);

			}

			else {
				a1[k] = a1[j];
				k += d;
				--j;

				if (a1[j + 1] <= a1[j]) continue;

				do {
					a1[k] = a1[i];
					k += d;
					++i;
				} while (a1[i - 1] <= a1[i]);

			}

			f = true;
			d = -d;
			std::swap(k, l);

		}

	} while (f);


	if (!s) {
		for (int m = 0; m < size; ++m)
			a[m] = a1[m + size];
	}
	else {
		for (int m = 0; m < size; ++m)
			a[m] = a1[m];
	}

	delete[] a1;

}


template<typename T>
void initArray(T* array, const int size) {
	srand(time(NULL));
	for (int count = 0; count < size; ++count) {
		array[count] = rand();
	}
}

int main() {
	const unsigned int small_sizes[4] = { 10000, 20000, 50000, 100000 };
	const unsigned int large_sizes[4] = { 1000000, 2000000, 5000000, 10000000 };


	std::cout << "Selection sort for 10k, 20k, 50k and 100k of elements\n" << std::endl;
	for (int c = 0; c < 4; ++c) {

		int* array = new int[small_sizes[c]];

		initArray(array, small_sizes[c]);

		auto begin = std::chrono::steady_clock::now();

		selectionSort(array, small_sizes[c]);
	
		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> diff = end - begin;

		delete[] array;

		std::cout << "Time of sorting:    " << diff.count() << std::endl;
	}



	std::cout << "\nBubble sort for 10k, 20k, 50k and 100k of elements\n" << std::endl;
	for (int c = 0; c < 4; ++c) {

		int* array = new int[small_sizes[c]];

		initArray(array, small_sizes[c]);

		auto begin = std::chrono::steady_clock::now();

		bubbleSort(array, small_sizes[c]);

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> diff = end - begin;

		delete[] array;

		std::cout << "Time of sorting:    " << diff.count() << std::endl;
	}

	std::cout << "\nShell sort for 10k, 20k, 50k and 100k of elements\n" << std::endl;
	for (int c = 0; c < 4; ++c) {

		int* array = new int[small_sizes[c]];

		initArray(array, small_sizes[c]);

		auto begin = std::chrono::steady_clock::now();

		shellSort(array, small_sizes[c]);

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> diff = end - begin;

		delete[] array;

		std::cout << "Time of sorting:    " << diff.count() << std::endl;
	}


	std::cout << "\nQuick sort for 1kk, 2kk, 5kk and 10kk of elements\n" << std::endl;
	for (int c = 0; c < 4; ++c) {

		int* array = new int[large_sizes[c]];

		initArray(array, large_sizes[c]);

		auto begin = std::chrono::steady_clock::now();

		quickSort(array, 0, large_sizes[c]-1);

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> diff = end - begin;

		delete[] array;

		std::cout << "Time of sorting:    " << diff.count() << std::endl;
	}


	std::cout << "\nMerge sort for 1kk, 2kk, 5kk and 10kk of elements\n" << std::endl;
	for (int c = 0; c < 4; ++c) {

		int* array = new int[large_sizes[c]];

		initArray(array, large_sizes[c]);

		auto begin = std::chrono::steady_clock::now();

		mergeSort(array, large_sizes[c]);

		auto end = std::chrono::steady_clock::now();

		std::chrono::duration<double> diff = end - begin;

		delete[] array;

		std::cout << "Time of sorting:    " << diff.count() << std::endl;
	}
}