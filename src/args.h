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
	O_BFHELP,         // Show Brainfuck help

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
    '?',
	'b'
};

const string OPTION_PARAMS[NUM_OPTIONS] = 
{
	"",
	"",
	"",
	"",
	"",
	"",
	"<path>",
	"<script_string>",
	"<input_string>",
	"",
	"",
	"",
	""
};

const string OPTION_DESCRIPTIONS[NUM_OPTIONS] =
{
	"Dump memory at the end of execution.",
	"Dump memory after every command (combine with -q to avoid output interfering).",
	"When dumping memory, display values as chars.",
	"When dumping memory, display values as unsigned ints (0 - 255).",
	"When dumping memory, display values as signed ints (-128 - 127). This is the default setting.",
	"Show minimized script before run.",
	"Run code from the given file.",
	"Run code from the given string.",
	"Sets the input as a string to use for execution.",
	"Quiet (no output).",
	"Ignore input (all get commands behave as EOF).",
	"Show this help menu.",
	"Show help on how to write in Brainfuck."
};

extern bitset<NUM_OPTIONS> options;
extern string o_filename;
extern string o_stringscript;
extern string o_input;

///////////////////////////////////////////////////////////

vector<string> parseArgs(int argc, char** argv);
