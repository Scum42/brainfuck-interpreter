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
    ']'
};

const char COMMENT_CHAR = '#';