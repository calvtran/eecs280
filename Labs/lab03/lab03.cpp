#include <iostream>
#include <fstream>
#include <cstring>
#include "lab03.h"

using namespace std;

// REQUIRES: str1 and str2 point to C-strings
// EFFECTS:  If str1 and str2 contain exactly the same characters, returns 0.
//           Otherwise, return a positive number if the first differing char
//           has a greater value in str1 than in str2 and a negative number in
//           the opposite case (you may NOT call strcmp).
int strcmp_eecs280(const char *str1, const char *str2) {
    const char *ptr1 = str1;
    const char *ptr2 = str2;

    int longest;
    if (strlen(str1) > strlen(str2)) {
	   longest = strlen(str1);
    }
    else if (strlen(str1) < strlen(str2)) {
	   longest = strlen(str2);
    }
    else {
	   longest = strlen(str1);
    }

    for (int i = 0; i < longest; ++i) {
	   if (*(ptr1 + i) != *(ptr2 + i)) {
		  if (*(ptr1 + i) > *(ptr2 + i)) {
			 return 1;
		  }
		  else {	// ptr1 < ptr2
			 return -1;
		  }
	   }
    }
    return 0;
}

// EFFECTS:  Prints "Please enter a word: " to prompt the user to enter a word
//           and then reads a word from cin to be returned. After reading the
//           input, clean up by printing a newline to cout.
string get_user_word() {
    string word;
    cout << "Please enter a word: ";
    cin >> word;
    cout << endl;
    return word;
    return "quit";
}

// EFFECTS: Opens the given file and returns a vector containing all the words
//          in the file. If the file cannot be opened, prints an error message
//          and returns an empty vector.
vector<string> read_words_from_file(const string &filename) {
    vector<string> words;
    string word_in;
    ifstream fin;
    fin.open(filename);
    if (!fin.is_open()) {
	   cout << "Error: Unable to open file!" << endl;
    }
    else {
	   while (fin >> word_in) {
		  words.push_back(word_in);
	   }
    }

    return words;
}

// EFFECTS:  Returns true if the given word is contained in the vector of valid
//           words.
// NOTE:     You MUST use the strcmp_eecs280 function (NOT strcmp).
bool find_word(const char *word, const vector<string> &valid_words) {
    for (size_t i = 0; i < valid_words.size(); ++i) {
	   if (strcmp_eecs280(word, valid_words[i].c_str()) == 0) {
		  return true;
	   }
    }

    return false;
}
