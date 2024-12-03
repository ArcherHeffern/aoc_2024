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

struct Scanner {
    vector<string>& lines;
    int cur;
    int line;

    string MUL = "mul(";
    string DO = "do()";
    string DONT = "don't()";

    Scanner(vector<string>& lines, int start, int line): lines(lines), cur(start), line(line) {};

    int scan_product() {
        if (!scan_word(MUL)) return 0;
        int n1 = scan_number();
        if (!consume(',')) return 0;
        int n2 = scan_number();
        if (!consume(')')) return 0;
        return n1 * n2;
    }

    bool scan_do() {
        return scan_word(DO);
    }

    bool scan_dont() {
        return scan_word(DONT);
    }


    bool scan_word(string& s) {
        bool ok = lines[line].substr(cur, s.size()) == s;
        if (ok)
            cur += s.size();
        return ok;
    }

    bool is_at_end() {
        return line >= lines.size() and cur >= lines[cur].size();
    }

    char peek() {
        if (is_at_end()) {
            return '\0';
        }
        return lines[line][cur];
    }

    char advance() {
        char c = peek();
        cur++;
        return c;
    }

    bool consume(char c) {
        return advance() == c;
    }

    int scan_number() {
        int num = 0;
        while (isdigit(peek())) {
            num = num * 10 + (advance() - '0');
        }
        return num;
    }
};

long long a(vector < string > lines)
{
    long long solution = 0;
    
    // mul(number,number)
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            solution += Scanner(lines, j, i).scan_product();
        }
    }

    return solution;
}

long long b(vector < string > lines)
{
    long long solution = 0;
    bool enabled = true;
    
    // mul(number,number)
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            Scanner s(lines, j, i);
            if (s.scan_dont()) {
                enabled = false;
            } else if (s.scan_do()) {
                enabled = true;
            } else if (enabled) {
                solution += Scanner(lines, j, i).scan_product();
            }
        }
    }

    return solution;
}