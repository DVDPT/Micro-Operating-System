#pragma once

#include "SystemTypes.h"

template<class T>
class List;

template <class T>
struct Node
{
private:
	Node* _next;
	Node* _prev;
	T* _value;

	friend class List<T>;
public:
	Node() : _next(NULL), _prev(NULL), _value(NULL)
	{}

	T* GetValue(){return _value;}

	void SetValue(T* value){ _value = value; }

	bool IsInList(){ return _next == NULL && _prev == NULL; }


};

template <class T>
class List
{
	Node<T> _head;

	bool IsLastNode(Node<T>* node){return node->_next == &_head;}
	bool IsFirstNode(Node<T>* node){return node->_prev == &_head;}
public:
	NOINLINE List() : _head()
	{
		_head._next =  &_head;
		_head._prev = &_head;
		_head._value = NULL;
	}

	NOINLINE bool IsEmpty(){ return (bool)(_head._next == &_head); }

	NOINLINE Node<T>* GetFirst(){ return IsEmpty() ? NULL : _head._next; }

	NOINLINE Node<T>* GetLast(){ return IsEmpty() ? NULL : _head._prev; }

	NOINLINE Node<T>* GetNext(Node<T> * node) { return IsLastNode(node) ? NULL : node->_next;}

	NOINLINE Node<T>* GetPrevious(Node<T> * node) { return IsFirstNode(node) ? NULL : node->_prev;}

	NOINLINE void AddFirst(Node<T>* node)
	{
		node->_prev = &_head;
		node->_next = _head._next;
		_head._next->_prev = node;
		_head._next = node;
	}

	NOINLINE void AddLast(Node<T>* node)
	{
		node->_next = &_head;
		node->_prev = _head._prev;
		_head._prev->_next = node;
		_head._prev = node;
	}

	NOINLINE void Remove(Node<T>* node)
	{
		node->_prev->_next = node->_next;
		node->_next->_prev = node->_prev;
		node->_next = node->_prev = NULL;
	}

	NOINLINE void RemoveFirst(){ Remove(_head._next); }
	NOINLINE void RemoveLast(){ Remove(_head._prev); }
	
	NOINLINE void Enqueue(Node<T>* node)
	{
		AddLast(node);
	}

	NOINLINE Node<T>* Dequeue()
	{
		Node<T> * ret = GetFirst();
		if(ret)
			Remove(ret);
		return ret;
	}
};
