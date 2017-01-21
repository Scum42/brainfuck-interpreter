////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <sstream>

#include "args.h"
#include "commands.h"
#include "loopPair.h"

using namespace std;

////////////////////////////////////////////////////////

#pragma region PROTOTYPES

string trim(string script);
void execute();
void validate();
void validate(int pos);
unsigned int match(bool forward);
void memdump(Command cmd);

#pragma endregion

////////////////////////////////////////////////////////

#pragma region GLOBAL MEMORY

int pointer = 0;
map<int, char> memory;

string script = "";
stringstream input;
unsigned int currentInstruction = 0;

int memlower = 0;
int memupper = 0;

vector<LoopPair> loopStarts;
vector<LoopPair> loopEnds;

#pragma endregion

////////////////////////////////////////////////////////

#pragma region MAIN

int main(int argc, char** argv)
{
    vector<string> args = parseArgs(argc, argv);

    if (options[O_HELP])
    {
        cout << "Syntax:\nbf [ -? ] [ -d ] [ -D ] [ -c ] [ -u ] [ -j ] [ -m ] [ -q ] [ -f <filename> | -s <script_string> ] [ -i <input> ]\n\n";
        cout << "-?                    Show this help menu.\n";
        cout << "-d                    Dump memory at the end of execution.\n";
        cout << "-D                    Dump memory after every command (combine with -q to avoid output interfering).\n";
        cout << "-c                    When dumping memory, display values as chars\n";
        cout << "-u                    When dumping memory, display values as unsigned ints (0 - 255).\n";
        cout << "-j                    When dumping memory, display values as signed ints (-128 - 127). This is the default setting.\n";
        cout << "-m                    Show minimized script before run.\n";
        cout << "-q                    Quiet (no output)\n";
        cout << "-Q                    Ignore input (all get commands will return zero)\n";
        cout << "-f <filename>         Run code from the given file.\n";
        cout << "-s <script_string>    Run code from the given string.\n";
        cout << "-i <input>            Sets the input to use for execution.\n\n";
        exit(0);
    }

    if (options[O_FILENAME])
    {
        ifstream file(o_filename);
        stringstream ss;
        ss << file.rdbuf();
        script = ss.str();
    }
    else if (options[O_STRING_SCRIPT])
    {
        script = o_stringscript;
    }

    if (options[O_INPUT])
    {
        input << o_input;
    }

    script = trim(script);

    if (options[O_SHOW_MIN]) cout << "\nMinimized script:\n" << script << endl;

    execute();
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region TRIM

string trim(string script)
{
    string result = "";
    bool ignore = false;
    for each (char c in script)
    {
        bool isCmd = false;

        for (int i = 0; i < NUM_COMMANDS; i++)
        {
            if (ignore)
            {
                if (c == '\n') ignore = false;
                continue;
            }

            if (c == COMMAND_CHARS[i])
            {
                isCmd = true;
            }
            else if (c == COMMENT_CHAR)
            {
                ignore = true;
            }
        }

        if (isCmd) result += c;
    }

    return result;
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region VALIDATE

void validate() { validate(pointer); }
void validate(int pos)
{
    if (memory.find(pos) == memory.end())
    {
        memory[pos] = 0;
    }
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region MATCH

unsigned int match(bool forward)
{
    // See if this bracket is matched; return the matching instruction
    vector<LoopPair>& mylist = forward ? loopStarts : loopEnds;
    vector<LoopPair>& matchlist = forward ? loopEnds : loopStarts;
    for each (LoopPair lp in mylist)
    {
        if (lp.instruction == currentInstruction)
        {
            for each (LoopPair lp2 in matchlist)
            {
                if (lp.id == lp2.id)
                {
                    return lp2.instruction;
                }
            }
        }
    }

    // Set up my pair
    LoopPair myPair;
    lastID++;
    myPair.id = lastID;
    myPair.instruction = currentInstruction;

    // Match it
    int count = 1;
    int matchingInstruction = currentInstruction;
    bool couldFind = true;
    while (count > 0)
    {
        if (forward)
        {
            matchingInstruction++;
            if (matchingInstruction >= script.length())
            {
                couldFind = false;
                break;
            }

            if (script[matchingInstruction] == COMMAND_CHARS[Endloop]) count--;
            else if (script[matchingInstruction] == COMMAND_CHARS[Loop]) count++;
        }
        else
        {
            matchingInstruction--;
            if (matchingInstruction < 0)
            {
                couldFind = false;
                break;
            }

            if (script[matchingInstruction] == COMMAND_CHARS[Endloop]) count++;
            else if (script[matchingInstruction] == COMMAND_CHARS[Loop]) count--;
        }
    }

    // Quit if the command is unmatched
    if (!couldFind)
    {
        cout << "FATAL ERROR: Unmatched loop command found at position " << currentInstruction << endl;
        exit(1);
    }

    // Add the entries for the commands, then return the matching instruction
    LoopPair otherPair;
    otherPair.id = lastID;
    otherPair.instruction = matchingInstruction;

    mylist.push_back(myPair);
    matchlist.push_back(otherPair);

    return otherPair.instruction;
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region EXECUTE

void execute()
{
    //cout << "/// OUTPUT ///\n";
    cout << endl;
    for (; currentInstruction < script.length(); currentInstruction++)
    {
        char cmd = script[currentInstruction];

        Command command = NOT_A_COMMAND;

        for (int j = 0; j < NUM_COMMANDS; j++)
        {
            if (cmd == COMMAND_CHARS[j])
            {
                command = static_cast<Command>(j);
                break;
            }
        }

        if (command == NOT_A_COMMAND) continue;

        switch (command)
        {
            case Left:
            {
                pointer--;
                if (pointer < memlower) memlower = pointer;
                break;
            }
            case Right:
            {
                pointer++;
                if (pointer > memupper) memupper = pointer;
                break;
            }
            case Inc:
            {
                validate();
                memory[pointer]++;
                break;
            }
            case Dec:
            {
                validate();
                memory[pointer]--;
                break;
            }
            case Loop:
            {
                unsigned int matchingInstruction = match(true);
                validate();
                if (memory[pointer] == 0) currentInstruction = matchingInstruction;
                break;
            }
            case Endloop:
            {
                unsigned int matchingInstruction = match(false);
                validate();
                if (memory[pointer] != 0) currentInstruction = matchingInstruction;
                break;
            }
            case Get:
            {
                if (options[O_IGNORE_INPUT])
                {
                    memory[pointer] = 0;
                }
                else
                {
                    char in = 0;
                    if (input.good()) in = input.get();
                    if (in == -1) in = 0;
                    memory[pointer] = in;
                }
                break;
            }
            case Put:
            {
                if (!options[O_QUIET]) cout << memory[pointer];
                break;
            }
        }

        if (options[O_DUMP_VERBOSE]) memdump(command);
    }

    if (options[O_DUMP]) memdump(NOT_A_COMMAND);
    else cout << endl;
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region MEMDUMP

void memdump(Command cmd)
{
    if (cmd != NOT_A_COMMAND) cout << COMMAND_CHARS[cmd] << ": ";
    else cout << endl << "\nFINAL MEMORY: ";

    for (int i = memlower; i <= memupper; i++)
    {
        validate(i);
        cout << "[";
        if (i == pointer) cout << ">";
        else cout << " ";

        cout << left;

        if (options[O_DUMP_AS_CHAR])
        {
            cout << setw(1) << memory[i];
        }
        else if (options[O_DUMP_AS_UINT])
        {
            int outnum = static_cast<int>(memory[i]);
            if (outnum < 0) outnum += 256;
            cout << setw(3) << outnum;
        }
        else
        {
            cout << setw(4) << static_cast<int>(memory[i]);
        }
        
        cout << " ]";
    }

    if (cmd == Put)
    {
        cout << " out: '" << memory[pointer] << "'";
    }
    else if (cmd == Get)
    {
        cout << " in: ";
        if (memory[pointer] == 0) cout << "nul";
        else cout << "'" << memory[pointer] << "'";
    }
    else if ((cmd == Loop && memory[pointer] == 0) ||
             (cmd == Endloop && memory[pointer] != 0))
    {
        cout << " jump";
    }

    cout << endl;
}

#pragma endregion

////////////////////////////////////////////////////////
