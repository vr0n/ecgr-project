#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include <map>

using namespace std;

void regAsmt(int procNum, int lastStageNum, int regMap[3][5]){
  bool found = false;
  //if assigned, update and return original assignment
  for(int y = 0; y<5; y++){
    if(regMap[1][y] == procNum){
      found = true;
      regMap[2][y] = lastStageNum;
      return;
    }
  }
  //else assign to first unused register
  if(!found){
    for(int y = 0; y<5; y++){
      if((regMap[2][y] == 5) || (regMap[2][y] == -1)){
	regMap[1][y] = procNum;
	regMap[2][y] = lastStageNum;
	return;
      }
    }
  }
}

int getReg(int procNum, int regMap[3][5]){
  for(int y = 0; y<5; y++){
    if(regMap[1][y] == procNum){
      return regMap[0][y];
    }
  }
  return -1;
}

void forwardDataALU(string pDest[5][20], string pSrc[5][20], bool src2){
  if(!src2){
    pDest[2][7] = pSrc[4][0];
    pDest[3][3] = pSrc[4][0];
    pDest[3][4] = pSrc[4][0];
    pDest[4][2] = pSrc[4][0];
  }
  else{
    pDest[2][8] = pSrc[4][0];
    pDest[3][5] = pSrc[4][0];
  }
}

void forwardDataSET(string pDest[5][20], string pSrc[5][20], bool src2){
  if(!src2){
    pDest[2][7] = pSrc[4][3];
    pDest[3][3] = pSrc[4][3];
    pDest[3][4] = pSrc[4][3];
    pDest[4][2] = pSrc[4][3];
  }
  else{
    pDest[2][8] = pSrc[4][3];
    pDest[3][5] = pSrc[4][3];
  }
}

void forwardDataLOAD(string pDest[5][20], string pSrc[5][20], bool src2){
  if(!src2){
    pDest[2][7] = pSrc[4][1];
    pDest[3][3] = pSrc[4][1];
    pDest[3][4] = pSrc[4][1];
    pDest[4][2] = pSrc[4][1];
  }
  else{
    pDest[2][8] = pSrc[4][1];
    pDest[3][5] = pSrc[4][1];
  }
}

void forwardDataMOVE(string pDest[5][20], string pSrc[5][20], bool src2){
  if(!src2){
    pDest[2][7] = pSrc[4][2];
    pDest[3][3] = pSrc[4][2];
    pDest[3][4] = pSrc[4][2];
    pDest[4][2] = pSrc[4][2];
  }
  else{
    pDest[2][8] = pSrc[4][2];
    pDest[3][5] = pSrc[4][2];
  }
}

void printReg2(int regNum, string p1_reg[5][20], string p2_reg[5][20], string p3_reg[5][20], string p4_reg[5][20], string p5_reg[5][20]){
  if(regNum == 1){
    printReg(p1_reg);
  }
  else if(regNum == 2){
    printReg(p2_reg);
  }
  else if(regNum == 3){
    printReg(p3_reg);
  }
  else if(regNum == 4){
    printReg(p4_reg);
  }
  else if(regNum == 5){
    printReg(p5_reg);
  }
}

