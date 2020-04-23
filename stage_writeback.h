#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

string mux19(string opt0, string opt1, string opt2, string opt3, string ctrl){
  string output = opt0;
  if(ctrl == "01"){
    output = opt1;
  }
  else if(ctrl == "10"){
    output = opt2;
  }
  else if(ctrl == "11"){
    output = opt3;
  }
  return output;
}

void run_writeback(string p1_reg[5][20], string registers[16]){
  string regWriteData = mux19(p1_reg[4][0], p1_reg[4][1], p1_reg[4][2], p1_reg[4][3], p1_reg[4][4]);
  int destAddress = binUnsignedToDecInt(p1_reg[4][5]);
  if(p1_reg[1][7] == "1"){
    registers[destAddress] = regWriteData;
  }
}
