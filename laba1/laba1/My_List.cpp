
#include "My_List.h"
#include "My_List.h"
#include <functional>

LIST::~LIST()
{
//	std::cout << "destr\n";
	while (!empty())
	{
		del_from_head();
	}
	
	delete head;
}

bool LIST::empty()
{
	return !head->next;
}

void LIST::add_to_head(TInfo elem)
{
	add_by_pointer(head->next, elem);
	if (head == tail)
		tail = tail->next;
	++size;
}

void LIST::add_to_tail(TInfo elem)
{
	add_by_pointer(tail->next, elem);
	tail = tail->next;
}

void LIST::add_after(ptrNODE ptr, TInfo elem)
{
	if (ptr)
	{
		add_by_pointer(ptr->next, elem);
		if (ptr == tail)
			tail = tail->next;
	}
}

void LIST::del_from_head()
{
	if (head->next)
	{
		del_by_pointer(head->next);
		if (!head->next)
			tail = head;
		--size;
	}
}

void LIST::del_after(ptrNODE ptr)
{
	if (ptr && ptr->next)
	{
		if (ptr->next == tail)
			tail = ptr;
		del_by_pointer(ptr->next);
		if (empty())
			tail = head;
		--size;
	}
}
void LIST::clear(ptrNODE ptr)
{
	while(!empty())
		del_from_head();
}

void LIST::create_by_stack(std::ifstream& file)
{
	TInfo elem;
	while (file >> elem)
		add_to_head(elem);
}

void LIST::create_by_queue(std::ifstream& file)
{
	TInfo elem;
	while (file >> elem)
		add_to_tail(elem);
}

void LIST::create_by_order(std::ifstream& file)
{
	TInfo elem;
	ptrNODE p = nullptr;
	auto find_place = [this](TInfo elem) ->ptrNODE
	{
		ptrNODE result = head;
		while (result->next && result->next->info < elem)
			result = result->next;
		return result;
	};
	while (file >> elem)
	{
		p = find_place(elem);
		add_after(p, elem);
	}
}

void LIST::print()
{
	ptrNODE p = head->next;
	if (empty())
		std::cout << "no elem\n";
	while (p)
	{
		std::cout << p->info << ' ';
		p = p->next;
	}
}

