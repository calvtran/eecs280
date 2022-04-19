// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <sstream>

using namespace std;

// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
    Matrix *mat = new Matrix;
    Matrix *mat_expect = new Matrix;

    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, width, height);
    Matrix_init(mat_expect, width, height);

    Matrix_fill(mat, value);

    for (int r = 0; r < height; ++r) {
	   for (int c = 0; c < width; ++c) {
		  ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
	   }
    }

    // Correct Matrix
    for (int r = 0; r < height; ++r) {
	   for (int c = 0; c < width; ++c) {
		  *Matrix_at(mat_expect, r, c) = value;
	   }
    }
    
    ASSERT_TRUE(Matrix_equal(mat, mat_expect));

    delete mat; // delete the Matrix
    delete mat_expect;
}

// Fills a 5x5 Matrix with a value, uses Matrix_print to
// output the width, height, and the contents
// of that Matrix to an output string stream, and then
// checks if it matches the expected output string stream.
TEST(test_matrix_print) {
    Matrix *mat = new Matrix;
    const int width = 3;
    const int height = 5;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 0);

    stringstream expect_out, out;
   
    expect_out << "3 5\n"
	   << "0 0 0 \n"
	   << "0 0 0 \n"
	   << "0 0 0 \n"
	   << "0 0 0 \n"
	   << "0 0 0 \n";

    Matrix_print(mat, out);

    int in, in_expected;

    out >> in;						// "3"
    expect_out >> in_expected;
    ASSERT_EQUAL(in, in_expected);		//Check width
    ASSERT_EQUAL(in, width);

    out >> in;						// "5"
    expect_out >> in_expected;		
    ASSERT_EQUAL(in, in_expected);		//Check height
    ASSERT_EQUAL(in, height);

    for (int r = 0; r < height; ++r) {		    //Check Matrix
	   for (int c = 0; c < width; ++c) {
		  out >> in;					    // "0 0 0 \n"
		  expect_out >> in_expected;
		  ASSERT_EQUAL(in, in_expected);
	   }
    }
    
    delete mat;
}

TEST(test_matrix_print2) {
    Matrix *mat = new Matrix;
    const int width = 3;
    const int height = 3;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 0);

    stringstream out;
    string line1, line2, line3, line4;
    
    Matrix_print(mat, out);

    getline(out, line1);			 // "3 3\n"
    ASSERT_EQUAL(line1[0], '3');
    ASSERT_EQUAL(line1[1], ' ');
    ASSERT_EQUAL(line1[2], '3');

    getline(out, line2);			 // "0 0 0 \n"
    ASSERT_EQUAL(line2[0], '0');
    ASSERT_EQUAL(line2[1], ' ');
    ASSERT_EQUAL(line2[2], '0');
    ASSERT_EQUAL(line2[3], ' ');
    ASSERT_EQUAL(line2[4], '0');
    ASSERT_EQUAL(line2[5], ' ');

    getline(out, line3);			 // "0 0 0 \n"
    ASSERT_EQUAL(line3[0], '0');
    ASSERT_EQUAL(line3[1], ' ');
    ASSERT_EQUAL(line3[2], '0');
    ASSERT_EQUAL(line3[3], ' ');
    ASSERT_EQUAL(line3[4], '0');
    ASSERT_EQUAL(line3[5], ' ');

    getline(out, line4);			 // "0 0 0 \n"
    ASSERT_EQUAL(line4[0], '0');
    ASSERT_EQUAL(line4[1], ' ');
    ASSERT_EQUAL(line4[2], '0');
    ASSERT_EQUAL(line4[3], ' ');
    ASSERT_EQUAL(line4[4], '0');
    ASSERT_EQUAL(line4[5], ' ');
    
    delete mat;
}

// Initializes a 3x5 Matrix and checks
// if Matrix_width and Matrix_height
// returns the correct width and height.
TEST(test_matrix_width_and_height) {
    // TEST 1: Basic
    Matrix *mat = new Matrix;

    const int width = 5;
    const int height = 3;
    Matrix_init(mat, width, height);

    ASSERT_EQUAL(Matrix_width(mat), width);
    ASSERT_EQUAL(Matrix_height(mat), height);

    // TEST 2: Stress
    const int width2 = 500;
    const int height2 = 500;
    Matrix_init(mat, width2, height2);

    ASSERT_NOT_EQUAL(Matrix_width(mat), width);
    ASSERT_NOT_EQUAL(Matrix_height(mat), height);
    ASSERT_EQUAL(Matrix_width(mat), width2);
    ASSERT_EQUAL(Matrix_height(mat), height2);

    delete mat;
}

