#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

string mux14(string opt1, string opt2, string ctrl){
  string output = opt1;
  if(ctrl == "1"){
    output = opt2;
  }
  return output;
}

string readMem(string address, string memory[4096]){
  string read = "";
  int index = (binUnsignedToDecInt(address));
  for(int x = index; x < (index + 4); x++){
    read = read + memory[x];
  }
  return read;
}

void writeMem(string data, string address, string memory[4096]){
  int index = binUnsignedToDecInt(address);
  for(int x = index; x < (index + 4); x++){
    memory[x] = data.substr(((x-index)*8), 8);
  }
}

void run_memory(string p1_reg[5][20], string memory[4096]){
  string memAddress = mux14(p1_reg[3][5], p1_reg[3][4], p1_reg[3][0]);
  memAddress = decIntToBinUnsigned(((int)binFloatToDecDouble(memAddress)), 8);
  
  string ctrl_memReadEnable = p1_reg[3][1];
  string ctrl_memWriteEnable = p1_reg[3][2];
  string memWriteData = p1_reg[3][3];
  string memRead = "";
  
  if(ctrl_memReadEnable == "1"){
    memRead = readMem(memAddress, memory);
  }
  
  if(ctrl_memWriteEnable == "1"){
    writeMem(memWriteData, memAddress, memory);
  }

  p1_reg[4][1] = memRead; //mem read to input 1 of mux19
  
}
