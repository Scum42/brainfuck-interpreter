==================================================================

BRAINFUCK INTERPRETER

Anthony Libardi

==================================================================

ABOUT

	"Brainfuck" (hereafter referred to as BF to avoid the obscenity) is a language designed primarily to challenge and amuse programmers (hence the name). It is based on the idea of a Turing Machine, a tape that extends infinitely left and right from the read/write head, which can either read the state of the cell it's over or write a 1 or a 0 to that cell. This idea was first created by Alan Turing, and was used to show that something as simple as this can theoretically compute anything that can be computed. This property of a language or system is now known as being "Turing complete."
	
	BF is essentially a Turing machine with extra features, along with the language to issue it commands. It uses the same principal of an infinite tape and a read/write head, except the cells may contain any 8-bit number rather than simply 1 or 0. Also, Importantly, in BF, all cells are initialized with the value 0. The language consists of only eight commands:
	
		> : Move the r/w head to the right
		< : Move the r/w head to the left
		+ : Increment the value in the cell under the r/w head
		- : Decrement the value in the cell under the r/w head
		[ : If the value under the r/w head is 0, jump to the matching ']' command
		] : If the value under the r/w head is not 0, jump to the matching '[' command
		. : Print the value under the r/w head, interpreted as an ASCII character
		, : Get one byte of input, interpreted as an ASCII character, and write that into the current cell
		
	But I've added one command for debbugging purposes, or as a simpler way to display output:
	
		* : Dump memory (display a visual representation of the tape and the values it contains)
		
==================================================================

USE

	Syntax:
	bf [ -? ] [ -b ] [ -d ] [ -D ] [ -c ] [ -j ] [ -u ] [ -r ] [ -q ] [ -Q ] [ -m ] [ -f <path> ] [ -s <script> ] [ -i <string> ]

	-? ............ Show this help menu.
	-b ............ Show help on how to write in Brainfuck.
	-d ............ Dump memory at the end of execution.
	-D ............ Dump memory after every command (combine with -q to avoid output interfering).
	-c ............ When dumping memory, display values as chars.
	-j ............ When dumping memory, display values as signed ints (-128 - 127).
	-u ............ When dumping memory, display values as unsigned ints (0 - 255). This is the default setting.
	-r ............ Show a performance report after execution.
	-q ............ Quiet (no output). Also suppresses memory dumping by the * command.
	-Q ............ Ignore input (all get commands return EOF).
	-m ............ Show minimized script before run.
	-f <path> ..... Run code from the given file.
	-s <script> ... Run code from the given string.
	-i <string> ... Sets the input as a string to use for execution.

==================================================================
