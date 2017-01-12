#include <iostream>
#include <map>

#include "args.h"
#include "commands.h"

using namespace std;
map<int, char> memory;

string trim(string script);
bool execute(char cmd);

int main(int argc, char** argv)
{
    vector<string> args = convertArgs(argc, argv);
    for each (string s in args) cout << s << endl;

    string script = trim(args[1]);
    cout << endl << script << endl;

    system("pause");
}

///// TRIM /////////////////////////////////////////////////////

string trim(string script)
{
    string result = "";
    for each (char c in script)
    {
        bool isCmd = false;
        
        for (int i = 0; i < NUM_COMMANDS; i++)
            if (c == COMMAND_CHARS[i])
                isCmd = true;

        if (isCmd) result += c;
    }

    return result;
}

///// EXECUTE //////////////////////////////////////////////////

bool execute(char cmd)
{
    return true;
}