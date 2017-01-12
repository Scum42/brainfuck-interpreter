#include "args.h"

vector<string> convertArgs(int argc, char** argv)
{
    vector<string> result;

    for (int i = 0; i < argc; i++)
    {
        string arg = "";
        for (int j = 0; true; j++)
        {
            char c = argv[i][j];
            if (c == '\0') break;
            arg += c;
        }
        result.push_back(arg);
    }

    return result;
}