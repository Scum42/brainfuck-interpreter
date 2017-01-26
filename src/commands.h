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

const char COMMENT_CHAR = '#';