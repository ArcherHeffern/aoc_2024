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

void a_r(vector<string>& lines, int index, int i, int j, int& count, string& target, int direction);
int a(vector < string > v);
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

    cout << "A: " << a(lines) << endl;
    cout << "B: " << b(lines) << endl;

}

int a(vector < string > lines)
{
    int solution = 0;

    string xmas = "XMAS";

    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            a_r(lines, 0, i, j, solution, xmas, 0);
        }
    }

    return solution;
}

const int NONE = 0;
const int DIRECTIONS[8][3] = {
    {1, -1, -1}, 
    {2, -1, 0},
    {3, -1, 1},
    {4, 0, -1},
    {5, 0, 1},
    {6, 1, -1},
    {7, 1, 0},
    {8, 1, 1}
};

void a_r(vector<string>& lines, int index, int i, int j, int& count, string& target, int direction) {
    if (index == target.size()) {
        count++;
        return;
    }

    if (i < 0 or i >= lines.size() or j < 0 or j >= lines[i].size()) {
        return;
    }

    if (lines[i][j] != target[index]) {
        return;
    }

    for (auto [d_direction, di, dj]: DIRECTIONS) {
        if (direction == NONE or direction == d_direction) {
            a_r(lines, index+1, i+di, j+dj, count, target, d_direction);
        }
    }
}

bool mas_diag(vector<string>& lines, int i, int j) {
    int top_left = lines[i-1][j-1];
    int bottom_right = lines[i+1][j+1];

    if (top_left == 'M' and bottom_right == 'S') {
        return true;
    }
    if (top_left == 'S' and bottom_right == 'M') {
        return true;
    }

    return false;
}

bool mas_antidiag(vector<string>& lines, int i, int j) {
    int top_left = lines[i+1][j-1];
    int bottom_right = lines[i-1][j+1];

    if (top_left == 'M' and bottom_right == 'S') {
        return true;
    }
    if (top_left == 'S' and bottom_right == 'M') {
        return true;
    }

    return false;
}

long long b(vector < string > lines)
{
    long long solution = 0;

    for (size_t i = 1; i < lines.size()-1; i++) {
        for (size_t j = 1; j < lines[i].size()-1; j++) {
            if (lines[i][j] != 'A') {
                continue;
            }
            if (mas_diag(lines, i, j) and mas_antidiag(lines, i, j)) {
                solution++;
            }
        }
    }

    return solution;
}
