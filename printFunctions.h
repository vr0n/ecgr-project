#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

void printInstructionMemory(vector<string> instructionMemory){
  cout << "//////////////////// INSTRUCTION MEMORY //////////////////////" << endl;
  cout << "NOTE: any lines following a SET opperation (first 5b == 00000) will be displayed the same way, but really are IEEE 754 format" << endl;
  for(int i = 0; i < instructionMemory.size(); i++){
    cout << instructionMemory.at(i).substr(0, 5) << " ";
    cout << instructionMemory.at(i).substr(5, 4) << " ";
    cout << instructionMemory.at(i).substr(9, 4) << " ";
    cout << instructionMemory.at(i).substr(13, 4) << " ";
    cout << instructionMemory.at(i).substr(17) << " ";
    cout << " :" << i << endl;
  }
  cout << endl;
}

void printRegisters(string registers[16]){
  cout << "///////////////////////// REGISTERS /////////////////////////" << endl;
  for(int i = 0; i<16; i++){
    cout << registers[i] << " ~ reg loc: [" << i << "] fp rep: " << binFloatToDecDouble(registers[i]) << endl;
  }
  cout << endl;
}

void printMemory(string memory[4096], int cutoff){
  if(cutoff > 4096){
    cutoff = 4096;
  }
  cout << "/////////////////////////// MEMORY ///////////////////////////" << endl;
  string memData = "00000000000000000000000000000000";
  for(int i = 0; i<cutoff; i += 4){
    memData =  memory[i] + memory[i+1] + memory[i+2] + memory[i+3];
    cout << memData << " ~ mem loc: [" << (i/4) << "] fp rep: " << binFloatToDecDouble(memData) << endl;
  }
  cout << endl;
}

void printReg(string p1_reg[5][20]){
  cout << "/////////////////// PROCESS REGISTERS ///////////////////////" << endl;
  string reverseReg[20][5];
  string tempReg[100];
  for(int y = 0; y < 20; y++){
    for(int x = 0; x < 5; x++){
      tempReg[(x*20)+y] = p1_reg[x][y];
    }
  }

  for(int z = 0; z < 100; z++){
    reverseReg[z%20][z/20] = tempReg[z];
  }

  for(int y = 0; y < 5; y++){
    for(int x = 0; x < 20; x++){
      cout << "[" << reverseReg[x][y] << "] ~ ";
    }
    cout << endl;
  }
  cout << endl;
}

void printProcMap(int regMap[3][5]){
  cout << "///////////////// PROCESS REGISTERS MAP ///////////////////////" << endl;
  for(int y = 0; y<5; y++){
    for(int x = 0; x<3; x++){
      cout << regMap[x][y] << " ";
    }
    cout << endl;
  }
  cout << endl;
}
