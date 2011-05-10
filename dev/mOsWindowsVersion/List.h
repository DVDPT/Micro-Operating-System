#pragma once

#include "KernelTypes.h"

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

	INLINE T* GetValue(){return _value;}

	Void INLINE SetValue(T* value){ _value = value; }


};

template <class T>
class List
{
	Node<T> _head;

	BOOL INLINE IsLastNode(Node<T>* node){return node->_next == &_head;}
	BOOL INLINE IsFirstNode(Node<T>* node){return node->_prev == &_head;}
public:
	List()
	{
		_head._next = _head._prev = &_head;
		_head._value = NULL;
	}

	INLINE BOOL IsEmpty(){ return _head._next == &_head; }

	INLINE Node<T>* GetFirst(){ return IsEmpty() ? NULL : _head._next; }

	INLINE Node<T>* GetLast(){ return IsEmpty() ? NULL : _head._prev; }

	INLINE Node<T>* GetNext(Node<T> * node) { IsLastNode(node) ? NULL : node->_next;}

	INLINE Node<T>* GetPrevious(Node<T> * node) { IsFirstNode(node) ? NULL : node->_prev;}

	INLINE Void AddFirst(Node<T>* node)
	{
		node->_prev = &_head;
		node->_next = _head._next;
		_head._next->_prev = node;
		_head._next = node;
	}

	INLINE Void AddLast(Node<T>* node)
	{
		node->_next = _head;
		node->_prev = _head._prev;
		_head._prev->_next = node;
		_head._prev = node;
	}

	INLINE Void Remove(Node<T>* node)
	{
		node->_prev->_next = node->_next;
		node->_next->_prev = node->_prev;
		node->_next = node->_prev = NULL;
	}

	INLINE Void RemoveFirst(){ Remove(_head._next); }
	INLINE Void RemoveLast(){ Remove(_head._prev); }
		
	INLINE Void Enqueue(Node<T>* node)
	{
		AddLast(node);
	}

	INLINE Node<T>* Dequeue()
	{
		Node<T> * ret = GetFirst();
		if(ret)
			Remove(ret);
		return ret;
	}
};
