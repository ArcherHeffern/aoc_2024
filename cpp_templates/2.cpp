#include "bits/stdc++.h"
// #include "debug.h"

/*
Parses input file to vector of strings
eg. 
hello world
how are you
-> 
{ "hello world", "how are you" }
*/

const bool USE_TESTFILE = true;

using namespace std;

long long a(vector < string > v);
long long b(vector < string > v);

int main(int argc, char **argv)
{

    string filename = argv[0];
    filename = filename.substr(2);

    ifstream f("data/" + filename + (USE_TESTFILE ? ".test" : ".in"));

    int num_lines;
    vector < string > lines;
    string line;

    while (getline(f, line)) {
	lines.push_back(line);
    }

    long long a_res = a(lines);
    cout << "A: " << a_res << endl;
    long long b_res = b(lines);
    cout << "B: " << b_res << endl;
}

long long a(vector < string > lines)
{
    long long solution = 0;

    for (size_t i = 0; i < lines.size(); i++) {
	cout << lines[i] << endl;
    }

    return solution;
}

long long b(vector < string > lines)
{
    long long solution = 0;

    for (size_t i = 0; i < lines.size(); i++) {
	cout << lines[i] << endl;
    }

    return solution;
}
