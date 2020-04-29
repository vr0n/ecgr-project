#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;


//TODO set/ reset flags
//TODO check for flag conditions

//Function prototypes
string alu_fadd(string, string);
string alu_fsub(string, string);
string alu_fneg(string);
string alu_fmul(string, string);
string alu_fdiv(string, string);
string alu_floor(string);
string alu_ceil(string);
string alu_round(string);
string alu_fabs(string);
string alu_min(string, string);
string alu_max(string, string);
string alu_pow(string, string);
string alu_exp(string);
string alu_sqrt(string);
string mux8(string, string, string);

//TODO: make bit-level
string alu_fadd( string v1, string v2 ) {
  
    double val1 = binFloatToDecDouble( v1 );
    double val2 = binFloatToDecDouble( v2 );

    double ans = val1 + val2;

    string ret = decDoubleToBinFloat(ans);

    return ret;
}

//TODO: make bit-level
string alu_fsub( string v1, string v2 ) {
  
    double val1 = binFloatToDecDouble( v1 );
    double val2 = binFloatToDecDouble( v2 );

    double ans = val1 - val2;

    string ret = decDoubleToBinFloat(ans);

    return ret;
}

string alu_fneg( string v1 ) {
    string sign = v1.substr(0, 1);

    if ( sign == "1" ) {
        v1[0] = '0';
    }

    if ( sign == "0" ) {
        v1[0] = '1';
    }

    return v1;
}

string alu_fmul( string v1, string v2 ) {
  
    double val1 = binFloatToDecDouble( v1 );
    double val2 = binFloatToDecDouble( v2 );

    double ans = val1 * val2;

    string ret = decDoubleToBinFloat(ans);

    return ret;
}

string alu_fdiv( string v1, string v2 ) {
    double val1 = binFloatToDecDouble( v1 );
    double val2 = binFloatToDecDouble( v2 );

    double ans = val1 / val2;

    string ret = decDoubleToBinFloat(ans);

    return ret;
}

//"round to integer"
string alu_floor( string v1 ) {
  //To accomplish this, if the form of the number is 2^exp * 1.mant, then all
	//mantissa bits that are more than 'exp' number of places from the radix are
	//set equal to zero. The other are left alone.
	int i;
	int expInt = 0;
	int expArray[8];
	int mantArray[23];
	string result = "";
	string tempIn = "";
	string tempOut = "";
	
	//Retreive the bits from the input value's exponent, and store them in an
	//array of ints. Also keep track of the total exponent value.
	for (i = 0; i < 8; i++) {
		expArray[i] = ((int)v1[i+1] - 48);
		expInt += (expArray[i] * pow(2, 7-i));
	}
	//Retrieve the bits from the input value's mantissa and store them
	//in an array of ints.
	for (i = 0; i < 23; i++) {
		mantArray[i] = ((int)v1[i+9] - 48);
	}
	
	//Fix the exponent's bias
	expInt -= 127;
	
	//If the input is positive, the floor function rounds down. This truncates
	//mantissa bits. If the input is negative, the floor function rounds the
	//mantissa bits up, therefore, it can be passed to the ceiling function as
	//a positive number, then have the result of that function be negated.
	if (((int)v1[0] - 48) == 0) {
		//This only works if the power that exponent is less than the total
		//amount of mantissa bits.
		if (expInt < 23) {
			for (i = expInt; i < 23; i++) {
				mantArray[i] = 0;
			}
		}
		
		//Should always default to a 0 given that this branch only processes positive
		//numbers. Leaving it here for futures debug purposes.
		if (((int)v1[0] - 48) == 0) {
			result += "0";
		}
		else {
			result += "1";
		}
		
		for (i = 0; i < 8; i++) {
			if (((int)v1[i+1] - 48) == 0) {
				result += "0";
			}
			else {
				result += "1";
			}
		}
		
		for (i = 0; i < 23; i++) {
			if (mantArray[i] == 0) {
				result += "0";
			}
			else {
				result += "1";
			}
		}
	}
	
	//Negate the input, then send to the ceiling function. Negate the result of the ceiling function.
	else {
		tempIn += alu_fneg(v1);
		tempOut += alu_ceil(tempIn);
		result += alu_fneg(tempOut);
	}
	
	return result;
}

