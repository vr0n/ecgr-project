#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

//input: 32b string of 1's and 0's in IEEE 754 notation
//output: decimal result as a double
double binFloatToDecDouble(string rawBin){
  if(rawBin == "Positive_Infinity"){
    cout << "Positive_Infinity" <<endl;
    return  ((pow(2, 31))+1);
  }
  else if(rawBin == "Negative_Infinity"){
    cout << "Negative_Infinity" <<endl;
    return  (-(pow(2, 31))-1);
  }
  else if(rawBin == "NaN"){
    cout << "NaN" << endl;
    return 1337;
  }
	int sign = 0;
	int floatArray[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int exp = 0;
	double mant = 0.0;

	double dec = 0.0;

	//binary string to array
	for(int i = 31; i>=0; i--){
		floatArray[i] = ((int)rawBin[i]) - 48;
	}

	//extract sign
	sign = floatArray[0];

	//extract + adjust exponent
	for(int i = 1; i<9; i++){
		if(floatArray[i] == 1){
			exp = exp + pow(2, (8-i));
		}
	}

	exp = exp - 127;

	//extract + adjust mantissa
	for(int i = 9; i<32; i++){
		if(floatArray[i] == 1){
			mant = mant +(1/ pow(2, (i-8)));
		}
	}
	mant = mant + 1.0;

	//check for zero
	if(exp==-127 && mant==1.0){
		return 0;
	}
   
	//check for +inf, -inf, NaN
	if(exp==128){
		if(mant==1.0){
			if(sign==0){
				cout << "Positive_Infinity" <<endl;
				return  ((pow(2, 31))+1);
			}
			else{
				cout << "Negative_Infinity" << endl;
				return  (-(pow(2, 31))-1);
			}
		}
		else{
			cout << "NaN" << endl;
			return 1337;
		}
		  
	}

	//calculate based on parts of floatArray
	dec = ((pow(2, exp))*mant);
	if(sign==1){
		dec = -dec;
	}
	return dec;
}

//input: decimal number as a double
//output: 32b string of 1's and 0's in IEEE 754 notation
string decDoubleToBinFloat(double tempDec){
	string signBin = "0";
	string mantBin = "";
	string expBin = "";
	
	//check for zero
	if(tempDec == 0){
	  return "00000000000000000000000000000000";
	}
	//check for -inf
	if(tempDec<(-(pow(2, 31)))){
		return "Negative_Infinity";
	}
	//check for +inf
	if(tempDec>(pow(2, 31))){
		return "Positive_Infinity";
	}
	
//sign binary	
	if(tempDec<0){	
	signBin = "1";
		tempDec = abs(tempDec);
	}
	
//mantissa binary
	bool foundFirstOne = false;
	int loopNum = 0;
	int startingIndex = -1;
	int wholeDec = (int)(tempDec)/1;
	int expInt = 255;
	
	//calculate the whole number portion of mantissa
	while(wholeDec>0){
		loopNum = loopNum + 1;	
		if(wholeDec%2!=0){
			//flag the first "1" was found
			if(!foundFirstOne){
				foundFirstOne = true;
			}
			mantBin = "1" + mantBin;		  
		}
		else{
			mantBin = "0" + mantBin;
		}
		wholeDec = wholeDec/2;
       	}
	//calculate starting index of part of mantissa to be stored
        if(foundFirstOne){
		for(int i = 0; i<mantBin.length(); i++){
		  if(((int)mantBin[i])==49){
			startingIndex = i+1;
			i = mantBin.length();
		  }
		}
		//calculate exponent in base 10
		expInt = mantBin.length()-1;	
	}
	//calculate fractional portion of mantissa
	double fracDec = fmod(tempDec, 1);
	for(int i = mantBin.length(); i<=23; i++){
		loopNum = loopNum + 1;
		fracDec = fracDec*2;
		if(fracDec>=1){
			mantBin = mantBin + "1";
			//flag first "1" was found
			//calculate starting index of mantissa to be stored
			//extend loop to fill 23 bits
			//calculate exponent in base 10
			if(!foundFirstOne){
				foundFirstOne = true;
				startingIndex = loopNum;
				i = 0;
				expInt = -(loopNum);
			}	  
		}
		else{
			mantBin = mantBin + "0";
		}
		fracDec = fmod(fracDec, 1);
		//if still no first "1", keep calculating
		if((!foundFirstOne)&&(i==24)){
			i = 0;
		}
	}
	//trim mantissa to fit 23 bits based on starting index of first "1"
	mantBin = mantBin.substr(startingIndex, mantBin.length());

//exponent binary
	//adjust exponent for bias
	expInt = expInt + 127;
	//calculate exponent in binary
	for(int i = (pow(2, 7)); i>0; i = (i/2)){
		if(expInt >= i){
			expBin = expBin + "1";
			expInt = expInt - i;
		}
		else{
			expBin = expBin + "0";
		}
	}
	return (signBin + expBin + mantBin);
}


//inputs: int value to convert, number of bits in binary to put the value in
//output: unsigned binary string of specified number of bits in length
string decIntToBinUnsigned(int value, int numOfBits){
	string decoded = "";
	//converts integer to desired number of binary bits
	//TODO: Rachel, check can fit within desired number of bits
	for(int i = value; decoded.length()<numOfBits; i = i/2){
		if(i%2!=0){
			decoded = "1" + decoded;
		}
		else{
			decoded = "0" + decoded;
		}
	}
	return decoded;
}

//inputs: int value to convert, number of bits in binary to put the value in
//output: signed bit binary string of specified number of bits in length
string decIntToBinSigned(int value, int numOfBits){
	string decoded = "";
        decoded = decIntToBinUnsigned(value, (numOfBits-1));
	//converts to signed bit notation
	if(value >=0){
		decoded = "0" + decoded;
	}
	else{
		decoded = "1" + decoded;
	}
	return decoded;
}

//input: raw string that contains a double
//output: double that was within raw string
double stringRawToDecDouble(string rawString){
	string pureString = "";
	//gets rid of chars in string that are not "." or "-" or numeric
	for(int i = 0; i<rawString.length(); i++){
		if(((int)rawString[i] == 45)||
		((int)rawString[i] == 46)||
		(((int)rawString[i] > 47)&&((int)rawString[i] < 58))){
			pureString = pureString + rawString[i];
		}
	}
	double decodedDouble = 0.0;
	bool isNegative = false;
	int temp = 0;

	//find and convert floating point portion
	for(int i=0; i<pureString.length(); i++){
		if((int)pureString[i]==46){
			//split string if floating point
			string floatString = pureString.substr(i+1);
			pureString = pureString.substr(0, i);
			for(int x = 0; x < floatString.length(); x++){
				temp = (int)floatString[x] - 48;
				decodedDouble = decodedDouble + (temp * pow(.1, (x+1)));
			}
			i = pureString.length();
		}
	}

	//convert whole number portion
	for(int x = 0; x <pureString.length(); x++){
		if((x==0)&&((int)pureString[0] == 45)){
			isNegative = true;
		}
		else{
			temp = (int)pureString[x] - 48;
			decodedDouble = decodedDouble + (temp * pow(10, (pureString.length() -1 -x)));
		}
	}
	

	//if negative, make negative
	if(isNegative){
		decodedDouble = -decodedDouble;
	}
	return decodedDouble;
}

//input: raw string that contains a double
//output: 32b string of 1's and 0's in IEEE 754 notation
string stringRawToBinFloat(string rawString){
  return decDoubleToBinFloat(stringRawToDecDouble(rawString));
}

//input: raw string that contains the register number in decimal
//output: 4b unsigned binary string
string decodeRegister(string rawString){
  return decIntToBinUnsigned((int)stringRawToDecDouble(rawString), 4);
}

//input: int of number of zeros wanted
//output: string of that many zeros in length
string addZeros(int numZeros){
	string zeros = "";
	//make a string of specified bits of zeros
	for(int i = 0; i < numZeros; i++){
		zeros += "0";
	}
	return zeros;
}


//input: unsigned binary string
//output: decimal integer value
int binUnsignedToDecInt(string op ) {
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

//input: signed bit binary string
//output: decimal integer value
int binSignedToDecInt(string binSigned){
  int temp = 0;
  int decodedInt = 0;
  for(int x = 1; x <binSigned.length(); x++){
    temp = (int)binSigned[x] - 48;
    decodedInt = decodedInt + (temp * pow(2, (binSigned.length() -1 -x)));
  }
  if((int)binSigned[0] == 49){
    decodedInt = -decodedInt;
  }
  return decodedInt;
}

//returns the adjusted instruction memory index accounting for SET inserts
int instrLineAdjust(int realLine, string setPattern){
  int tempLine = 0;
  for(int i = 0; i<setPattern.length(); i++){
    if(((int)setPattern[i]-48) == 0){
      if(tempLine == realLine){
	realLine = i;
	i = setPattern.length();
      }
      tempLine ++;
    }
  }
  return realLine;
}

//returns number of SET ops given the SET pattern string
int numSetOps(string setPattern){
  int c = 0;
  for(int i = 0; i<setPattern.length(); i++){
    if((int)setPattern[i] == 49){
      c ++;
    }
  }
  return c;
}