// Fills a 5x5 Matrix with a value,
// points to an element in the Matrix,
// and then checks if Matrix_row returns the correct row
// and if 'Matrix_column' returns the correct column
// of which the element is located.
TEST(test_matrix_row_and_column) {
    // TEST 1: Basic
    Matrix *mat = new Matrix;
    Matrix_init(mat, 5, 7);
    Matrix_fill(mat, 0);

    const int row = 2;
    const int col = 3;
    const int value = 25;
    int *const ptr = Matrix_at(mat, row, col);	// Contant ptr to row 2, col 3
    *Matrix_at(mat, row, col) = value;			// set value at ptr to 25

    ASSERT_EQUAL( Matrix_row(mat, ptr), row );
    ASSERT_EQUAL( Matrix_column(mat, ptr), col );
    ASSERT_EQUAL(*Matrix_at(mat, Matrix_row(mat, ptr), Matrix_column(mat, ptr))
	   , value);

    // TEST 2: Edge
    Matrix *mat2 = new Matrix;
    Matrix_init(mat2, 500, 500);
    Matrix_fill(mat2, 0);

    const int row2 = 499;
    const int col2 = 499;
    int *const ptr2 = Matrix_at(mat2, row2, col2);  // Const ptr to last row, last col
    *Matrix_at(mat2, row2, col2) = value;		  // set value at ptr to 25

    int *const ptr3 = Matrix_at(mat2, 0, 0);		  // Const ptr to row 0, col 0
    *Matrix_at(mat2, 0, 0) = value;			  // set value at ptr to 25

    ASSERT_EQUAL( Matrix_row(mat2, ptr2), row2);
    ASSERT_EQUAL( Matrix_column(mat2, ptr2), col2);
    ASSERT_EQUAL(*Matrix_at(mat2, Matrix_row(mat2, ptr2), Matrix_column(mat2, ptr2))
	   , value);

    ASSERT_EQUAL(Matrix_row(mat2, ptr3), 0);
    ASSERT_EQUAL(Matrix_column(mat2, ptr3), 0);
    ASSERT_EQUAL(*Matrix_at(mat2, Matrix_row(mat2, ptr3), Matrix_column(mat2, ptr3))
	   , value);

    delete mat;
    delete mat2;
}

// Fills a 5x5 Matrix with a value,
// sets the elements on outer border of the Matrix to a different value,
// and then compares it with the expected Matrix to see 
// if that value is in the correct spots.
TEST(test_fill_border) {
    Matrix *mat = new Matrix;
    Matrix *mat_expect = new Matrix;

    const int value = 0;
    const int border_value = 1;
    Matrix_init(mat, 5, 5);
    Matrix_fill(mat, value);

    Matrix_fill_border(mat, border_value);

    // Correct Matrix
    Matrix_init(mat_expect, 5, 5);
    Matrix_fill(mat_expect, value);
    for (int c = 0; c < 5; ++c) {	 // Fill top row
	   *Matrix_at(mat_expect, 0, c) = border_value;
    }
    for (int r = 0; r < 5; ++r) {	 // Fill left col
	   *Matrix_at(mat_expect, r, 0) = border_value;
    }
    for (int r = 0; r < 5; ++r) {	 // Fill right col
	   *Matrix_at(mat_expect, r, 4) = border_value;
    }
    for (int c = 0; c < 5; ++c) {	 // Fill bottom row
	   *Matrix_at(mat_expect, 4, c) = border_value;
    }

    ASSERT_TRUE(Matrix_equal(mat, mat_expect));

    delete mat;
    delete mat_expect;
}

TEST(test_fill_border_edge) {
    Matrix *mat = new Matrix;
    Matrix *mat_expect = new Matrix;

    const int value = 0;
    const int border_value = 1;
    Matrix_init(mat, 3, 500);
    Matrix_fill(mat, value);

    Matrix_fill_border(mat, border_value);

    // Correct Matrix
    Matrix_init(mat_expect, 3, 500);
    Matrix_fill(mat_expect, value);
    for (int r = 0; r < 500; ++r) {	 // Fill left col
	   *Matrix_at(mat_expect, r, 0) = border_value;
    }
    *Matrix_at(mat_expect, 0, 1) = border_value;
    for (int r = 0; r < 500; ++r) {	 // Fill right col
	   *Matrix_at(mat_expect, r, 2) = border_value;
    }
    *Matrix_at(mat_expect, 499, 1) = border_value;

    ASSERT_TRUE(Matrix_equal(mat, mat_expect));

    delete mat;
    delete mat_expect;
}

TEST(test_fill_border_edge2) {
    Matrix *mat = new Matrix;
    Matrix *mat_expect = new Matrix;

    const int border_value = 1;
    Matrix_init(mat, 2, 2);

    Matrix_fill_border(mat, border_value);

    // Correct Matrix
    Matrix_init(mat_expect, 2, 2);
    *Matrix_at(mat_expect, 0, 0) = border_value;
    *Matrix_at(mat_expect, 0, 1) = border_value;
    *Matrix_at(mat_expect, 1, 0) = border_value;
    *Matrix_at(mat_expect, 1, 1) = border_value;

    ASSERT_TRUE(Matrix_equal(mat, mat_expect));

    delete mat;
    delete mat_expect;
}

