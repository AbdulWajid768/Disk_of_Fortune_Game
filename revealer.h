/*
 * Name: YOUR NAME
 * REVEALER Class Definition
 * Course: CSI218 (Spring 2018)
 * Date: THE DATE
 * Description: Revealer class definition declaring data members
 *				and member functions.  Represents a list of items
 *				that is hidden but is revealed when a match is
 *				provided.
 */

#ifndef REVEALER_H
#define REVEALER_H

#include <string>
using namespace std;

// Class to represent a list of hidden items to be progressively revealed
// (initially hidden).
template<class T>
class Revealer
{
public:
	// Constructor to set up list of items, initially all hidden.
	Revealer(const T origItems[], int size);

	// Copy constructor.
	Revealer(const Revealer& otherRevealer);
	// Assignment operator.
	Revealer<T>& operator =(const Revealer& otherRevealer);
	// Destructor.
	~Revealer();

	// Return size of list of items.
	int getSize() const;

	// Return number of items currently revealed in list.
	int getNumRevealed() const;

	// Display list, showing revealed items (hidden items
	// shown using a generic placeholder).
	void display() const;

	// Unhide all the items that match passed item.  Items
	// will be shown next time display() is used.
	int unhide(T hiddenItem);

private:
	// What to display for hidden items.
	static const string PLACEHOLDER;

	// Store values of particular type in list (dynamic array).
	T* items;
	// Record whether an item should be revealed (dynamic array).
	bool* revealed;
	// Number of elements in both dynamic arrays.
	int numItems;
};

#endif