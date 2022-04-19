// Project UID c1f28c309e55405daf00c565d57ff9ad

#include "List.h"
#include "unit_test_framework.h"

using namespace std;

// Add your test cases here

TEST(test_list_empty) {
    List<int> empty_list;

    // Test when empty
    ASSERT_TRUE(empty_list.empty());

    // Test when NOT empty
    empty_list.push_back(0);
    ASSERT_FALSE(empty_list.empty());
}

TEST(test_list_size) {
    List<int> list;

    // Test when empty
    ASSERT_EQUAL(list.size(), 0);

    // Test with 1 element
    list.push_back(1);
    ASSERT_EQUAL(list.size(), 1);

    // Test with 3 elements
    list.push_back(2);
    list.push_back(3);
    ASSERT_EQUAL(list.size(), 3);
}

TEST(test_list_front_back) {
    List<int> list;

    // Test when list has 1 element (front == back) 
    list.push_back(0);	   // {0}
    ASSERT_EQUAL(list.front(), list.back());
    ASSERT_EQUAL(&list.front(), &list.back());

    // Test assignment (1 element)
    list.front() = 1;	   // {1}
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 1);

    list.back() = 2;	   // {2}
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(), 2);

    // Test with 3 elements
    list.push_front(1);
    list.push_back(3);	   // {1, 2, 3}
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 3);
}

TEST(test_list_push_front_back) {
    List<int> list;

    list.push_back(3);   // {3}

    // Simple Test
    list.push_front(2);
    list.push_back(4);
    // {2, 3, 4}
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(), 4);

    list.push_front(1);
    list.push_back(5);
    // {1, 2, 3, 4, 5}
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 5);
}

TEST(test_list_pop_front_back) {
    List<int> list;

    // Test pop_front()
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    // {1, 2, 3}

    list.pop_front();			 // {2, 3}
    ASSERT_EQUAL(list.front(), 2);
    ASSERT_EQUAL(list.back(), 3);
    list.pop_front();			 // {3}
    ASSERT_EQUAL(list.front(), 3);
    ASSERT_EQUAL(list.back(), 3);
    list.pop_front();			 // {}
    ASSERT_TRUE(list.empty());

    // Test pop_back()
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    // {1, 2, 3}

    list.pop_back();			 // {1, 2}
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 2);
    list.pop_back();			 // {1}
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 1);
    list.pop_back();			 // {}
    ASSERT_TRUE(list.empty());
}

TEST(test_list_clear) {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    // {1, 2, 3}

    // Simple Test
    list.clear();
    ASSERT_TRUE(list.empty());
}

TEST(test_list_copy_ctor) {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    // {1, 2, 3}

    List<int> list_copy(list);

    list.pop_back();
    list.pop_back();
    list.pop_back();
    list.push_back(0);
    list.push_back(0);
    list.push_back(0);
    // {0, 0, 0}

    // Test Copy
    ASSERT_EQUAL(list_copy.front(), 1);
    ASSERT_EQUAL(list_copy.back(), 3);

    // Test if deep copy
    ASSERT_NOT_EQUAL(&list_copy.front(), &list.front());
    ASSERT_NOT_EQUAL(&list_copy.back(), &list.back());
}

TEST(test_list_assignment_op) {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    // {1, 2, 3}

    List<int> list2;

    list2.push_back(0);
    list2.push_back(0);
    list2.push_back(0);
    // {0, 0, 0}

    // Test with two different lists
    list2 = list;					// list2 = {1, 2, 3}
    ASSERT_EQUAL(list2.front(), 1);
    ASSERT_EQUAL(list2.back(), 3);

    // Test self assignment
    list = list;
    ASSERT_FALSE(list.empty());

    // Test return type
    List<int> list3;

    list3.push_back(0);
    list3.push_back(0);
    list3.push_back(0);
    // {0, 0, 0}

    ASSERT_EQUAL(&(list2 = list3), &list2);
    list = list2;
    // list = {0, 0, 0}
    ASSERT_EQUAL(list.front(), 0);
    ASSERT_EQUAL(list.back(), 0);
}

TEST(test_iterator_op) {
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    // {1, 2, 3}

    List<int>::Iterator iter1 = list.begin();   // iter1 points to 1
    List<int>::Iterator end = list.end();	   // end is a nullptr
    const List<int>::Iterator null;	 

    // Test end()
    ASSERT_TRUE(end == null);

    // Test operations (!=, ++, *, ==)
    int i = 1;
    for (List<int>::Iterator it = list.begin(); it != end; ++it, ++i, ++iter1) {
	   ASSERT_EQUAL(*it, i);
	   ASSERT_TRUE(iter1 == it);
    }
}

void check_list(List<int> list_in) {
    const int arr[3] = { 1, 2, 3 };
    int i = 0;
    for (List<int>::Iterator it = list_in.begin();
	   it != list_in.end() || i < 3;
	   ++it, ++i) {
	   ASSERT_EQUAL(*it, arr[i]);
    }
}

TEST(test_iterator_erase) {
    List<int> list;
    list.push_back(10);	   // remove
    list.push_back(1);
    list.push_back(2);
    list.push_back(5);	   // remove
    list.push_back(3);
    list.push_back(0);	   // remove
    // {10, 1, 2, 5, 3, 0}
    
    // Test remove at front
    List<int>::Iterator remove10 = list.begin();
    list.erase(remove10);	  // remove 10 from list
    // {1, 2, 5, 3, 0}

    // Test remove at middle
    List<int>::Iterator remove5 = ++(++list.begin());
    list.erase(remove5);		  // remove 5 from list
    // {1, 2, 3, 0}

    // Test remove at back
    List<int>::Iterator remove0 = ++++++list.begin();
    list.erase(remove0);		  // remove 0 from list
    // {1, 2, 3}

    //Check list
    check_list(list);
}

TEST(test_iterator_insert) {
    List<int> list;
    // {}

    // Test insert in empty list
    list.insert(list.begin(), 3);		// insert 3
    // {3}
    ASSERT_EQUAL(list.front(), 3);

    // Test insert (one element already in list)
    list.insert(list.begin(), 1);		// insert 1 before 3
    // {1, 3}
    ASSERT_EQUAL(list.front(), 1);
    ASSERT_EQUAL(list.back(), 3);

    // Test middle insert
    list.insert(++list.begin(), 2);	// insert 2 before 3 (in middle)
    // {1, 2, 3}
    check_list(list);
}

TEST_MAIN()
