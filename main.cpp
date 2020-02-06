#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <bits/stdc++.h>

using namespace std;

//Function prototypes
vector<int> conversionMenu();
int power(int);
vector<int> stringToVectorofInts(string);
vector<int> getExponent(vector<int>);
vector<int> getMantissa(vector<int>);
int expToDec(vector<int>);
float mantissaBinToDec(vector<int>);
float fpToDec(int, int, float);
int setSignBit(float);
vector<int> setExponentBits(float);
vector<int> setMantissaBits(vector<int>, float);

//The framework for determining which conversion the user wishes to do
vector<int> guidedConversion() {
    int signBit;
    int exponentSum;
    int choice = 2;
    float mantissaMultiplier;
    vector<int> IEEE754(32, 0);
    vector<int> exponent(8, 0);
    vector<int> mantissa(23, 0);
    
    //Menu to prompt user for which type of conversion they are making
    cout << endl << "Which conversion would you like to make?" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "0 - Base-10 Decimal --> IEEE-754 Floating Point (Binary Format)" << endl;
    cout << "1 - IEEE-754 Floating Point (Binary Format) --> Base-10 Decimal" << endl << endl;
    cin >> choice;
    
    //Loops through same choices if user enters invalid choice
    while(choice < 0 || choice > 1) {
        choice = 2;
        cout << endl << "NOT A VALID SELECTION " << choice << endl;
        cout << "Which conversion would you like to make?" << endl;
        cout << "---------------------------------------------------------------" << endl;
        cout << "0 - Base-10 Decimal --> IEEE-754 Floating Point (Binary Format)" << endl;
        cout << "1 - IEEE-754 Floating Point (Binary Format) --> Base-10 Decimal" << endl << endl;
        cin >> choice;
    }
    
    //User chose to convert Base-10 decimal to IEEE-754
    if(choice == 0) {
        string inputStr;
        float input;
        
        cout << endl << "Input a Base-10 decimal number: ";
        cin >> inputStr;
        
        //Case where user inputs infinity
        if(inputStr == "infinity" || inputStr == "Infinity") {
            for(int i = 1; i < 9; i++) {
                IEEE754[i] = 1;
            }
            
            cout << "IEEE-754 floating point representation: ";
            for(int i = 0; i < 32; i++) {
                cout << IEEE754[i];
            }
            cout << endl << endl;
        }
        //Case where user inputs negative infinity
        else if(inputStr == "-infinity" || inputStr == "-Infinity") {
            for(int i = 0; i < 9; i++) {
                IEEE754[i] = 1;
            }
            
            cout << "IEEE-754 floating point representation: ";
            for(int i = 0; i < 32; i++) {
                cout << IEEE754[i];
            }
            cout << endl << endl;
        }
        //Case where user inputs not a number
        else if(inputStr == "NaN" || inputStr == "nan" || inputStr == "NAN") {
            for(int i = 1; i < 32; i++) {
                IEEE754[i] = 1;
            }
            
            cout << "IEEE-754 floating point representation: ";
            for(int i = 0; i < 32; i++) {
                cout << IEEE754[i];
            }
            cout << endl << endl;
        }
        //Case where user inputs a valid decimal number
        else {
            //Function which parses input string into a float datatype
            input = stof(inputStr);
            
            //Determines whether the input is positive or negative and sets the
            //sign bit accordingly
            IEEE754[0] = setSignBit(input);
            
            //Determines the proper binary value to represent the base 2 multiplier
            //and sets the 8 bits equal to a vector of ints of length 8
            exponent = setExponentBits(input);
            
            //Copies the previously calculated bits to the final vector which
            //represents the IEEE-754 format for floating point numbers
            for(int i = 1; i < 9; i++) {
                IEEE754[i] = exponent[i-1];
            }
            
            //Determines the proper binary value to represent the mantissa and
            //sets the 23 bits equal to a vector of ints of length 23
            mantissa = setMantissaBits(exponent, input);
            
            //Copies the previously calculated bits over to the end of the final
            //IEEE-754 vector
            for(int i = 9; i < 32; i++) {
                IEEE754[i] = mantissa[i-9];
            }
            
            //Output the original base-10 decimal number again followed by the
            //calculated IEEE-754 floating point number
            cout << endl << "Base-10 decimal number: " << inputStr << endl;
            cout << "IEEE-754 floating point representation: ";
            for(int i = 0; i < 32; i++) {
                cout << IEEE754[i];
            }
            cout << endl << endl;
        }
    }
    
    //User chose to convert IEEE-754 to decimal
    else {
        bool nonBinary = false;
        choice = 2;
        
        cout << endl << "Which mode would you like to use?" << endl;
        cout << "-------------------------------------------------------------------------------------------" << endl;
        cout << "0 - INTERACTIVE (Enter Sign Bit, Exponent Bits, and Mantissa as separate binary strings.)" << endl;
        cout << "1 - ADVANCED (Enter Sign Bit, Exponent Bits, and Mastissa all as one 32-bit binary string.)" << endl << endl;
        cin >> choice;
        
        //Loops through same choices if user enter invalid choice
        while(choice < 0 || choice > 1) {
            cout << endl << "NOT A VALID SELECTION" << endl;
            cout << endl << "Which mode would you like to use?" << endl;
            cout << "-------------------------------------------------------------------------------------------" << endl;
            cout << "0 - INTERACTIVE (Enter Sign Bit, Exponent Bits, and Mantissa as separate binary strings.)" << endl;
            cout << "1 - ADVANCED (Enter Sign Bit, Exponent Bits, and Mastissa all as one 32-bit binary string.)" << endl << endl;
            cin >> choice;
        }
        
        //User chose interactive mode
        if(choice == 0) {
            string exponentStr;
            string mantissaStr;
            
            choice = 2;
            
            //Prompt user for first bit (Sign Bit)
            cout << "What is the first bit (Sign Bit)?" << endl;
            cout << "---------------------------------" << endl;
            cout << "0 - Positive decimal resultant" << endl;
            cout << "1 - Negative decimal resultant" << endl << endl;
            cin >> choice;
            
            //Loop while user input in invalid
            while(choice < 0 || choice > 1) {
                cout << endl << "NOT A VALID SELECTION" << endl;
                cout << "What is the first bit (Sign Bit)?" << endl;
                cout << "---------------------------------" << endl;
                cout << "0 - Positive decimal resultant" << endl;
                cout << "1 - Negative decimal resultant" << endl << endl;
                cin >> choice;
            }
            
            //Set choice equal to sign bit
            signBit = choice;
            choice = 2;
            
            //Prompt the user for the exponent bits
            cout << endl << "What are the exponent bits? (Enter as 8-bit binary number)" << endl;
            cout << "----------------------------------------------------------" << endl;
            cin >> exponentStr;
            
            exponent = stringToVectorofInts(exponentStr);
            
            //Test to see if user put in non-binary values in the string
            for(int i = 0; i < exponent.size(); i++) {
                if(exponent[i] > 1 || exponent[i] < 0) {
                    nonBinary = true;
                }
            }
            
            //Loop while too few bits, too many bits, or invalid bits were input
            while(exponent.size() != 8 || nonBinary == true) {
                //Too many bits input
                if(exponent.size() > 8 && nonBinary == false) {
                    cout << endl << "You input too many bits." << endl;
                    cout << endl << "What are the exponent bits? (Enter as 8-bit binary number)" << endl;
                    cout << "----------------------------------------------------------" << endl;
                    cin >> exponentStr;
                    
                    exponent = stringToVectorofInts(exponentStr);
                    
                    for(int i = 0; i < exponent.size(); i++) {
                        if(exponent[i] > 1 || exponent[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
                //Too few bits input
                else if(exponent.size() < 8 && nonBinary == false) {
                    cout << endl << "You input too few bits." << endl;
                    cout << endl << "What are the exponent bits? (Enter as 8-bit binary number)" << endl;
                    cout << "----------------------------------------------------------" << endl;
                    cin >> exponentStr;
                    
                    exponent = stringToVectorofInts(exponentStr);
                    
                    for(int i = 0; i < exponent.size(); i++) {
                        if(exponent[i] > 1 || exponent[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
                //Input values for binary string that are not 1's or 0's
                else if (nonBinary == true) {
                    cout << endl << "You entered values in the binary string that are non-binary" << endl;
                    cout << endl << "What are the exponent bits? (Enter as 8-bit binary number)" << endl;
                    cout << "----------------------------------------------------------" << endl;
                    cin >> exponentStr;
                    
                    exponent = stringToVectorofInts(exponentStr);
                    nonBinary = false;
                    
                    for(int i = 0; i < exponent.size(); i++) {
                        if(exponent[i] > 1 || exponent[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
            }
            
            //Prompt the user to the mantissa bits
            cout << endl << "What are the mantissa bits? (Enter as 23-bit binary number)" << endl;
            cout << "-----------------------------------------------------------" << endl;
            cin >> mantissaStr;
            
            mantissa = stringToVectorofInts(mantissaStr);
            
            //Test to see if user put in non-binary values in the string
            for(int i = 0; i < mantissa.size(); i++) {
                if(mantissa[i] > 1 || mantissa[i] < 0) {
                    nonBinary = true;
                }
            }
            
            //Loop while too few bits, too many bits, or invalid bits were input
            while(mantissa.size() != 23 || nonBinary == true) {
                //Too many bits input
                if(mantissa.size() > 23 && nonBinary == false) {
                    cout << endl << "You input too many bits." << endl;
                    cout << endl << "What are the mantissa bits? (Enter as 23-bit binary number)" << endl;
                    cout << "----------------------------------------------------------" << endl;
                    cin >> mantissaStr;
                    
                    mantissa = stringToVectorofInts(mantissaStr);
                    
                    for(int i = 0; i < mantissa.size(); i++) {
                        if(mantissa[i] > 1 || mantissa[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
                //Too few bits input
                else if(mantissa.size() < 23 && nonBinary == false) {
                    cout << endl << "You input too few bits." << endl;
                    cout << endl << "What are the mantissa bits? (Enter as 23-bit binary number)" << endl;
                    cout << "----------------------------------------------------------" << endl;
                    cin >> mantissaStr;
                    
                    mantissa = stringToVectorofInts(mantissaStr);
                    
                    for(int i = 0; i < mantissa.size(); i++) {
                        if(mantissa[i] > 1 || mantissa[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
                //Input values for binary string that are not 1's or 0's
                else if (nonBinary == true) {
                    cout << endl << "You entered values in the binary string that are non-binary" << endl;
                    cout << endl << "What are the exponent bits? (Enter as 8-bit binary number)" << endl;
                    cout << "----------------------------------------------------------" << endl;
                    cin >> mantissaStr;
                    
                    mantissa = stringToVectorofInts(mantissaStr);
                    nonBinary = false;
                    
                    for(int i = 0; i < mantissa.size(); i++) {
                        if(mantissa[i] > 1 || mantissa[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
            }
        }
        
        //User chose advanced mode
        else {
            string IEEE754str;

            cout << endl << "Enter a 32-bit binary string (Enter as a 32-bit binary number)" << endl;
            cout << "--------------------------------------------------------------" << endl;
            cin >> IEEE754str;
            
            IEEE754 = stringToVectorofInts(IEEE754str);
            
            //Test to see if user put in non-binary values in the string
            for(int i = 0; i < IEEE754.size(); i++) {
                if(IEEE754[i] > 1 || IEEE754[i] < 0) {
                    nonBinary = true;
                }
            }
            
            //Loop while too few bits, too many bits, or invalid bits were input
            while(IEEE754.size() != 32 || nonBinary == true) {
                //Too many bits input
                if(IEEE754.size() > 8 && nonBinary == false) {
                    cout << endl << "You input too many bits." << endl;
                    cout << endl << "Enter a 32-bit binary string (Enter as a binary number)" << endl;
                    cout << "-------------------------------------------------------" << endl;
                    cin >> IEEE754str;
                    
                    IEEE754 = stringToVectorofInts(IEEE754str);
                    
                    for(int i = 0; i < IEEE754.size(); i++) {
                        if(IEEE754[i] > 1 || IEEE754[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
                //Too few bits input
                else if(IEEE754.size() < 8 && nonBinary == false) {
                    cout << endl << "You input too few bits." << endl;
                    cout << endl << "Enter a 32-bit binary string (Enter as a binary number)" << endl;
                    cout << "-------------------------------------------------------" << endl;
                    cin >> IEEE754str;
                    
                    IEEE754 = stringToVectorofInts(IEEE754str);
                    
                    for(int i = 0; i < IEEE754.size(); i++) {
                        if(IEEE754[i] > 1 || IEEE754[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
                //Input values for binary string that are not 1's or 0's
                else if (nonBinary == true) {
                    cout << endl << "You entered values in the binary string that are non-binary" << endl;
                    cout << endl << "Enter a 32-bit binary string (Enter as a binary number)" << endl;
                    cout << "-------------------------------------------------------" << endl;
                    cin >> IEEE754str;
                    
                    IEEE754 = stringToVectorofInts(IEEE754str);
                    nonBinary = false;
                    
                    for(int i = 0; i < IEEE754.size(); i++) {
                        if(IEEE754[i] > 1 || IEEE754[i] < 0) {
                            nonBinary = true;
                        }
                    }
                }
            }
            
            signBit = IEEE754[0];
            exponent = getExponent(IEEE754);
            mantissa = getMantissa(IEEE754);
        }
        
        exponentSum = expToDec(exponent);
        mantissaMultiplier = mantissaBinToDec(mantissa);
        
        cout << endl << "IEEE-754 floating point number: " << signBit;
        
        for(int i = 0; i < exponent.size(); i++) {
            cout << exponent[i];
        }
        
        for(int i = 0; i < mantissa.size(); i++) {
            cout << mantissa[i];
        }
        
        cout << endl;
        cout << "Base-10 decimal representation: " << fpToDec(signBit, exponentSum, mantissaMultiplier) << endl << endl;
    }
    
    return IEEE754;
}

//Function which takes in an exponent and returns the value of 2 raised to
//that exponent
int power(int exponent) {
    int result = 1;
    
    if(exponent > 0) {
        while(exponent > 0) {
            result = result * 2;
            exponent--;
        }
    }
    
    return result;
}

//Takes in a single string of binary integers, then outputs a vector of the same
//length as the string, with each index housing a subsequent binary digit
vector<int> stringToVectorofInts(string binaryStr) {
    vector<int> vectorOfInts;
    
    for(int i = 0; i < binaryStr.size(); i++) {
        vectorOfInts.push_back(binaryStr[i] - '0');
    }
    
    return vectorOfInts;
}

//Takes in the full 32-bit IEEE754 floating point vector, then copies the bits at
//indicies 1 through 8 a new vector of length 8
vector<int> getExponent(vector<int> IEEE754) {
    vector<int> exponent;
    
    for(int i = 1; i <= 9; i++) {
        exponent.push_back(IEEE754[i]);
    }
    
    return exponent;
}

//Takes in the full 32-bit IEEE754 floating point vector, then uses the bits at
//indices 9 through 31 to calculate the mantissa
vector<int> getMantissa(vector<int> IEEE754) {
    vector<int> mantissa;
    
    for(int i = 9; i <= 31; i++) {
        mantissa.push_back(IEEE754[i]);
    }
    
    return mantissa;
}

//Takes in the exponent bits and uses them to determine the actual exponent 
//that the two multiplier is raised to
int expToDec(vector<int> exponent) {
    int exponentSum = -127;
    
    for(int i = 0; i <= 7; i++) {
        if(exponent[i] == 1) {
            exponentSum += power(7-i);
        }
    }
    
    return exponentSum;
}

//Takes in the bits found for the mantissa and converts them into a usable
//mantissa multiplier
float mantissaBinToDec(vector<int> mantissa) {
    float mantissaMultiplier = 0.0;
    float fraction;
    
    for(int i = 0; i < mantissa.size(); i++) {
        fraction = 0;
        if(mantissa[i] == 1) {
            fraction = 1.0 / (power(i) * 2);
        }
        mantissaMultiplier += fraction;
    }
    
    mantissaMultiplier += 1.0;
    
    return mantissaMultiplier;
}

//Takes in the sign bit, integer exponent which the 2 muliplier is raised to,
//and the mantissa multiplier and calculates the base-10 decimal number which
//the input 32-bit IEEE754 floating point number represents
float fpToDec (int signBit, int exponentSum, float mantissaMultiplier) {
    float floatingPoint = (float)power(exponentSum) * mantissaMultiplier;
    
    if(signBit == 1) {
        floatingPoint *= -1.0;
    }
    
    return floatingPoint;
}

//A simple function which outputs a zero if the base-10 input is greater than
//zero, or outputs a 1 if the input is less than zero
int setSignBit(float input) {
    if(input > 0.0) {
        return 0;
    }
    else if(input < 0.0) {
        return 1;
    }
}

//Calculates the 8 exponent bits of the IEEE754 floating point number given
//the base-10 decimal input
vector<int> setExponentBits(float input) {
    vector<int> exponentBits(8, 0);
    int exponent = 0;
    int divisor;
    
    input = abs(input);
    
    if(input >= 2.0) {
        while(input >= 2.0) {
            input /= 2.0;
            exponent++;
        }
    }
    else {
        exponent++;
        while(input < 2.0) {
            input *= 2.0;
            exponent--;
        }
    }
    
    exponent += 127;
    
    for(int i = 7; i >= 0; i--) {
        divisor = 1;
        
        for(int j = i; j > 0; j--) {
            divisor *= 2;
        }
        
        if((exponent / divisor) == 1) {
            exponentBits[7-i] = 1;
            exponent -= divisor;
        }
    }
    return exponentBits;
}

//Calculated the 23 mantissa bits of the IEEE754 floating point number given
//the previously calculated exponent bits as well as the base-10 decimal input
vector<int> setMantissaBits(vector<int> exponentBits, float input) {
    int exponent = 0;
    int multiple = 1;
    float divisor = 1.0;
    float mantissa;
    vector<int> mantissaBits(23, 0);
    
    input = abs(input);
    
    for(int i = 7; i >= 0; i--) {
        if(exponentBits[i] == 1) {
            exponent += multiple;
        }
        multiple *= 2;
    }
    
    exponent -= 127;
    
    if(exponent > 0) {
        for(int i = 1; i <= exponent; i++) {
            divisor *= 2.0;
        }
        input /= divisor;
    }
    else if(exponent < 0) {
        for(int i = -1; i >= exponent; i--) {
            divisor /= 2.0;
        }
        input /= divisor;
    }
    
    input -= 1.0;
    divisor = 0.5;
    
    for(int i = 0; i < 23; i++) {
        if((input / divisor) >= 1.0) {
            mantissaBits[i] = 1;
            input -= divisor;
        }
        divisor /= 2.0;
    }
    
    return mantissaBits;
}

//Main function
int main() {
    
    guidedConversion();
    
    return 0;
}