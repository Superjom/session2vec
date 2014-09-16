#include "utils.h"
#include "vec.h"
#include "trainer.h"
#include "vocab.h"

void test_line2records() {
	vector<record_t> records;
	line2records("1 2\t2 3\t3 4", records);
	cout << records.size() << endl;
	for(int i=0; i<records.size(); ++i) {
		cout << i << "#" << endl;
		for(int j=0; j<records[i].size(); ++j) {
			cout << records[i][j] << " ";
		}
		cout << endl;
	}
}

void test_records2pair() {
	vector< vector<index_t> > records;
	line2records("1 2\t2 3\t3 4\t4 5\n", records);
	vector<pair_t> pairs;
	records2pairs(records, pairs);

	cout << pairs.size() << endl;
	for(int i=0; i<pairs.size(); ++i) {
		cout << "pair#" << i << endl;
		cout << "positive: " <<endl;
		for(int j =0; j<pairs[i].first.size(); ++j) {
			cout << pairs[i].first[j] << " ";
		}
		cout << endl;
		for(int j=0; j<pairs[i].second.size(); ++j) {
			cout << pairs[i].second[j] << " ";
		}
		cout << endl;
	}
}