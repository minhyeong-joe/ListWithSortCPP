/** ADT list: Array-based implementation.
    Listing 9-1.
    @file ArrayList.h */

#ifndef ARRAY_LIST_
#define ARRAY_LIST_

#include "ListInterface.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class ArrayList : public ListInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 5; // Small capacity to test for a full list
	ItemType items[DEFAULT_CAPACITY+1];      // Array of list items (not using element [0]
   int itemCount;                         // Current count of list items
   int maxItems;                          // Maximum capacity of the list

	  // Helper functions for sortList
	 void swap(ItemType& a, ItemType& b);
	 int partition(ItemType* array, const int& start, const int& end);
	 void quickSort(ItemType* array, const int& start, const int& end);
public:
   ArrayList();
   // Copy constructor and destructor are supplied by compiler

   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   bool remove(int position);
   void clear();

   /** @throw PrecondViolatedExcep if position < 1 or
                                      position > getLength(). */
   ItemType getEntry(int position) const throw(PrecondViolatedExcep);

   /** @throw PrecondViolatedExcep if position < 1 or
                                      position > getLength(). */
   void replace(int position, const ItemType& newEntry)
                               throw(PrecondViolatedExcep);

	 /** @throw PrecondViolatedExcep if the list is empty. */
   void displayList() const throw(PrecondViolatedExcep);

   void sortList();
}; // end ArrayList

#include "ArrayList.cpp"
#endif
