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
	 //TODO: CHECKS
	  //binary string to array
		for(int i = 31; i>=0; i--){
			floatArray[i] = ((int)rawBin[i]) - 48;
		}
		//extract sign, exponent, and mantissa
		sign = floatArray[0];

		for(int i = 1; i<9; i++){
			if(floatArray[i] == 1){
				exp = exp + pow(2, (8-i));
			}
		}

		exp = exp - 127;

		for(int i = 9; i<32; i++){
			if(floatArray[i] == 1){
				mant = mant +(1/ pow(2, (31-i)));
			}
		}
		mant = mant + 1.0;
	}
};

double binToDec(MyFloat tempFloat){
	double dec = 0.0;
	dec = pow(tempFloat.mant, tempFloat.exp);
	if(tempFloat.sign==1){
		dec = -dec;
	}
	return dec;
};

string decToBin(double tempDec){
	string signBin = "0";
	string mantBin = "";
	string expBin = "";
	
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
	while(wholeDec>0){
		loopNum = loopNum + 1;	
		if(wholeDec%2!=0){
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
        if(foundFirstOne){
		for(int i = 0; i<mantBin.length(); i++){
		  if(((int)mantBin[i])==49){
			startingIndex = i+1;
			i = mantBin.length();
		  }
		}
		expInt = mantBin.length()-1;	
	}
	double fracDec = fmod(tempDec, 1);
	for(int i = mantBin.length(); i<=23; i++){
		loopNum = loopNum + 1;
		fracDec = fracDec*2;
		if(fracDec>=1){
			mantBin = mantBin + "1";
			if(!foundFirstOne){
				foundFirstOne = true;
				startingIndex = loopNum;
				i = 0;
			}	  
		}
		else{
			mantBin = mantBin + "0";
		}
		fracDec = fmod(fracDec, 1);
		if((!foundFirstOne)&&(i==24)){
			i = 0;
		}
	}
	mantBin = mantBin.substr(startingIndex, mantBin.length());
	
//exponent binary	
	expInt = expInt + 127;
	for(int i = (pow(2, 7)); i>0; i = (i/2)){
		if(expInt >= i){
			expBin = expBin + "1";
			expInt = expInt - i;
		}
		else{
			expBin = expBin + "0";
		}
	}
	//print for testing purposes
	cout << "S: " + signBin << endl;
	cout << "E: " + expBin << endl;
	cout << "M: " + mantBin << endl;
	cout << endl;
	return (signBin + expBin + mantBin);
}

int main(){
	decToBin(6.345);

	return 0;
}
