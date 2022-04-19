#include <iostream>

#include "lab09.h"

using namespace std;

// REQUIRES: n >= 1
// EFFECTS: Prints the hailstone sequence starting at n
// NOTE:    Uses tail recursion
void hailstone(int n) {
    if (n == 1) {
	   cout << n << ' ';
    }
    else if (n % 2 == 0) {
	   cout << n << ' ';
	   hailstone(n / 2);
    }
    else {
	   cout << n << ' ';
	   hailstone(3*n + 1);   
    }
}

// REQUIRES: n >= 1
// EFFECTS: Prints the hailstone sequence starting at n
// NOTE:    Uses iteration
void hailstone_iter(int n) {
    for (; n != 1;) {
	   cout << n << ' ';
	   if (n % 2 == 0) {
		  n /= 2;
	   }
	   else {
		  n = 3 * n + 1;
	   }
    }

    cout << n << ' ';
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses recursion
int count_digits(int n, int digit) {
    if (digit == n) {
	   return 1;
    }
    else if (0 <= n && n < 10) {
	   return 0;
    }
    else if (n % 10 == digit) {
	   return count_digits(n/10, digit) + 1;
    }
    else {
	   return count_digits(n/10, digit) + 0;
    }
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses iteration
int count_digits_iter(int n, int digit) {
    int sum;
    for (sum = 0; n > 10 || digit == n; n /= 10) {
	   if (digit == n) {
		  sum += 1;
		  if (n < 10) { 
			 break;
		  }
	   }
	   if (n % 10 == digit) {
		  sum += 1;
	   }
    }
    return sum;
}

// REQUIRES 0 <= digit <= 9, n >= 0
// EFFECTS: Returns count + the number of times digit appears in n
// NOTE:    Uses tail recursion
static int count_digits_helper(int n, int digit, int count) {
    if (digit == n) {
	   return count + 1;
    }
    else if (0 <= n && n < 10) {
	   return count;
    }
    else if (n % 10 == digit) {
	   return count_digits_helper(n / 10, digit, ++count);
    }
    else {
	   return count_digits_helper(n / 10, digit, count);
    }
}

// REQUIRES: 0 <= digit <= 9, n >= 0
// EFFECTS: Returns the number of times digit appears in n
// NOTE:    Uses tail recursion
int count_digits_tail(int n, int digit) {
    return count_digits_helper(n, digit, 0);
}
