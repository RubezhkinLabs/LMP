#include <iostream>
#include <omp.h>
#include <fstream>
#include<Windows.h>

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

void count_max(int** a, int beg, int end, int& count, int& max_num)
{
	count = 0;
	max_num = 0;
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
}

int count_max_p(int** arr)
{
	int max_num = 0;
	int max_count = 0;
	omp_lock_t lock;
	omp_init_lock(&lock);
#pragma omp parallel shared(arr)
	{
		int loc_count = 0;
		int loc_num = 0;
#pragma omp for schedule(static, 5)
		for (int i = 0; i < N * M; i++)
		{
			if (arr[i / M][i % M] > loc_num)
			{
				loc_num = arr[i / M][i % M];
				loc_count = 1;
			}
			else if (arr[i / M][i % M] == loc_num)
				loc_count++;
		}
		omp_set_lock(&lock);
		std::cout << loc_num << " " <<loc_count << "\n";
		if (loc_num > max_num)
		{
			max_num = loc_num;
			max_count = loc_count;
		}
		else if (loc_num == max_num)
			max_count += loc_count;
		omp_unset_lock(&lock);
	}
	omp_destroy_lock(&lock);

	return max_count;
}

int main()
{
	srand(GetTickCount());
	std::fstream file("data.txt");
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
		arr[i] = new int[M];


	for (int i = 0; i < N * M; i++)
		arr[i / M][i % M] = rand()%10;
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			std::cout << arr[i][j] << " ";
		std::cout << "\n";
	}

	std::cout << count_max_p(arr) << "\n" << count_max_np(arr);
}
