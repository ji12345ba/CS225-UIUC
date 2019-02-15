#include "List.h"

int main() {
  //test case

  List<int> testlist, testlist2;
  testlist2.insertBack(1);
  testlist.insertBack(2);
  testlist2.insertBack(3);
  testlist.insertBack(4);
  testlist.insertBack(5);
  testlist2.insertBack(6);
  testlist.insertBack(7);
  testlist.insertBack(8);
  testlist2.insertBack(9);
  testlist.insertBack(10);
  testlist2.insertBack(11);
  testlist.print(cout);
  testlist2.print(cout);
  testlist.mergeWith(testlist2);
  testlist.print(cout);
  testlist2.print(cout);
  return 0;
}
