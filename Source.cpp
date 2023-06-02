#include<iostream>

const int N = 10;
const int M = 10;
int arr[N][M];
int Max = -1;
int Min = -1;
int res = 0;

void task(int n = 0, int m = 0)
{
	res += arr[n][m];
	if (n < N - 1)
		task(n + 1, m);
	if (m < M - 1)
		task(n, m + 1);
	if (n == N - 1 && m == M - 1)
	{
		if (Max == -1 || Max < res)
			Max = res;
		if (Min == -1 || Min > res)
			Min = res;
	}
	res -= arr[n][m];
}

void main()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			std::cin >> arr[i][j];

	task();
	std::cout << Max << " " << Min;
}