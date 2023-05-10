#include <iostream>
#include <Windows.h>
#include <process.h>

const size_t N = 5;
const size_t M = 5;
const size_t NTHREAD = 3;

using INFORM = struct elem
{
	int** a;
	size_t beg, end;
	int max_num = 0;
	int count = 0;
};

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

unsigned __stdcall count_max(void* a)
{
	INFORM* inform = (INFORM*)a;
	inform->count = 0;
	inform->max_num = 0;
	for (int i = inform->beg; i < inform->end; i++)
	{
		if (inform->a[i / N][i % N] > inform->max_num)
		{
			inform->max_num = inform->a[i / N][i % N];
			inform->count = 1;
		}
		else if (inform->a[i / N][i % N] == inform->max_num)
			inform->count++;
	}
	_endthreadex(0);
	return 0;
}

int count_max_p(int** a)
{
	HANDLE TH[NTHREAD];
	unsigned THID[NTHREAD];
	INFORM inform[NTHREAD];
	size_t n = N * M / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		inform[i].a = a;
		inform[i].beg = i * n;
		inform[i].count = 0;
		inform[i].max_num = 0;
		if (i == NTHREAD - 1)
			inform[i].end = N * M;
		else
			inform[i].end = (i + 1) * n;
		TH[i] = (HANDLE)_beginthreadex(nullptr, 0, &count_max, &inform[i], 0, nullptr);
	}
	WaitForMultipleObjects(NTHREAD, TH, true, INFINITE);

	int gl_max_num = inform[0].max_num;
	int gl_count = inform[0].count;

	for (size_t i = 1; i < NTHREAD; i++)
	{
		if (gl_max_num < inform[i].max_num)
		{
			gl_max_num = inform[i].max_num;
			gl_count = inform[i].count;
		}
		else if (gl_max_num == inform[i].max_num)
			gl_count += inform[i].count;
	}

	for (size_t i = 0; i < NTHREAD; i++)
		CloseHandle(TH[i]);

	return gl_count;
}

int main()
{
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
		arr[i] = new int[M];
	for (int i = 0; i < N * M; i++)
		std::cin >> arr[i / N][i % N];
	std::cout << count_max_np(arr) << "\n" << count_max_p(arr);
}
