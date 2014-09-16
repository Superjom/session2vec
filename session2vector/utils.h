#ifndef _UTILS_H_
#define _UTILS_H_
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

// types
typedef float ItemType;
typedef unsigned int index_type;
typedef const string& costr;

template<class T=ItemType>
void showVector(const vector<T> &vec) {
	for(int i=0; i<vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

template<class T=index_type>
T stoi(costr v) {
	return atoi(v.c_str());
}

float stof(costr v) {
	return atof(v.c_str());
}



#endif