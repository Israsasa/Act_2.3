// =================================================================
//
// File: list.h
// Author: Jorge Israel Sandoval Sánchez - A01710373
// Date: 29/09/2023
// 
// =================================================================
#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>
#include "exception.h"
#include "header.h"

template <class T> class List;

// =================================================================
// Definition of the Node class
// =================================================================
template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*);

	T	    value;
	Node<T> *next;

	friend class List<T>;
};

// =================================================================
// Constructor. Initializes the value of the node. The variable next
// is initialized to null.
//
// @param val, stored value in the node.
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), next(NULL) {
}

// =================================================================
// Constructor. Initializes both instance variables.
//
// @param val, stored value in the node.
// @param nxt, the next node.
// =================================================================
template <class T>
Node<T>::Node(T val, Node* nxt) : value(val), next(nxt) {
}

// =================================================================
// Definition of the List class
// =================================================================
template <class T>
class List {
private:
	Node<T> *head;
	uint 	size;

public:
	List();
	~List();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T    front() const;
	T    last() const;
	T    get(uint) const;

	void push_front(T);
	void push_back(T);
	void insert_at(T, uint);

	T    pop_front();
	T 	 pop_back();
	T    remove_at(uint);

	long int  indexOf(T) const;

	int aSalvo(int, int);
};

// =================================================================
// Constructor. Initializes both instance variables to zero.
// =================================================================
template <class T>
List<T>::List() :head(NULL), size(0) {
}

// =================================================================
// Destructor. Remove all items from the list.
// =================================================================
template <class T>
List<T>::~List() {
	clear();
}

// =================================================================
// Returns if the list is empty or not
//
// @returns true if the list is empty, false otherwise.
// =================================================================
template <class T>
bool List<T>::empty() const {
	return (head == NULL);
}

// =================================================================
// Returns the number of items in the list.
//
// @returns size, the number of items in the list.
// =================================================================
template <class T>
uint List<T>::length() const {
	return size;
}

// =================================================================
// Determines if an item is in the list.
//
// @returns true if val is in the list, false otherwise
// =================================================================
template <class T>
bool List<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

// =================================================================
// Remove all items from the list.
// =================================================================
template <class T>
void List<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}

// =================================================================
// String representation of the elements in the list.
//
// @returns a string containing all the elements of the list.
// =================================================================
template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Returns the first item in the list.
//
// @returns the object T at the beginning of the list.
// @throws NoSuchElement, if the list is empty.
// =================================================================
template <class T>
T List<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

// =================================================================
// Returns the last item in the list.
//
// @returns the object T at the end of the list.
// @throws NoSuchElement, if the list is empty.
// =================================================================
template <class T>
T List<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Returns the element that is in the position indicated by index.
// Complexity: O(n)
// @returns the element in index
// @throws IndexOutOfBounds, if index >= size.
// =================================================================
template <class T>
T List<T>::get(uint index) const {
	T aux;
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}else if (index>=size)
	{
		throw IndexOutOfBounds();
	}
	p = head;
	while (index!=0) {
		index--;
		p = p->next;
	}
	aux = p->value;
	return aux;
}

// =================================================================
// Add an item to the beginning of the list. Increase the size of
// the list.
// =================================================================
template <class T>
void List<T>::push_front(T val) {
	Node<T> *q;

	q = new Node<T>(val);
	q->next = head;
	head = q;
	size++;
}

// =================================================================
// Add an item to the end of the list. Increase the size of
// the list.
// =================================================================
template <class T>
void List<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = p;
	p->next = q;
	size++;
}

// =================================================================
// Add an element in index (0 <= index <= size). The element that
// was in that position is shifted to the right.
// Complexity: O(n)
// @throws IndexOutOfBounds, if index > size.
// =================================================================
template <class T>
void List<T>::insert_at(T val, uint index) {
	Node<T> *p, *q, *a;

	if (empty()) {
		throw NoSuchElement();
	}else if (index>size)
	{
		throw IndexOutOfBounds();
	}

	p = head;
	q = NULL;
	a = new Node<T>(val);
	
	if (index == 0)
	{
		a->next = p;
		head = a;
	}else if (index!=0){
		while (index!=0){	
			index--;
			q = p;
			p = p->next;
			if (index == 0){
				q->next = a;
				a->next = p;
			}
		}
	}
	size++;
}