void executePip(string registers[16], string memory[4096], vector<string> instructionMemory, int scheduleSize, string p1_reg[5][20], string p2_reg[5][20], string p3_reg[5][20], string p4_reg[5][20], string p5_reg[5][20]){

  int scheduleSizeX = scheduleSize*2 + 5;
  int scheduleSizeY = scheduleSize*2;
  //set default schedule values
  int schedule[scheduleSizeX][scheduleSizeY];
  string currentInstr = "";
  for(int y = 0; y<scheduleSizeY; y++){
    for(int x = 0; x<scheduleSizeX; x++){
      schedule[x][y] = -1;
    }
  }

  string trackSetOps = "";
  int freeSpotY = 0;
  int freeSpotX = 0;
  int haltNum = -2;
  
  string op = "";
  string src1R = "";
  string src2R = "";
  string instrM1 = "";
  string instrM2 = "";
  string opM1 = "";
  string opM2 = "";
  string destRM1 = "";
  string destRM2 = "";

  //default values for dependencies map
  int dependencies[6][scheduleSize];
  for(int x = 0; x<6; x++){
    for(int y = 0; y<scheduleSize; y++){
      dependencies[x][y] = -1;
    }
  }

  int ii = 0;
  int indexM1 = 0;
  int indexM2 = 0;
  
  //go through every instruction
  for(int i = 0; i < instructionMemory.size(); i++){
    ii = -1;
    //get this instruction + opcode + destinstation register and previous 2 if applicable
    //info of previous 2 used for RAW dependency identification
    currentInstr = instructionMemory.at(i);
    op = currentInstr.substr(0,5);
    //track SET ops for branching and instruction relativity
    trackSetOps += "0";
    if(op=="00000"){
      trackSetOps += "1";
    }
    if(i>0){
      indexM1 = (i - (((int)trackSetOps[i-1]-48)+1));
      instrM1 = instructionMemory.at(indexM1);
      opM1 = instrM1.substr(0,5);
      destRM1 = instrM1.substr(5,4);
      ii = indexM1;
      if(ii>0){
	indexM2 = (ii - (((int)trackSetOps[ii-1]-48)+1));
	instrM2 = instructionMemory.at(indexM2);
	opM2 = instrM2.substr(0,5);
	destRM2 = instrM2.substr(5,4);
      }
      else{
	instrM2 = "--------------------------------";
	opM2 = "-----";
	destRM2 = "----";
      }
    }
    else{
      instrM1 = "--------------------------------";
      instrM2 = "--------------------------------";
      opM1 = "-----";
      opM2 = "-----";
      destRM1 = "----";
      destRM2 = "----";
    }
    //get the source registers for this instruction
    src1R = currentInstr.substr(9,4);
    src2R = "----";
    
    //schedule this instruction
    for(int s = 0; s <5; s++){
      if(op=="10110"){
	s = 4;
      }
      schedule[freeSpotX+s][freeSpotY] = i;
    }
    //no src1R for SET
    if(op =="00000"){
      src1R = "----";
    }
    //do nothing for a cycle to allow for LOAD forwarding
    else if(op == "00001"){
      freeSpotX ++;
      freeSpotY ++;
    }
    //first register is also a source for STORE instruction
    else if(op == "00010"){
      src2R = currentInstr.substr(5,4);
    }

    //TODO: edit for unconditional branch weird way
    
    //do nothing for 4 cycles to allow for branching
    else if((op == "10010")||
	    (op == "10011")||
	    (op == "10100")){
      if(op == "10010"){
	src1R = "----"; // also no src1R for B
      }
      freeSpotX += 4;
      freeSpotY += 4;
    }
    //instruction number to halt program at
    else if((op == "10110")&&(haltNum == -2)){
      src1R = "----"; // also no src1R for HALT
      haltNum = i;
    }
    //no src1R for NOP
    else if(op == "10101"){
      src1R = "----";
    }
    //src2R only used for add/ sub/ mul/ div/ min/ max
    else if((op == "00100")||
	    (op == "00101")||
	    (op == "00111")||
	    (op == "01000")||
	    (op == "01101")||
	    (op == "01110")){
      src2R = currentInstr.substr(13, 4);
    }
    //no destination for STORE/ NOP/ HALT
    //for no prediction, branching spaced and not causing hazards
    //so no dest for branching either
    if((opM1 == "00010")||
       (opM1 == "10101")||
       (opM1 == "10110")||
       (opM1 == "10010")||
       (opM1 == "10011")||
       (opM1 == "10100")){
      destRM1 = "----";
    }
    //same as above for other previous instruction
    if((opM2 == "00010")||
       (opM2 == "10101")||
       (opM2 == "10110")||
       (opM2 == "10010")||
       (opM2 == "10011")||
       (opM2 == "10100")){
      destRM2 = "----";
    }

    //check for dependencies
    //no dependencies for SET/ NOP/ HALT
    if((op != "00000")||
       (op != "10101")||
       (op != "10110")){
      if(src1R != "----"){
	if(src1R == destRM1){
	  dependencies[0][i] = binUnsignedToDecInt(src1R);
	  dependencies[1][i] = binUnsignedToDecInt(destRM1);
	  dependencies[2][i] = (indexM1);
	}
	else if(src1R == destRM2){
	  dependencies[0][i] = binUnsignedToDecInt(src1R);
	  dependencies[1][i] = binUnsignedToDecInt(destRM2);
	  dependencies[2][i] = (indexM2);
	}
      }
      if(src2R != "----"){
	if(src2R == destRM1){
	  dependencies[3][i] = binUnsignedToDecInt(src2R);
	  dependencies[4][i] = binUnsignedToDecInt(destRM1);
	  dependencies[5][i] = (indexM1);
	}
	else if(src2R == destRM2){
	  dependencies[3][i] = binUnsignedToDecInt(src2R);
	  dependencies[4][i] = binUnsignedToDecInt(destRM2);
	  dependencies[5][i] = (indexM2);
	}
      }
    }

    //skip next line if SET
    if(op == "00000"){
      i++;
    }
    //go to next possible scheduling location
    freeSpotX ++;
    freeSpotY ++;
  }
  
  
  printInstructionMemory(instructionMemory);
  //print schedule
  cout << "////////////////////////// SCHEDULE //////////////////////////" << endl;
  for(int y = 0; y<(scheduleSizeY); y++){
    for(int x = 0; x<(scheduleSizeX); x++){
      if(schedule[x][y] != -1){
	cout << schedule[x][y];
      }
      else{
	cout << "-";
      }
    }
    cout << endl;
  }
  cout << endl;

  /////////////////////////////////////////////////////////////dependencies printing (delete)
  for(int y = 0; y < scheduleSize; y++){
    for(int x = 0; x < 6; x++){
      cout << dependencies[x][y] << " ";
    }
    cout << endl;
  }
  cout << endl;
  
  //initialize process register map
  int regMap[3][5];
  for(int x = 0; x < 3; x++){
    for(int y = 0; y < 5; y++){
      if(x==0){
	regMap[x][y] = (y+1);
      }
      else{
	regMap[x][y] = -1;
      }
    }
  }
  
  //execute schedule
  int stageNum = 0; //FDXMW
  int assignedReg = 0; //assigned process register
  int src1Dep = -1; //instruction src1 is dependent on
  int src2Dep = -1; //instruction src2 is dependent on
  int dep1Reg = -1; //current register in use by 1st instruction that is depended on
  int dep2Reg = -1; //current register in use by 2nd instruction that is depended on
  int jump = -2; //variable to use for branching
  for(int x = 0; x<scheduleSizeX; x++){
    //loop through each clock cycle
    for(int y = 0; y<scheduleSizeY; y++){
      if((schedule[x][y] != -1)&&(schedule[x][y] != haltNum)){
	//determine the current stage
	stageNum = 0;
	for(int q = 0; q < 5; q++){
	  if((x+q)<scheduleSizeX){
	     if(schedule[x][y] == schedule[x+q][y]){
	       stageNum ++;
	     }
	  }
	}
	stageNum = 6 - stageNum;
	int i = schedule[x][y];
	regAsmt(schedule[x][y], stageNum, regMap);
	assignedReg = getReg(schedule[x][y], regMap);
	src1Dep = dependencies[2][i];
	src2Dep = dependencies[5][i];
	//execute based on current stage
	if(stageNum == 1){
	  cout << "FETCH" << endl;
	  if(assignedReg == 1){
	    run_fetch(instructionMemory, p1_reg, schedule[x][y], trackSetOps);
	  }
	  else if(assignedReg == 2){
	    run_fetch(instructionMemory, p2_reg, schedule[x][y], trackSetOps);
	  }
	  else if(assignedReg == 3){
	    run_fetch(instructionMemory, p3_reg, schedule[x][y], trackSetOps);
	  }
	  else if(assignedReg == 4){
	    run_fetch(instructionMemory, p4_reg, schedule[x][y], trackSetOps);
	  }
	  else if(assignedReg == 5){
	    run_fetch(instructionMemory, p5_reg, schedule[x][y], trackSetOps);
	  }
	}
	else if(stageNum == 2){
	  cout << "DECODE" << endl;
	  if(assignedReg == 1){
	    run_decode(registers, p1_reg);
	  }
	  else if(assignedReg == 2){
	    run_decode(registers, p2_reg);
	  }
	  else if(assignedReg == 3){
	    run_decode(registers, p3_reg);
	  }
	  else if(assignedReg == 4){
	    run_decode(registers, p4_reg);
	  }
	  else if(assignedReg == 5){
	    run_decode(registers, p5_reg);
	  }
	}
	else if(stageNum == 3){
	  //forward data
	  if((src1Dep != -1)||(src2Dep != -1)){
	    if(src1Dep != -1){
	      dep1Reg = getReg(src1Dep, regMap);
	      if(instructionMemory.at(src1Dep).substr(0,5) == "00000"){
		if(dep1Reg == 1){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p1_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p1_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p1_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p1_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p1_reg, false);
		  }
		}
		else if(dep1Reg == 2){
		  if(assignedReg == 1){
		    p1_reg[0][19] = "1"; //is pip
		    forwardDataSET(p1_reg, p2_reg, false);
		  }
		  else if(assignedReg == 2){
		    p2_reg[0][19] = "1"; //is pip
		    forwardDataSET(p2_reg, p2_reg, false);
		  }
		  else if(assignedReg == 3){
		    p3_reg[0][19] = "1"; //is pip
		    forwardDataSET(p3_reg, p2_reg, false);
		  }
		  else if(assignedReg == 4){
		    p4_reg[0][19] = "1"; //is pip
		    forwardDataSET(p4_reg, p2_reg, false);
		  }
		  else if(assignedReg == 5){
		    p5_reg[0][19] = "1"; //is pip
		    forwardDataSET(p5_reg, p2_reg, false);
		  }
		}
		else if(dep1Reg == 3){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p3_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p3_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p3_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p3_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p3_reg, false);
		  }
		}
		else if(dep1Reg == 4){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p4_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p4_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p4_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p4_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p4_reg, false);
		  }
		}
		else if(dep1Reg == 5){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p5_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p5_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p5_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p5_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p5_reg, false);
		  }
		}
	      }
	      else if(instructionMemory.at(src1Dep).substr(0,5) == "00011"){
		if(dep1Reg == 1){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p1_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p1_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p1_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p1_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p1_reg, false);
		  }
		}
		else if(dep1Reg == 2){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p2_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p2_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p2_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p2_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p2_reg, false);
		  }
		}
		else if(dep1Reg == 3){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p3_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p3_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p3_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p3_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p3_reg, false);
		  }
		}
		else if(dep1Reg == 4){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p4_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p4_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p4_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p4_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p4_reg, false);
		  }
		}
		else if(dep1Reg == 5){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p5_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p5_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p5_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p5_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p5_reg, false);
		  }
		}
	      }
	      else if(instructionMemory.at(src1Dep).substr(0,5) == "00001"){
		if(dep1Reg == 1){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p1_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p1_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p1_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p1_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p1_reg, false);
		  }
		}
		else if(dep1Reg == 2){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p2_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p2_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p2_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p2_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p2_reg, false);
		  }
		}
		else if(dep1Reg == 3){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p3_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p3_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p3_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p3_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p3_reg, false);
		  }
		}
		else if(dep1Reg == 4){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p4_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p4_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p4_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p4_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p4_reg, false);
		  }
		}
		else if(dep1Reg == 5){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p5_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p5_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p5_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p5_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p5_reg, false);
		  }
		}
	      }
	      else if((instructionMemory.at(src1Dep).substr(0,5) != "00001")||
		      (instructionMemory.at(src1Dep).substr(0,5) != "00010")||
		      (instructionMemory.at(src1Dep).substr(0,5) != "10101")||
		      (instructionMemory.at(src1Dep).substr(0,5) != "10110")){
		if(dep1Reg == 1){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p1_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p1_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p1_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p1_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p1_reg, false);
		  }
		}
		else if(dep1Reg == 2){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p2_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p2_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p2_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p2_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p2_reg, false);
		  }
		}
		else if(dep1Reg == 3){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p3_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p3_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p3_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p3_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p3_reg, false);
		  }
		}
		else if(dep1Reg == 4){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p4_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p4_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p4_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p4_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p4_reg, false);
		  }
		}
		else if(dep1Reg == 5){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p5_reg, false);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p5_reg, false);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p5_reg, false);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p5_reg, false);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p5_reg, false);
		  }
		}
	      }
	    }
	    if(src2Dep != -1){
	      dep2Reg = getReg(src2Dep, regMap);
	      if(instructionMemory.at(src2Dep).substr(0,5) == "00000"){
		if(dep2Reg == 1){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p1_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p1_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p1_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p1_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p1_reg, true);
		  }
		}
		else if(dep2Reg == 2){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p2_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p2_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p2_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p2_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p2_reg, true);
		  }
		}
		else if(dep2Reg == 3){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p3_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p3_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p3_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p3_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p3_reg, true);
		  }
		}
		else if(dep2Reg == 4){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p4_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p4_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p4_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p4_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p4_reg, true);
		  }
		}
		else if(dep2Reg == 5){
		  if(assignedReg == 1){
		    forwardDataSET(p1_reg, p5_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataSET(p2_reg, p5_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataSET(p3_reg, p5_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataSET(p4_reg, p5_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataSET(p5_reg, p5_reg, true);
		  }
		}
	      }
	      else if(instructionMemory.at(src2Dep).substr(0,5) == "00011"){
		if(dep2Reg == 1){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p1_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p1_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p1_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p1_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p1_reg, true);
		  }
		}
		else if(dep2Reg == 2){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p2_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p2_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p2_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p2_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p2_reg, true);
		  }
		}
		else if(dep2Reg == 3){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p3_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p3_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p3_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p3_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p3_reg, true);
		  }
		}
		else if(dep2Reg == 4){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p4_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p4_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p4_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p4_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p4_reg, true);
		  }
		}
		else if(dep2Reg == 5){
		  if(assignedReg == 1){
		    forwardDataMOVE(p1_reg, p5_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataMOVE(p2_reg, p5_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataMOVE(p3_reg, p5_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataMOVE(p4_reg, p5_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataMOVE(p5_reg, p5_reg, true);
		  }
		}
	      }
	      else if(instructionMemory.at(src2Dep).substr(0,5) == "00001"){
		if(dep2Reg == 1){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p1_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p1_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p1_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p1_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p1_reg, true);
		  }
		}
		else if(dep2Reg == 2){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p2_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p2_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p2_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p2_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p2_reg, true);
		  }
		}
		else if(dep2Reg == 3){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p3_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p3_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p3_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p3_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p3_reg, true);
		  }
		}
		else if(dep2Reg == 4){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p4_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p4_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p4_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p4_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p4_reg, true);
		  }
		}
		else if(dep2Reg == 5){
		  if(assignedReg == 1){
		    forwardDataLOAD(p1_reg, p5_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataLOAD(p2_reg, p5_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataLOAD(p3_reg, p5_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataLOAD(p4_reg, p5_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataLOAD(p5_reg, p5_reg, true);
		  }
		}
	      }
	      else if((instructionMemory.at(src2Dep).substr(0,5) != "00001")||
		      (instructionMemory.at(src2Dep).substr(0,5) != "00010")||
		      (instructionMemory.at(src2Dep).substr(0,5) != "10101")||
		      (instructionMemory.at(src2Dep).substr(0,5) != "10110")){
		if(dep2Reg == 1){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p1_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p1_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p1_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p1_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p1_reg, true);
		  }
		}
		else if(dep2Reg == 2){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p2_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p2_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p2_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p2_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p2_reg, true);
		  }
		}
		else if(dep2Reg == 3){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p3_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p3_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p3_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p3_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p3_reg, true);
		  }
		}
		else if(dep2Reg == 4){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p4_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p4_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p4_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p4_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p4_reg, true);
		  }
		}
		else if(dep2Reg == 5){
		  if(assignedReg == 1){
		    forwardDataALU(p1_reg, p5_reg, true);
		  }
		  else if(assignedReg == 2){
		    forwardDataALU(p2_reg, p5_reg, true);
		  }
		  else if(assignedReg == 3){
		    forwardDataALU(p3_reg, p5_reg, true);
		  }
		  else if(assignedReg == 4){
		    forwardDataALU(p4_reg, p5_reg, true);
		  }
		  else if(assignedReg == 5){
		    forwardDataALU(p5_reg, p5_reg, true);
		  }
		}
	      }
	    }
	  }
	  cout << "EXECUTE" << endl;
	  if(assignedReg == 1){
	    run_execute(p1_reg);
	  }
	  else if(assignedReg == 2){
	    run_execute(p2_reg);
	  }
	  else if(assignedReg == 3){
	    run_execute(p3_reg);
	  }
	  else if(assignedReg == 4){
	    run_execute(p4_reg);
	  }
	  else if(assignedReg == 5){
	    run_execute(p5_reg);
	  }
	}
	else if(stageNum == 4){
	  cout << "MEMORY" << endl;
	  if(assignedReg == 1){
	    run_memory(p1_reg, memory);
	  }
	  else if(assignedReg == 2){
	    run_memory(p2_reg, memory);
	  }
	  else if(assignedReg == 3){
	    run_memory(p3_reg, memory);
	  }
	  else if(assignedReg == 4){
	    run_memory(p4_reg, memory);
	  }
	  else if(assignedReg == 5){
	    run_memory(p5_reg, memory);
	  }
	}
	else if(stageNum == 5){
	  cout << "WRITEBACK" << endl;
	  if(assignedReg == 1){
	    run_writeback(p1_reg, registers);
	  }
	  else if(assignedReg == 2){
	    run_writeback(p2_reg, registers);
	  }
	  else if(assignedReg == 3){
	    run_writeback(p3_reg, registers);
	  }
	  else if(assignedReg == 4){
	    run_writeback(p4_reg, registers);
	  }
	  else if(assignedReg == 5){
	    run_writeback(p5_reg, registers);
	  }
	}
      }
      //if HALT, exit program
      else if(schedule[x][y] == haltNum){
	x = scheduleSizeX;
	y = scheduleSizeY;
      }
    }
  }

  printRegisters(registers);
  
  ////////////////////////////////////////////////////////////////////////////
  // CHANGE CUTOFF MEMORY PRINTING HERE //////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////
  
  //change cutoff value (ex: 800) if printing memory larger than current address
  //will not affect execution, just printing
  //max cutoff value: 4096
  printMemory(memory, 140);
}
