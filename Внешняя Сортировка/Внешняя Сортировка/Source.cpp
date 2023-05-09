#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <map>

const int N = 9;

struct Elem
{
	int num;
	char ch;
};

struct Sequence
{
	std::fstream file;
	Elem elem;
	bool eof, eor;
	void ReadNext();
	void StartRead(std::string filename);
	void StartWrite(std::string filename);
	void Close();
	void Copy(Sequence& x);
	void CopyRun(Sequence& x);
};

void In(std::string filename, Sequence f[N])
{
	Sequence f0;
	std::string name;
	f0.StartRead(filename);
	for (int i = 0; i < N / 2; i++)
	{
		name = "f" + std::to_string(i) + ".txt";
		f[i].StartWrite(name);
	}
	bool flag;
	int i = 0;
	while (!f0.eof)
	{
		do
		{
			flag = f[i].elem.num < f0.elem.num && ('a' <= f[i].elem.ch && f[i].elem.ch < 'z');
			f[i].CopyRun(f0);
		} while (flag && !f0.eof);
		i = (i + 1) % (N / 2);
	}
	f0.Close();
	for (int i = 0; i < N / 2; i++)
		f[i].Close();
}

void Out(std::string filename, Sequence f[N], int in)
{
	Sequence f0;
	std::string str = "f" + std::to_string(in) + ".txt";
	f[in].StartRead(str);
	if (!f[in].eof)
	{
		f0.StartWrite(filename);
		Elem el;
		while (!f[in].eof)
			f0.CopyRun(f[in]);
		f0.Close();
	}
	f[in].Close();
}

void print(std::string str)
{
	Sequence file;
	file.StartRead(str);
	Elem el;
	while (!file.eof)
	{
		el = file.elem;
		std::cout << el.num << ' ';
		file.ReadNext();
	}
	file.Close();
	std::cout << "\n";
}

void printall()
{
	for (int i = 0; i < N; i++)
	{
		Sequence file;
		std::string name = "f" + std::to_string(i) + ".txt";
		print(name);
	}
	std::cout << "\n";
}


void Sorting(std::string filename)
{
	Sequence f[N];
	In(filename, f);
	int count(0);
	bool step = 0;
	int cnt = N / 2;
	int cnt1;
	bool cont;
	int Min;
	int minIn;
	std::string name;
	int ord;
	int lcf;
	std::map <int, int> Q;
	for (int i = 0; i < N; i++)
		Q[i] = i;
	do
	{
		count = 0;

		for (int i = cnt; i < N; i++)
		{
			name = "f" + std::to_string(Q[i]) + ".txt";
			f[Q[i]].StartWrite(name);
		}
		//printall();
		for (int i = 0; i < cnt; i++)
		{
			name = "f" + std::to_string(Q[i]) + ".txt";
			f[Q[i]].StartRead(name);
		}

		ord = cnt;

		for (int i = 0; i < cnt;)
		{
			if (f[Q[i]].eof)
			{
				std::swap(Q[i], Q[cnt - 1]);
				cnt--;
			}
			else
				i++;
		}

		while (cnt > 0)
		{
			Min = f[Q[0]].elem.num;
			for (int i = 0; i < cnt; i++)
				Min = min(f[Q[i]].elem.num, Min);
			cont = ((Min > f[Q[ord]].elem.num) && ('a' <= f[Q[ord]].elem.ch && f[Q[ord]].elem.ch <= 'z'));

			cnt1 = cnt;

			while (cnt1 > 1)
			{
				minIn = 0;
				for (int i = 0; i < cnt1; i++)
					if (f[Q[minIn]].elem.num > f[Q[i]].elem.num)
						minIn = i;

				f[Q[ord]].Copy(f[Q[minIn]]);
				lcf = Q[ord];

				if (f[Q[minIn]].eor)
				{
					std::swap(Q[minIn], Q[cnt1-1]);
					cnt1--;
				}
			}

			f[Q[ord]].CopyRun(f[Q[0]]);

			for (int i = 0; i < cnt;)
			{
				if (f[Q[i]].eof)
				{
					std::swap(Q[i], Q[cnt - 1]);
					cnt--;
				}
				else
					i++;
			}

			for (int i = 0; i < cnt; i++)
				f[Q[i]].eor = 0;
			count++;
			if (!cont)
				ord = max(N / 2 + step, (ord + 1) % N);
		}


		for (int i = 0; i < N; i++)
			f[i].Close();
		step = !step;
		cnt = N / 2 + step;

		for (int i = 0; i < N / 2; i++)
			std::swap(Q[i], Q[N - i - 1]);
	} while (count > 1);
	Out(filename, f, lcf);
	for (int i = 0; i < N; i++)
	{
		name = "f" + std::to_string(i) + ".txt";
		const char* file = name.c_str();
		remove(file);
	}

}

void Create_File(std::string filename, int cnt)
{
	std::ofstream file(filename, std::ios::binary);
	srand(GetTickCount64());
	Elem el;
	for (int i = 0; i < cnt; ++i)
	{
		el.num = rand() % 100;
		el.ch = char('a' + rand() % 26);
		file.write((char*)&el, sizeof(el));
	}
	file.close();

}

bool  CheckFile(std::string filename)
{
	std::ifstream file(filename, std::ios::binary);
	Elem x, y;
	bool check(true);
	file.read((char*)&y, sizeof(y));
	while (!file.eof() && check)
	{
		x = y;
		file.read((char*)&y, sizeof(y));
		check = x.num <= y.num;
	}
	file.close();
	return check;
}

int main()
{
	Create_File("data.txt", 1000);

	print("data.txt");
	std::cout << "\n";
	Sorting("data.txt");

	if (CheckFile("data.txt"))
		std::cout << "File is ordered";
	else
		std::cout << "Not ordered";
	std::cout << "\n";

	std::ifstream file("data.txt", std::ios::binary);
	Elem el;
	print("data.txt");

	std::cin.get();
	return 0;
}

void Sequence::ReadNext()
{
	if (!file.read((char*)&elem, sizeof(elem)))
		eof = true;
	else
		eof = false;
}

void Sequence::StartRead(std::string filename)
{
	file.open(filename, std::ios::in | std::ios::binary);
	ReadNext();
	eor = eof;
}

void Sequence::StartWrite(std::string filename)
{
	file.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);
}

void Sequence::Close()
{
	file.close();
}

void Sequence::Copy(Sequence& x)
{
	elem = x.elem;
	file.write((char*)&elem, sizeof(elem));
	x.ReadNext();
	x.eor = x.eof || (x.elem.num < elem.num);
}

void Sequence::CopyRun(Sequence& x)
{
	do
	{
		Copy(x);
	} while (!x.eor);
}
