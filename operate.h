#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

/*
  Take a 32-bit string and calculate based on
  our ISA documentation.
*/
void operate(string op){
    string oppCode = op.substr(0, 5);
    //giant else if statement, lol
    if ( op == "00000" ) { 
        cout << "Got Set" << endl;
	}
    else if ( op == "00001" ) { 
        cout << "Got Load" << endl;
	}
    else if ( op == "00010" ) { 
        cout << "Got Store" << endl;
	}
    else if ( op == "00011" ) { 
        cout << "Got Move" << endl;
	}
    else if ( op == "00100" ) { 
        cout << "Got Fadd" << endl;
	}
    else if ( op == "00101" ) { 
        cout << "Got Fsub" << endl;
	}
    else if ( op == "00110" ) { 
        cout << "Got Fneg" << endl;
	}
    else if ( op == "00111" ) { 
        cout << "Got Fmul" << endl;
	}
    else if ( op == "01000" ) { 
        cout << "Got Fdiv" << endl;
	}
    else if ( op == "01001" ) { 
        cout << "Got Floor" << endl;
	}
    else if ( op == "01010" ) { 
        cout << "Got Ceil" << endl;
	}
    else if ( op == "01011" ) { 
        cout << "Got Round" << endl;
	}
    else if ( op == "01100" ) { 
        cout << "Got Fabs" << endl;
	}
    else if ( op == "01101" ) { 
        cout << "Got Min" << endl;
	}
    else if ( op == "01110" ) { 
        cout << "Got Max" << endl;
	}
    else if ( op == "01111" ) { 
        cout << "Got Pow" << endl;
	}
    else if ( op == "10000" ) {
        cout << "Got Exp" << endl;
	}
    else if ( op == "10001") { 
        cout << "Got Sqrt" << endl;
	}
    else if ( op == "10010" ) {
        cout << "Got B" << endl;
	}
    else if ( op == "10011" ) {
        cout << "Got BZ" << endl;
	}
    else if ( op == "10100" ) {
        cout << "Got BN" << endl;
    }
    else if ( op == "10101" ) {
        cout << "Got Nop" << endl;
    }
    else if ( op == "10110" ) {
        cout << "Got Halt" << endl;
    }
}
