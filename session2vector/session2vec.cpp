#include <fstream>
#include "utils.h"
#include "vec.h"
#include "trainer.h"
using namespace std;


void line2pairs(costr line, vector<pair_t> &pairs);

void line2records(costr line, vector<record_t> &records);

bool records2pairs(const vector<record_t> &records, record_t &prequery, vector<pair_t> &pairs);

class Session2Vec {

public:

	Session2Vec(int len_vec, index_t vocab_size, float alpha, costr train_filename, costr valid_filename="") \
		:train_filename(train_filename), valid_filename(valid_filename)
	{
		trainer.init(len_vec, vocab_size, alpha);
		loadDataset(train_filename, valid_filename);
	}

	void run(int niter=100) {
		for (int no=0; no<niter; no++) {
			float train_cost = train();
			float valid_cost = valid();
			cout << "iter #" << no << "\ttrain\t" << train_cost << "\tvalid\t" << valid_cost << endl;
		}
	}



protected:

	float train(int niter=100) {
		pair<index_t, index_t> costs(0,0);	
		for(vector<vector<record_t> >::iterator rs_t=trainset.begin(); rs_t!=trainset.end(); ++rs_t) {
			vector<pair_t> pairs;
			record_t prequery;
			records2pairs(*rs_t, prequery, pairs);
			// train with each pair
			ItemType L;
			for(vector<pair_t>::iterator it=pairs.begin(); it!=pairs.end(); ++it) {
				L = trainer.train_iter(prequery, it->first, it->second);
				updateCost(L, costs);
			}
		}
		return getCost(costs);
	}

	float valid() {
		float cost = 0.0;
		if(!valid_filename.empty()) {
			pair<index_t, index_t> costs(0,0);	
			for(vector<vector<record_t> >::iterator rs_t=validset.begin(); rs_t!=validset.end(); ++rs_t) {
				vector<pair_t> pairs;
				record_t prequery;
				records2pairs(*rs_t, prequery, pairs);
				// train with each pair
				ItemType L;
				for(vector<pair_t>::iterator it=pairs.begin(); it!=pairs.end(); ++it) {
					L = trainer.test_iter(prequery, it->first, it->second);
					updateCost(L, costs);
				}
			}
			cost = getCost(costs);
		}
		return cost;
	}

	void loadDataset(costr train_filename, costr valid_filename) {

		cout << "loading trainset:\t" << train_filename << endl;
		_loadData(train_filename, trainset);
		cout << "loaded " << trainset.size() << " records from trainset" << endl;

		if(!valid_filename.empty()) {
			cout << "loading validate:\t" << valid_filename << endl;
			_loadData(valid_filename, validset);
			cout << "loaded " << validset.size() << "records from validset" << endl;
		}
	}
	// load dataset from file
	void _loadData(costr filename, vector< vector<record_t> >&dataset) {
		ifstream infile(filename.c_str());
		if(!infile) {
			cout << "ERROR: no such file: " << filename << endl;
			exit(-1);
		}
		index_t nrecords = 0;
		string line;
		while(getline(infile, line)) {
			nrecords++;
			vector<record_t> records;
			line2records(line, records);
			dataset.push_back(records);
		}
	}

	float updateCost(float L, pair<index_t, index_t> &costs) {
		if(L > 0) {
			costs.second++;
		} else {
			costs.first++;
		}
	}

	float getCost(const pair<index_t, index_t> &costs) {
		return (float)costs.first / (costs.first + costs.second);
	}

private:
	Trainer trainer;
	string train_filename, valid_filename;

	vector< vector<record_t> > trainset;
	vector< vector<record_t> > validset;

}; // end class

void line2records(costr line, vector<record_t> &records)
{
	int last_split_pos = -1;
	strings_t records_str;
	string newline = trim(line);
	split(newline, records_str, "\t");
	for(strings_iter_t it=records_str.begin(); it!=records_str.end(); ++it) {
		//cout << "part: " << *it << endl;
		indexs_t indexs;
		strings_t indexs_str;
		split(*it, indexs_str, " ");
		for(strings_iter_t st=indexs_str.begin(); st!=indexs_str.end(); ++st) {
			indexs.push_back(atoi(st->c_str()));
		}
		records.push_back(indexs);
	}
}

bool records2pairs(const vector<record_t> &records, record_t &prequery, vector<pair_t> &pairs)
{
	if(records.size() < 3) return false;
	prequery = records[0];
	for(int i=1; i<records.size()-1; i++) {
		for(int j=i+1; j<records.size(); j++) {
			pair_t _pair(records[i], records[j]);
			pairs.push_back(_pair);
		}
	}
	return true;
}

void line2pairs(costr line, vector<pair_t> &pairs) {
	vector<record_t> records;
    record_t prequery;
	line2records(line, records);
	records2pairs(records, prequery, pairs);
}

//#include "test.h"


int main()
{
	//test_records2pair();
    Session2Vec session2vec(8, 337122, 0.01, "1.sample");
    session2vec.run(1);
	return 0;
}
