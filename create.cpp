#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

const string HELP_MESSAGE =
    "Usage: \n"
    "create [files...] : Create c++ templates. Add to gitignore. Skips already existing files.\n"
    "create -aoc[:n|d|rn|rd|cn|cd] [files...] : Creates c++ templates and input data files for advent of code.\n"
    "create -r|d [files...] : Deletes template and data files, and remove them from .gitignore.\n"
    "create -h|-help|--help [-aoc] : Print help message.\n"
    "create -h|-help|--help -aoc : Print Advent of Code flag help message.\n";

const string HELP_MESSAGE_AOC =
    "Usage: \n"
    "All commands will create a template, a testfile, and add the created binary to .gitignore. Each template has an 'a' and 'b' method\n"
    "create -aoc [files...]: Template parses input files into a vector of strings.\n"
    "create -aoc:(n|d|rn|rd) [files...]: Template parses input files into a vector<vector<int> rowwise.\n"
    "create -aoc:(cn|cd) [files...]: Template parses input files into a vector<vector<int> columnwise.\n";

const string BITS_STDCPP_PATH =
    "/Users/archerheffern/Desktop/code/aoc/bits/";
const string TEMPLATE_DIR = "./cpp_templates/";

#define TEMPLATE_NONE 1
#define TEMPLATE_AOC_STRING 2	// vector<string> rowwise
#define TEMPLATE_AOC_ROWS_OF_NUMBERS 3	// vector<vector<int>> of rows
#define TEMPLATE_AOC_COLUMNS_OF_NUMBERS 4	// vector<vector<int>> of columns

void create_template(string filename);
void remove_template(string filename);
bool is_aoc();
bool file_exists(string filename);
void file_remove_line(string path, string line);


bool show_help = false;
int template_ = TEMPLATE_NONE;
bool remove_mode = false;
bool is_git_repo = file_exists(".git");

int main(int argc, char *argv[])
{
    if (argc == 1) {
	cout << HELP_MESSAGE;
	return 0;
    }

    while (argc > 1 and argv[1][0] == '-' and argv[1][0] != '\0') {
	string possible_arg = argv[1];

	if (possible_arg == "-h" or possible_arg ==
	    "-help" or possible_arg == "--help") {
	    show_help = true;
	} else if (possible_arg.substr(0, 4) == "-aoc") {
	    if (possible_arg.size() == 4) {
		template_ = TEMPLATE_AOC_STRING;
	    } else {
		if (possible_arg[4] != ':' or possible_arg.size() < 6) {
		    fprintf(stderr, "Invalid -aoc argument\n");
		    exit(1);
		}
		string option = possible_arg.substr(5);
		if (option == "n" or option == "d")
		    template_ = TEMPLATE_AOC_ROWS_OF_NUMBERS;
		else if (option == "rn" or option == "rd")
		    template_ = TEMPLATE_AOC_ROWS_OF_NUMBERS;
		else if (option == "cn" or option == "cd")
		    template_ = TEMPLATE_AOC_COLUMNS_OF_NUMBERS;
		else {
		    fprintf(stderr, "Invalid -aoc argument\n");
		    exit(1);
		}
	    }
	} else if (possible_arg == "-r" or possible_arg == "-d") {
	    remove_mode = true;
	}
	argc--;
	argv++;
    }

    // Options
    if (show_help) {
	if (is_aoc()) {
	    cout << HELP_MESSAGE_AOC;
	} else {
	    cout << HELP_MESSAGE;
	}

	return 0;
    }

    if (file_exists("bits")) {
	cout << "bits/stdc++.h exists. Skipping creation. \n";
    } else {
	string command = "cp -r " + BITS_STDCPP_PATH + " .";
	system(command.c_str());
    }

    for (int i = 1; i < argc; i++) {
	string filename = string(argv[i]);
	if (remove_mode) {
	    remove_template(filename);
	} else {
	    create_template(filename);
	}
    }
}

void create_template(string filename)
{
    string cpp_file = filename + ".cpp";
    if (file_exists(cpp_file)) {
	cout << "File " << filename << " exists. Skipping...\n";
	return;
    }

    if (is_git_repo) {
	ofstream gitignore(".gitignore", ofstream::app);
	gitignore << filename << endl;
	gitignore.close();
    }

    ofstream of = ofstream(cpp_file);
    ifstream inf = ifstream(TEMPLATE_DIR + to_string(template_) + ".cpp");
    string line;
    while (getline(inf, line)) {
	of << line << endl;
    }


    if (is_aoc()) {
	ofstream("data/" + filename + ".in");
	ofstream("data/" + filename + ".test");
    }
}

void remove_template(string filename)
{
    string cpp_file = filename + ".cpp";

    if (file_exists(filename)) {
	remove(filename.c_str());
    }

    if (file_exists(cpp_file)) {
	remove(cpp_file.c_str());
    }

    string data_path = "data/" + filename + ".in";
    string test_data_path = "data/" + filename + ".test";
    if (file_exists(data_path)) {
	remove(data_path.c_str());
    }
    if (file_exists(test_data_path)) {
	remove(test_data_path.c_str());
    }

    if (is_git_repo and file_exists(".gitignore")) {
	file_remove_line(".gitignore", filename);
    }
}

bool is_aoc()
{
    return template_ == TEMPLATE_AOC_COLUMNS_OF_NUMBERS or template_ ==
	TEMPLATE_AOC_STRING or template_ == TEMPLATE_AOC_ROWS_OF_NUMBERS;
}

bool file_exists(string filename)
{
    struct stat s;
    return !stat(filename.c_str(), &s);
}

void file_remove_line(string path, string line)
{
    string out_path = path + ".bak";
    ifstream in_file(path);
    ofstream out_file(out_path);
    string cur_line;
    while (getline(in_file, cur_line)) {
	if (cur_line != line) {
	    out_file << cur_line << endl;
	}
    }
    rename(out_path.c_str(), path.c_str());
}
