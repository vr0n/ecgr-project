#include "bestController.h"
#include "operate.h"
#include "execute.h"
#include <fstream>

using namespace std;

string instr[16];

int main(){
//    decToBin(8.345);
//    binToDec((MyFloat) "01101101101100000011000011010111");
//    operate("01101101101100000011000011010111");
    ifstream file("asm.txt");
    string reg;
    int i = 0;

    while ( getline(file, reg) ) {
        if ( reg[0] == '-' ) {
            continue;
        }

        if ( i > 16 ) {
            cout << "We caonly have 16 registers!" << endl;

            return 1;
        }
        instr[i] = reg;
        i += 1;
    }

    for ( int j = 0; j < ( sizeof(instr)/sizeof(*instr) ); j++ ) {
        if ( instr[j].empty() ) {
            continue;
        }
        cout << "main: Calling execute with " + instr[j] << endl;
        string binStr = execute(instr[j]);

        cout << "main: Calling operate" << endl;
        operate(binStr);
    }

    return 0;
}
