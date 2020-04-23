#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

void controllerSet(string controls[11], string opcode){
  //[0]: source 2 selection
  //[1]: write to register enable
  //[2]: ALU second input source
  //[3]: ALU controller (5bits)
  //[4]: is a negative branch
  //[5]: is a zero branch
  //[6]: is an unconditional branch
  //[7]: memory address source
  //[8]: read memory enable
  //[9]: write memory enable
  //[10]: destination register data source (2bits)
  controls[3] = opcode;
  
  if(opcode == "00000"){//SET
    controls[10] = "11";
    controls[1] = "1";
  }
  else if (opcode == "00001"){//LOAD
    controls[7] = "1";
    controls[8] = "1";
    controls[10] = "01";
    controls[1] = "1";
  }
  else if (opcode == "00010"){//STORE
    controls[0] = "1";
    controls[7] = "0";
    controls[9] = "1";
  }
  else if (opcode == "00011"){//MOVE
    controls[10] = "10";
    controls[1] = "1";
  }
  else if (opcode == "00100"){//FADD
    controls[0] = "0";
    controls[2] = "0";
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "00101"){//FSUB
    controls[0] = "0";
    controls[2] = "0";
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "00110"){//FNEG
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "00111"){//FMUL
    controls[0] = "0";
    controls[2] = "0";
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "01000"){//FDIV
    controls[0] = "0";
    controls[2] = "0";
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "01001"){//FLOOR
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "01010"){//CEIL
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "01011"){//ROUND
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "01100"){//FABS
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "01101"){//MIN
    controls[0] = "0";
    controls[2] = "0";
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "01110"){//MAX
    controls[0] = "0";
    controls[2] = "0";
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "01111"){//POW
    controls[2] = "1";
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "10000"){//EXP
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "10001"){//SQRT
    controls[10] = "00";
    controls[1] = "1";
  }
  else if (opcode == "10010"){//B
    controls[6] = "1";
  }
  else if (opcode == "10011"){//BZ
    controls[0] = "1";
    controls[2] = "0";
    controls[5] = "1";
    
  }
  else if (opcode == "10100"){//BN
    controls[0] = "1";
    controls[2] = "0";
    controls[4] = "1";
  }
  else if (opcode == "10101"){//NOP
  }
  else if (opcode == "10110"){//HALT
  }  
}

string mux6(string option0, string option1, string ctrl_src2Selection){
  string output = option0;
  if(ctrl_src2Selection == "1"){
    output = option1;
  }
  return output;
}

//TODO: Rachel, actually get rid of this
string signExt32b(string originalBinSigned){
  string msb = originalBinSigned.substr(0, 1);
  string binSignedExtended = originalBinSigned;
  for(int n = 0; n < (32 - originalBinSigned.length()); n++){
    binSignedExtended = msb + binSignedExtended;
  }
  return originalBinSigned;
}

void run_decode(string registers[16], string p1_reg[5][20]){
  string controls[11] = {"0","0","0","00000","0","0","0","0","0","0","00"};
  //[0]: source 2 selection
  //[1]: write to register enable
  //[2]: ALU second input source
  //[3]: ALU controller (5bits)
  //[4]: is a negative branch
  //[5]: is a zero branch
  //[6]: is an unconditional branch
  //[7]: memory address source
  //[8]: read memory enable
  //[9]: write memory enable
  //[10]: destination register data source (2bits)
  controllerSet(controls, p1_reg[1][0]);
  p1_reg[1][6] = controls[0];//ctrl_src2Selection to mux6 ctrl
  p1_reg[1][7] = controls[1];//ctrl_regWriteEnable to reg write ctrl
  p1_reg[2][2] = controls[2];//ctrl_alu2Src to mux8 ctrl
  p1_reg[2][3] = controls[3];//ctrl_aluCtrl to alu ctrl
  p1_reg[2][4] = controls[4];//ctrl_branchNeg to gate_AND12
  p1_reg[2][5] = controls[5];//ctrl_branchZero to gate_AND13
  p1_reg[2][6] = controls[6];//ctrl_branchUncond to gate_OR17
  p1_reg[3][0] = controls[7];//ctrl_memAddressSrc to mux14 ctrl
  p1_reg[3][1] = controls[8];//ctrl_readMemEnable to mem read ctrl
  p1_reg[3][2] = controls[9];//ctrl_writeMemEnable to mem write ctrl
  p1_reg[4][4] = controls[10];//ctrl_destWriteRegSrc to mux19 ctrl

  p1_reg[1][8] = mux6(p1_reg[1][3], p1_reg[1][4], p1_reg[1][6]);//mux6 output to srcAddress2

  string reg1Data = registers[binUnsignedToDecInt(p1_reg[1][2])];
  string reg2Data = registers[binUnsignedToDecInt(p1_reg[1][8])];

  p1_reg[2][7] = reg1Data; //reg1 data to alu source 1
  p1_reg[3][3] = reg1Data; //reg1 data to memory write data
  p1_reg[3][4] = reg1Data; //reg1 data to inout 1 of mux14
  p1_reg[4][2] = reg1Data; //reg1 data to input 2 of mux19

  p1_reg[2][8] = reg2Data; //reg2 data to input 0 of mux8
  p1_reg[3][5] = reg2Data; //reg2 data to input 0 of mux14

  p1_reg[2][9] = signExt32b(p1_reg[1][5]); //SE output to input 1 of mux8
}

