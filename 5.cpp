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

struct TupleCmp {

    template <typename T>
    size_t operator() (const pair<T, T> t) const {
        return t.first + t.second * 51;
    };
};

void vector_print(vector<int> &v);
void print_input(unordered_map<int, unordered_set<int>>& v1, vector<vector<int>>& v2);
long long a(unordered_map<pair<int, int>, bool, TupleCmp> relations, vector<vector<int>>& v2);
long long b(unordered_map<pair<int, int>, bool, TupleCmp> relations, vector<vector<int>>& v2);

int main(int argc, char **argv)
{

    string filename = argv[0];
    filename = filename.substr(2);

    ifstream f("data/" + filename + (USE_TESTFILE ? ".test" : ".in"));

    int num_lines;
    unordered_map<pair<int, int>, bool, TupleCmp> lines;
    vector<vector<int>> lines2;
    string line;

    while (getline(f, line))
    {
        if (line == "")
        {
            break;
        }
        stringstream ss(line);
        string n1_s;
        string n2_s;
        getline(ss, n1_s, '|');
        getline(ss, n2_s);

        int n1 = stoi(n1_s);
        int n2 = stoi(n2_s);
        lines[{n1, n2}] = true;
        lines[{n2, n1}] = false;
    }

    while (getline(f, line))
    {
        vector<int> nums;
        string num;
        line += ",";
        stringstream ss(line);
        while (getline(ss, num, ','))
        {
            nums.push_back(stoi(num));
        }
        lines2.push_back(nums);
    }

    cout << "A: " << a(lines, lines2) << endl;
    cout << "B: " << b(lines, lines2) << endl;
}

void sort_arr(unordered_map<pair<int, int>, bool, TupleCmp> relations, vector<int>& arr) {
    const auto cmp = [&relations](int i1, int i2) -> bool {
        return relations[{i1, i2}];
    };
    sort(arr.begin(), arr.end(), cmp);
};

long long a(unordered_map<pair<int, int>, bool, TupleCmp> relations, vector<vector<int>>& v2) {
    long long solution = 0;

    for (int i = 0; i < v2.size(); i++) { // Over lines
        vector<int> line_copy = v2[i];
        sort_arr(relations, line_copy);
        if (line_copy == v2[i]) {
            solution += line_copy[line_copy.size()/2];
        } 
    }

    return solution;
}

long long b(unordered_map<pair<int, int>, bool, TupleCmp> relations, vector<vector<int>>& v2) {
    long long solution = 0;

    for (int i = 0; i < v2.size(); i++) { // Over lines
        vector<int> line_copy = v2[i];
        sort_arr(relations, line_copy);
        if (line_copy != v2[i]) {
            solution += line_copy[line_copy.size()/2];
        }
    }

    return solution;
}

void vector_print(vector<int> &v)
{
    for (int n : v)
    {
        cout << n << ", ";
    }
    cout << endl;
}

void print_input(unordered_map<int, unordered_set<int>>& v1, vector<vector<int>>& v2)
{
    for (const auto &[k, v] : v1)
    {
        cout << k << ": ";
        for (int n : v)
        {
            cout << n << ", ";
        }
        cout << endl;
    }
    cout << endl;

    for (size_t i = 0; i < v2.size(); i++)
    {
        for (int j = 0; j < v2[i].size(); j++)
        {
            cout << v2[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}