// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

TEST(test_empty_tree) {
    BinarySearchTree <int> tree;

    // Test when empty
    ASSERT_TRUE(tree.empty());

    // Test when NOT empty
    tree.insert(0);
    ASSERT_FALSE(tree.empty());
}

TEST(test_size_tree) {
    BinarySearchTree <int> tree;

    // Test when empty
    ASSERT_EQUAL(tree.size(), 0u);

    // Test with one element
    tree.insert(5);
    ASSERT_EQUAL(tree.size(), 1u);

    // Test with all nodes going left	    5
    tree.insert(3);				 //	   3
    tree.insert(1);				 //	  1
    ASSERT_EQUAL(tree.size(), 3u);

    // Test with nodes on both sides	    5
    tree.insert(7);				 //	   3 7
    tree.insert(9);				 //	  1   9
    ASSERT_EQUAL(tree.size(), 5u);

    // Test with MOAR nodes	    	          5
    tree.insert(4);				 //	  3     7 
    tree.insert(8);				 //	 1 4   8 9
    ASSERT_EQUAL(tree.size(), 7u);

    // Test with all nodes going right
    BinarySearchTree <int> tree2;
    tree2.insert(1);			 //	  1
    tree2.insert(5);			 //	   5
    tree2.insert(9);			 //	    9
    ASSERT_EQUAL(tree2.size(), 3u);

    // Moar test uwu
    tree2.insert(6);			 //	  1
    tree2.insert(7);			 //	   5
    tree2.insert(8);			 //	    9
							 //	   6
							 //	    7
							 //	     8
    ASSERT_EQUAL(tree2.size(), 6u);
}

TEST(test_height_tree) {
    BinarySearchTree <int> tree;

    // Test empty
    ASSERT_EQUAL(tree.height(), 0u);

    // Test 1 element
    tree.insert(5);
    ASSERT_EQUAL(tree.height(), 1u);

    // Test with elements on left and right
    tree.insert(3);					//	 5
			 					//   3
    ASSERT_EQUAL(tree.height(), 2u);

    tree.insert(7);					//	  5
			 					//   3   7
    ASSERT_EQUAL(tree.height(), 2u);

    // Test with one more element on left
    tree.insert(1);	    //	   5
			 	    //	 3   7
				    //   1
    ASSERT_EQUAL(tree.height(), 3u);

    // Test with one more element on right
    tree.insert(9);	    //	   5
    tree.insert(8);	    //	 3   7
			 	    //   1	  9
				    //		 8
    ASSERT_EQUAL(tree.height(), 4u);

    // Test with full tree		  5
    tree.insert(-2);	//	    3     7 
    tree.insert(-1);	//	  1	       9
			 	    //   -2		 8
				    //     -1
    ASSERT_EQUAL(tree.height(), 5u);
}

TEST(test_copy_tree) {
    BinarySearchTree <int> tree;

    // Test copy empty tree
    BinarySearchTree <int> tree_copy_empty(tree);
    ASSERT_TRUE(tree_copy_empty.empty());

    // Test copy filled tree
    tree.insert(2);	    //   2
    tree.insert(1);	    //  1 3
    tree.insert(3);

    BinarySearchTree <int> tree_copy(tree);
    BinarySearchTree<int>::Iterator it = tree.begin();    // 1
    BinarySearchTree<int>::Iterator it_copy = tree_copy.begin();
    for (int i = 1; i <= 3; ++i, ++it, ++it_copy) {
	   ASSERT_EQUAL(*it, *it_copy);		// Same datum
	   ASSERT_NOT_EQUAL(&(*it), &(*it_copy));	// Diff addresses
	   ASSERT_NOT_EQUAL(it, it_copy);	// Diff addresses
    }

    // Test copy filled tree (Advanced)
    BinarySearchTree <int> tree2;
    tree2.insert(5);	    //	    5
    tree2.insert(3);	    //    3       7
    tree2.insert(7);	    //  2	  4	 6	8
    tree2.insert(2);
    tree2.insert(4);
    tree2.insert(6);
    tree2.insert(8);

    BinarySearchTree <int> tree_copy2(tree2);
    BinarySearchTree<int>::Iterator it2 = tree2.begin();
    BinarySearchTree<int>::Iterator it2_copy = tree_copy2.begin();
    for (int i = 2; i <= 8; ++i, ++it2, ++it2_copy) {
	   ASSERT_EQUAL(*it2, *it2_copy);		// Same datum
	   ASSERT_NOT_EQUAL(&(*it2), &(*it2_copy));	// Diff addresses
	   ASSERT_NOT_EQUAL(it2, it2_copy);	// Diff addresses
    }
}

