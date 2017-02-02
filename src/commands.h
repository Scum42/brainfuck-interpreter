#pragma once

enum Command
{
    NOT_A_COMMAND = -1,

    C_LEFT,
    C_RIGHT,
    C_INCREMENT,
    C_DECREMENT,
    C_GET,
    C_PUT,
    C_LOOP_BEGIN,
    C_LOOP_END,
	C_DUMP,

    NUM_COMMANDS
};

const char COMMAND_CHARS[NUM_COMMANDS] =
{
	'<',
	'>',
	'+',
	'-',
	',',
	'.',
	'[',
	']',
	'*'
};

const string COMMAND_DESCRIPTIONS[NUM_COMMANDS] = 
{
	"Move the data pointer left.",
	"Move the data pointer right.",
	"Increment the value under the data pointer.",
	"Decrement the value under the data pointer.",
	"Get a single-byte character from the input list and store it under the data pointer. If there was no input, it will set the cell to zero.",
    "Print out the value under the pointer as an ASCII character.",
    "If the value under the pointer is zero, skip to the matching closed bracket.",
    "If the value under the pointer isn't zero, skip to the matching open bracket.",
    "Unique to this implementation of Brainfuck: Dump the current memory. Good for debugging."
};

const char COMMENT_CHAR = '#';