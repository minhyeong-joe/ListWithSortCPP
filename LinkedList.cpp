/** Implementation file for the class LinkedList.
 @file LinkedList.cpp */

//#include "LinkedList.h"  // Header file
#include <cassert>

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(NULL), itemCount(0)
{
}  // end default constructor


/******* CHANGE COPY TO CONSTRUCTOR IMPLEMENTATION TO A RECURSIVE IMPLEMENTATION ************
 ******* NOTE: YOU CAN CREATE A HELPER METHOD, AND THE HELPER METHOD DOES THE RECURSION WORK *********/
template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) : itemCount(aList.itemCount)
{
   Node<ItemType>* origChainPtr = aList.headPtr;  // Points to nodes in original chain

   if (origChainPtr == NULL)
      headPtr = NULL;  // Original list is empty
   else
   {
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());

      // Copy remaining nodes
      Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
      while (origChainPtr != NULL)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();

         // Create a new node containing the next item
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);

         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr);

         // Advance pointer to new last node
         newChainPtr = newChainPtr->getNext();

         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while

      newChainPtr->setNext(NULL);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      // Create a new node containing the new entry
      Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

      // Attach new node to chain
      if (newPosition == 1)
      {
         // Insert new node at beginning of chain
         newNodePtr->setNext(headPtr);
         headPtr = newNodePtr;
      }
      else
      {
         // Find node that will be before new node
         Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);

         // Insert new node after node to which prevPtr points
         newNodePtr->setNext(prevPtr->getNext());
         prevPtr->setNext(newNodePtr);
      }  // end if

      itemCount++;  // Increase count of entries
   }  // end if

   return ableToInsert;
}  // end insert

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      Node<ItemType>* curPtr = NULL;
      if (position == 1)
      {
         // Remove the first node in the chain
         curPtr = headPtr; // Save pointer to node
         headPtr = headPtr->getNext();
      }
      else
      {
         // Find node that is before the one to delete
         Node<ItemType>* prevPtr = getNodeAt(position - 1);

         // Point to node to delete
         curPtr = prevPtr->getNext();

         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
      }  // end if

      // Return node to system
      curPtr->setNext(NULL);
      delete curPtr;
      curPtr = NULL;

      itemCount--;  // Decrease count of entries
   }  // end if

   return ableToRemove;
}  // end remove

template<class ItemType>
void LinkedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
}  // end clear

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      Node<ItemType>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      std::string message = "getEntry() called with an empty list or ";
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end getEntry

template<class ItemType>
void LinkedList<ItemType>::replace(int position, const ItemType& newEntry) throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      Node<ItemType>* nodePtr = getNodeAt(position);
      nodePtr->setItem(newEntry);
   }
   else
   {
      std::string message = "replace() called with an invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end replace

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
   // Debugging check of precondition
   assert( (position >= 1) && (position <= itemCount) );

   // Count from the beginning of the chain
   Node<ItemType>* curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();

   return curPtr;
}  // end getNodeAt

template<class ItemType>
void LinkedList<ItemType>::displayList() const throw(PrecondViolatedExcep) {
  if(!isEmpty()) {
    for(int i = 1; i <= itemCount; i++ ) {
      std::cout << i << ". " << getEntry(i) << std::endl;
    }
    std::cout << std::endl;
  } else {
    std::string message = "There is no entry in the list.";
    throw(PrecondViolatedExcep(message));
  }
}

template<class ItemType>
void LinkedList<ItemType>::sortList() {
  // copy all items in linked list to an temporary array.
  ItemType tempArray[itemCount];
  for(int i = 0; i < itemCount; i++) {
    tempArray[i] = getEntry(i+1);
  }

  // sort the temporary array in ascending order.
  quickSort(tempArray, 0, itemCount-1);

  // copy all items from sorted array to the linked list.
  for(int i = 0; i < itemCount; i++) {
    replace(i+1, tempArray[i]);
  }
}

template<class ItemType>
void LinkedList<ItemType>::swap(ItemType& a, ItemType& b) {
  ItemType temp = a;
  a = b;
  b = temp;
}

template<class ItemType>
int LinkedList<ItemType>::partition(ItemType* array, const int& start, const int& end) {
  int pivotIndex = start;
  ItemType pivot = array[end];
  for(int i = pivotIndex; i < end; i++) {
    if(array[i] <= pivot) {
      swap(array[i], array[pivotIndex]);
      pivotIndex++;
    }
  }
  swap(array[pivotIndex], array[end]);
  return pivotIndex;
}

template<class ItemType>
void LinkedList<ItemType>::quickSort(ItemType* array, const int& start, const int& end) {
  if (start < end) {
    int pivotIndex = partition(array, start, end);

    quickSort(array, start, pivotIndex-1);
    quickSort(array, pivotIndex+1, end);
  }
}
//  End of implementation file.
