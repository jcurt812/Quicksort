#include <iostream>
#include <string>
#include <vector>
#include <array>
#include "QS.h"
#include <algorithm>

using namespace std;

QS::QS() {
	maxIndex = 0;
	insertPos = 0;
	arrayPtr = NULL;
}
	
QS::~QS() {
	if (arrayPtr != NULL)
	{
		delete[] arrayPtr;
	}
}

void QS::sortHelper(int left, int right, int pivotIndex) {
	if ((right - left) > 1) {
		int newPiv = partition(left, right, pivotIndex);

		int leftQuarter = medianOfThree(left, newPiv - 1);
		int rightQuarter = medianOfThree(newPiv + 1, right);

		sortHelper(left, newPiv - 1, leftQuarter);
		sortHelper(newPiv + 1, right, rightQuarter);
	}
}

	/*
	* sortAll()
	*
	* Sorts elements of the array.  After this function is called, every element in the array is less than or equal its successor.
	*
	* Does nothing if the array is empty.
	*/
void QS::sortAll() {
	if (arrayPtr == NULL || insertPos == 0) {
		cout << "ERROR: Array is empty" << endl;
	}
	else {
		int pivot = medianOfThree(0, insertPos - 1);
		sortHelper(0, insertPos - 1, pivot);
	}
}

	/*
	* medianOfThree()
	*
	* The median of three pivot selection has two parts:
	*
	* 1) Calculates the middle index by averaging the given left and right indices:
	*
	* middle = (left + right)/2
	*
	* 2) Then bubble-sorts the values at the left, middle, and right indices.
	*
	* After this method is called, data[left] <= data[middle] <= data[right].
	* The middle index will be returned.
	*
	* Returns -1 if the array is empty, if either of the given integers
	* is out of bounds, or if the left index is not less than the right
	* index.
	*
	* @param left
	* 		the left boundary for the subarray from which to find a pivot
	* @param right
	* 		the right boundary for the subarray from which to find a pivot
	* @return
	*		the index of the pivot (middle index); -1 if provided with invalid input
	*/
int QS::medianOfThree(int left, int right) {
	if (arrayPtr == NULL || insertPos == 0) {
		return -1;
	}
	else if (left < 0 || right >= insertPos) {
		return -1;
	}
	else if (left >= right) {
		return -1;
	}
	else {
		int middleIndex = (left + right) / 2;
		// int placeholder = 0;

		while (arrayPtr[left] > arrayPtr[middleIndex] || 
			   arrayPtr[left] > arrayPtr[right] || 
			   arrayPtr[middleIndex] > arrayPtr[right]) {

			if (arrayPtr[middleIndex] <= arrayPtr[left]) {
				int placeholder = arrayPtr[left];
				arrayPtr[left] = arrayPtr[middleIndex];
				arrayPtr[middleIndex] = placeholder;

				// swap(arrayPtr[left], arrayPtr[middleIndex]);
			}

			if (arrayPtr[right] <= arrayPtr[middleIndex]) {
				int placeholder = arrayPtr[middleIndex];
				arrayPtr[middleIndex] = arrayPtr[right];
				arrayPtr[right] = placeholder;
			}
		}

	return middleIndex;
	}
}

	/*
	* Partitions a subarray around a pivot value selected according to
	* median-of-three pivot selection.  Because there are multiple ways to partition a list,
	* we will follow the algorithm on page 611 of the course text when testing this function.
	*
	* The values which are smaller than the pivot should be placed to the left
	* of the pivot; the values which are larger than the pivot should be placed
	* to the right of the pivot.
	*
	* Returns -1 if the array is null, if either of the given integers is out of
	* bounds, or if the first integer is not less than the second integer, or if the
	* pivot is not within the sub-array designated by left and right.
	*
	* @param left
	* 		the left boundary for the subarray to partition
	* @param right
	* 		the right boundary for the subarray to partition
	* @param pivotIndex
	* 		the index of the pivot in the subarray
	* @return
	*		the pivot's ending index after the partition completes; -1 if
	* 		provided with bad input
	*/
int QS::partition(int left, int right, int pivotIndex) {
	if (arrayPtr == NULL || insertPos == 0) {
		return -1;
	}
	else if (left < 0 || right >= insertPos) {
		return -1;
	}
	else if (left >= right) {
		return -1;
	}
	else if (pivotIndex < left || pivotIndex > right) {
		return -1;
	}
	else {
		int placeholder = 0;
		placeholder = arrayPtr[pivotIndex];  //switch pivot & left
		arrayPtr[pivotIndex] = arrayPtr[left];  //switch pivot & left
		arrayPtr[left] = placeholder; //switch pivot & left

		int up = left + 1;
		int down = right;

		do {
			while (up != right && arrayPtr[up] <= arrayPtr[left]) {
				++up;
			}

			while (down > (left) && arrayPtr[down] > arrayPtr[left]) {
				--down;
			}
			if (up < down) {
				int placeholderThree = arrayPtr[down];
				arrayPtr[down] = arrayPtr[up];
				arrayPtr[up] = placeholderThree;
			}
		} while (up < down);

	int placeholderTwo = arrayPtr[down];
	arrayPtr[down] = arrayPtr[left];
	arrayPtr[left] = placeholderTwo;

	return down;
	}
}

	/*
	* Produces a comma delimited string representation of the array. For example: if my array
	* looked like {5,7,2,9,0}, then the string to be returned would look like "5,7,2,9,0"
	* with no trailing comma.  The number of cells included equals the number of values added.
	* Do not include the entire array if the array has yet to be filled.
	*
	* Returns an empty string, if the array is NULL or empty.
	*
	* @return
	*		the string representation of the current array
	*/
string QS::getArray() const {
	string arrayString = "";
	if (insertPos == 0) {
		arrayString = "";
		return arrayString;
	}
	else {
		for (unsigned int i = 0; i < insertPos - 1; ++i) {
			arrayString = arrayString + to_string(arrayPtr[i]) + ","; 
		}
	arrayString = arrayString + (to_string(arrayPtr[insertPos - 1]));
	return arrayString;
	}
}

	/*
	* Returns the number of elements which have been added to the array.
	*/
int QS::getSize() const {
	return (insertPos);
}

	/*
	* Adds the given value to the end of the array starting at index 0.
	* For example, the first time addToArray is called,
	* the give value should be found at index 0.
	* 2nd time, value should be found at index 1.
	* 3rd, index 2, etc up to its max capacity.
	*
	* If the array is filled, do nothing.
	* returns true if a value was added, false otherwise.
	*/
bool QS::addToArray(int value) {
	if (insertPos == maxIndex) {
		return false;
	}
	else {
		arrayPtr[insertPos] = value;
		++insertPos;
		return true;
	}
}

	/*
	* Dynamically allocates an array with the given capacity.
	* If a previous array had been allocated, delete the previous array.
	* Returns false if the given capacity is non-positive, true otherwise.
	*
	* @param
	*		size of array
	* @return
	*		true if the array was created, false otherwise
	*/
bool QS::createArray(int capacity) {
	if (capacity < 0) {
		return false;
	}
	if (arrayPtr != NULL) {
		delete [] arrayPtr;
		arrayPtr = NULL;
	}
	insertPos = 0;
	maxIndex = (capacity);
	arrayPtr = new int[capacity];
	return true;
}

	/*
	* Resets the array to an empty or NULL state.
	*/
void QS::clear() {
	//delete [] arrayPtr;
	//arrayPtr = NULL;
	insertPos = 0;
}