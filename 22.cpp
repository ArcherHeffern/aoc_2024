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

#define u64 unsigned long long
#define u64FourTuple tuple<u64, u64, u64, u64>

struct u64FourTupleHasher {
    size_t operator() (u64FourTuple four_tuple) const {
        return get<0>(four_tuple) + get<1>(four_tuple) * 17 + get<2>(four_tuple) * 31 + get<3>(four_tuple) * 51;
    }
};

u64 a(vector < u64 > v);
u64 b(vector <u64> secrets);

int main(int argc, char **argv)
{
    string filename = argv[0];
    filename = filename.substr(2);

    ifstream f("data/" + filename + (USE_TESTFILE ? ".test" : ".in"));

    int num_lines;
    vector <u64> secrets;
    u64 secret;

    while (f >> secret) {
        secrets.push_back(secret);
    }

    u64 a_res = a(secrets);
    cout << "A: " << a_res << endl;
    u64 b_res = b(secrets);
    cout << "B: " << b_res << endl;
}

void mix(u64& secret, u64 number) {
    secret ^= number;
}

void prune(u64& secret) {
    secret %= 16777216;
}

u64 next_secret(u64 secret) {
    mix(secret, secret * 64);
    prune(secret);
    mix(secret, secret/32);
    prune(secret);
    mix(secret, secret*2048);
    prune(secret);
    return secret;
}

u64 next_secret(u64 secret, int skip) {
    for (int i = 0; i < skip; i++) {
        secret = next_secret(secret);
    }
    return secret;
}

u64 a(vector <u64> secrets)
{
    u64 solution = 0;

    for (u64 secret: secrets) {
        solution += next_secret(secret, 2000);
    }

    return solution;
}

// unordered_map< tuple<int, int, int, int>, int>    Four tuple of diffs -> count
// For each secret generation, keep track of all four tuples seen. Only update above map if not in seen_four_tuples. 

void process_secret(u64 secret, int num_to_process, unordered_map<u64FourTuple, u64, u64FourTupleHasher>& four_tuple_scores) {
    deque<u64> d;
    u64 new_secret;
    unordered_set<u64FourTuple, u64FourTupleHasher> seen;
    
    while (num_to_process --> 0) {
        new_secret = next_secret(secret);
        d.push_back(new_secret%10 - secret%10);
        secret = new_secret;
        if (d.size() > 4) {
            d.pop_front();
            u64FourTuple ft = { d[0], d[1], d[2], d[3] };
            if (seen.count(ft))
                continue;
            seen.insert(ft);
            four_tuple_scores[ft] += secret%10;
        }
    }
}

u64 b(vector <u64> secrets)
{
    u64 solution = 0;

    unordered_map<u64FourTuple, u64, u64FourTupleHasher> four_tuple_scores;

    for (u64 secret: secrets) {
        process_secret(secret, 2000, four_tuple_scores);
    }

    for (const auto& [k, v]: four_tuple_scores) {
        solution = max(solution, v);
    }

    return solution;
}
