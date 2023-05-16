#include <iostream>
#include <future>

const size_t N = 5;
const size_t M = 5;
const size_t NTHREAD = 5;

struct Max_Elem
{
	int count;
	int num;
};

Max_Elem count_max(int** a, int beg, int end)
{
	Max_Elem el;
	el.num = 0;
	el.count = 0;
	for (int i = beg; i < end; i++)
	{
		if (a[i / N][i % N] > el.num)
		{
			el.num = a[i / N][i % N];
			el.count = 1;
		}
		else if (a[i / N][i % N] == el.num)
			el.count++;
	}
	return el;
}

Max_Elem count_max_p(int** a)
{
	std::future<Max_Elem> TH[NTHREAD];
	size_t n = N * M / NTHREAD;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		if (i == NTHREAD - 1)
			TH[i] = std::async(std::launch::async, count_max, a, i * n, N * N);
		else
			TH[i] = std::async(count_max, a, i * n, (i + 1) * n);
	}

	Max_Elem res;
	res.count = 0;
	res.num = 0;

	Max_Elem tmp;

	for (size_t i = 0; i < NTHREAD; i++)
	{
		tmp = TH[i].get();
		if (res.num < tmp.num)
		{
			res.num = tmp.num;
			res.count = tmp.count;
		}
		else if (res.num == tmp.num)
			res.count += tmp.count;
	}

	return res;
}

int main()
{
	int** arr = new int* [N];
	for (int i = 0; i < N; i++)
		arr[i] = new int[M];
	for (int i = 0; i < N * M; i++)
		std::cin >> arr[i / N][i % N];

	std::cout << count_max(arr, 0, N*N).count << "\n" << count_max_p(arr).count;
}
