#include <iostream>
#include <thread>

const size_t N = 5;
const size_t M = 5;
const size_t NTHREAD = 5;


int count_max_np(int** a)
{
	int max_num = a[0][0];
	int count = 0;
	for (int i = 0; i < N * M; i++)
	{
		if (a[i / N][i % N] > max_num)
		{
			max_num = a[i / N][i % N];
			count = 1;
		}
		else if (a[i / N][i % N] == max_num)
			count++;
	}
	return count;
}

void count_max(int ** a, int beg, int end, int &count, int& max_num)
{
	count = 0;
	max_num = 0;
	for (int i = beg; i < end; i++)
	{
		if (a[i / N][i % N] > max_num)
		{
			max_num = a[i / N][i % N];
			count = 1;
		}
		else if (a[i / N][i % N] == max_num)
			count++;
	}
}

int count_max_p(int** a)
{
	std::thread TH[NTHREAD];
	int max_num[NTHREAD];
	int max_count[NTHREAD];
	size_t n = N * M / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		if (i == NTHREAD - 1)
			TH[i] = std::thread(count_max, a, i*n, N*N, std::ref(max_count[i]),std::ref(max_num[i]));
		else
			TH[i] = std::thread(count_max, a, i * n, (i+1)*n, std::ref(max_count[i]), std::ref(max_num[i]));
	}
	for (int i = 0; i < NTHREAD; i++)
		TH[i].join();

	int gl_max_num = max_num[0];
	int gl_count = max_count[0];

	for (size_t i = 1; i < NTHREAD; i++)
	{
		if (gl_max_num < max_num[i])
		{
			gl_max_num = max_num[i];
			gl_count = max_count[i];
		}
		else if (gl_max_num == max_num[i])
			gl_count += max_count[i];
	}

	return gl_count;
}

int main()
{
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
		arr[i] = new int[M];
	for (int i = 0; i < N * M; i++)
		std::cin >> arr[i / N][i % N];
	int res, num;
	count_max(arr, 0, N * N, res, num);
	std::cout << res << "\n" << count_max_p(arr);
}
