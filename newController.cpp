#include <iostream>
#include <cmath>
using namespace std;
class MyFloat{
	public:
	int sign = 0;
	int floatArray[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int exponent = 0; //integer variable used to store the power which the base 2 is raised to
	double mant = 0; //variable for storing the fractional part of the mantissa
	MyFloat(string rawBin){
		
		
		for(int i = 31; i>=0; i--){
			floatArray[i] = ((int)rawBin[i]) - 48;
		}

		sign = floatArray[0];

		for(int i = 1; i<9; i++){
			if(floatArray[i] == 1){
				exponent += pow(2, (8-i));
			}
		}

		exponent -= 127;

		for(int i = 9; i<32; i++){
			if(floatArray[i] == 1){
				mant += pow(2, -(i-8));
			}
		}
	}
};

double binToDec(MyFloat tempFloat){
	double dec = 0.0;
	
	dec = pow(2, tempFloat.exponent) * (1 + tempFloat.mant);
	if(tempFloat.sign){
		dec = -dec;
	}
	return dec;
};

string specialCaseCheck(MyFloat tempFloat){
	string specialCase = "0";
	
	//Each of the three special cases requires an exponent of 128 (eight 1-bits)
	if(tempFloat.exponent == 128){
		//If the mantissa is 0, it can be either + or - infinity
		if(tempFloat.mant == 0){
			//Check whether it is + or - infinity
			if(tempFloat.sign == 0){
				specialCase = "Infinity";
			}
			else{
				specialCase = "-Infinity";
			}
		}
		//If the mantissa is nonzero, it will be NaN
		else{
			specialCase = "NaN";
		}
	}
	return specialCase;
};

int main(){
	string testFloat = "11111111100000001000000000000000"; 
	MyFloat myTestFloat(testFloat);
	string specialCaseOutput = specialCaseCheck(myTestFloat);
	
	//If the input meets a special case, output the corresponding string.
	//If not, then run the conversion
	if(specialCaseOutput != "0"){
		cout << specialCaseOutput << endl;
	}
	else{
		double val = binToDec(myTestFloat);
		cout << val << endl;
	}
	return 0;
}