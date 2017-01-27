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

    for (unsigned int i = 0; i < args.size(); i++)
    {
        string arg = args[i];
        if (arg[0] == '-')
        {
            for (unsigned int j = 1; j < arg.length(); j++)
            {
                for (int k = 0; k < NUM_OPTIONS; k++)
                {
                    if (arg[j] == OPTION_CHARS[k])
                    {
                        options[k] = true;

                        switch (k)
                        {
                            case O_FILENAME:
                                o_filename = args[++i];
                                break;
                            case O_STRING_SCRIPT:
                                o_stringscript = args[++i];
                                break;
                            case O_INPUT:
                                o_input = args[++i];
                                break;
                        }
                    }
                }
            }
        }
    }

    return args;
}