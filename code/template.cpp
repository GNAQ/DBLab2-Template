#include <cstdio>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <chrono>
#include <cstring>
#include <string>
#include <sstream>
#include <filesystem>
using std::cout, std::endl, std::string, std::vector, std::pair;
using ll = long long;

int mem_lim;
string infile;
string tf[2] = {"1.tmp", "2.tmp"};
vector<pair<int, int>> partitions[2];

struct Record {
	ll v;
	char uuid[37];
	int bytes;
	bool operator< (const Record &b) const {
		return this->v < b.v;
	}
	bool operator> (const Record &b) const {
		return this->v > b.v;
	}
	bool operator== (const Record &b) const {
		return this->v == b.v;
	}
};

void swapname() {
	std::swap(tf[1], tf[0]);
	std::swap(partitions[0], partitions[1]);
}

void parseRec(const string &s, Record &r) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ',' || s[i] == ' ') {
			r.v = std::stoll(s.substr(0, i));
			for (int j = i + 1; j < s.size(); j++) {
				r.uuid[j - i - 1] = s[j];
			}
			r.uuid[36] = 0;
			r.bytes = s.size();
			break;
		}
	}
}

void QSort(int l, int r, Record *rec) { 
}

void innerblockSort(int elem_limit) {
	std::ifstream inf(infile);
	std::ofstream outf(tf[0]);
	string line;
	
	Record *rec = new Record[elem_limit + 2];
	int line_count = 0, total_count = 0, block_id = 0;
	ll total_bytes = 0;
	
	partitions[0].push_back({elem_limit, 0});
	while (std::getline(inf, line)) {
		parseRec(line, rec[line_count]);
		
		++line_count;
		++total_count;
		if (line_count == elem_limit) {
			// sort the data and output to file
			
			
			line_count = 0;
			block_id++;
		}
	}
	// process remaining data
	if (line_count) {
		// sort the data and output to file
	}
	else {
		partitions[0].pop_back();
	}
	delete[] rec;
}

bool externalMerge() {
	
	int part_count = partitions[0].size();
	Record *rec = new Record[part_count];
	vector<int> mapping;
	vector<int> read_count(part_count);
	
	std::ifstream ifs[part_count];
	std::ofstream outf("out.csv");
	string line;
	for (int i = 0; i < part_count; i++) {
		ifs[i] = std::ifstream(tf[0]);
		ifs[i].seekg(partitions[0][i].second);
		std::getline(ifs[i], line);
		parseRec(line, rec[i]);
		read_count[i]++;
	}
	
	// do merge sort with some algorithm
	
	delete[] rec;
}

void execMerge() {
	// UUID4 36chars
	// int elem_limit = 1LL * mem_lim * 1024 * 1024 / sizeof(Record) - 2;
	int elem_limit = 1LL * mem_lim * 1024 / sizeof(Record) - 2; // NOTE test with kb mem
	
	cout << "ELEM LIMIT = " << elem_limit << endl;
	
	// block inner sorting
	innerblockSort(elem_limit);
	
	// external sorting
	externalMerge();
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		cout << "Please run with 2 arguments in order: mem= (in MB) file=" << endl;
		return 0;
	}
	string arg1 = string(argv[1]), arg2 = string(argv[2]);
	if (arg1.substr(0, 3) == "mem" && arg2.substr(0, 4) == "file") {
		
		mem_lim = std::stoi(arg1.substr(4));
		infile = arg2.substr(5);
		
		cout << "Sorting file " << infile << " with memory limit " << mem_lim << " MB" << endl;
	}
	else {
		cout << "Please run with 2 arguments in order: mem= (in MB) file=" << endl;
		return 0;
	}
	
	execMerge();
	
}