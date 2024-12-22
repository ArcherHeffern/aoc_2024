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

const bool USE_TESTFILE = false;

using namespace std;

long long a(string v);
long long b(string v);

int main(int argc, char **argv)
{

    string filename = argv[0];
    filename = filename.substr(2);

    ifstream f("data/" + filename + (USE_TESTFILE ? ".test" : ".in"));

    string line;

    getline(f, line);


    long long a_res = a(line);
    cout << "A: " << a_res << endl;
    long long b_res = b(line);
    cout << "B: " << b_res << endl;

}

long long a(string line)
{
    assert(line.size() % 2 == 1 && "Memory input should not end with empty space");
    long long solution = 0;

	int l = 0;
    int r = line.size()-1;
    int index = 0;
    // 2333133121414131402
    while (l <= r) {
        if (line[l] == '0') {
            l++;
            continue;
        }
        if (line[r] == '0') {
            r -= 2;
            continue;
        }
        if (l % 2 == 0) {
            int id = l/2; 
            solution += id * index;
            line[l] -= 1;
        } else {
            int id = r/2;
            solution += id * index;
            line[l] -= 1;
            line[r] -= 1;
        }

        index++;
    }


    return solution;
}

long long b(string line)
{
    long long solution = 0;

	cout << line << endl;

    return solution;
}
