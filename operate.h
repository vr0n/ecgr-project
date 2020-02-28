using namespace std;

/*
  Take a 32-bit string and calculate based on
  our ISA documentation.
*/
string registerFile[16] = { "000100010100010001010001001000100","010100010001110001100101000100010","010010011000100001000010000101100","010010010010010010010001000100100","010001000100010000100010001001000","010001000100010010001000100100100","100010001000100010101010101001000","011010010101000111100111100001000","001010010100100100100100101101000","100100100100100100010010010010100","001010010100100100100100101000100","011010001010010001000100000000000","000000000000000000000000000000000","000000000000000000000000000000000","000000000000000000000000000000000","000000000000000000000000000000000",}

int convBin( string op ) {
    for i in op
}

void operate(string op){
    string oppCode = op.substr(0, 5);
    string r1 = op.substr(5, 4);
    string r2 = op.substr(9, 4);
    string r3 = op.substr(13, 4);
    string num = op.substr(17, 15); 

    //giant else if statement, lol
    // Set instruction
    if ( oppCode == "00000" ) { 
        //registerFile[r1] = num
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
        //registerFile[r1] = registerFile[r2] + registerFile[r3]
	}
    // Fsub instruction
    else if ( oppCode == "00101" ) { 
        //registerFile[r1] = registerFile[r2] - registerFile[r3]
	}
    // Fneg instruction
    else if ( oppCode == "00110" ) { 
        //registerFile[r1] = ( registerFile[r2] * -1 )
	}
    // Fmul instruction
    else if ( oppCode == "00111" ) { 
        //registerFile[r1] = registerFile[r2] * registerFile[r3]
	}
    // Fdiv instruction
    else if ( oppCode == "01000" ) { 
        //registerFile[r1] = registerFile[r2] / registerFile[r3]
	}
    // Floor instruction
    else if ( oppCode == "01001" ) { 

	}
    // Ceil instruction
    else if ( oppCode == "01010" ) { 

	}
    // Round instruction
    else if ( oppCode == "01011" ) { 

	}
    // Fabs instruction
    else if ( oppCode == "01100" ) { 

	}
    // Min instruction
    else if ( oppCode == "01101" ) { 

	}
    // Max instruction
    else if ( oppCode == "01110" ) { 

	}
    // Pow instruction
    else if ( oppCode == "01111" ) { 

	}
    // Exp instruction
    else if ( oppCode == "10000" ) {

	}
    // Sqrt instruction
    else if ( oppCode == "10001") { 

	}
    // B instruction
    else if ( oppCode == "10010" ) {

	}
    // BZ instruction
    else if ( oppCode == "10011" ) {

	}
    // BN instruction
    else if ( oppCode == "10100" ) {

    }
    // Nop instruction
    else if ( oppCode == "10101" ) {

    }
    // Halt instruction
    else if ( oppCode == "10110" ) {

    }
}
