#include "My_List.h"
#include <functional>

ptrNODE find_place(ptrNODE begin, const TInfo& good)
{
	ptrNODE p = begin; 
	while (p && p->info.compare(good) < 0)
		p = p->next;
	return p;
}

DLIST::DLIST(const char* filename)
{
	std::ifstream file(filename);
	TInfo good(file);
	first_node(good);
	ptrNODE place;
	while (!file.eof())
	{
		TInfo good(file);
		place = find_place(begin, good);
		if (place)
			add_before(place, good);
		else
			add_after(end, good);
	}
	file.close();
}

void DLIST::first_node(const TInfo& good)
{
	begin = new NODE(good);
	end = begin;
}

bool DLIST::empty()
{
	return begin == nullptr;
}

void DLIST::add_after(ptrNODE ptr, const TInfo& good)
{
	ptrNODE p = new NODE(good, ptr->next, ptr);
	if (ptr == end)
		end = p;
	else
		ptr->next->prev = p;
	ptr->next = p;
}

void DLIST::add_before(ptrNODE ptr, const TInfo& good)
{
	ptrNODE p = new NODE(good, ptr, ptr->prev);
	if (ptr == begin)
		begin = p;
	else
		ptr->prev->next = p;
	ptr->prev = p;
}

void DLIST::del_before(ptrNODE& ptr)
{
	if (ptr && ptr->prev)
	{
		if (ptr->prev == begin)
			begin = ptr;
		Delete(ptr->prev);
		--size;
	}
}

void DLIST::del_after(ptrNODE& ptr)
{
	if (ptr && ptr->next)
	{
		if (ptr->next == end)
			end = ptr;
		Delete(ptr->next);
		--size;
	}
}

void DLIST::print()
{
	ptrNODE ptr = begin;
	while (ptr)
	{
		ptr->info.print();
		ptr = ptr->next;
	}
}

DLIST::~DLIST()
{
	while (!empty())
		Delete(begin);
}

TInfo& DLIST::Delete(ptrNODE& ptr)
{
	ptrNODE p = ptr; 
	if (ptr == begin)
	{
		begin = p->next;
		ptr = begin;
		if (p->next)
			p->next->prev = nullptr;
	}
	else
		if (ptr == end)
		{
			end = p->prev;
			ptr = end;
			if (p->prev)
				p->prev->next = nullptr;
		}
		else
		{
			ptr = ptr->next;
			p->next->prev = p->prev;
			p->prev->next = p->next;
		}
	static TInfo good;
	good = p->info;
	delete p;
	return good;
}

// переключ