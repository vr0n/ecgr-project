#include "bestController.h"
#include "operate.h"
#include "execute.h"
#include <fstream>

using namespace std;

ifstream registers("registerFile");
ifstream memory("memoryFile");

string registerFile[16];
string memoryFile[4096];

int main(){
//    decToBin(8.345);
//    binToDec((MyFloat) "01101101101100000011000011010111");
//    operate("01101101101100000011000011010111");
    string instr[16];
    string reg;
    string mem;

    for ( int i = 0; i < 16; i++ ){
        while ( getline(registers, reg) ){
            registerFile[i] = reg;
        }
    }

    for ( int i = 0; i < 4096; i++ ){
        while ( getline(memory, mem) ){
            memoryFile[i] = mem;
        }
    }

    cout << "test of register file" << endl;
    cout << registerFile[4] << endl;
    cout << "test of memory file" << endl;
    cout << memoryFile[4] << endl;

    ifstream file("asm.txt");
    string assem;
    int i = 0;

    while ( getline(file, assem) ) {
        if ( assem[0] == '-' ) {
            continue;
        }

        if ( i > 16 ) {
            cout << "We only have 16 registers!" << endl;

            return 1;
        }
        instr[i] = assem;
        
        i += 1;
    }

    for ( int j = 0; j < ( sizeof(instr)/sizeof(*instr) ); j++ ) {
        if ( instr[j].empty() ) {
            continue;
        }
        cout << "main: Calling execute with '" + instr[j] + "'" << endl;
        string binStr = execute(instr[j]);
        
        if ( binStr.empty() ) {
            continue;
        }

        cout << "main: Calling operate with '"  + binStr + "'" << endl;
        operate(binStr, registerFile, memoryFile);
    }

    return 0;
}
