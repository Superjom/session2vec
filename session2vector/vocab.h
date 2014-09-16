#ifndef _VOCAB_H_
#define _VOCAB_H_
#include "utils.h"
#include "vec.h"

class Vocab {
public:
	typedef float value_type;

	Vocab() {}

	Vocab(index_t size, int len_vec, bool random_init=true) :\
		size(size), len_vec(len_vec) {

        cout << "---init vocab" << endl;
        cout << "vocab_size " << size << endl;
        cout << "len_vec " << len_vec << endl;
        cout << endl;
		initVecs(random_init);
	}

	void init(index_t size, int len_vec, bool random_init=true) {
		Vocab(size, len_vec, random_init);
	}

	void updateVec(const vector<index_t> &ids, Vec grad, float alpha) {
		for(vector<index_t>::const_iterator id_t=ids.begin(); id_t != ids.end(); ++id_t) {
			for(int i=0; i<len_vec; ++i) {
				vecs[*id_t][i] -= alpha * grad[i];
			}
		}
	}

	Vec sum(const vector<index_t> &ids) const {
        cout << "sum ---- " << endl;
        cout << "len_vec " << len_vec << endl;
		Vec vec(len_vec);
		for(vector<index_t>::const_iterator id_t=ids.begin(); id_t!=ids.end(); ++id_t) {
			vec += vecs[*id_t];
		}
		return vec;
	}


protected:
	void initVecs(bool random_init) {
		cout << "init vectors" << endl;
        cout << "len_vec" << len_vec << endl;
		vecs.clear();
		for(index_t i=0; i<size; i++) {
			Vec vec(len_vec);
			if(random_init) vec.randInit();
			vecs.push_back(vec);
		}
	}

	

private:
	index_t size;
	int len_vec;
	vector<Vec> vecs;
};


#endif
