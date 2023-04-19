//54 условие в image.png
#include <iostream>

const int n = 3;

int res = -1;
int b_res[n];
int c_res[n];

int b_tmp[n];
int c_tmp[n];

int b_per[n];
bool us[n];

void print(int arr[n])
{
	for (int i = 0; i < n; i++)
		std::cout << arr[i] << " ";
	std::cout << "\n";
}

void cmp()
{
	int k = 0;
	for (int i = 0; i < n; i++)
		k += b_per[i] * c_tmp[i];
	if (res == -1 || abs(k) < res)
	{
		res = abs(k);
		for (int i = 0; i < n; i++)
		{
			b_res[i] = b_per[i];
			c_res[i] = c_tmp[i];
		}
	}
}

void per(int lvl = 0)
{
	if (lvl == n)
		cmp();
	else
		for (int i = 0; i < n; i++)
			if (!us[i])
			{
				us[i] = true;
				b_per[lvl] = b_tmp[i];
				per(lvl + 1);
				us[i] = 0;
				b_per[lvl] = 0;
			}
}

void task(int* a, int b = 0, int c = 0)
{
	if (b < n)
	{
		b_tmp[b] = a[b + c];
		task(a, b + 1, c);
		b_tmp[b] = 0;
	}
	if (c < n && b != 0)
	{
		c_tmp[c] = a[b + c];
		task(a, b, c + 1);
		c_tmp[c] = 0;
	}
	if (b == n && c == n)
	{
		per();
	}
}


void main()
{
	int* a = new int[n * 2];
	for (int i = 0; i < n * 2; i++)
		std::cin >> a[i];
	//for (int i = 0; i < n * 2; i++)
	//{
	//	int num = std::rand() % 20 -10;
	//	a[i] = num;
	//	std::cout << num << " ";
	//}
	std::cout << "\n";
	task(a);
	std::cout << res << "\n";
	print(b_res);
	print(c_res);
}
