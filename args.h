#pragma once

#include <vector>
#include <string>
#include <bitset>
using namespace std;

///////////////////////////////////////////////////////////

enum Option
{
    O_DUMP = 0,       // Dump memory after running
    O_DUMP_VERBOSE,   // Dump memory after every command
    O_SHOW_MIN,       // Show the script actually executed - the "minimized" script.
    O_FILENAME,       // Followed by filename to interpret
    O_STRING_SCRIPT,  // Followed by string to interpret
    O_INPUT,          // Followed by input for the program
    O_HELP,           // Show help

    NUM_OPTIONS
};

extern bitset<NUM_OPTIONS> options;
extern string o_filename;
extern string o_stringscript;
extern string o_input;

///////////////////////////////////////////////////////////

vector<string> parseArgs(int argc, char** argv);
