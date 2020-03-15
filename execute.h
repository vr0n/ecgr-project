using namespace std;

string execute( string instr ) {
    string binStr = "";
    string line = getline(cin, instr, ' ');

    while ( getline(line, x) ) {
        cout << x << endl;
    }

    return binStr;
}
