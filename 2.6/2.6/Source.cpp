#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <Windows.h>
#include <condition_variable>

using TInfo = int;
const int N = 5;

class ThreadQueue
{
private:
	std::mutex mutex;
	std::queue<TInfo> queue;
public:
	void push(TInfo elem, int ID)
	{
		std::lock_guard<std::mutex> locker(mutex);
		queue.push(elem);
		std::cout << 'P' << ID << " -> " << elem << '\n';
	}
	bool try_pop(TInfo& elem, int ID)
	{
		bool result = false;
		std::lock_guard<std::mutex> locker(mutex);
		if (!queue.empty())
		{
			result = true;
			elem = queue.front();
			queue.pop();
			std::cout << 'C' << ID << " <- " << elem << '\n';
		}
		else
			std::cout << 'C' << ID << " sleep\n";
		return result;
	}
	bool empty()
	{
		return queue.empty();
	}
};
ThreadQueue TQ;
std::mutex mut;
std::condition_variable cv;
volatile long volume_work_producer = 5;
volatile long volume_work_consumer = 5;

void task_producer(int ID)
{
	while (_InterlockedExchangeAdd(&volume_work_producer, -1) > 0)
	{
		TInfo elem = rand() % 10;
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
		TQ.push(elem, ID);
		cv.notify_all();
	}
}
void task_consumer(int ID)
{
	while (_InterlockedExchangeAdd(&volume_work_consumer, -1) > 0)
	{
		TInfo elem;
		std::unique_lock<std::mutex> locker(mut);
		cv.wait_for(locker, std::chrono::seconds(5),
			[]() {return !TQ.empty(); });
		if (TQ.try_pop(elem, ID))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		else
		{
			_InterlockedExchangeAdd(&volume_work_consumer, 1);
		}
	}
}

int main()
{
	srand(GetTickCount());

	std::thread worker[N];
	for (int i = 0; i < N; i++)
	{
		if (i < N / 2)
			worker[i] = std::thread(task_producer, i);
		else
			worker[i] = std::thread(task_consumer, i);
	}

	for (int i = 0; i < 5; i++)
		worker[i].join();

	std::cin.get();
	return 0;
}