//TODO: make bit-level
//"round to integer"
string alu_ceil( string v1 ) {
    double val1 = binFloatToDecDouble( v1 );

    double cl = ceil(val1);

    string ret = decDoubleToBinFloat(cl);

    return ret;
}

//TODO: make bit-level
//"round to integer"
string alu_round( string v1 ) {
    double val1 = binFloatToDecDouble( v1 );

    double rnd = round(val1);

    string ret = decDoubleToBinFloat(rnd);

    return ret;
}

string alu_fabs( string v1 ) {
  if(((int)v1[0] - 48) == 1) {
    v1[0] = '0';
  }
  return v1;
}

string alu_min(string v1, string v2){
  int sign1, sign2, i;
	int bits1[31];
	int bits2[31];
	
	sign1 = ((int)v1[0] - 48);
	sign2 = ((int)v2[0] - 48);
	
	//If the first input is positive, and the second is negative, right away we
	//know that the second input is the min.
	if (sign1 == 0 && sign2 == 1) {
		return v2;
	}
	//If the first input is negative, and the second is positive, right away we
	//know that the first input is the min.
	else if (sign1 == 1 && sign2 == 0) {
		return v1;
	}
	//If both inputs are negative, their other bits will have to be compared
	//in order to determine which is the max
	else if (sign1 == 1 && sign2 == 1) {
	  i = 1;
	  while (((int)v1[i] - 48) == ((int)v2[i] - 48)) {
  		i++;
  	}
  		
  	if (((int)v1[i] - 48) > ((int)v2[i] - 48)) {
  		return v1;
  	}
  	else {
  		return v2;
  	}
	}
	//If both inputs are positive, their other bits will have to be compered
	//in order to determine which in the max
	else {
		i = 1;
		while (((int)v1[i] - 48) == ((int)v2[i] - 48)) {
			i++;
		}
		
		if (((int)v1[i] - 48) > ((int)v2[i] - 48)) {
			return v2;
		}
		else {
			return v1;
		}
	}
}

string alu_max(string v1, string v2){
  int sign1, sign2, i;
	int bits1[31];
	int bits2[31];
	
	sign1 = (int)v1[0] - 48;
	sign2 = (int)v2[0] - 48;
	
	//If the first input is positive, and the second is negative, right away we
	//know that the first input is the max.
	if (sign1 == 0 && sign2 == 1) {
		return v1;
	}
	//If the first input is negative, and the second is positive, right away we
	//know that the second input is the max.
	else if (sign1 == 1 && sign2 == 0) {
		return v2;
	}
	//If both inputs are negative, their other bits will have to be compared
	//in order to determine which is the max
	else if (sign1 == 1 && sign2 == 1) {
		i = 1;
		while (((int)v1[i] - 48) == ((int)v2[i] - 48)) {
			i++;
		}
		
		if (((int)v1[i] - 48) > ((int)v2[i] - 48)) {
			return v2;
		}
		else {
			return v1;
		}
	}
	//If both inputs are positive, their other bits will have to be compered
	//in order to determine which in the max
	else {
		i = 1;
		while (((int)v1[i] - 48) == ((int)v2[i] - 48)) {
			i++;
		}
		
		if (((int)v1[i] - 48) > ((int)v2[i] - 48)) {
			return v1;
		}
		else {
			return v2;
		}
	}
}

string alu_pow(string v1, string v2){
  double val1 = binFloatToDecDouble(v1);
  int val2 = binSignedToDecInt(v2);
  
  string result = decDoubleToBinFloat(pow(val1, val2));

  return result;
}

string alu_exp(string v1){
  double e = 2.718281828;
  double val1 = binFloatToDecDouble(v1);

  string result = decDoubleToBinFloat(pow(e, val1));
  
  return result;
}

