#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

using namespace std;

const string HELP_MESSAGE = "Usage: create [-aoc[:n]] [files...]\n";

bool file_exists( string filename ) {
    struct stat s;
    return !stat( filename.c_str(), &s );
}

int main( int argc, char* argv[] ) {
    if ( argc == 1 ) {
        cout << HELP_MESSAGE;
        return 0;
    }
    string possible_arg = argv[1];
    if ( possible_arg == "-h" ) {
        cout << HELP_MESSAGE;
        return 0;
    }

    bool aoc_read_strings = false;
    bool aoc_read_numbers = false;
    if ( possible_arg == "-aoc" ) {
        aoc_read_strings = true;
        argc--;
        argv++;
    }
    if ( possible_arg == "-aoc:n" ) {
        aoc_read_numbers = true;
        argc--;
        argv++;
    }

    bool git_repo = file_exists( ".git" );

    
	string filename = "/Users/archerheffern/Desktop/code/atcoder/371/bits";
    if ( file_exists( "bits" ) ) {
        cout << "bits/stdc++.h exists. Skipping creation. \n";
    } else {
        string command = "cp -r " + filename + " .";
        system( command.c_str() );
    }

    for ( int i = 1; i < argc; i++ ) {
        string in_filename = string( argv[i] );
        string filename = in_filename + ".cpp";
        if ( file_exists( filename ) ) {
            cout << "File " << filename << " exists. Skipping...\n";
            continue;
        }

        if ( git_repo ) {
            ofstream gitignore( ".gitignore", ofstream::app );
            gitignore << in_filename << endl;
            if ( aoc_read_strings or aoc_read_numbers ) {
                gitignore << in_filename + ".in" << endl;
            }
            gitignore.close();
        }

        ofstream of = ofstream( filename ); 
        of << 
        "#include \"bits/stdc++.h\"\n"
        "// #include \"debug.h\"\n"
        "\n"
        "using namespace std;\n"
        "\n\n"
        "int main() {\n"
        "\n";

        if ( aoc_read_strings ) {
            of << 
            "\tifstream f(\"" + in_filename + ".in\");\n"
            "\tint num_lines;\n"
            "\tvector<string> lines;\n"
            "\tstring line;\n"
            "\t\n"
            "\twhile (getline(f, line)) {\n"
            "\t\tlines.push_back(line);\n"
            "\t\tnum_lines++;\n"
            "\t}\n"
            "\t\n"
            "\tfor (size_t i = 0; i < lines.size(); i++) {\n"
            "\t\t\n"
            "\t}\n";
        }

        if (aoc_read_numbers) {
            of << 
            "\tifstream f(\"" + in_filename + ".in\");\n"
            "\tint num_lines;\n"
            "\tvector<int> nums;\n"
            "\tint num;\n"
            "\t\n"
            "\twhile (f >> num) {\n"
            "\t\tnums.push_back(num);\n"
            "\t\tnum_lines++;\n"
            "\t}\n"
            "\t\n"
            "\tfor (size_t i = 0; i < nums.size(); i++) {\n"
            "\t\t\n"
            "\t}\n";
        }

        if ( aoc_read_strings or aoc_read_numbers ) {
            ofstream( in_filename + ".in" );
        }

        of << 
        "\treturn 0;\n" 
        "}\n";
    }

}
