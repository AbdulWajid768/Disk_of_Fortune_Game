/*
 * Name: YOUR NAME
 * Revealer Class Member Function Definitions
 * Course: CSI218 (Spring 2018)
 * Date: THE DATE
 * Description: Revealer member function definitions.
 */

#ifndef REVEALER_CPP
#define REVEALER_CPP

#include <iostream>
#include "revealer.h"
using namespace std;

// Definitions for template class constants.

template<class T>
const string Revealer<T>::PLACEHOLDER = "_";

// Definitions for template class member functions.

// Constructor to set up list of items, initially all hidden.
template<class T>
Revealer<T>::Revealer(const T origItems[], int size)
{
	// Store size of both arrays.
	numItems = size;

	// Allocate array to hold items.
	items = new T[numItems];

	// Allocate array to store whether each item
	// is revealed (else hidden).
	revealed = new bool[numItems];

	// Copy passed items into internal dynamic array
	// and mark all items as being hidden (not revealed).
	for (int i = 0; i < numItems; i++)
	{
		items[i] = origItems[i];
		revealed[i] = false;
	}
}

// REMOVE
// Copy constructor.
template<class T>
Revealer<T>::Revealer(const Revealer& otherRevealer)
{
	numItems = otherRevealer.numItems;
	items = new T[numItems];
	revealed = new bool[numItems];
	for (int i = 0; i < numItems; i++)
	{
		items = otherRevealer.items[i];
		revealed[i] = false;
	}
}

// Assignment operator.
template<class T>
Revealer<T>& Revealer<T>::operator =(const Revealer& otherRevealer)
{
	if (this != &otherRevealer)
	{
		numItems = otherRevealer.numItems;
		items = new T[numItems];
		revealed = new bool[numItems];
		for (int i = 0; i < numItems; i++)
		{
			items = otherRevealer.items[i];
			revealed[i] = false;
		}
	}
	return *this;
}

// Destructor.
template<class T>
Revealer<T>::~Revealer()
{
	delete[] items;
	delete[] revealed;
	items = NULL;
	revealed = NULL;
	numItems = 0;
}
// End REMOVE

// Return size of list of items.
template<class T>
int Revealer<T>::getSize() const
{
	return numItems;
}

// Return number of items currently revealed in list.
template<class T>
int Revealer<T>::getNumRevealed() const
{
	int count = 0;
	for (int i = 0; i < numItems; i++)
		if (revealed[i])
			count++;
	return count;
}

// Display list, showing revealed items (hidden items
// shown using a generic placeholder).
template<class T>
void Revealer<T>::display() const
{
	for (int i = 0; i < numItems; i++)
	{
		cout << " ";

		if (revealed[i])
			cout << items[i];
		else
			cout << PLACEHOLDER;  // hidden
	}
}

// Unhide all the items that match passed item.  Items
// will be shown next time display() is used.
template<class T>
int Revealer<T>::unhide(T hiddenItem)
{
	int count = 0;
	for (int i = 0; i < numItems; i++)
		if (items[i] == hiddenItem)
		{
			revealed[i] = true;
			count++;
		}
	return count;
}

#endif