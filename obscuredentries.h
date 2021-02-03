/*
 * Name: YOUR NAME
 * HiddenEntries Class Definition
 * Course: CSI218 (Fall 2020)
 * Date: THE DATE
 * Description: HiddenEntries class definition declaring data members
 *				and member functions.  Stores a 2D vector whose entries
				can be displayed or obscured via standard output (<<).
				Whether to display an entry is stored in a dynamic 2D
				array of bools.
 */

#ifndef OBSCUREDENTRIES_H
#define OBSCUREDENTRIES_H

#include <vector>
using namespace std;

// Class to represents 2D vector of entries of some type
// that are either shown or obscured.
template<class T>
class ObscuredEntries
{
public:
	// Constructor to store entries (vector passed) and set all as
	// hidden.  Value displayed for hidden entries is also passed.
	ObscuredEntries(const vector<vector<T>>& values, const T& hiddenVal);

	// Copy constructor.
	ObscuredEntries(const ObscuredEntries& otherObscuredEntries);

	// Assignment operator.
	ObscuredEntries<T>& operator =(const ObscuredEntries& otherObscuredEntries);

	// Return number of rows in 2D entries.
	int getNumRows() const;

	// Return number of columns in 2D entries for particular row.
	int getNumCols(int row) const;
	// Precondition: row passed should be within valid # of
	// rows (indices start at zero).

	// Display 2D entries (each row on separate line, certain
	// entries hidden by displaying special value).
	void display() const;

	// Get value at particular location within 2D entries.
	T getEntry(int row, int col) const;
	// Precondition: row and col passed should be within
	// valid # of rows and columns (indices start at zero).

	// Reveal entry at particular location within 2D entries.
	void unhide(int row, int col);
	// Precondition: row and col passed should be within
	// valid # of rows and columns (indices start at zero).


	//Make and Initialize the shown dynamic array
	void initializeShown();

	//Tell whether the entry is hidden or not
	bool isHidden(int row, int col) const;

	// Destructor.
	~ObscuredEntries();
private:
	// Store entries (values of particular type) in 2D vector.
	vector<vector<T>> contents;
	bool** shown;  // which entries to show
	T hiddenValue; // what to display for hidden entries
};

#endif