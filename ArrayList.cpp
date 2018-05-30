/** Implementation file for the class ArrayList.
 @file ArrayList.cpp */

//#include "ArrayList.h"  // Header file

template<class ItemType>
ArrayList<ItemType>::ArrayList() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

template<class ItemType>
bool ArrayList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int ArrayList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

template<class ItemType>
bool ArrayList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1)
                           && (newPosition <= itemCount + 1)
                           && (itemCount < maxItems);
   if (ableToInsert)
   {
      // Make room for new entry by shifting all entries at
      // positions >= newPosition toward the end of the array
      // (no shift if newPosition == itemCount + 1)
      for (int entryPosition = itemCount; entryPosition >= newPosition; entryPosition--)
         items[entryPosition + 1] = items[entryPosition]; // copy the entry right

      // Insert new entry
      items[newPosition] = newEntry;
      itemCount++;  // Increase count of entries
   }  // end if

   return ableToInsert;
}  // end insert

template<class ItemType>
bool ArrayList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      // Remove entry by shifting all entries after the one at
      // position toward the beginning of the array
      // (no shift if position == itemCount)
      for (int entryPosition = position; entryPosition < itemCount; entryPosition++)
         items[entryPosition] = items[entryPosition + 1]; // copy entry on the right to left

      itemCount--;  // Decrease count of entries
   }  // end if

   return ableToRemove;
}  // end remove

template<class ItemType>
void ArrayList<ItemType>::clear()
{
   itemCount = 0;
}  // end clear

template<class ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      return items[position];
   }
   else
   {
      std::string message = "getEntry() called with an empty list or ";
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end getEntry

template<class ItemType>
void ArrayList<ItemType>::replace(int position, const ItemType& newEntry) throw(PrecondViolatedExcep)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      items[position] = newEntry;
   }
   else
   {
      std::string message = "replace() called with an empty list or ";
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message));
   }  // end if
}  // end replace

template<class ItemType>
void ArrayList<ItemType>::displayList() const throw(PrecondViolatedExcep) {
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
void ArrayList<ItemType>::sortList() {
  quickSort(items, 1, itemCount); // passing in 1 as start and itemCount as end because items array is not using items[0].
}

template<class ItemType>
void ArrayList<ItemType>::swap(ItemType& a, ItemType& b) {
  ItemType temp = a;
  a = b;
  b = temp;
}

template<class ItemType>
int ArrayList<ItemType>::partition(ItemType* array, const int& start, const int& end) {
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
void ArrayList<ItemType>::quickSort(ItemType* array, const int& start, const int& end) {
  if (start < end) {
    int pivotIndex = partition(array, start, end);

    quickSort(array, start, pivotIndex-1);
    quickSort(array, pivotIndex+1, end);
  }
}

template<class ItemType>
ListInterface<ItemType>* ArrayList<ItemType>::operator+(const ListInterface<ItemType>* rhs) const {
  ListInterface<ItemType>* concatList = new ArrayList<ItemType>;
  for(int i=1; i <= getLength(); i++) {
    concatList->insert(i, getEntry(i));
  }
  for(int i=1; i <= rhs->getLength(); i++) {
    concatList->insert(concatList->getLength()+1, rhs->getEntry(i));
  }
  return concatList;
}


//  End of implementation file.
