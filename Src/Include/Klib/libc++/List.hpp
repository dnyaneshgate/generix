/* 
 * File:   List.hpp
 * Author: dnyaneshg
 *
 * Created on December 1, 2012, 9:38 PM
 */

#ifndef __GENERIX_LIBCPP_LIST_HPP__
#define	__GENERIX_LIBCPP_LIST_HPP__

#include <Types.hpp>
#include <Macros.hpp>
#include <Assert.hpp>

template<class T> class ListIterator;
template<class T> class List;

template <class T>
class ListNode {
	friend class List<T>;
	friend class ListIterator<T>;
	//member functions
public:
protected:
private:

	ListNode<T>(ListNode<T> * next, const T& data, ListNode<T> * prev) : Next(next), Data(data), Prev(prev)
	{
	}

	~ListNode<T>()
	{
	}

	//member variables
public:
protected:
private:
	ListNode<T> *Next;
	T Data;
	ListNode<T> *Prev;
};

template <class T>
class ListIterator {
	friend class List<T>;
	//member functions
public:
	~ListIterator<T>()
	{
	}
protected:
private:

	ListIterator<T>(ListNode<T> * pointer) : Pointer(pointer)
	{
	}
	//member variables
public:

	T& operator*()
	{
		return Pointer->Data;
	}

	const ListIterator<T>& operator++()
	{
		ASSERT(Pointer != ZERO);
		Pointer = Pointer->Next;
		return *this;
	}

	const ListIterator<T>& operator--()
	{
		ASSERT(Pointer != ZERO);
		Pointer = Pointer->Prev;
		return *this;
	}

	BOOL operator !=(const ListIterator<T>& Other)
	{
		return (this->Pointer != Other.Pointer);
	}

protected:
private:
	ListNode<T> * Pointer;
};

template<class T>
class List {
private:
	ListNode<T> *head, *tail;
protected:
public:
	typedef ListIterator<T> iterator;

	List() : head(ZERO), tail(ZERO)
	{
	}

	~List()
	{
		clear();
	}
	bool empty();
	void clear();
	void push_front(const T& elem);
	T& pop_front();
	void push_back(const T& elem);
	T& pop_back();

	iterator begin()
	{
		return (ListIterator<T > (head));
	}

	iterator end()
	{
		return ListIterator<T > (ZERO);
	}
};

template<class T>
bool List<T>::empty()
{
	return (head == ZERO);
}

template<class T>
void List<T>::clear()
{
	ListNode<T> *p = head, *t;
	while (p != ZERO) {
		t = p->Next;
		delete p;
		p = t;
	}
}

template<class T>
void List<T>::push_front(const T& elem)
{
	ListNode<T> *newnode = new ListNode<T > (ZERO, &elem, ZERO);
	ASSERT(newnode != ZERO);
	if (head == ZERO)
		head = newnode;
	else {
		newnode->Next = head;
		head->Prev = newnode;
	}
	head = newnode;
}

template<class T>
void List<T>::push_back(const T& elem)
{
	ListNode<T> *newnode = new ListNode<T > (ZERO, elem, ZERO);
	//printk("newnode = %x\n", (UINT)newnode);
	ASSERT(newnode != ZERO);
	if (head == ZERO)
		head = newnode;
	else {
		tail->Next = newnode;
		newnode->Prev = tail;
	}
	tail = newnode;
}

template<class T>
T& List<T>::pop_front()
{
	ListNode<T> *node = head;
	head = head->Next;
	head->Prev = ZERO;
	T val = node->Data;
	delete node;
	return val;
}

template<class T>
T& List<T>::pop_back()
{
	ListNode<T> *node = tail;
	tail = tail->Prev;
	T val = node->Data;
	delete node;
	return val;
}

#endif	/* __GENERIX_LIBCPP_LIST_HPP__ */

