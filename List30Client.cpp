//Test Driver for ListInterface 2.0 implementations,
//data structures: ArrayList & LinkedList
//Will choose which data structure to test at run-time

#include <iostream>
#include <string>
#include "LinkedList.h" // ADT list operations implemented as LinkedList
#include "ArrayList.h"  // ADT list operations implemented as ArrayList

template<class friendItemType>
ostream& operator<<(ostream &output, const ListInterface<friendItemType>* list) {
  for (int i=1; i <= list->getLength(); i++) {
    output << list->getEntry(i) << " ";
  }
  output << endl;
  return output;
};

void listTester(ListInterface<std::string>* listPtr, ListInterface<std::string>* listPtr2)
{
   std::string data[] = {"one", "two" };
   std::string data2[] = {"three", "four"};

   for (int i = 0; i < 2; i++)
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

   for (int i = 0; i < 2; i++)
   {
      if (listPtr2->insert(i + 1, data2[i]))
      {
         try
         {
            std::cout << "Inserted " << listPtr2->getEntry(i + 1) << " at position " << (i + 1) << std::endl;
         } catch (PrecondViolatedExcep except)
         {
            std::cout << "Exception thrown getting entry inserted at list end!" << std::endl;
            std::cout << except.what() << std::endl;
         }
      }
      else
         std::cout << "Cannot insert " << data2[i] << " at position " << (i + 1) << std::endl;
   }  // end for

   std::cout<<"List contents\n";
   // std::cout<<listPtr<<std::endl;
   for(int i=1; i <= listPtr->getLength(); i++) {
     std::cout << listPtr->getEntry(i) <<  " ";
   }
   std::cout << std::endl;
   std::cout<<"List2 contents\n";
   // std::cout<<listPtr2<<std::endl;
   for(int i=1; i <= listPtr2->getLength(); i++) {
     std::cout << listPtr2->getEntry(i) <<  " ";
   }
   std::cout << std::endl;



} // end listTester

int main()
{
   char a;
   std::cout<<"Enter A for ArrayList/ Enter L for LinkedList\n";
   std::cin>>a;
   if (a == 'l' || a == 'L') {


   ListInterface<std::string>* listPtr = new LinkedList<std::string>();
   ListInterface<std::string>* listPtr2 = new LinkedList<std::string>();
   ListInterface<std::string>* listPtr3 = new LinkedList<std::string>();

   listTester(listPtr, listPtr2);
   listPtr3 = (*listPtr) + listPtr2;
   std::cout<<"NEW LIST CONCAT\n";
   // std::cout<<listPtr3<<std::endl;
   for(int i=1; i <= listPtr3->getLength(); i++) {
     std::cout << listPtr3->getEntry(i) <<  " ";
   }
   std::cout << std::endl;

   }
   else {
   	ListInterface<std::string>* listPtr = new ArrayList<std::string>();
   	ListInterface<std::string>* listPtr2 = new ArrayList<std::string>();
   	ListInterface<std::string>* listPtr3 = new ArrayList<std::string>();
    listTester(listPtr, listPtr2);
   listPtr3 = (*listPtr) + listPtr2;
   std::cout<<"NEW LIST CONCAT\n";
   std::cout<<listPtr3<<std::endl;
   }

   return 0;
}  // end main
