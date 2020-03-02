#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

class MyFloat{
	public:
	int sign = 0;
	int floatArray[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int exp = 0;
	double mant = 0;
	MyFloat(string rawBin){
	  
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
	}
};

double binToDec(MyFloat tempFloat){
	double dec = 0.0;
	//check for zero
	if(tempFloat.exp==0){
		return 0;
	}
	//check for +inf, -inf, NaN
	if(tempFloat.exp==255){
		if(tempFloat.mant==0){
			if(tempFloat.sign==0){
				cout << "Positive_Infinity" <<endl;
				return 1337;
			}
			else{
				cout << "Negative_Infinity" << endl;
				return 1337;
			}
		}
		else{
			cout << "NaN" << endl;
			return 42;
		}
		  
	}
	//calculate based on parts of MyFloat
	dec = ((pow(2, tempFloat.exp))*tempFloat.mant);
	if(tempFloat.sign==1){
		dec = -dec;
	}
	return dec;
};

string decToBin(double tempDec){
	string signBin = "0";
	string mantBin = "";
	string expBin = "";
	
	//check for zero
	if(tempDec == 0){
	  return "0";
	}
	//check for -inf
	if(tempDec<(pow(2, -126))){
		return "Negative_Infinity";
	}
	//check for +inf
	if(tempDec>((pow(2, 127))*2)){
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

string stripUnwantedChars(string rawString){
	string pureString = "";
	//gets rid of chars in string that are not "." or "-" or numeric
	for(int i = 0; i<rawString.length(); i++){
		if(((int)rawString[i] == 45)||
		((int)rawString[i] == 46)||
		(((int)rawString[i] > 47)&&((int)rawString[i] < 58))){
			pureString = pureString + rawString[i];
		}
	}
	return pureString;
}

double stringToDouble(string rawString){
	rawString = stripUnwantedChars(rawString);
	double decodedDouble = 0.0;
	bool isNegative = false;
	int temp = 0;

	//find and convert floating point portion
	for(int i=0; i<rawString.length(); i++){
		if((int)rawString[i]==46){
			//split string if floating point
			string floatString = rawString.substr(i+1);
			rawString = rawString.substr(0, i);
			for(int x = 0; x < floatString.length(); x++){
				temp = (int)floatString[x] - 48;
				decodedDouble = decodedDouble + (temp * pow(.1, (x+1)));
			}
			i = rawString.length();
		}
	}

	//convert whole number portion
	for(int x = 0; x <rawString.length(); x++){
		if((x==0)&&((int)rawString[0] == 45)){
			isNegative = true;
		}
		else{
			temp = (int)rawString[x] - 48;
			decodedDouble = decodedDouble + (temp * pow(10, (rawString.length() -1 -x)));
		}
	}
	

	//if negative, make negative
	if(isNegative){
		decodedDouble = -decodedDouble;
	}

	return decodedDouble;
}

string intToRegularBin(int value, int numOfBits){
	string decoded = "";
	//converts integer to desired number of binary bits
	//TODO: Rachel, check can fit within desired number of bits
	for(int i = value; decoded.length()<=(numOfBits -1); i = i/2){
		if(i%2!=0){
			decoded = "1" + decoded;
		}
		else{
			decoded = "0" + decoded;
		}
	}
	//converts to signed bit notation because Rachel was tired
	//TODO: Rachel, make it 2's comp instead
	if(value >=0){
		decoded = "0" + decoded;
	}
	else{
		decoded = "1" + decoded;
	}
	return decoded;
}






