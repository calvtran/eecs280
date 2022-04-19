#include "stats.h"
#include "p1_library.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    string column, filename;

    cout << "enter a filename" << endl;
    cin >> filename;
    cout << "enter a column name" << endl;
    cin >> column;
    cout << "reading column " << column << " from "
	   << filename << endl;

    vector<double> data = extract_column(filename, column);

    cout << "Summary (value: frequency)" << endl;
    vector<vector<double> > summary = summarize(data);
    for (size_t i = 0; i < summary.size(); i++)       
    {
	   for (size_t j = 0; j < summary[i].size(); j++)
	   {
		  if (j == 0) {
			 cout << summary[i][j];
		  }
		  else {
			 cout << ": " << summary[i][j];
		  }
	   }
	   cout << endl;
    }

    cout << endl;
    cout << "count = " << count(data) << endl;
    cout << "sum = " << sum(data) << endl;
    cout << "mean = " << mean(data) << endl;
    cout << "stdev = " << stdev(data) << endl;
    cout << "median = " << median(data) << endl;
    cout << "mode = " << mode(data) << endl;
    cout << "min = " << min(data) << endl;
    cout << "max = " << max(data) << endl;

    for (double p = 0; p <= 1; p += 0.25) {
	   cout << setfill(' ') << setw(3) << (p * 100) << "th ";
	   cout << "percentile = ";
	   cout << percentile(data, p) << endl;
    }

    return 0;
}