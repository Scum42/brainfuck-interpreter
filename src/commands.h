#pragma once

enum Command
{
    NOT_A_COMMAND = -1,

    Left,
    Right,
    Inc,
    Dec,
    Get,
    Put,
    Loop,
    Endloop,
	Dump,

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
	"Get a single-byte character from the input list and store it under the data pointer. If there was no input, it will leave the cell unchanged."
};

const char COMMENT_CHAR = '#';