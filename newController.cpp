#include <iostream>
#include <cmath>
using namespace std;
class MyFloat{
	public:
	int sign = 0;
	int floatArray[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int exponent = 0;
	double mant = 0;
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

int main(){
	string testFloat = "01000010010000000000000100000000";
	MyFloat myTestFloat(testFloat);
	
	double val = binToDec(myTestFloat);
	cout << val << endl;
	return 0;
}