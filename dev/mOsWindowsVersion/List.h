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

	friend List<T>;
public:
	Node() : _next(NULL), _prev(NULL), _value(NULL)
	{}

	T* GetValue(){return _value;}

	Void SetValue(T* value){ _value = value; }


};

template <class T>
class List
{
	Node<T> _head;

	BOOL IsLastNode(Node<T>* node){return node->_next == &_head;}
	BOOL IsFirstNode(Node<T>* node){return node->_prev == &_head;}
public:
	NOINLINE List() : _head()
	{
		_head._next =  &_head;
		_head._prev = &_head;
		_head._value = NULL;
	}

	NOINLINE BOOL IsEmpty(){ return (BOOL)(_head._next == &_head); }

	NOINLINE Node<T>* GetFirst(){ return IsEmpty() ? NULL : _head._next; }

	NOINLINE Node<T>* GetLast(){ return IsEmpty() ? NULL : _head._prev; }

	NOINLINE Node<T>* GetNext(Node<T> * node) { IsLastNode(node) ? NULL : node->_next;}

	NOINLINE Node<T>* GetPrevious(Node<T> * node) { IsFirstNode(node) ? NULL : node->_prev;}

	NOINLINE Void AddFirst(Node<T>* node)
	{
		node->_prev = &_head;
		node->_next = _head._next;
		_head._next->_prev = node;
		_head._next = node;
	}

	NOINLINE Void AddLast(Node<T>* node)
	{
		node->_next = &_head;
		node->_prev = _head._prev;
		_head._prev->_next = node;
		_head._prev = node;
	}

	NOINLINE Void Remove(Node<T>* node)
	{
		node->_prev->_next = node->_next;
		node->_next->_prev = node->_prev;
		node->_next = node->_prev = NULL;
	}

	NOINLINE Void RemoveFirst(){ Remove(_head._next); }
	NOINLINE Void RemoveLast(){ Remove(_head._prev); }
	
	NOINLINE Void Enqueue(Node<T>* node)
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
