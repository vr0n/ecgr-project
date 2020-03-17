using namespace std;



string decodeRegister(string raw){
	//get integer value
	int temp = (int)stringToDouble(raw);
	//convert into binary of 4 bits
	return intToRegularBin(temp, 4);
}

string addZeros(int numZeros){
	string zeros = "";
	//make a string of specified bits of zeros
	for(int i = 0; i < numZeros; i++){
		zeros += "0";
	}
	return zeros;
}

//combine into instruction depending on which instruction it is
string oppToCode(string opp, string second, string third, string fourth){
	string translated = "";
	if(opp == "Set"){
		translated = "00000";
		translated += decodeRegister(second);
		translated += addZeros((4+4+15));
	}
	else if(opp == "Load"){
		translated = "00001";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros((4+15));
	}
	else if(opp == "Store"){
		translated = "00010";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros((4+15));
	}
	else if(opp == "Move"){
		translated = "00011";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros((4+15));
	}
	else if(opp == "Fadd"){
		translated = "00100";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "Fsub"){
		translated = "00101";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "Fneg"){
		translated = "00110";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros((4+15));
	}
	else if(opp == "Fmul"){
		translated = "00111";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "Fdiv"){
		translated = "01000";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "Floor"){
		translated = "01001";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "Ceil"){
		translated = "01010";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "Round"){
		translated = "01011";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "Fabs"){
		translated = "01100";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "Min"){
		translated = "01101";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "Max"){
		translated = "01110";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "Pow"){
		translated = "01111";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4);
		translated += intToRegularBin((int)stringToDouble(fourth), 15);
	}
	else if(opp == "Exp"){
		translated = "10000";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "Sqrt"){
		translated = "10001";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "B"){
		translated = "10010";
		translated += decodeRegister(second);
		translated += addZeros(4+4+15);
	}
	else if(opp == "BZ"){
		translated = "10011";
		translated += decodeRegister(second);
		translated += addZeros(4+4);
		translated += intToRegularBin((int)stringToDouble(third), 15);
	}
	else if(opp == "BN"){
		translated = "10100";
		translated += decodeRegister(second);
		translated += addZeros(4+4);
		translated += intToRegularBin((int)stringToDouble(third), 15);
	}
	else if(opp == "Nop"){
		translated = "10101";
		translated += addZeros(4+4+4+15);
	}
	else if(opp == "Halt"){
		translated = "10110";
		translated += addZeros(4+4+4+15);
	}
    else {
        cout << "execute: No oppCode found! Exiting and continuing" << endl;

        return translated;
    }

    cout << "execute: oppToCode is returning '" + translated + "'" << endl;
	return translated;
}

string execute( string line ) {
    string arr[4] = { "", "", "", "" };

    istringstream iss(line);

    cout << "execute: Grabbing words from line" << endl;

    int i = 0;
    for( string line; iss >> line; ){
        if( line[0] == '-' ) {
            break;
        }

        arr[i] = line;
        i++;
    }
    
    string var1 = arr[0];
    string var2 = arr[1];
    string var3 = arr[2];
    string var4 = arr[3];

    string binVal = oppToCode(var1, var2, var3, var4);

    return binVal;
}