string alu_sqrt(string v1){
  double val1 = binFloatToDecDouble(v1);

  string result = decDoubleToBinFloat(sqrt(val1));

  return result;
}

//also doubles as mux18
string mux8(string option1, string option2, string ctrl_mux8){
  string theChosenOne = option1;
  if(ctrl_mux8 == "1"){
    theChosenOne = option2;
  }
  return theChosenOne;
}

void run_execute(string p1_reg[5][20]){
  string alu_src1 = p1_reg[2][7];
  string alu_src2 = mux8(p1_reg[2][8], p1_reg[2][9], p1_reg[2][2]);
  string alu_ctrl = p1_reg[2][3];

  string ctrl_flagNegative = "0";
  string ctrl_flagZero = "0";

  string ctrl_pcSrc = "0";
  string alu_output = "00000000000000000000000000000000";

  //determine alu output
  if (alu_ctrl == "00100"){//FADD
    alu_output = alu_fadd(alu_src1, alu_src2);
  }
  else if (alu_ctrl == "00101"){//FSUB
    alu_output = alu_fsub(alu_src1, alu_src2);
  }
  else if (alu_ctrl == "00110"){//FNEG
    alu_output = alu_fneg(alu_src1);
  }
  else if (alu_ctrl == "00111"){//FMUL
    alu_output = alu_fmul(alu_src1, alu_src2);
  }
  else if (alu_ctrl == "01000"){//FDIV
    alu_output = alu_fdiv(alu_src1, alu_src2);
  }
  else if (alu_ctrl == "01001"){//FLOOR
    alu_output = alu_floor(alu_src1);
  }
  else if (alu_ctrl == "01010"){//CEIL
    alu_output = alu_ceil(alu_src1);
  }
  else if (alu_ctrl == "01011"){//ROUND
    alu_output = alu_round(alu_src1);
  }
  else if (alu_ctrl == "01100"){//FABS
    alu_output = alu_fabs(alu_src1);
  }
  else if (alu_ctrl == "01101"){//MIN
    alu_output = alu_min(alu_src1, alu_src2);
  }
  else if (alu_ctrl == "01110"){//MAX
    alu_output = alu_max(alu_src1, alu_src2);
  }
  else if (alu_ctrl == "01111"){//POW
    alu_output = alu_pow(alu_src1, alu_src2);
  }
  else if (alu_ctrl == "10000"){//EXP
    alu_output = alu_exp(alu_src1);
  }
  else if (alu_ctrl == "10001"){//SQRT
    alu_output = alu_sqrt(alu_src1);
  }
  else if (alu_ctrl == "10011"){//BZ
    if(binFloatToDecDouble(alu_src2) == 0){
      ctrl_flagZero = "1";
    }
  }
  else if (alu_ctrl == "10100"){//BN
    if(binFloatToDecDouble(alu_src2) < 0){
      ctrl_flagNegative = "1";
    }
  }

  //adjust jump value for SET gaps
  int realJump = binUnsignedToDecInt(p1_reg[2][1]);
  string setPattern = p1_reg[0][2];
  realJump = instrLineAdjust(realJump, setPattern);

  p1_reg[2][1] = decIntToBinUnsigned(realJump, 8); // adjust jump value to account for SET opperations
  
  //determine if branch value will be used
  if(((p1_reg[2][4] == "1")&&(ctrl_flagNegative == "1"))||
     ((p1_reg[2][5] == "1")&&(ctrl_flagZero == "1"))||
     (p1_reg[2][6] == "1")){
    ctrl_pcSrc = "1";
  }

  p1_reg[2][12] = ctrl_pcSrc; //mux18 control
  p1_reg[0][1] = mux8(p1_reg[2][0], p1_reg[2][1], p1_reg[2][12]); //output mux18 to next PC value
  p1_reg[4][0] = alu_output; //alu output to input 0 of mux19

  
  
}

