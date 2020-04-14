#include "bestController.h"
#include "operate.h"
#include "execute.h"
#include <fstream>

using namespace std;

string registerFile[16];
string memoryFile[4096];

string vals[16] = {"01000000100000000000000000000000","01000000100000000000000000000000","00000000000000000000000000000000","01000001100000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000","00000000000000000000000000000000"};

void readFiles() {
    ifstream registers("registerFile");
    ifstream memory("memoryFile");

    int k = 0;
    while ( !registers.eof() ) {
        getline( registers, registerFile[k] );
        k++;
    }
    registers.close();

    k = 0;
    while ( !memory.eof() ) {
        getline( memory, memoryFile[k] );
        k++;
    }
    memory.close();
}

void writeFiles() {
    ofstream newRegisters;
    ofstream newMemory;
    newRegisters.open("registerFile");
    newMemory.open("memoryFile");
    int k = 0;

    for ( k = 0; k < 16; k++ ){
            newRegisters << vals[k] + "\n";
    }
    newRegisters.close();

    for ( k = 0; k < 4096; k++ ){
        newMemory << memoryFile[k] + "\n";
    }
    newMemory.close();
}

int main(){
    string instr[16];
    string reg;
    string mem;

    readFiles();

    ifstream file("test_files/isa_test0.txt");
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
        cout << "\nmain: Calling execute with '" + instr[j] + "'" << endl;
        if (instr[j] == "Halt" ){
            cout << "main: Halting!" << endl;
            writeFiles();
            return 0;
        }
        string binStr = execute(instr[j]);
        
        if ( binStr.empty() ) {
            continue;
        }

        cout << "main: Calling operate with '"  + binStr + "'" << endl;
        operate(binStr, registerFile, memoryFile);
    }

    writeFiles();

    return 0;
}
