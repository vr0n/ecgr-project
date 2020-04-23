#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

#include "helperFunctions.h"
#include "printFunctions.h"

using namespace std;

string mux20(string ctrl_isSet){
  string output = "00000001";
  if(ctrl_isSet == "1"){
    output = "00000010";
  }
  return output;
}

string adder(string input1, string input2){
  int in1 = binUnsignedToDecInt(input1);
  int in2 = binUnsignedToDecInt(input2);
  return decIntToBinUnsigned((in1+in2), 8);
}

void resetReg(string p1_reg[5][20]){
  for(int x = 0; x < 5; x++){
    for(int y = 0; y < 20; y++){
      p1_reg[x][y] = "";
    }
  }
}

void run_fetch(vector<string> instructionMemory, string p1_reg[5][20], int instrNum, string trackSetOps){
  //reset process register from previous process
  resetReg(p1_reg);
  p1_reg[0][2] = trackSetOps; // pattern of SET opperations for correct branch numbers
  p1_reg[0][0] = decIntToBinUnsigned(instrNum, 8);//pc value from scheduler
  string currentInstruction = instructionMemory.at(binUnsignedToDecInt(p1_reg[0][0]));
  p1_reg[1][0] = currentInstruction.substr(0, 5); //opcode to controller
  p1_reg[4][5] = currentInstruction.substr(5, 4); //reg1 to destAddress
  p1_reg[1][2] = currentInstruction.substr(9, 4); //reg2 to srcAddress1
  p1_reg[1][3] = currentInstruction.substr(13, 4); //reg3 to input 0 of mux6
  p1_reg[1][4] = currentInstruction.substr(5, 4); //reg1 to input 1 of mux6
  p1_reg[2][1] = currentInstruction.substr(17, 15); //optInt to input 1 of mux18
  p1_reg[1][5] = currentInstruction.substr(17, 15); //optInt to sign extender
  
  //if set instruction
  string ctrl_isSet = "0";
  if(p1_reg[1][0]=="00000"){
    ctrl_isSet = "1";
    currentInstruction = instructionMemory.at(binUnsignedToDecInt(adder("00000001", p1_reg[0][0])));
    p1_reg[4][3] = currentInstruction; //full 32b to input 3 of mux19
  }
  else{
    p1_reg[4][3] = "00000000000000000000000000000000";
  }
  
  string adderInput1 = mux20(ctrl_isSet);
  p1_reg[2][0] = adder(adderInput1, p1_reg[0][0]);//adderResult to input 0 of mux18
  p1_reg[0][1] = p1_reg[2][0]; //default value for next PC
}

