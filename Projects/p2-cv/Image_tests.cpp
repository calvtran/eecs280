// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_image_init_is_basic) {
    Image *img = new Image;
    Image *img_expect = new Image;
    
    const Pixel white = { 0, 0, 0 };
    const int width = 3;
    const int height = 3;
    Image_init(img_expect, width, height);
    for (int r = 0; r < height; ++r) {
	   for (int c = 0; c < width; ++c) {
		  Image_set_pixel(img_expect, r, c, white);
	   }
    }

    string input = "P3\n3 3\n255\n0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0\n0 0 0 0 0 0 0 0 0\n";
   
    istringstream in_stream(input); 
    Image_init(img, in_stream);

    ASSERT_TRUE( Image_equal(img, img_expect) );

    delete img;
    delete img_expect;
}

TEST(test_image_init_is_edge) {
    Image *img = new Image;

    // A very poorly behaved input PPM.
    string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
    istringstream ss_input(input);
    Image_init(img, ss_input);

    // Should be well behaved when you print it though!
    string output_correct = "P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n";
    ostringstream ss_output;
    Image_print(img, ss_output);
    string actual = ss_output.str();
    ASSERT_EQUAL(actual, output_correct);

    delete img;
}

TEST(test_image_width_and_height) {
    Image *img = new Image;

    const int width = 2;
    const int height = 3;

    Image_init(img, width, height);

    ASSERT_EQUAL(Image_width(img), width);
    ASSERT_EQUAL(Image_height(img), height);

    delete img;
}

TEST(test_set_and_get_pixel) {
    Image *img = new Image;

    const Pixel red = { 255, 0, 0 };
    const Pixel green = { 0, 255, 0 };
    const Pixel blue = { 0, 0, 255 };
    const Pixel black = { 255, 255, 255 };

    Image *img_expect = new Image;
    string input = "P3\n2 2\n255\n255 0 0 0 255 0\n0 0 255 255 255 255";
    istringstream in(input);
    Image_init(img_expect, in);

    // TEST Image_set_pixel
    Image_init(img, 2, 2);
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, black);
    ASSERT_TRUE(Image_equal(img, img_expect));

    // TEST Image_get_pixel
    ASSERT_TRUE( Pixel_equal(Image_get_pixel(img, 0, 0), red) );
    ASSERT_TRUE( Pixel_equal(Image_get_pixel(img, 0, 1), green) );
    ASSERT_TRUE( Pixel_equal(Image_get_pixel(img, 1, 0), blue) );
    ASSERT_TRUE( Pixel_equal(Image_get_pixel(img, 1, 1), black) );

    delete img;
    delete img_expect;
}

TEST(test_image_fill) {
    Image *img = new Image;
    Image *img_expect = new Image;

    const Pixel black = { 0, 0, 0 };

    Image_init(img, 2, 2);
    Image_fill(img, black);

    // Correct image
    Image_init(img_expect, 2, 2);
    Image_set_pixel(img_expect, 0, 0, black);
    Image_set_pixel(img_expect, 0, 1, black);
    Image_set_pixel(img_expect, 1, 0, black);
    Image_set_pixel(img_expect, 1, 1, black);

    ASSERT_TRUE(Image_equal(img, img_expect));

    delete img;
    delete img_expect;
}


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