// =================================================================
// Delete the item at the beginning of the list.
//
// @returns the element that was at the beginning of the list.
// @throws NoSuchElement if the list is empty
// =================================================================
template <class T>
T List<T>::pop_front() {
	T val;
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	head = p->next;
	val = p->value;

	delete p;
	size--;
	return val;
}

// =================================================================
// Delete the item at the end of the list.
//
// @returns the element that was at the end of the list.
// @throws NoSuchElement if the list is empty
// =================================================================
template <class T>
T List<T>::pop_back() {
	Node<T> *p, *q;
	T val;

	if (empty()) {
		throw NoSuchElement();
	}

	if (size == 1) {
		return pop_front();
	}

	q = NULL;
	p = head;
	while (p->next != NULL) {
		q = p;
		p = p->next;
	}

	q->next = p->next;
	val = p->value;

	delete p;
	size--;

	return val;
}

// =================================================================
// Delete the element found in index (0 <= index <size).
// Complexity O(n)
// @returns the element that was in index.
// @throws IndexOutOfBounds, if index >= size.
// =================================================================
template <class T>
T List<T>::remove_at(uint index) {
	T aux;
	Node<T> *p,*q;

	if (empty()) {
		throw NoSuchElement();
	}else if (index>=size)
	{
		throw IndexOutOfBounds();
	}
	
	p = head;

	if (index == 0)
	{
		aux = p->value;
		p = p->next;
		head = p;
	}

	while (index!=0) {
		index--;
		q = p;
		p = p->next;
		if (index == 0)
		{
			aux = p->value;
			q->next = p->next;
			delete p;
		}
	}
	size--;
	return aux;
}

// =================================================================
// Returns the position of an item in the list.
// Complexity: O(n)
// @returns the position of an item in the list, -1 otherwise.
// =================================================================
template <class T>
long int List<T>::indexOf(T val) const {
	int index = 0;
	Node<T> *p,*q;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p != NULL) {
		if (p->value == val)
		{
			return index;
		}
		index++;
		p = p->next;
	}
	return -1;
}
// =================================================================
// Returns the position in which person must start the counter for the first one to survive
// Complexity: O(n)
// @returns the position in which person start the counter.
// if list is empty, return -1
// =================================================================
template <class T>
int List<T>::aSalvo(int n, int k){
	int res;
	int pos = 0;
	int salta = 0;
	int b = k;
	int con = n;
	Node <T> *p, *q, *r;
	p = head;
	if (head != NULL)
	{
		
		while (head->next != NULL)
		{
			b--;
			if (b == 0)
			{
				if (q->next != NULL)
				{
					q->next = p->next;
				}
				con --;
				if (head->value == p->value)
				{
					head = p->next;
					pos = 1;
				}
				delete p;
				if (con>1)
				{
					if (q->next == NULL)
					{
						p = head;
					} else{
						p = q->next;
					}
					b = k-1;
					while (b != 0)
					{
						b--;
						r = p;
						if (p->next == NULL)
						{
							p = head;
						}else{
							p = p->next;
						}
					}
					if (r->next != NULL)
					{
						r->next = p->next;
					} else{
						head = p->next;
						p->next = q->next;
						q->next = p;
						salta = 1;
					}
					if (q->next == NULL && pos == 1)
					{
						p->next = head;
						head = p;
						pos = 0;
						// Checar
					}else if (salta == 0){
						// Obvio
						p->next = q->next;
						if (p->value != q->value)
						{
							q->next = p;
						} else{
							r->next = p;
						}
					}
					salta = 0;
					b = k;
				}
			}
			q = p;
			if (p->next == NULL)
			{
				p = head;
			} else{
				p = p->next;
			}
		}
		q = head;
		res = q->value;
		
		if(res == 1)
		{
			return res;
		}else if(res == 2)
		{
			return n;
		}else{
			return n-(res-2);
		}
	}
	return -1;
}

#endif /* LIST_H */
