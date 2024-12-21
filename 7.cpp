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
bool possible(long long result, vector<long long>& operands);
bool _possible(long long result, vector<long long>& operands, long long index, long long total);

bool possible_w_merge(long long result, vector<long long>& operands);
bool _possible_w_merge(long long result, long long cur, vector<long long>& operands, long long index);

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

void parse_line(string& line, long long& result, vector<long long>& operands) {
    size_t pos = line.find(':');
    string label_string = line.substr(0, pos);
    string operands_string = line.substr(pos+1);
    stringstream label_ss(label_string);
    stringstream operands_ss(operands_string);

    label_ss >> result;

    long long operand;
    while (operands_ss >> operand) {
        operands.push_back(operand);
    }
}

long long a(vector < string > lines)
{
    long long solution = 0;

    for (string& line: lines) {
        long long result;
        vector<long long> operands;
        parse_line(line, result, operands);

        if (possible(result, operands)) {
            solution += result;
        }
    }

    return solution;
}

bool possible(long long result, vector<long long>& operands) {
    return _possible(result, operands, 1, operands[0]);
}

bool _possible(long long result, vector<long long>& operands, long long index, long long total) {
    if (index == operands.size()) {
        return result == total;
    }

    bool add = _possible(result, operands, index+1, total+operands[index]);
    bool mul = _possible(result, operands, index+1, total*operands[index]);

    return add or mul;
}

long long b(vector < string > lines)
{
    long long solution = 0;

    for (string& line: lines) {
        long long result;
        vector<long long> operands;
        parse_line(line, result, operands);

        if (possible_w_merge(result, operands)) {
            solution += result;
        }
    }

    return solution;
}

bool possible_w_merge(long long result, vector<long long>& operands) {
    return _possible_w_merge(result, 0, operands, 0);
}

bool _possible_w_merge(long long result, long long cur, vector<long long>& operands, long long index) {
    if (index == operands.size()) {
        return result == cur;
    }
    if (cur > result) {
        return false;
    }

    // Update current_operand

    if (index > 0) {
        bool mul = _possible_w_merge(result, cur*operands[index], operands, index+1);
        if (mul)
            return true;

        long long un_num = stoll(to_string(cur) + to_string(operands[index]));
        bool un = _possible_w_merge(result, un_num, operands, index+1);
        if (un) 
            return true;
    }
    return _possible_w_merge(result, cur+operands[index], operands, index+1);

}