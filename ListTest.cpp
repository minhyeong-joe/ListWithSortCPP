//Test Driver for ListInterface 2.0 implementations,
//data structures: ArrayList & LinkedList
//Will choose which data structure to test at run-time

#include <iostream>
#include <string>
#include "LinkedList.h" // ADT list operations implemented as LinkedList
#include "ArrayList.h"  // ADT list operations implemented as ArrayList



void copyConstructorTester()
{
   LinkedList<std::string> list;
   std::string items[] = {"zebra", "ostrich", "tiger", "tarantula", "fish", "falcom"};
	for (int i = 0; i < 6; i++)
   {
		std::cout << "Adding " << items[i] << std::endl;
        bool success = list.insert(1, items[i]);
        if (!success)
         std::cout << "Failed to add " << items[i] << " to the list." << std::endl;
	}
   list.displayList();    /****** 	uncomment to test ******/

   LinkedList<std::string> copyOfList(list);
   std::cout << "Copy of list: ";
   copyOfList.displayList();  /******** uncomment to test ********/

   std::cout << "The copied list: ";
   list.displayList();       /****** uncomment to test **********/
}  // end copyConstructorTester

void listTester(ListInterface<std::string>* listPtr)
{
   std::string data[] = {"ostrich", "tiger", "tarantula", "fish", "falcom", "sheep", "horse"};
   for (int i = 0; i < 6; i++)
   {
      if (listPtr->insert(i + 1, data[i]))
      {
         try
         {
            std::cout << "Inserted " << listPtr->getEntry(i + 1) << " at position " << (i + 1) << std::endl;
         } catch (PrecondViolatedExcep except)
         {
            std::cout << "Exception thrown getting entry inserted at list end!" << std::endl;
            std::cout << except.what() << std::endl;
         }
      }
      else
         std::cout << "Cannot insert " << data[i] << " at position " << (i + 1) << std::endl;
   }  // end for

   listPtr->displayList();    /******** uncomment to test ************/
   listPtr->sortList();
   listPtr->displayList();

   std::cout << "After replacing the entry at position 3 with XXX: ";
   try
   {
      listPtr->replace(3, "XXX");
   }
   catch (PrecondViolatedExcep except)
   {
      std::cout << "Exception thrown getting entry at position 3!" << std::endl;
      std::cout << except.what() << std::endl;
   }
   try
   {
      listPtr->replace(12, "elephant");
   }
   catch (PrecondViolatedExcep except)
   {
      std::cout << "Exception thrown getting entry at position 3!" << std::endl;
      std::cout << except.what() << std::endl;
   }
   listPtr->displayList();  /****** uncomment to test **************/
   listPtr->sortList();
   listPtr->displayList(); /********* uncomment to test *********/

   std::cout << "clear: " << std::endl;
   listPtr->clear();
   std::cout << "isEmpty: returns " << listPtr->isEmpty() << "; should be 1 (true)" << std::endl;


} // end listTester

int main()
{
   char a;
   std::cout<<"Enter A for ArrayList/ Enter L for LinkedList\n";
   std::cin>>a;
   if (a == 'l' || a == 'L') {


       ListInterface<std::string>* listPtr = new LinkedList<std::string>();
       listTester(listPtr);
       //copyConstructorTester();
   }
   else {
   	ListInterface<std::string>* listPtr = new ArrayList<std::string>();
        listTester(listPtr);
   }

   return 0;
}  // end main
