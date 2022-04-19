/* stats_tests.cpp
 *
 * Unit tests for the simple statistics library
 * Project UID 5366c7e2b77742d5b2142097e51561a5
 *
 * EECS 280 Project 1
 *
 * Protip #1: Write tests for the functions BEFORE you implement them!  For
 * example, write tests for median() first, and then write median().  It sounds
 * like a pain, but it helps make sure that you are never under the illusion
 * that your code works when it's actually full of bugs.
 *
 * Protip #2: Instead of putting all your tests in main(),  put each test case
 * in a function!
 */


#include "stats.h"
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>
using namespace std;

void test_summarize();
void test_count();
void test_sum();
void test_mean();
void test_median();
void test_mode();
void test_min();
void test_max();
void test_stdev();
void test_percentile();

// Add prototypes for you test functions here.

int main()
{
  test_summarize();
  test_count();
  test_sum();
  test_mean();
  test_median();
  test_mode();
  test_min();
  test_max();
  test_stdev();
  test_percentile();

  return 0;
}

void test_summarize()
{
    cout << "test_summarize" << endl;

    vector<double> data;
    data.push_back(17);
    data.push_back(2);
    data.push_back(1);
    data.push_back(2);
    data.push_back(2);
    data.push_back(1);

    vector<vector<double> > v{
	   { 1, 2 },
	   { 2, 3 },
	   { 17, 1 } 
    };
    
    assert(summarize(data) == v);

    cout << "PASS!\n\n";
}

void test_count()
{
    cout << "test_count" << endl;

    vector<double> data;
    data.push_back(17);
    data.push_back(2);
    data.push_back(1);
    data.push_back(2);
    data.push_back(2);
    data.push_back(1);

    assert(count(data)==6);

    cout << "PASS!\n\n";
}

void test_sum()
{
  cout << "test_sum" << endl;

  vector<double> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);

  assert(sum(data) == 6);

  cout << "PASS!\n\n";
}

void test_mean()
{
    cout << "test_mean" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);

    assert(mean(data) == 2);

    cout << "PASS!\n\n";
}

void test_median()
{
    cout << "test_median" << endl;

    vector<double> data;
    data.push_back(1);
    data.push_back(5);
    data.push_back(2);
    data.push_back(8);
    data.push_back(7);
    assert(median(data) == 5);

    cout << "Odd n PASS!\n";

    vector<double> data2;
    data2.push_back(1);
    data2.push_back(6);
    data2.push_back(2);
    data2.push_back(8);
    data2.push_back(7);
    data2.push_back(2);
    assert(median(data2) == 4);

    cout << "Even n PASS!\n\n";
}

void test_mode()
{
    cout << "test_mode" << endl;
    assert(mode({ 1,2,3 }) == 1);
    assert(mode({ 1,1,2,2 }) == 1);
    assert(mode({ 2,2,1,1 }) == 1);
    assert(mode({ 1,2,1,2 }) == 1);
    assert(mode({ 1,2,1,2,2 }) == 2);

    cout << "PASS!\n\n";
}

void test_min()
{
    cout << "test_min" << endl;

    vector<double> data;
    data.push_back(24);
    data.push_back(15);
    data.push_back(9);
    data.push_back(5);
    data.push_back(3);
    data.push_back(2);

    assert(min(data)==2);

    cout << "PASS!\n\n";
}

void test_max()
{
    cout << "test_max" << endl;

    vector<double> data;
    data.push_back(24);
    data.push_back(15);
    data.push_back(9);
    data.push_back(5);
    data.push_back(3);
    data.push_back(2);

    assert(max(data) == 24);

    cout << "PASS!\n\n";
}

void test_stdev()
{
    cout << "test_stdev" << endl;
    vector<double> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(4);
    data.push_back(5);

    assert(stdev(data) == sqrt(10.0 / 4.0));
    
    cout << "PASS!\n\n";
}

void test_percentile()
{
    cout << "test_percentile" << endl;

    vector<double> data;
    data.push_back(15);
    data.push_back(20);
    data.push_back(35);
    data.push_back(40);
    data.push_back(50);

    assert(percentile(data, 0.4) == 29);

    cout << "PASS!\n\n";
}
