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
    O_DUMP_AS_CHAR,   // When dumping memory, output as char
    O_DUMP_AS_UINT,   // When dumping memory, output as 0 - 255
    O_DUMP_AS_INT,    // When dumping memory, output as -128 - 127 (default)
    O_SHOW_MIN,       // Show the script actually executed - the "minimized" script.
    O_FILENAME,       // Followed by filename to interpret
    O_STRING_SCRIPT,  // Followed by string to interpret
    O_INPUT,          // Followed by input for the program
    O_QUIET,          // Disables output
    O_IGNORE_INPUT,   // All get commands read a zero
    O_HELP,           // Show help

    NUM_OPTIONS
};

const char OPTION_CHARS[NUM_OPTIONS] =
{
    'd',
    'D',
    'c',
    'u',
    'j',
    'm',
    'f',
    's',
    'i',
    'q',
    'Q',
    '?'
};

extern bitset<NUM_OPTIONS> options;
extern string o_filename;
extern string o_stringscript;
extern string o_input;

///////////////////////////////////////////////////////////

vector<string> parseArgs(int argc, char** argv);
