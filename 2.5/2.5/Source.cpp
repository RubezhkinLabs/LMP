#include<iostream>
#include<thread>
#include<mutex>
#include<queue>
#include<fstream>

struct port
{
	int* start, * end;
};
using TInfo = port;

struct Res
{
	int Num;
	int Count;
};

class MyQueue
{
private:
	std::queue<TInfo> queue;
	std::mutex mutex;
public:
	void push(TInfo elem)
	{
		queue.push(elem);
	}

	bool try_pop(TInfo& elem)
	{
		bool result = false;
		std::lock_guard<std::mutex> locker(mutex);
		if (!queue.empty())
		{
			result = true;
			elem = queue.front();
			queue.pop();
		}

		return result;
	}

	bool empty()
	{
		return queue.empty();
	}
};

const int BLOCK = 10;
const int THREAD = 4;
const int N = 5;
const int M = 5;
MyQueue myQueue;

std::atomic<int> global_count;
std::atomic<int> global_num;

Res task(TInfo chank)
{
	Res res;
	res.Num = *chank.start;
	res.Count = 0;
	for (int* p = chank.start; p != chank.end; ++p)
	{
		if (*p > res.Num)
		{
			res.Num = *p;
			res.Count = 1;
		}
		else if (*p == res.Num)
			res.Count++;
	}
	return res;
}

void Fill(int a[N][M])
{
	for (int i = 0; i < N*M; i++)
	{
		a[i/M][i%M] = rand() % 5;
	}
}

std::mutex mut;

void task_consumer()
{
	port port;
	Res loc_res;
	while (!myQueue.empty())
	{
		if (myQueue.try_pop(port))
		{
			loc_res = task(port);
			mut.lock();
			if (global_num < loc_res.Num)
			{
				global_num = loc_res.Num;
				global_count = loc_res.Count;
			}
			else if (global_num == loc_res.Num)
				global_count += loc_res.Count;
			mut.unlock();
		}
	}
}

int main()
{
	std::thread worker[N];
	int arr[N][M];
	//Fill(arr);
	std::fstream file("data.txt");
	for (int i = 0; i < N * M; i++)
		file >> arr[i / M][i % M];
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			std::cout << arr[i][j] << " ";
		std::cout << "\n";
	}
	for (int i = 0; i < N*M / BLOCK; i++)
	{
		port port;
		port.start = *arr+i * BLOCK;
		port.end = port.start + BLOCK;
		myQueue.push(port);
	}

	port port;
	port.start = *arr + N * M - N * M % BLOCK;
	port.end = port.start + N * M % BLOCK;
	myQueue.push(port);

	for (int i = 0; i < N; i++)
	{
		worker[i] = std::thread(task_consumer);
	}

	for (int i = 0; i < N; i++)
	{
		worker[i].join();
	}

	port.start = *arr;
	port.end = *arr + N * M;
	std::cout << task(port).Count << '\n';

	std::cout<< global_count << '\n';

	std::cin.get();
}