#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
struct NODE
{
	NODE* ptrs[26];
	bool eow = false;
	NODE()
	{
		for (int i = 0; i < 26; ++i)
			ptrs[i] = nullptr;
	}
};
using TrieTree = NODE*;
void init(TrieTree& root)
{
	root = nullptr;
}
bool empty(TrieTree root)
{
	return root == nullptr;
}

void add(TrieTree& t, const std::string word, size_t i)
{
	if (!t)
	{
		t = new NODE;

	}
	if ((word.length()) - 1 < i)
		t->eow = true;
	else
		add(t->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptr_empty(TrieTree t)
{
	bool res = true;
	size_t i = 0;
	while (i < 26 && res)
		if (!t->ptrs[i])
			++i;
		else
			res = false;
	return res;
}

void del(TrieTree& t, const std::string word, size_t i)
{
	if (t)
		if (i <= word.length() - 1)
			del(t->ptrs[word[i] - 'a'], word, i + 1);
		else
		{
			t->eow = false;
			if (all_ptr_empty(t))
			{
				delete t;
				t = nullptr;
			}
		}
}

void print(TrieTree t, std::string word)//тут есть механизм обхода дерева
{
	if (t->eow)
	{
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			print(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

void clear(TrieTree& t)
{
	for (size_t i = 0; i < 26; ++i)

		if (t->ptrs[i])
			clear(t->ptrs[i]);
	delete t;
	t = nullptr;
}

void task(TrieTree& t, std::string d, std::string word)
{
	bool flag = 1;
	int i = 0;
	while (i < 26 && flag)
	{
		if (word.find(d) != -1)
		{
			clear(t);
			flag = false;
		}
		else if (t->ptrs[i])
			task(t->ptrs[i], d, word + char(i + 'a'));
		i++;
	}
	if (!empty(t) &&  all_ptr_empty(t) && !t->eow)
		clear(t);
}

void printall(TrieTree t, std::string word)
{
	bool flag = 1;
	for (int i = 0; i < 26; i++)
		if (t->ptrs[i])
			flag = 0;
	if (flag)
	{
		std::cout << word << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			printall(t->ptrs[i], word + char(i + 'a'));
		}
	}
}

int main()
{
	bool flag = 1;
	while (flag)
	{
		std::ifstream file("D.txt");
		TrieTree root;
		init(root);
		std::string word;
		while (std::getline(file, word))
		{
			if (word.length())
				add(root, word, 0);
		}
		file.close();
		print(root, "");

		std::string del;
		std::cout << "\nenter word for del: ";
		std::getline(std::cin, del);
		std::cout << "\n";
		task(root, del, "");

		print(root, "");
		//std::cout << "\n";
		//print(root, "");
		clear(root);
		std::cout << "Continue?(1-Y,0-N)\n";
		std::cin >> flag;
		std::cin.ignore();
	}
}