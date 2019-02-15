#include "../cs225/catch/catch.hpp"
#include "tests_helper.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../cs225/PNG.h"
#include "../cs225/HSLAPixel.h"

#include "../List.h"

using namespace cs225;


TEST_CASE("List::insertFront", "[weight=5][part=1]") {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

  REQUIRE(list.size() == 10);
}


//
// Iterator Tests:
//
TEST_CASE("List::begin() returns an iterator to the front of the list", "[weight=1][part=1]") {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

  List<unsigned>::ListIterator iter = list.begin();
  REQUIRE( *iter == 9 );
}

TEST_CASE("List::ListIterator::operator++ advances the iterator (pre-increment)", "[weight=1][part=1]") {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

  List<unsigned>::ListIterator iter = list.begin();
  ++iter;
  REQUIRE( *iter == 8 );
}

TEST_CASE("List::ListIterator::operator++ advances the iterator (post-increment)", "[weight=1][part=1]") {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

  List<unsigned>::ListIterator iter = list.begin();
  iter++;
  iter++;
  REQUIRE( *iter == 7 );
}

TEST_CASE("List::ListIterator::operator++ (post-increment) returns an un-incremented iterator", "[weight=1][part=1]") {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

  List<unsigned>::ListIterator iter = list.begin();
  List<unsigned>::ListIterator pre = iter++;

  REQUIRE( *pre == 9 );
}

TEST_CASE("List::ListIterator::operator-- moves the iterator backwards", "[weight=1][part=1]") {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

  List<unsigned>::ListIterator iter = list.begin();

  iter++;  REQUIRE( *iter == 8 );
  iter++;  REQUIRE( *iter == 7 );
  iter--;  REQUIRE( *iter == 8 );
  iter--;  REQUIRE( *iter == 9 );
}

TEST_CASE("List::ListIterator::operator-- (post-increment) returns an un-incremented iterator", "[weight=1][part=1]") {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertFront(i); }

  List<unsigned>::ListIterator iter = list.begin();

  iter++; // 9 --> 8
  iter++; // 8 --> 7
  List<unsigned>::ListIterator seven = iter--;

  REQUIRE( *seven == 7 );
}

TEST_CASE("List::ListIterator::end is reached", "[weight=1][part=1]") {
  List<unsigned> list;
  list.insertFront(1);
  list.insertFront(2);
  list.insertFront(3);

  List<unsigned>::ListIterator iter = list.begin();
  iter++;
  iter++;
  iter++;

  REQUIRE( (bool)(iter == list.end()) );
}

TEST_CASE("List::ListIterator::end is not ::begin in a non-empty list", "[weight=1][part=1]") {
  List<unsigned> list;
  list.insertFront(1);
  list.insertFront(2);
  list.insertFront(3);

  REQUIRE( (bool)(list.begin() != list.end()) );
}


//
// Non-iterator Tests:
//
TEST_CASE("List::insertBack", "[weight=5][part=1]") {
  List<unsigned> list;
  for (unsigned i = 0; i < 10; i++) { list.insertBack(i); }
  REQUIRE(list.size() == 10);
}

TEST_CASE("List::reverse", "[weight=5][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reserve.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverse();
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reserve.png");
  INFO("Output image `out` saved as actual-reverse.png");

  REQUIRE( out == expected );
}

TEST_CASE("List::reverseNth #1", "[weight=5][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reserveN_1.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverseNth(in.height() * 20);

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reserveN_1.png");
  INFO("Output image `out` saved as actual-reverseN_1.png");

  REQUIRE( out == expected );
}

TEST_CASE("List::reverseNth #2", "[weight=5][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-reserveN_2.png");

  List<HSLAPixel> list = imageToList(in);
  list.reverseNth(in.height() * 61);

  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-reserveN_2.png");
  INFO("Output image `out` saved as actual-reverseN_2.png");

  REQUIRE( out == expected );
}

TEST_CASE("List::waterfall", "[weight=10][part=1]") {
  PNG in;        in.readFromFile("tests/alma.png");
  PNG expected;  expected.readFromFile("tests/expected-waterfall.png");

  List<HSLAPixel> list = imageToList(in);
  list.waterfall();
  PNG out = listToImage(list, in.width(), in.height());
  out.writeToFile("actual-waterfall.png");
  INFO("Output image `out` saved as actual-waterfall.png");

  REQUIRE( out == expected );
}
