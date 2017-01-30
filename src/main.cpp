////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>

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
unsigned int totalCommands = 0;

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
		cout << "Placeholder: A new system for this help command is incoming.\n\n";
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

	auto begin = chrono::high_resolution_clock::now();
	execute();
	if (options[O_REPORT])
	{
		auto end = chrono::high_resolution_clock::now();
		auto dur = chrono::duration_cast<chrono::microseconds>(end - begin);

		int length = 30;
		cout << left << setw(length) << "Minimized script length: " << script.length() << " chars\n";
		cout << left << setw(length) << "Total commands run: " << totalCommands << " commands\n";
		cout << left << setw(length) << "Time to run: " << dur.count() / 1000.0f << " milliseconds\n";
	}
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region TRIM

string trim(string script)
{
	string result = "";
	int openingBracketCounter = 0;
	bool noBracketCommentYet = true;

	for each (char c in script)
	{
		bool isCmd = false;

		if (noBracketCommentYet && c == COMMAND_CHARS[C_LOOP_BEGIN])
		{
			openingBracketCounter++;
			continue;
		}
		else if (openingBracketCounter != 0)
		{
			if (c == COMMAND_CHARS[C_LOOP_BEGIN]) openingBracketCounter++;
			else if (c == COMMAND_CHARS[C_LOOP_END]) openingBracketCounter--;
			continue;
		}

		for each (char cmdChar in COMMAND_CHARS)
		{
			if (c == cmdChar)
			{
				noBracketCommentYet = false;
				isCmd = true;
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
	unsigned int matchingInstruction = currentInstruction;
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

			if (script[matchingInstruction] == COMMAND_CHARS[C_LOOP_END]) count--;
			else if (script[matchingInstruction] == COMMAND_CHARS[C_LOOP_BEGIN]) count++;
		}
		else
		{
			matchingInstruction--;
			if (matchingInstruction < 0)
			{
				couldFind = false;
				break;
			}

			if (script[matchingInstruction] == COMMAND_CHARS[C_LOOP_END]) count++;
			else if (script[matchingInstruction] == COMMAND_CHARS[C_LOOP_BEGIN]) count--;
		}
	}

	// Quit if the command is unmatched
	if (!couldFind)
	{
		cout << "FATAL ERROR: Unmatched loop command found at instruction " << currentInstruction << endl;
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
		case C_LEFT:
		{
			pointer--;
			if (pointer < memlower) memlower = pointer;
			break;
		}
		case C_RIGHT:
		{
			pointer++;
			if (pointer > memupper) memupper = pointer;
			break;
		}
		case C_INCREMENT:
		{
			validate();
			memory[pointer]++;
			break;
		}
		case C_DECREMENT:
		{
			validate();
			memory[pointer]--;
			break;
		}
		case C_LOOP_BEGIN:
		{
			unsigned int matchingInstruction = match(true);
			validate();
			if (memory[pointer] == 0) currentInstruction = matchingInstruction;
			break;
		}
		case C_LOOP_END:
		{
			unsigned int matchingInstruction = match(false);
			validate();
			if (memory[pointer] != 0) currentInstruction = matchingInstruction;
			break;
		}
		case C_GET:
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
		case C_PUT:
		{
			if (!options[O_QUIET]) cout << memory[pointer];
			break;
		}
		case C_DUMP:
		{
			memdump(C_DUMP);
			break;
		}
		}

		if (options[O_DUMP_VERBOSE]) memdump(command);
		if (options[O_REPORT]) totalCommands++;
	}

	if (options[O_DUMP]) memdump(NOT_A_COMMAND);
	else cout << endl;
}

#pragma endregion

////////////////////////////////////////////////////////

#pragma region MEMDUMP

void memdump(Command cmd)
{
	if (cmd == NOT_A_COMMAND) cout << endl << "\nFINAL MEMORY: ";
	else cout << COMMAND_CHARS[cmd] << ": ";

	for (int i = memlower; i <= memupper; i++)
	{
		validate(i);
		cout << "[";
		if (i == pointer) cout << ">";
		else cout << " ";

		cout << right;

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

	if (cmd == C_PUT)
	{
		cout << " out: '" << memory[pointer] << "'";
	}
	else if (cmd == C_GET)
	{
		cout << " in: ";
		if (memory[pointer] == 0) cout << "nul";
		else cout << "'" << memory[pointer] << "'";
	}
	else if ((cmd == C_LOOP_BEGIN && memory[pointer] == 0) ||
		(cmd == C_LOOP_END && memory[pointer] != 0))
	{
		cout << " jump";
	}

	cout << endl;
}

#pragma endregion

////////////////////////////////////////////////////////
