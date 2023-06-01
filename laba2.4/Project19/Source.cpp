#include <iostream>
#include <thread>
#include <fstream>
#include <process.h>
#include <Windows.h>

const size_t N = 5;
const size_t M = 5;
const size_t NTHREAD = 5;


int count_max_np(int** a)
{
	int max_num = a[0][0];
	int count = 0;
	for (int i = 0; i < N * M; i++)
	{
		if (a[i / M][i % M] > max_num)
		{
			max_num = a[i / M][i % M];
			count = 1;
		}
		else if (a[i / M][i % M] == max_num)
			count++;
	}
	return count;
}

volatile long ResourceInUse = FALSE;
void count_max(int** a, int beg, int end, volatile long& count, volatile long& max_num)
{
	int loc_count = 0;
	int loc_max_num = 0;
	for (int i = beg; i < end; i++)
	{
		if (a[i / M][i % M] > max_num)
		{
			max_num = a[i / M][i % M];
			count = 1;
		}
		else if (a[i / M][i % M] == max_num)
			count++;
	}
	while (_InterlockedExchange(&ResourceInUse, TRUE))
		Sleep(0);
	if (loc_max_num > max_num)
	{
		max_num = loc_max_num;
		count = loc_count;
	}
	else if (loc_max_num == max_num)
	{
		max_num += loc_max_num;
	}
	_InterlockedExchange(&ResourceInUse, FALSE);
}

int count_max_p(int** a)
{
	std::thread TH[NTHREAD];
	long max_num;
	long max_count;
	size_t n = N * M / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		if (i == NTHREAD - 1)
			TH[i] = std::thread(count_max, a, i * n, N * N, std::ref(max_count), std::ref(max_num));
		else
			TH[i] = std::thread(count_max, a, i * n, (i + 1) * n, std::ref(max_count), std::ref(max_num));
	}
	for (int i = 0; i < NTHREAD; i++)
		TH[i].join();

	return max_count;
}

int main()
{
	std::fstream file("data.txt");
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
		arr[i] = new int[M];


	for (int i = 0; i < N * M; i++)
		file >> arr[i / M][i % M];
	std::cout << count_max_p(arr) << "\n" << count_max_np(arr);
}
