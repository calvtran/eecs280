#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "processing.h"
using namespace std;
// ./resize.exe horses.ppm horses_400x250.ppm 400 250
int main(int argc, char *argv[]) { 
    ifstream fin;
    ofstream fout;
    string in_file = argv[1];
    string out_file = argv[2];
    fin.open(in_file);
    fout.open(out_file);
    if (!fin.is_open()) {
	   cout << "Error opening file: " << in_file << endl;
	   return 1;
    }
    
    if (!fout.is_open()) {
	   cout << "Error opening file: " << out_file << endl;
	   return 1;
    }

    Image* img = new Image;
    Image_init(img, fin);

    if (argc < 6) {
	   int ds_height = Image_height(img);
	   int ds_width = atoi(argv[3]);

	   if (ds_width < 0 || ds_width > Image_width(img)) {
		  cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH \n"
			 << "WIDTH and HEIGHT must be less than or equal to original"
			 << endl;
		  return 1;
	   }

	   if (argc == 5) {
		  ds_height = atoi(argv[4]);

		  if (ds_height < 0 || ds_height > Image_height(img)) {
			 cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME HEIGHT\n"
				<< "WIDTH and HEIGHT must be less than or equal to original"
				<< endl;
			 return 1;
		  }
	   }

	   seam_carve(img, ds_width, ds_height);
	   Image_print(img, fout);
	   delete img;
	   fin.close();
	   fout.close();
	   return 0;
    }
    else {
	   fin.close();
	   fout.close();
	   return 1;
    }
}