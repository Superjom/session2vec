#ifndef _VEC_H_
#define _VEC_H_

#include <iostream>
#include <vector>
#include <cmath>
#include "utils.h"
using namespace std;

class Vec {
public:
	typedef ItemType value_type;
	typedef vector<value_type>::iterator iterator;
	Vec() {}

	Vec(int size) {
		vec.reserve(size);
		vec.resize(size, 0.0);
	}

	Vec(const Vec &vec): vec(vec.vec) { }

	Vec(const vector<value_type> &vec) {
		this->vec = vec;
	}

	// operators ------------------------------------
	value_type dot(Vec &other) {
		value_type sum = 0.0;
		for(index_type i=0; i<other.size(); ++i) {
			sum += vec[i] * other[i];
		}
	}

	value_type mean() const {
		value_type res = 0.0;
		for(index_type i=0; i<vec.size(); i++) {
			res += vec[i];
		}
		return res / vec.size();
	}

	value_type sum() const {
		value_type res = 0.0;
		for(index_type i=0; i<vec.size(); i++) {
			res += vec[i];
		}
		return res;
	}

	friend Vec operator+(const Vec &other, value_type v) {
		Vec newVec(other);
		for(iterator it=newVec.begin(); it!=newVec.end(); ++it) {
			*it += v;
		}
		return newVec;
	}

	friend Vec operator+=(const Vec &a, const Vec &b) {
		assert(a.size() == b.size());
		for(int i=0; i<a.size(); ++i) {
			a[i] += b[i];
		}
	}

	friend Vec operator*(const Vec &other, value_type v) {
		Vec newVec(other);
		for(iterator it=newVec.begin(); it!=newVec.end(); ++it) {
			*it *= v;
		}
		return newVec;
	}

	friend Vec operator+(const Vec &a, const Vec &b) {
		assert(a.size() == b.size());
		Vec newVec(a);
		for(index_type i=0; i<a.size(); i++) {
			newVec[i] += b[i];
		}
		return newVec;
	}

	friend Vec operator*(const Vec &a, const Vec &b) {
		assert(a.size() == b.size());
		Vec newVec(a);
		for(index_type i=0; i<newVec.size(); i++) {
			newVec[i] *= b[i];
		}
		return newVec;
	}

	friend Vec operator/= (const Vec &a, value_type v) {
		for(iterator it=begin(); it!=end(); ++it) {
			*it /= v;
		}
	}

	// get element
	value_type operator[](index_type i) const {
		return vec[i];
	}

	value_type &operator[](index_type i) {
		return vec[i];
	}

	//api
	index_type size() {
		return vec.size();
	}

	void display() {
		cout << "size: ---------" <<size() << "----------" << endl;
		showVector(vec);
	}

	// iterators
	iterator begin() {
		return vec.begin();
	}

	iterator end() {
		return vec.end();
	}

	// Ëæ»ú³õÊ¼»¯
	void randInit() {
		float r;
		for(index_type i=0; i<size(); i++) {
			r = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) - 0.5) / 100;
			vec[i] = r;
		}
	}

private:
	vector<value_type> vec;
};

Vec sin(const Vec& vec) {
	Vec newVec(vec);
	for(Vec::iterator it=newVec.begin(); it!=newVec.end(); ++it) {
		*it = sin(*it);
	}
	return newVec;
}

Vec cos(const Vec&vec) {
	Vec newVec(vec);
	for(Vec::iterator it=newVec.begin(); it!=newVec.end(); ++it) {
		*it = cos(*it);
	}
	return newVec;
}

ItemType dot(Vec &a, Vec &b) {
	ItemType res = 0.0;
	for(index_type i=0; i<a.size(); ++i) {
		res += a[i] * b[i];
	}
	return res;
}


#endif