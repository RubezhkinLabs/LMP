#include <iostream>
#include <fstream>
#include <string>

using TInfo = char;
struct NODE
{
	TInfo info;
	NODE* left, * right;
	int count = 1;
	NODE() {}
	NODE(TInfo info, NODE* left = nullptr, NODE *right = nullptr): info(info), left(left), right(right) {}
	~NODE()
	{
		left = nullptr;
		right = nullptr;
	}
};

using Tree = NODE*;

void Clear(Tree& t)
{
	if (t)
	{
		Clear(t->left);
		Clear(t->right);
		delete t;
		t = nullptr;
	}
}

void Print(Tree t, int level=0)
{
	if (t)
	{
		Print(t->right, level + 1);
		for (int i = 0; i < level; i++)
			std::cout << ' ';
		std::cout << t->info << '\n';
		Print(t->left, level + 1);
	}
}


using TElem = Tree;

Tree Build_Formula(std::ifstream& file)
{
	char c = file.get();
	Tree root = new NODE(' ');
	if (c >= '0' && c <= '9')
		root->info = c;
	else
	{
		root->left = Build_Formula(file);
		root->info = file.get();
		root->right = Build_Formula(file);
		c = file.get();
	}
	return root;
}

void tree_formula(Tree root)
{
	if (root)
	{
		if (!(root->info >= '0' && root->info <= '9'))
			std::cout << '(';
		tree_formula(root->left);
		std::cout << root->info;
		tree_formula(root->right);
		if (!(root->info >= '0' && root->info <= '9'))
			std::cout << ')';
	}
}

using SInfo = Tree;

class stack
{
private:
	SInfo* elements;
	int size;
	int top;
public:
	stack();
	~stack();
	bool empty();
	bool full();
	void resize(int n_size);
	int get_alloc_size();
	void push(SInfo elem);
	SInfo pop();
	SInfo Top();
	void View();
};

stack::stack()
{
	size = 1;
	elements = new SInfo[size];
	top = -1;
}

stack::~stack()
{
	delete[] elements;
}

bool stack::empty()
{
	return top == -1;
}

bool stack::full()
{
	return top == size - 1;
}

void stack::resize(int n_size)
{
	if (n_size > size)
	{
		SInfo* temp = new SInfo[n_size];
		for (int i = 0; i <= top; i++)
			temp[i] = elements[i];
		size = n_size;
		delete[] elements;
		elements = temp;
	}
}

int stack::get_alloc_size()
{
	return size;
}

void stack::push(SInfo elem)
{
	if (size == top + 1)
		resize(2 * size);
	elements[++top] = elem;
}

SInfo stack::pop()
{
	SInfo elem = elements[top--];
	return elem;
}

SInfo stack::Top()
{
	return elements[top];
}

void stack::View()
{
	for (int i = top; i >= 0; i--)
		std::cout << elements[i] << ' ';
	std::cout << std::endl;
}


bool check(Tree r1, Tree r2)
{
	if (r1->right && r1->left && r2->right&&r2->left)
	{
		return (r1->info == r2->info) && check(r1->right, r2->right) && check(r1->left, r2->left);
	}
	else
	{
		if (r1->info == r2->info)
		{
			if ((!r1->right && !r2->right))
				if ((!r1->left && !r2->left) || (r1->left && r2->left && ((r1->left->info) == (r2->left->info))))
					return true;
		}
		else if ((!r1->left && !r2->left))
			if (r1->right && r2->right && ((r1->right->info) == (r2->right->info)))
				return true;
		return false;
	}
}

void task1(Tree root)
{
	if (root->right && root->left)
	{
		task1(root->right);
		task1(root->left);
		if(root->info=='+'||root->info=='-')
			if (root->left->info == '*' && root->right->info == '*')
			{
				if (check(root->left->left, root->right->left))
				{
					std::swap(root->right->right, root->right->left);
					std::swap(root->left->right, root->left->left);
				}
				else if (check(root->left->left, root->right->right))
				{
					std::swap(root->left->right, root->left->left);
				}
				else if (check(root->left->right, root->right->left))
				{
					std::swap(root->right->right, root->right->left);
				}
				if (check(root->right->right, root->left->right))
				{
					std::swap(root->left->info, root->info);
					Clear(root->left->right);
					root->left->right = root->right->left;
					Tree ptr = root->right->right;
					root->right->left = nullptr;
					root->right->right = nullptr;
					Clear(root->right);
					root->right = ptr;
				}
			}
	}
}

void task2(Tree root)
{
	Tree src = root;
	stack st;
	stack oper;

	while (src)
	{
		if (src->left)
		{
			if (src->right)
				st.push(src->right);
			if (src->info == '+' || src->info == '-')
				oper.push(src);
			src = src->left;
		}
		else if (src->right)
		{
			if (src->info == '+' || src->info == '-')
				oper.push(src);
			src = src->right;
		}
		else if (st.empty())
			src = nullptr;
		else
			src = st.pop();
	}
	while (!oper.empty())
	{
		src = oper.Top();
		if (src->left->info == '*' && src->right->info == '*')
		{
			if (check(root->left->left, root->right->left))
			{
				std::swap(root->right->right, root->right->left);
				std::swap(root->left->right, root->left->left);
			}
			else if (check(root->left->left, root->right->right))
			{
				std::swap(root->left->right, root->left->left);
			}
			else if (check(root->left->right, root->right->left))
			{
				std::swap(root->right->right, root->right->left);
			}
			if (check(root->right->right, root->left->right))
			{
				std::swap(root->left->info, root->info);
				Clear(root->left->right);
				root->left->right = root->right->left;
				Tree ptr = root->right->right;
				root->right->left = nullptr;
				root->right->right = nullptr;
				Clear(root->right);
				root->right = ptr;
			}
		}
		oper.pop();
	}
}

void main()
{
	std::ifstream file("form.txt");
	Tree root;
	root = Build_Formula(file);

	tree_formula(root);
	std::cout << '\n';
	task2(root);
	tree_formula (root);

	Clear(root);
	std::cin.get();

}