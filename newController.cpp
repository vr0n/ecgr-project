#include <iostream>
#include <cmath>
using namespace std;
class MyFloat{
	public:
	int sign = 0;
	int floatArray[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	int exp = 0;
	int mant = 0;
	MyFloat(string rawBin){
		//THIS IS A REVISION TEST
		for(int i = 31; i>=0; i--){
			floatArray[i] = ((int)rawBin[i]) - 48;
		}

		sign = floatArray[0];

		for(int i = 1; i<9; i++){
			if(floatArray[i] == 1){
				exp = exp + pow(2, (9-i));
			}
		}

		exp = exp - 127;

		for(int i = 9; i<32; i++){
			if(floatArray[i] == 1){
				mant = mant + pow(2, (32-i));
			}
		}
	}
};

double binToDec(MyFloat tempFloat){
	double dec = 0.0;
	dec = pow(tempFloat.mant, tempFloat.exp);
	if(tempFloat.sign){
		dec = -dec;
	}
	return dec;
};

int main(){
	string testFloat = "10001000001111001111000001011010";
	MyFloat myTestFloat(testFloat);
	
	double val = binToDec(myTestFloat);
	cout << val << endl;

	return 0;
}