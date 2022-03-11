

#include <iostream>

#include "list.h"

void Push_Size_TEST()
{
  lab618::CSingleLinkedList<int> list;
  int one = 1;
  int two = 2;
  int three = 3;
  std::cout << "Size " << list.getSize() << std::endl; // 0
  list.pushBack(one);
  std::cout << "Size " << list.getSize() << std::endl; // 1
  list.pushBack(two);
  list.pushFront(three);
  std::cout << "Size " << list.getSize() << std::endl;           // 3
  std::cout << list.popFront() << " " << list.popFront() << " "; // 3 1
  std::cout << "Size " << list.getSize() << std::endl;           // 1
  list.pushFront(one);
  std::cout << list.popFront() << " " << list.popFront() << " "; // 1 2
}

void Clear_TEST()
{
  lab618::CSingleLinkedList<int> list;
  std::cout << "Size " << list.getSize() << std::endl; // 0
  list.clear();
  std::cout << "Size " << list.getSize() << std::endl; // 0

  int one = 1;
  int two = 2;
  int three = 3;
  list.pushBack(one);
  list.pushBack(two);
  list.pushFront(three);
  std::cout << "Size " << list.getSize() << std::endl; // 3
  list.clear();
  std::cout << "Size after clear " << list.getSize() << std::endl; // 0
}

void CycleErase_TEST()
{
  lab618::CSingleLinkedList<int> list;
  int one = 1;
  int two = 2;
  int three = 3;

  list.pushBack(two);
  list.pushBack(one);
  list.pushBack(two);
  list.pushBack(two);
  list.pushBack(three);
  list.pushBack(two);

  std::cout << "LIST: ";
  for (lab618::CSingleLinkedList<int>::CIterator it = list.begin();
       it.isValid(); ++it)
  {
    std::cout << it.getData() << " ";
  }
  std::cout << std::endl; // 2 1 2 2 3 2

  for (lab618::CSingleLinkedList<int>::CIterator it = list.begin();
       it.isValid(); ++it)
  {
    if (it.getData() == 2)
    {
      list.erase(it);
    }
  }

  std::cout << "LIST without 2: ";
  for (lab618::CSingleLinkedList<int>::CIterator it = list.begin();
       it.isValid(); ++it)
  {
    std::cout << it.getData() << " ";
  }
  std::cout << std::endl; // 1 3
}

void BorderCases_TEST()
{
  lab618::CSingleLinkedList<int> list;
  int one = 1;
  int two = 2;
  int three = 3;

  list.pushBack(two);
  lab618::CSingleLinkedList<int>::CIterator it = list.begin();
  std::cout << it.getData() << std::endl; // 2

  list.erase(it);
  std::cout << list.getSize() << std::endl; // 0

  list.pushBack(one);
  list.pushBack(two);
  std::cout << "LIST: ";
  for (lab618::CSingleLinkedList<int>::CIterator it = list.begin();
       it.isValid(); ++it)
  {
    std::cout << it.getData() << " ";
  }
  std::cout << std::endl; // 1 2

  it = list.begin();
  ++it;
  list.erase(it);
  std::cout << "LIST: ";
  for (lab618::CSingleLinkedList<int>::CIterator it = list.begin();
       it.isValid(); ++it)
  {
    std::cout << it.getData() << " ";
  }
  std::cout << std::endl; // 1
}

void CDualLinkedList_TEST()
{
  lab618::CDualLinkedList<int> list;
  int one = 1;
  int two = 2;
  int three = 3;

  list.pushBack(one);
  list.pushBack(two);
  list.pushBack(three);
  std::cout << "LIST: ";
  for (lab618::CDualLinkedList<int>::CIterator it = list.begin(); it.isValid();
       ++it)
  {
    std::cout << it.getData() << " ";
  }
  std::cout << std::endl; // 1 2 3

  std::cout << "The same LIST, but reversed: ";
  for (lab618::CDualLinkedList<int>::CIterator it = list.end(); it.isValid();
       --it)
  {
    std::cout << it.getData() << " ";
  }
  std::cout << std::endl; // 3 2 1

  std::cout << "Size " << list.getSize() << std::endl; // 3
  list.clear();
  std::cout << "Size " << list.getSize() << std::endl; // 0

  list.pushFront(one);
  list.pushFront(two);
  list.pushFront(three);
  std::cout << "LIST: ";
  for (lab618::CDualLinkedList<int>::CIterator it = list.begin(); it.isValid();
       ++it)
  {
    std::cout << it.getData() << " ";
  }
  std::cout << std::endl; // 3 2 1

  std::cout << list.popBack() << " " << list.popFront() << " " << list.popBack()
            << " ";
  list.pushBack(one);
  std::cout << list.popFront() << std::endl; // 1 3 2 1
}

struct my_struct
{
  int number = 0;
  std::string str = "";

  my_struct() {}
  my_struct(int _number, std::string _str) : number(_number), str(_str) {}
};

void Struct_TEST()
{
  my_struct one(1, "one");
  my_struct two(2, "two");
  my_struct three(3, "three");
  lab618::CSingleLinkedList<my_struct> list_s;
  lab618::CDualLinkedList<my_struct> list_d;

  list_s.pushBack(two);
  list_s.pushBack(three);
  list_s.pushFront(one);
  for (lab618::CSingleLinkedList<my_struct>::CIterator it = list_s.begin();
       it.isValid(); ++it)
  {
    std::cout << it.getData().number << " ";
    list_s.erase(it);
  }
  std::cout << std::endl; // 1 2 3
  std::cout << "SIZE: " << list_s.getSize() << std::endl;

  list_d.pushBack(two);
  list_d.pushBack(three);
  list_d.pushFront(one);
  for (lab618::CDualLinkedList<my_struct>::CIterator it = list_d.end();
       it.isValid(); --it)
  {
    std::cout << it.getData().number << " ";
    list_d.eraseAndNext(it);
  }
  std::cout << std::endl; // 3 2 1
  std::cout << "SIZE: " << list_s.getSize() << std::endl;
}

int main()
{
  std::cout << std::endl
            << "Push_Size_TEST" << std::endl;
  Push_Size_TEST();

  std::cout << std::endl
            << "Clear_TEST" << std::endl;
  Clear_TEST();

  std::cout << std::endl
            << "CycleErase_TEST" << std::endl;
  CycleErase_TEST();

  std::cout << std::endl
            << "BorderCases_TEST" << std::endl;
  BorderCases_TEST();

  std::cout << std::endl
            << "CDualLinkedList_TEST" << std::endl;
  CDualLinkedList_TEST();

  std::cout << std::endl
            << "Struct_TEST" << std::endl;
  Struct_TEST();
  return 0;
}
