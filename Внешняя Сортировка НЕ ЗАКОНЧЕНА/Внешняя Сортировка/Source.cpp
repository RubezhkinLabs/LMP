// проанализируй этот код
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <string>
#include <map>

struct Elem
{
	int num;
	char ch;
};

struct Sequence
{
	std::fstream file;
	Elem elem;
	bool eof, eor;//конец ли чтения, конец ли последовательности
	void ReadNext();
	void StartRead(std::string filename);//подготовить к чтению, записи
	void StartWrite(std::string filename);
	//	void Open(std::string filename);
	void Close();
	void Copy(Sequence& x);//копирование из икс в нашу структуру
	void CopyRun(Sequence& x);//
	//предусмотеть печать фрагмента файла(с 10 по 15 например)
	//void print file(left, right);//отсортированного..?

};

//естественное, многопутевое, несбалансированное, однофазное равномерное

void In(std::string filename, Sequence f[5])
{
	Sequence f0;
	f0.StartRead(filename);
	f[0].StartWrite("f0.txt");
	f[1].StartWrite("f1.txt");
	while (!f0.eof)
	{
		do
		{
			f[0].CopyRun(f0);
		} while (f[0].elem.num < f0.elem.num);
		if (!f0.eof)
			do
			{
				f[1].CopyRun(f0);
			} while (f[1].elem.num < f0.elem.num);
	}
	f0.Close();
	f[0].Close();
	f[1].Close();
}

void Out(std::string filename, Sequence f[5], int in)
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
	std::ifstream f(str, std::ios::binary);
	Elem el;
	while (!f.read((char*)&el, sizeof(el)).eof())
	{
		std::cout << el.num << ' ' << el.ch << " ";
	}
	std::cout << "\n";
}

void printall()
{
	for (int i = 0; i < 5; i++)
	{
		std::string name = "f" + std::to_string(i) + ".txt";
		std::fstream file(name, std::ios::binary);
		Elem el;
		while (file.read((char*)&el, sizeof(el)))
		{
			std::cout << el.num << ' ' << el.ch << " ";
		}
		std::cout << "\n";
	}
}


void Sorting(std::string filename)
{
	Sequence f[5];
	In(filename, f);
	int count(0);
	bool cnt = 0;
	bool cnt1 = 0;
	bool cont;
	int Min;
	std::string name;
	int ord;
	int lcf;
	std::map <int, int> Q;
	for (int i = 0; i < 5; i++)
		Q[i] = i;
	do
	{
		count = 0;
		printall();
		for (int i = 0; i < 2 + cnt; i++)
		{
			name = "f" + std::to_string(Q[i]) + ".txt";
			f[Q[i]].StartRead(name);
		}
		for (int i = 2 + cnt; i < 5; i++)
		{
			name = "f" + std::to_string(Q[i]) + ".txt";
			f[Q[i]].StartWrite(name);
		}
		ord = 2 + cnt;

		while (!f[Q[0]].eof && !f[Q[1]].eof && (!cnt1 || !f[Q[2]].eof))
		{
			Min = min(f[Q[0]].elem.num, f[Q[1]].elem.num);
			if (cnt1)
				Min = min(Min, f[Q[2]].elem.num);
			cont = ((Min < f[Q[ord]].elem.num) && (f[Q[ord]].elem.num != NULL));

			if (!f[Q[0]].eor || !f[Q[1]].eor || !f[Q[2]].eor)
				lcf = Q[ord];
			if (cnt1)
			{
				while (!f[Q[0]].eor && !f[Q[1]].eor && !f[Q[2]].eor)
				{
					if (f[Q[0]].elem.num <= f[Q[1]].elem.num && (!cnt || f[Q[0]].elem.num <= f[Q[2]].elem.num))
						f[Q[ord]].Copy(f[Q[0]]);
					else if (f[Q[1]].elem.num < f[Q[0]].elem.num && (!cnt || f[Q[1]].elem.num <= f[Q[2]].elem.num))
						f[Q[ord]].Copy(f[Q[1]]);
					else if (cnt)
						f[Q[ord]].Copy(f[Q[2]]);
				}

				if (f[Q[0]].eor)
					std::swap(Q[0], Q[2]);
				if (f[Q[1]].eor)
					std::swap(Q[1], Q[2]);
			}

			while (!f[Q[0]].eor && !f[Q[1]].eor)
			{
				if (f[Q[0]].elem.num < f[Q[1]].elem.num)
					f[Q[ord]].Copy(f[Q[0]]);
				else
					f[Q[ord]].Copy(f[Q[1]]);
			}

			if (f[Q[0]].eor)
				std::swap(Q[0], Q[1]);
			f[Q[ord]].CopyRun(f[Q[0]]);

			Min = min(f[Q[0]].elem.num, f[Q[1]].elem.num);
			if (cnt1)
				Min = min(Min, f[Q[2]].elem.num);

			if (!cont)
				ord = max(2 + cnt, (ord + 1) % 5);


			if (cnt1 && (f[Q[0]].eof || f[Q[1]].eof || f[Q[2]].eof))
			{
				if (f[Q[0]].eof)
					std::swap(Q[0], Q[2]);
				else if (f[Q[1]].eof)
					std::swap(Q[1], Q[2]);
				cnt1 = false;
			}

			f[Q[0]].eor = f[Q[0]].eof;
			f[Q[1]].eor = f[Q[1]].eof;
			if (cnt1)
				f[Q[2]].eor = f[Q[2]].eof;
			count++;
		}

		if (f[Q[0]].eof)
			std::swap(Q[0], Q[1]);

		while (!f[Q[0]].eof)
		{
			f[Q[ord]].CopyRun(f[Q[0]]);
			lcf = Q[ord];
			ord = max(2 + cnt, (ord + 1) % 5);
			count++;
		}


		for (int i = 0; i < 5; i++)
			f[i].Close();

		cnt = !cnt;
		cnt1 = cnt;
		std::swap(Q[0], Q[4]);
		std::swap(Q[1], Q[3]);
	} while (count > 1);
	for (int in = 0; in < 2 + !cnt; in++)
		Out(filename, f, Q[in]);

}

void Create_File(std::string filename, int cnt)
{
	std::ofstream file(filename, std::ios::binary);
	std::ofstream orig("or.txt");
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
	Create_File("data.txt", 10);


	Sorting("data.txt");

	if (CheckFile("data.txt"))
		std::cout << "File is ordered";
	else
		std::cout << "Not ordered";
	std::cout << "\n";

	std::ifstream file("data.txt", std::ios::binary);
	Elem el;
	while (!file.read((char*)&el, sizeof(el)).eof())
	{
		std::cout << el.num << ' ' << el.ch << "\n";
	}
	printall();

	std::cin.get();
	return 0;
}

void Sequence::ReadNext()
{
	//eof = file.eof();
	//if (!eof)
	//	file.read((char*)&elem, sizeof(elem));
	//else
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
	file.write((char*)&x.elem, sizeof(x.elem));
	x.ReadNext();
	x.eor = x.eof || (x.elem.num < elem.num);//проверка, что текущее считанное колво элем не больше чем
}

void Sequence::CopyRun(Sequence& x)
{
	do
	{
		Copy(x);
	} while (!x.eor);
}
