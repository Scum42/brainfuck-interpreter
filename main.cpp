#include <iostream>
#include "args.h"

using namespace std;

int main(int argc, char** argv)
{
    vector<string> args = convertArgs(argc, argv);

    for each (string s in args) cout << s << endl;

    cin.get();
}