TEST(test_find_tree_node) {
    BinarySearchTree<int> tree;

    // Test find empty
    BinarySearchTree<int>::Iterator none;
    ASSERT_EQUAL(tree.find(5), none);

    // Test find full
    tree.insert(5);	    //	    5
    tree.insert(3);	    //    3       7
    tree.insert(7);	    //  1	  4	 6	9
    tree.insert(1);
    tree.insert(4);
    tree.insert(6);
    tree.insert(9);

    BinarySearchTree<int>::Iterator it = tree.min_element();
    for (int i = 1; i <= 9; ++i) {
	   if (i == 2 || i == 8) {
		  ASSERT_EQUAL(tree.find(i), none);   // Check when not found
	   }
	   else {
		  ASSERT_EQUAL(*(tree.find(i)), i);   // Check datum
		  ASSERT_EQUAL(tree.find(i), it);	   // Check node
		  ++it;
	   }
    }
}

TEST(test_insert_tree) {
    BinarySearchTree <int> tree;
    
    // Test insert into empty
    tree.insert(5);
    BinarySearchTree<int>::Iterator it = tree.begin();
    ASSERT_EQUAL(*it, 5);
    ASSERT_EQUAL(tree.size(), 1u);

    // Test insert left and right
    tree.insert(1);	    //    5
    tree.insert(9);	    //  1   9
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.find(1), tree.min_element());
    ASSERT_EQUAL(tree.find(9), tree.max_element());
    ASSERT_EQUAL(tree.size(), 3u);

    // Test insert right in left sub-tree
    tree.insert(3);	    //	5
				    //  1	  9
				    //   3
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.find(3), ++(tree.min_element()));
    ASSERT_EQUAL(tree.size(), 4u);

    // Test insert left in right sub-tree
    tree.insert(7);	    //	5
				    //  1	  9
				    //   3 7
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.find(7), tree.min_greater_than(5));
    ASSERT_EQUAL(tree.size(), 5u);

    // Test insert sub sub tree
    tree.insert(2);	    //	   5
    tree.insert(8);	    //	1	 9
				    //      3 7  
				    //	 2   8
    ASSERT_TRUE(tree.check_sorting_invariant());
    ASSERT_EQUAL(tree.find(2), ++(tree.min_element()));
    ASSERT_EQUAL(tree.find(8), ++(tree.find(7)));
    ASSERT_EQUAL(tree.size(), 7u);
}

TEST(test_tree_min_element) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator none;

    // Test empty tree
    ASSERT_EQUAL(tree.min_element(), none);

    // Test w/ one element
    tree.insert(9);
    ASSERT_EQUAL(*(tree.min_element()), 9);
    ASSERT_EQUAL(tree.min_element(), tree.begin());

    // Test w/ no left subtree
    tree.insert(11);	    //  9
    tree.insert(10);	    //	11
    tree.insert(12);	    //  10  12

    ASSERT_EQUAL(*(tree.min_element()), 9);
    ASSERT_EQUAL(tree.min_element(), tree.find(9));

    //Test w/ left subtree
    tree.insert(0); 	    //	    9
    tree.insert(-2);	    //	0	   11
    tree.insert(-1);	    // -2  -1   10  12 

    ASSERT_EQUAL(*(tree.min_element()), -2);
    ASSERT_EQUAL(tree.min_element(), tree.find(-2));
}

TEST(test_tree_max_element) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator none;

    // Test empty tree
    ASSERT_EQUAL(tree.max_element(), none);

    // Test w/ one element
    tree.insert(0);
    ASSERT_EQUAL(*(tree.max_element()), 0);
    ASSERT_EQUAL(tree.max_element(), tree.begin());

    // Test w/ no right subtree
    tree.insert(-2);	    //	  0
    tree.insert(-3);	    //   -2
    tree.insert(-1);	    // -3  -1

    ASSERT_EQUAL(*(tree.max_element()), 0);
    ASSERT_EQUAL(tree.max_element(), tree.find(0));

    //Test w/ right subtree
    tree.insert(50);	    //	   0
    tree.insert(100);	    //   -2     50
    tree.insert(10);	    // -3 -1  10  100

    ASSERT_EQUAL(*(tree.max_element()), 100);
    ASSERT_EQUAL(tree.max_element(), tree.find(100));
}

