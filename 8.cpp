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

    cout << "A: " << a(lines) << endl;
    cout << "B: " << b(lines) << endl;

}

struct SetPairHash {
    size_t operator() (const pair<int, int>& p) const {
        return p.first * 17 + p.second * 51;
    };
};

// Create groups of nodes with same frequency. Find all combinations of 2 and add the antinodes to a hashset. 
long long a(vector < string > lines)
{
    unordered_map<char, vector<pair<int, int>>> m;
    int H = lines.size();
    int W = lines[0].size();
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char c = lines[i][j];
            if (c != '.')
                m[c].push_back({i, j});
        }
    }

    unordered_set<pair<int, int>, SetPairHash> antinodes;

    for (const auto& [k, s]: m) {
        for (int i = 0; i < s.size()-1; i++) {
            for (int j = i+1; j < s.size(); j++) {
                pair<int, int> p1 = s[i];
                pair<int, int> p2 = s[j];
                int rise = p1.first - p2.first;
                int run = p1.second - p2.second;
                if (rise < 0 and run < 0) {
                    rise = -rise;
                    run = -run;
                }

                if (p1.second > p2.second)
                    swap(p1, p2);

                pair<int, int> new_left = new_left = { p1.first - rise, p1.second - run };
                pair<int, int> new_right = new_right = { p2.first + rise, p2.second + run };

                if (new_left.first >= 0 and new_left.first < H and new_left.second >= 0 and new_left.second < W) {
                    antinodes.insert(new_left);
                }

                if (new_right.first >= 0 and new_right.first < H and new_right.second >= 0 and new_right.second < W) {
                    antinodes.insert(new_right);
                }
            }
        }

    }
    return antinodes.size();
}

// Create groups of nodes with same frequency. Find all combinations of 2 and add the antinodes to a hashset. 
// This time handle resonant frequencies
long long b(vector < string > lines)
{
    unordered_map<char, vector<pair<int, int>>> m;
    int H = lines.size();
    int W = lines[0].size();
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char c = lines[i][j];
            if (c != '.')
                m[c].push_back({i, j});
        }
    }

    unordered_set<pair<int, int>, SetPairHash> antinodes;

    for (const auto& [k, s]: m) {
        for (int i = 0; i < s.size()-1; i++) {
            for (int j = i+1; j < s.size(); j++) {
                pair<int, int> p1 = s[i];
                pair<int, int> p2 = s[j];
                int rise = p1.first - p2.first;
                int run = p1.second - p2.second;
                if (rise < 0 and run < 0) {
                    rise = -rise;
                    run = -run;
                }

                if (p1.second > p2.second)
                    swap(p1, p2);

                pair<int, int> new_left = p1;
                pair<int, int> new_right = p2;

                while (new_left.first >= 0 and new_left.first < H and new_left.second >= 0 and new_left.second < W) {
                    antinodes.insert(new_left);
                    new_left = { new_left.first - rise, new_left.second - run };
                }

                while (new_right.first >= 0 and new_right.first < H and new_right.second >= 0 and new_right.second < W) {
                    antinodes.insert(new_right);
                    new_right = { new_right.first + rise, new_right.second + run };
                }
            }
        }

    }
    return antinodes.size();
}