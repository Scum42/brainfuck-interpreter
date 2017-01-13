#include "args.h"

bitset<NUM_OPTIONS> options;
string o_filename;
string o_stringscript;
string o_input;

vector<string> parseArgs(int argc, char** argv)
{
    vector<string> args;

    for (int i = 0; i < argc; i++)
    {
        string arg = "";
        for (int j = 0; true; j++)
        {
            char c = argv[i][j];
            if (c == '\0') break;
            arg += c;
        }
        args.push_back(arg);
    }

    for (int i = 0; i < args.size(); i++)
    {
        string arg = args[i];
        if (arg[0] == '-')
        {
            for (int j = 1; j < arg.length(); j++)
            {
                switch (arg[j])
                {
                    case 'd':
                        options[O_DUMP] = true;
                        break;
                    case 'D':
                        options[O_DUMP_VERBOSE] = true;
                        break;
                    case 'm':
                        options[O_SHOW_MIN] = true;
                        break;
                    case 'f':
                        options[O_FILENAME] = true;
                        o_filename = args[++i];
                        break;
                    case 's':
                        options[O_STRING_SCRIPT] = true;
                        o_stringscript = args[++i];
                        break;
                    case 'i':
                        options[O_INPUT] = true;
                        o_input = args[++i];
                        break;
                    case '?':
                        options[O_HELP] = true;
                        break;
                }
            }
        }
    }

    return args;
}