TEST(test_tree_min_greater_than) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int>::Iterator none;

    // Test empty tree
    ASSERT_EQUAL(tree.min_greater_than(5), none);

    // Test w/ one element
    tree.insert(5);
    ASSERT_EQUAL(*(tree.min_greater_than(4)), 5);
    ASSERT_EQUAL(tree.min_greater_than(4), tree.find(5));
    ASSERT_EQUAL(tree.min_greater_than(5), none);

    // Test w/ no left subtree
    tree.insert(7);	    //    5
    tree.insert(6);	    //  	  7
    tree.insert(9);	    //	 6 9

    for (int i = 0; i <= 7; ++i) {
	   if (i < 5) {
		  ASSERT_EQUAL(*(tree.min_greater_than(i)), 5);
		  ASSERT_EQUAL(tree.min_greater_than(i), tree.find(5));
	   } 
	   else if (i == 7) {
		  ASSERT_EQUAL(*(tree.min_greater_than(i)), i + 2);
		  ASSERT_EQUAL(tree.min_greater_than(i), tree.find(i + 2));
	   }
	   else {
		  ASSERT_EQUAL(*(tree.min_greater_than(i)), i + 1);
		  ASSERT_EQUAL(tree.min_greater_than(i), tree.find(i + 1));
	   }
    }

    // Test if no num greater than val
    ASSERT_EQUAL(tree.min_greater_than(9), none);

    //Test w/ left subtree
    tree.insert(3);	    //	   5
    tree.insert(1);	    //	3	 7
    tree.insert(4);	    //   1 4	6 9 

    ASSERT_EQUAL(*(tree.min_greater_than(3)), 4);
    ASSERT_EQUAL(tree.min_greater_than(3), tree.find(4));
    for (int i = 0; i <= 4; ++i) {
	   if (i == 1) {
		  ASSERT_EQUAL(*(tree.min_greater_than(i)), i + 2);
		  ASSERT_EQUAL(tree.min_greater_than(i), tree.find(i + 2));
	   }
	   else {
		  ASSERT_EQUAL(*(tree.min_greater_than(i)), i + 1);
		  ASSERT_EQUAL(tree.min_greater_than(i), tree.find(i + 1));
	   }
    }
}

TEST(test_check_sorting_invariant) {
    BinarySearchTree<int> tree;

    // Test empty tree
    ASSERT_TRUE(tree.check_sorting_invariant());

    // Test filled tree
    tree.insert(5);	    //	   5
    tree.insert(3);	    //	3	 7
    tree.insert(1);	    //   1 4	6 9
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(9);

    ASSERT_EQUAL(tree.min_element(), tree.find(1));
    ASSERT_EQUAL(tree.max_element(), tree.find(9));
    ASSERT_TRUE(tree.check_sorting_invariant());

    // Test broken invariant
    BinarySearchTree<int> tree2(tree);
    *tree2.max_element() = 2;
	   //	   5
	   //	3	 7
	   //    1 4	6 2 <--
    ASSERT_FALSE(tree2.check_sorting_invariant());

    // Test broken invariant 2
    *tree.min_element() = 8;
	   //  		5
	   //	  3	   7
	   //  --> 8 4	  6 9
    ASSERT_FALSE(tree.check_sorting_invariant());

    // Test broken invariant 3
    *tree.min_greater_than(2) = 5;
    *tree.min_greater_than(6) = 5;
	   //  		5
	   //   --> 5	   5 <--
	   //      1 4	  6 9
    ASSERT_FALSE(tree.check_sorting_invariant());
}

TEST(test_traverse_inorder) {
    BinarySearchTree<int> tree;

    // Test empty tree
    ostringstream output1;
    ostringstream correct1;
    tree.traverse_inorder(output1);
    ASSERT_EQUAL(output1.str(), correct1.str());

    // Test filled tree
    ostringstream output2;

    tree.insert(5);	    //	   5
    tree.insert(3);	    //	3	 7
    tree.insert(1);	    //   1 4	6 9
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(9);

    tree.traverse_inorder(output2);

    ostringstream correct2;	  // 1 3 4 5 6 7 9 
    for (int i = 1; i <= 9; ++i) {
	   if (i != 2 && i != 8) {
		  correct2 << i << " ";
	   }
    }

    ASSERT_EQUAL(output2.str(), correct2.str());
}

TEST(test_traverse_preorder) {
    BinarySearchTree<int> tree;

    // Test empty tree
    ostringstream output1;
    ostringstream correct1;
    tree.traverse_preorder(output1);
    ASSERT_EQUAL(output1.str(), correct1.str());

    // Test filled tree
    ostringstream output2;

    tree.insert(5);	    //	   5
    tree.insert(3);	    //	3	 7
    tree.insert(1);	    //   1 4	6 9
    tree.insert(4);
    tree.insert(7);
    tree.insert(6);
    tree.insert(9);

    tree.traverse_preorder(output2);

    ostringstream correct2;	  // 5 3 1 4 7 6 9 
    correct2 << 5 << " "
	   << 3 << " "
	   << 1 << " "
	   << 4 << " "
	   << 7 << " "
	   << 6 << " "
	   << 9 << " ";

    ASSERT_EQUAL(output2.str(), correct2.str());
}
TEST_MAIN()
