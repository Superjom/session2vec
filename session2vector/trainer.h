#ifndef TRAINER_H_
#define TRAINER_H_
#include "utils.h"
#include "vec.h"
#include "vocab.h"
/* 
*/
class Trainer {
public:
	typedef float value_type;

	Trainer() {}

	Trainer(int len_vec, index_t vocab_size, float alpha=0.01) : \
		len_vec(len_vec), vocab_size(vocab_size), alpha(alpha)
	{
        cout << "init trainer" << endl;
        cout << "len_vec " << len_vec << endl;
        cout << "vocab_size " << vocab_size << endl;
        cout << "alpha " << alpha << endl;
		vocab.init(vocab_size, len_vec, true);
	}

	void init(int len_vec, index_t vocab_size, float alpha=0.01) {
		Trainer(len_vec, vocab_size, alpha);
	}
	
	// TODO 
	value_type train_iter(record_t &preterms, record_t &nextterms1, record_t &nextterms2) {

		Vec xp = sin(vocab.sum(preterms));
		Vec xa = sin(vocab.sum(nextterms1));
		Vec xb = sin(vocab.sum(nextterms2));
		value_type exp__dot_xp_xa = exp(-dot(xp, xa));
		value_type exp__dot_xp_xb = exp(-dot(xp, xb));
		// 
		value_type score1 = 1.0 / (1.0 + exp__dot_xp_xa);
		value_type score2 = 1.0 / (1.0 + exp__dot_xp_xb);
		value_type L = 1 - (score1 - score2);
		if(L > 0.0) {
			value_type tmpa = - exp__dot_xp_xa / pow((1+exp__dot_xp_xa), 2);
			value_type tmpb = - exp__dot_xp_xb / pow((1+exp__dot_xp_xb), 2);
			Vec grad_L_xa = sin(xp) * cos(xa) * tmpa;
			Vec grad_L_xb = sin(xp) * cos(xb) * tmpb;
			Vec grad_L_xp = sin(xa) * cos(xp) * tmpa - sin(xb) * cos(xp) * tmpb;

			vocab.updateVec(nextterms1, grad_L_xa, alpha);
			vocab.updateVec(nextterms2, grad_L_xb, alpha);
			vocab.updateVec(preterms, grad_L_xp, alpha);
		}
		return L;
	}

	value_type test_iter(record_t &preterms, record_t &nextterms1, record_t &nextterms2) {

		Vec xp = sin(vocab.sum(preterms));
		Vec xa = sin(vocab.sum(nextterms1));
		Vec xb = sin(vocab.sum(nextterms2));
		value_type exp__dot_xp_xa = exp(-dot(xp, xa));
		value_type exp__dot_xp_xb = exp(-dot(xp, xb));

		value_type score1 = 1.0 / (1.0 + exp__dot_xp_xa);
		value_type score2 = 1.0 / (1.0 + exp__dot_xp_xb);
		value_type L = 1 - (score1 - score2);
		return L;
	}

protected:
	value_type cost(value_type score1, value_type score2) {
		return 1 - (score1 - score2);
	}


private:
	int len_vec;
	index_t vocab_size;
	float alpha;
	Vocab vocab;
};













#endif
