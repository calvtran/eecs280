#include "stats.h"
#include "p1_library.h"
#include <cassert>
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

vector<vector<double> > summarize(vector<double> v) {
    assert(!v.empty());
    vector<vector<double> > summ;

    sort(v);
    
    for (size_t i = 0; i < v.size(); i++) {
	   double val = v[i];
	   int freq = 0;
	   vector<double> newSumm;
	   summ.push_back(newSumm);
	   summ.at(i).push_back(val);
	   for (size_t j = 0; j < v.size(); j++) {
		  if (v[j] == val) {
			 ++freq;
		  }
	   }
	   summ.at(i).push_back(freq);
    }

    vector<double> temp;	   // Adds a vector {0, 0} after last vector element
    summ.push_back(temp);
    summ.at(summ.size() - 1).push_back(0);
    summ.at(summ.size() - 1).push_back(0);

    vector < vector<double> > summFinal;
    int ind = 0;
    for (size_t i = 0; i < (summ.size() - 1); i++) {
		  if ( (summ[i][0] != summ[i + 1][0]) ) {
			 vector<double> newSummFinal;
			 summFinal.push_back(newSummFinal);		// new Row
			 summFinal.at(ind).push_back(summ[i][0]);	// Val
			 summFinal.at(ind).push_back(summ[i][1]);	// Freq
			 ind++;
		  }
    }

    return summFinal;  
}

int count(vector<double> v) {
    return v.size();  
}

double sum(vector<double> v) {
    assert(!v.empty());
    double sum_result = 0;
    for (size_t i = 0; i < v.size(); i++){
	   sum_result += v[i];
    }
    return sum_result;  
}

double mean(vector<double> v) {
    assert(!v.empty());
    double mean_result;
    double sum_result = 0;
    for (size_t i = 0; i < v.size(); i++) {
	   sum_result += v[i];
    }
    mean_result = sum_result / v.size();
    return mean_result;  
}

double median(vector<double> v) {
    assert(!v.empty());
    sort(v);
    double med;

    if (v.size() % 2 == 0) {
	   double low, hi;
	   low = v[(v.size() / 2) - 1];
	   hi = v[(v.size() / 2)];
	   med = (low + hi)/2;
    }
    else {
	   med = v[((v.size() + 1) / 2) - 1];
    }

    return med;  
}

double mode(vector<double> v) {
    assert(!v.empty());
    int freq = 0;
    double mode;
    vector<vector<double> > summary = summarize(v);
    
    for (size_t i = 0; i < summary.size(); i++)
    {
	   if (summary[i][1] > freq) {
		  mode = summary[i][0];
		  freq += summary[i][1];
	   }
	   else if (summary[i][1] == freq) {
		  if (mode > summary[i][0])
			 mode = summary[i][0];
	   }
		  
    }

    return mode;  
}

double min(vector<double> v) {
    assert(!v.empty());
    sort(v);
    return v[0];  
}

double max(vector<double> v) {
    assert(!v.empty());
    sort(v);
    return v[v.size() - 1];
}

double stdev(vector<double> v) {
    assert(v.size() >= 2);
    double stdev;
    double top = 0;

    for (size_t j = 0; j < v.size(); j++) {
	   top += pow((v[j] - mean(v)), 2);
    }

    stdev = sqrt(top / (v.size() - 1));
    return stdev;  
}

double percentile(vector<double> v, double p) {
    assert(!v.empty());
    assert( (p == 1) || ((p < 1) && (0 <= p)) );
    double percentile, rank;

    sort(v);

    rank = ( p * (v.size() - 1) ) + 1;
    int k = static_cast<int> (rank);
    double d = (rank - k);
    size_t i = k;

    if (i < v.size()) {
	   percentile = v[k - 1] + (d*(v[k] - v[k - 1]));
    }
    else
    {
	   percentile = v[k - 1] + (d*(0 - v[k - 1]));
    }

    return percentile;  
}