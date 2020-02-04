#include <iostream>
#include <math.h>
 
using namespace std;

/*
    First function for converting the exponent
    Date: 2020-02-02
*/
float convertExp( string Bin ) {
    int i, val, ind, exp = 0; //index of loop, temp val, index of binary, exponent
    int length = (int) Bin.length(); //length for for loop (checked in getFloat

    ind = length; //set this to length, so we can do math shenanigans later

    for ( i = 0; i < length; i++ ) {
        val = (int) Bin[i] - 48; //int representation of a char is it's ascii value

        ind--; //set realistic index

        if ( val != 1 && val != 0 ) { //break out if we have not passed in binary
            cout << "Whoops. Not a binary number.";
            return 1;
        }

        /*
            the exponent is equal to the value (either '0' or '1')
            multiplied by 2 to the power of the current index.
            
            We set the index to run backward (see 'ind--;' above)
            so we don't have to do extra math later.
        */
        exp += ( val * pow(2, ind) );
    }
    
    exp -= 127; //adjust exponent

    float fin = (float) pow(2.0, exp); //return the value after it's been powered

    return fin;
}

/*
    function to convert the Mantissa
    Date: 2020-02-02
*/
float convertMan( string Bin ) {
    int i; //for loop index
    float val, man = 0.00; //val for testing and set the Mantissa to 0
    int length = (int) Bin.length(); //you understand this by now

    for ( i = 0; i < length; i++ ) {
        val = (float) Bin[i] - 48; //correct for ascii representation of char

        if ( val != 1 && val != 0 ) { //break out if not binary
            cout << "Whoops. Not a binary number.";
            return 1;
        }

        /*
            If anything is wrong with the function, 
            it is here. 

            I am multiplying th value (either '0' or '1')
            by 1/(2^index of loop + 1).

            so, if the current loop is on i = 3, then the
            value is (0 || 1) * 1/(2^4).
        */
        man += ( val * ( 1.0 / pow(2.0, ( i + 1 )) ));
    }

    return man;
}

/*
    Housing function for convertExp and convertMan.
    Idk why, but I really like modular programming, so, this function
    is actually three.
    Date: 2020-02-02
*/
float getFloat( string Binary )
{
    int length = Binary.length(); //The only reason this is here is for error catching.

    if ( length != 32 ) { //Catch the error of passing in a bad value.
        cout << "Value not entered in 32-bit format.";
        return 1.0;
    }

    int i;
    int expAll = 0;
    int manAll = 0;
    int Sign = (int) Binary[0] - 48; //Get the Sign bit
    int test;

    for (i = 1; i < 9; i++) {
        test = (int) Binary[i] - 48;

        if ( test == 1 ) {
            expAll++;
        }
    }

    for ( i = 9; i < 33; i++ ) {
        test = (int) Binary[i] - 48;

        if ( test == 1 ) {
            manAll++;
        }
    }

    if ( ( expAll + manAll ) == 31 ) {
        cout << "NaN" << endl;
        return 1.0;
    }
    else if ( expAll == 8 && manAll == 0 ) {
        if ( Sign == 0 ) {
            cout << "Infinity" << endl;
            return 1.0;
        }
        else {
            cout << "-Infinity" << endl;
            return 1.0;
        }
    }

    string Exponent = Binary.substr(1, 8); //Get the value for exponent
    string Mantissa = Binary.substr(9, 32); //Get the mantissa bits.

    float dec = convertExp( Exponent ); //send off for processing
    float frac = convertMan( Mantissa ); //send off for processing

    frac += 1;

    float ans = dec * frac; //We should not have numbers we can add

    if ( Sign == 1 ) { //if we have a negative number, make a negative number
        ans = ans * -1.0;
    }
    
    cout << ans << endl; 

    return ans;
}

/*
    What do you want me to say? It's the main function
    Date: 2020-02-02
*/
int main()
{
    string f; //start with a C++ string.
    f = "11111111111111111111111111111111"; //test value, actual function is dynamic
//    cin >> f; //this is here for the dynamic part i was talking about
    getFloat( f ); //send off for processing
    
    return 0;
}
