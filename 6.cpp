#include <tuple>
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

struct PairHash {
    size_t operator() (pair<int, int> p) const {
        return p.first + p.second * 51;
    };
};

long long a(vector < string > v);
long long b(vector < string > v);
void board_print(vector<string>& board);
bool has_loop(vector<string>& board, int direction, int i, int j);
void find_seen(vector<string>& board, int direction, int i, int j, unordered_set<pair<int, int>, PairHash>& seen);

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


int UP = 0;
int RIGHT = 1;
int DOWN = 2;
int LEFT = 3;

int MOVEMENT[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
char OBSTRUCTION = '#';
char NOTHING = '.';

int SEEN = '1';

size_t count_seen(vector<string>& board) {
    size_t count = 0;
    for (string& s: board) {
        for (char c: s) {
            if (c == SEEN) {
                count++;
            }
        }
    }
    return count;
}

pair<int, int> get_guard_location(vector<string>& lines, int& direction) {
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[0].size(); j++) {
            char c = lines[i][j];
            if (c == '^' or c == '>' or c == '<' or c == 'v') {
                if (c == '^')
                    direction = UP;
                else if (c == '>') 
                    direction = RIGHT;
                else if (c == '<')
                    direction = LEFT;
                else
                    direction = DOWN;
                lines[i][j] = SEEN;
                return {i, j};
            }
        }
    }
    throw logic_error("No guard found\n");
}

long long a(vector < string > board)
{
    long long solution = 0;

    int direction = DOWN;
    auto [i, j] = get_guard_location(board, direction);

    int height = board.size();
    int width = board[0].size();

    while (i >= 0 and i < height and j >= 0 and j < width) {
        int next_i = i + MOVEMENT[direction][1];
        int next_j = j + MOVEMENT[direction][0];

        if (next_i < 0 or next_i >= height or next_j < 0 or next_j >= width) {
            break;
        }

        if (board[next_i][next_j] == OBSTRUCTION) {
            direction = (direction + 1) % 4;
            continue;
        }

        i = next_i;
        j = next_j;
        board[i][j] = SEEN;
    }

    return count_seen(board);
}

long long b(vector < string > board)
{
    long long solution = 0;

    unordered_set<pair<int, int>, PairHash> seen;
    int direction = DOWN;
    auto [i, j] = get_guard_location(board, direction);
    find_seen(board, direction, i, j, seen);

    for (const auto [obs_i, obs_j]: seen) {
        board[obs_i][obs_j] = OBSTRUCTION;
        if (has_loop(board, direction, i, j)) {
            solution++;
        }
        board[obs_i][obs_j] = NOTHING;
    }

    return solution;
}

struct ThreeTupleHash {
    size_t operator() (tuple<int, int, int> t) const {
        return get<0>(t) + get<1>(t) * 17 + get<1>(t) * 51;
    };
};

bool has_loop(vector<string>& board, int direction, int i, int j) {

    unordered_set<tuple<int, int, int>, ThreeTupleHash> seen; // i, j, direction
    int height = board.size();
    int width = board[0].size();

    while (i >= 0 and i < height and j >= 0 and j < width) {
        int next_i = i + MOVEMENT[direction][1];
        int next_j = j + MOVEMENT[direction][0];

        if (next_i < 0 or next_i >= height or next_j < 0 or next_j >= width) {
            break;
        }

        if (board[next_i][next_j] == OBSTRUCTION) {
            direction = (direction + 1) % 4;
            continue;
        }

        i = next_i;
        j = next_j;
        if (seen.count({i, j, direction})) {
            return true;
        }
        seen.insert({i, j, direction});
    }
    return false;
}

void find_seen(vector<string>& board, int direction, int i, int j, unordered_set<pair<int, int>, PairHash>& seen) {

    int height = board.size();
    int width = board[0].size();

    while (i >= 0 and i < height and j >= 0 and j < width) {
        int next_i = i + MOVEMENT[direction][1];
        int next_j = j + MOVEMENT[direction][0];

        if (next_i < 0 or next_i >= height or next_j < 0 or next_j >= width) {
            break;
        }

        if (board[next_i][next_j] == OBSTRUCTION) {
            direction = (direction + 1) % 4;
            continue;
        }

        i = next_i;
        j = next_j;
        seen.insert({i, j});
    }
}

void board_print(vector<string>& board) {
    for (string& s: board) {
        printf("%s\n", s.c_str());
    }
}
