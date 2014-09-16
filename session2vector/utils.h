#ifndef _UTILS_H_
#define _UTILS_H_
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <cassert>
#include <cstdio>
#include <cstdlib>
using namespace std;

// types
typedef float ItemType;
typedef unsigned int index_t;
typedef const string& costr;
typedef vector<string> strings_t;
typedef vector<string>::iterator strings_iter_t;
typedef vector<index_t> indexs_t;

typedef vector<index_t> record_t;
typedef pair<record_t, record_t> pair_t;


void showVector(const vector<ItemType> &vec) {
	for(int i=0; i<vec.size(); ++i) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

index_t stoi(costr v) {
	return atoi(v.c_str());
}

float stof(costr v) {
	return atof(v.c_str());
}

void split(costr line, vector<string>& result, costr pattern) {
	string::size_type pos = 0, found = 0;
	while(found != string::npos) {
		found = line.find(pattern, pos);
		result.push_back(line.substr(pos, found - pos));
		pos = found + 1;
	}
}

string trim(costr str)
{
    string tags = " \n\t\r";
    string::size_type pos = str.find_first_not_of(tags);
    if(pos == string::npos)
    {
        return str;
    }
    string::size_type pos2 = str.find_last_not_of(tags);
    if(pos2 != string::npos)
    {
        return str.substr(pos, pos2 - pos + 1);
    }
    return str.substr(pos);
}


#endif
