// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include "unit_test_framework.h"

using std::pair;
using std::string;
using std::vector;

TEST(map_public_test) {
  // A map stores two types, key and value
  Map<string, double> words;

  // One way to use a map is like an array
  words["hello"] = 1;
  ASSERT_EQUAL(words["hello"], 1);

  // Maps store a std::pair type, which "glues" one key to one value.
  // The CS term is Tuple, a fixed-size heterogeneous container.
  pair<string, double> tuple;
  tuple.first = "world";
  tuple.second = 2;
  words.insert(tuple);
  ASSERT_EQUAL(words["world"], 2);

  // Here's the C++11 way to insert a pair
  words.insert({"pi", 3.14159});
  ASSERT_ALMOST_EQUAL(words["pi"], 3.14159, 0.00001);

  vector<string> expected_keys = { "hello", "pi", "world" };
  vector<double> expected_values = { 1, 3.14159, 2 };
  vector<string> actual_keys;
  vector<double> actual_values;
  // Iterate over map contents using a C++11 range-for loop
  // This is the equivalent without C++11:
  // for (Map<string, double>::Iterator it = words.begin();
  //      it != words.end(); ++it) {
  //   pair<string, double> &p = *it;
  for (auto &p : words) {
    auto word = p.first; //key
    auto number = p.second; //value
    actual_keys.push_back(word);
    actual_values.push_back(number);
  }
  ASSERT_EQUAL(expected_keys, actual_keys);
  ASSERT_EQUAL(expected_values, actual_values);

  // Check if a key is in the map.  find() returns an iterator.
  auto found_it = words.find("pi");
  ASSERT_NOT_EQUAL(found_it, words.end());
  auto &word = (*found_it).first; //key
  auto number = (*found_it).second; //value
  ASSERT_EQUAL(word, "pi");
  ASSERT_ALMOST_EQUAL(number, 3.14159, 0.00001);

  // When using the [] notation. An element not found is automatically created.
  // If the value type of the map is numeric, it will always be 0 "by default".
  ASSERT_EQUAL(words["bleh"], 0.0);
}

TEST(map_copy_ctor) {
    Map<string, int> map;

    Map<string, int> empty_copy(map);
    ASSERT_TRUE(empty_copy.empty());

    map.insert({ "a", 1 });
    map.insert({ "b", 2 });
    map.insert({ "c", 3 });

    Map<string, int> map_copy(map);
    ASSERT_EQUAL(map_copy["a"], 1 );
    ASSERT_EQUAL(map_copy["b"], 2 );
    ASSERT_EQUAL(map_copy["c"], 3 );
}

TEST(map_pair_ctor) {
    pair<string, int> tuple;
    tuple.first = "test";
    tuple.second = 0;

    Map<string, int> map(tuple);

    ASSERT_EQUAL(map["test"], 0);
}

TEST(map_empty) {
    Map<string, int> map;

    ASSERT_TRUE(map.empty());

    map.insert({ "test", 0 });

    ASSERT_FALSE(map.empty());
}

TEST(map_size) {
    Map<int, int> map;

    ASSERT_EQUAL(map.size(), 0u);
    
    for (size_t i = 0; i < 10; i++) {
	   map.insert({ i, i });
	   ASSERT_EQUAL(map.size(), i + 1);
    }
}

TEST(map_find) {
    Map<int, int> map;

    ASSERT_EQUAL(map.find(0), map.end());

    for (int i = 0; i < 10; i++) {
	   if (i != 2 && i != 8) {
		  map.insert({ i, i + 1});
	   }
    }

    auto it = map.begin();
    for (int j = 0; j < 10; ++j) {
	   if (j == 2 || j == 8) {
		  ASSERT_EQUAL(map.find(j), map.end());   // Check when not found
	   }
	   else {
		  ASSERT_EQUAL((*map.find(j)).first, (*it).first);   // Check datum
		  ASSERT_EQUAL((*map.find(j)).second, (*it).second);   // Check datum
		  ASSERT_EQUAL(map.find(j), it);			   // Check node
		  ++it;
	   }
    }
}

TEST(map_sq_brak_op) {
    Map<string, int> map;

    ASSERT_EQUAL(map["new"], 0);

    map["new"] = 1;

    ASSERT_FALSE(map.empty());
    ASSERT_EQUAL(map["new"], 1);
}

TEST(map_insert) {
    Map<int, int> map;

    auto it = map.begin();

    ASSERT_EQUAL(map.insert({ 0, 1 }).second, true);
    ASSERT_EQUAL(map.insert({ 0, 1 }).first, map.find(0));
    ASSERT_EQUAL(map.insert({ 0, 1 }).second, false);
}

TEST_MAIN()
