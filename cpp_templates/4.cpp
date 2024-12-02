#include "bits/stdc++.h"
// #include "debug.h"

/*
Parses input file of integers to vector<vector<int>> columnwise.
eg. 
1 2 3 
4 5 6
-> 
{ { 1, 4 }, { 2, 5 }, { 3, 6 } }
*/

const bool USE_TESTFILE = true;

using namespace std;

long long a(vector < vector < int >>v);
long long b(vector < vector < int >>v);

int main(int argc, char **argv)
{

    string filename = argv[0];
    filename = filename.substr(0, filename.find("."));

    ifstream f(filename + (USE_TESTFILE ? ".test" : ".in"));

    int num_lines;
    vector < vector < int >>lines;
    string line;

    while (getline(f, line)) {
	vector < int >cur_line;
	stringstream ss(line);
	int num;

	while (ss >> num) {
	    cur_line.push_back(num);
	}
	lines.push_back(cur_line);
    }

    cout << "A: " << a(lines) << endl;
    cout << "B: " << b(lines) << endl;

}

long long a(vector < vector < int >>lines)
{
    long long solution = 0;

    for (size_t i = 0; i < lines.size(); i++) {
	for (int j = 0; j < lines[i].size(); j++) {
	    vector < int >&line = lines[i];
	    int num = line[j];
	    cout << num << endl;
	}
    }

    return solution;
}

long long b(vector < vector < int >>lines)
{
    long long solution = 0;

    for (size_t i = 0; i < lines.size(); i++) {
	for (int j = 0; j < lines[i].size(); j++) {
	    vector < int >&line = lines[i];
	    int num = line[j];

	    cout << num << endl;
	}
    }

    return solution;
}
