////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <map>

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
void memdump();

#pragma endregion

////////////////////////////////////////////////////////

#pragma region GLOBAL MEMORY

int pointer = 0;
map<int, char> memory;

string script = "";
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
    vector<string> args = convertArgs(argc, argv);
    //for each (string s in args) cout << s << endl;

    script = trim(args[1]);
    execute();

    //cin.get();
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region TRIM

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

        if (command == NOT_A_COMMAND) return;

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
                break;
            }
            case Put:
            {
                cout << memory[pointer];
                break;
            }
        }

        //memdump();
    }

    memdump();
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region MEMDUMP

void memdump()
{
    cout << "\nMEMORY: ";
    for (int i = memlower; i <= memupper; i++)
    {
        validate(i);
        cout << "[ " << left << setw(4) << static_cast<int>(memory[i]) << " ]";
    }
    cout << endl;
}

#pragma endregion

////////////////////////////////////////////////////////
