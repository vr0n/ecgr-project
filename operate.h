using namespace std;

/*
  Take a 32-bit string and calculate based on
  our ISA documentation.
*/

int convBin( string op ) {
    int i; // for loop iterator
    int length = op.length() - 1; // length of string for iteration
    int val; //val for binary conversion either 0 or 1
    int dec = 0; //result
    int inc = 0; //keep track of where we are for binary purposes

    for ( i = length; i >= 0; i-- ) {
        val = (int) op[i] - 48;
        dec += ( val * pow(2, inc));
        inc++;
    }

    return dec;
}

void operate(string op, string registerFile[], string memoryFile[]){
    //ifstream registerFile ("registerFile");
    //ifstream memoryFile ("memoryFile");

    cout << "operate: Entered operate function" << endl;

    string oppCode = op.substr(0, 5);
    string r1 = op.substr(5, 4);
    string r2 = op.substr(9, 4);
    string r3 = op.substr(13, 4);
    string num = op.substr(17, 15); 

    //giant else if statement, lol
    // Set instruction
    if ( oppCode == "00000" ) { 
        int newR1 = convBin( r1 );
        int newNum = convBin( num );
        string val = decToBin( (double) newNum );
        registerFile[newR1] = val;
	}
    // Load instruction
    else if ( oppCode == "00001" ) { 
        //registerFile[r1] = memoryFile[r2]
	}
    // Store instruction
    else if ( oppCode == "00010" ) { 
        //memoryFile[r1] = registerFile[r2]
	}
    // Move instruction
    else if ( oppCode == "00011" ) { 
        //registerFile[r1] = registerFile[r2]
	}
    // Fadd instruction
    else if ( oppCode == "00100" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        
        double ans = val1 + val2;

        string val = decToBin( ans );

        registerFile[newR1] = val;
	}
    // Fsub instruction
    else if ( oppCode == "00101" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        
        double ans = val1 + val2;

        string val = decToBin( ans );
        registerFile[newR1] = val;
	}
    // Fneg instruction
    else if ( oppCode == "00110" ) { 
        //registerFile[r1] = ( registerFile[r2] * -1 )
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double ans = val1 * -1.00;

        string val = decToBin( ans );
        registerFile[newR1] = val;
	}
    // Fmul instruction
    else if ( oppCode == "00111" ) { 
        //registerFile[r1] = registerFile[r2] * registerFile[r3]
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        
        double ans = val1 * val2;

        string val = decToBin( ans );

        registerFile[newR1] = val;
	}
    // Fdiv instruction
    else if ( oppCode == "01000" ) { 
        //registerFile[r1] = registerFile[r2] / registerFile[r3]
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        
        double ans = val1 / val2;

        string val = decToBin( ans );
        registerFile[newR1] = val;
	}
    // Floor instruction
    else if ( oppCode == "01001" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        int ans = floor(val1);

        string val = decToBin( (double) ans );
        registerFile[newR1] = val;
	}
    // Ceil instruction
    else if ( oppCode == "01010" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );
        int ans = ceil(val1);

        string val = decToBin( (double) ans );
        registerFile[newR1] = val;
	}
    // Round instruction
    else if ( oppCode == "01011" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        int ans = round(val1);

        string val = decToBin( (double) ans );
        registerFile[newR1] = val;
	}
    // Fabs instruction
    else if ( oppCode == "01100" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        int ans = abs(val1);

        string val = decToBin( (double) ans );
        registerFile[newR1] = val;
	}
    // Min instruction
    else if ( oppCode == "01101" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );
        string val = "";

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        

        if ( val1 > val2 ) {
            string val = decToBin( val2 );
        }
        else {
            string val = decToBin( val1 );
        }

        registerFile[newR1] = val;
	}
    // Max instruction
    else if ( oppCode == "01110" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );
        string val = "";

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        

        if ( val1 < val2 ) {
            string val = decToBin( val2 );
        }
        else {
            string val = decToBin( val1 );
        }

        registerFile[newR1] = val;
	}
    // Pow instruction
    else if ( oppCode == "01111" ) { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newNum = convBin( num );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double ans = pow(val1, newNum);

        string val = decToBin( ans );
        registerFile[newR1] = val;
	}
    // Exp instruction
    else if ( oppCode == "10000" ) {
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double ans = exp(val1);

        string val = decToBin( ans );
        registerFile[newR1] = val;
	}
    // Sqrt instruction
    else if ( oppCode == "10001") { 
        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double ans = sqrt(val1);

        string val = decToBin( ans );
        registerFile[newR1] = val;
	}
    // B instruction
    else if ( oppCode == "10010" ) {

        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        
        double ans = val1 / val2;

        string val = decToBin( ans );
        registerFile[newR1] = val;
	}
    // BZ instruction
    else if ( oppCode == "10011" ) {

        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        
        double ans = val1 / val2;

        string val = decToBin( ans );
        registerFile[newR1] = val;
	}
    // BN instruction
    else if ( oppCode == "10100" ) {

        int newR1 = convBin( r1 );
        int newR2 = convBin( r2 );
        int newR3 = convBin( r3 );

        double val1 = binToDec( (MyFloat) registerFile[newR2] );        
        double val2 = binToDec( (MyFloat) registerFile[newR3] );        
        double ans = val1 / val2;

        string val = decToBin( ans );
        registerFile[newR1] = val;
    }
    // Nop instruction
    else if ( oppCode == "10101" ) {
        cout << "Nop" << endl;
    }
    // Halt instruction
    else if ( oppCode == "10110" ) {
        cout << "exiting..." << endl;

        return;
    }

    return;
}