// Fills a 5x5 Matix with a value, sets a different 
// greater value somewhere on the the Matrix,
// and then checks if 'Matrix_max' returns that greater value.
TEST(test_matrix_max) {
    Matrix *mat = new Matrix;

    // TEST 1: Basic
    const int width = 5;
    const int height = 5;
    Matrix_init(mat, width, height);
    const int value = 0;
    const int max_value = 1;

    // TEST 1a: All 0
    Matrix_fill(mat, value);				   // Fill w/ 0
    ASSERT_EQUAL(Matrix_max(mat), value);	   // Max = 0

    // TEST 1b: One value
    *Matrix_at(mat, 2, 2) = max_value;		   // 1 @ row 2, col 2
    ASSERT_EQUAL(Matrix_max(mat), max_value);   // Max = 1

    // TEST 2: Edge
    Matrix_init(mat, 500, 500);
    Matrix_fill(mat, value);				   // Fill w/ 0
    *Matrix_at(mat, 499, 499) = max_value;	   // 1 @ last row, last col
    ASSERT_EQUAL(Matrix_max(mat), max_value);   // Max = 1

    // TEST 3: Negative ints
    const int neg_value = -100;
    const int max_neg_value = -1;
    Matrix_fill(mat, neg_value);				  // Fill w/ -100
    *Matrix_at(mat, 2, 2) = max_neg_value;		  // -1 @ row 2, col 2
    ASSERT_EQUAL(Matrix_max(mat), max_neg_value);	  // Max = -1

    delete mat;
}

// Fills a 5x5 Matrix with a value,
// sets a different lesser value somewhere on the Matrix,
// and then checks if 'Matrix_column_of_min_value_in_row' 
// returns the appropriate column of which that value is located 
// and if 'Matrix_min_value_in_row' returns its value.
TEST(test_matrix_column_and_value_of_min_value_in_row) {
    // TEST 1: Basic
    Matrix *mat = new Matrix;

    const int width = 5;
    const int height = 5;
    Matrix_init(mat, width, height);
    const int value = 1;
    const int min_value = 0;
    const int row_2 = 2;

    const int col_2 = 2;

    Matrix_fill(mat, value);						 // Fill w/ 1
    *Matrix_at(mat, row_2, col_2) = min_value;		 // 0 @ row 2, col 2
    ASSERT_EQUAL( Matrix_column_of_min_value_in_row(mat, row_2, 0, height), 
	   col_2);
    ASSERT_EQUAL( Matrix_min_value_in_row(mat, row_2, 0, height), min_value);

    // TEST 2: Edge (Same val across row)
    Matrix_fill(mat, value);					 // Fill w/ 1
    *Matrix_at(mat, row_2, 0) = min_value;		 // 0 @ row 2, col 0 (min)
    *Matrix_at(mat, row_2, 1) = min_value;		 // 0 @ row 2, col 1
    *Matrix_at(mat, row_2, 2) = min_value;		 // 0 @ row 2, col 2
    *Matrix_at(mat, row_2, 3) = min_value;		 // 0 @ row 2, col 3
    *Matrix_at(mat, row_2, 4) = min_value;		 // 0 @ row 2, col 4
    ASSERT_EQUAL( Matrix_column_of_min_value_in_row(mat, row_2, 0, height), 0);
    ASSERT_EQUAL( Matrix_min_value_in_row(mat, row_2, 0, height), min_value);

    // TEST 3: Edge (inclusive and exclusive)
    Matrix_fill(mat, value);						 // Fill w/ 1
    *Matrix_at(mat, row_2, 0) = min_value - 1;		 // -1 @ row 2, col 0 (included, min)
    *Matrix_at(mat, row_2, 4) = min_value - 2;		 // -1 @ row 2, col 4 (excluded)
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, row_2, 0, 4), 0);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, row_2, 0, 4), min_value - 1);

    // TEST 4: Edge (Last row)
    Matrix_init(mat, 500, 500);
    const int row_499 = 499;
    Matrix_fill(mat, value);					  // Fill w/ 1
    *Matrix_at(mat, row_499, 499) = min_value;	  // 0 @ row 499, col 499
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, row_499, 0, 500), 499);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, row_499, 0, 500), min_value);
    
    // TEST 5: Negative ints
    const int neg_value = -10;
    const int min_neg_value = -100;
    const int row_3 = 3;

    const int col_of_min_neg = 3;

    Matrix_fill(mat, neg_value);						    // Fill w/ -10
    *Matrix_at(mat, row_3, col_of_min_neg) = min_neg_value;	    // -100 @ row 3, col 3
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, row_3, 0, height),
	   col_of_min_neg);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, row_3, 0, height), min_neg_value);

    delete mat;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
