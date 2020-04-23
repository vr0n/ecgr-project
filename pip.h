#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;


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

  //TODO Rachel, only skip LOAD if dependent?

  string trackSetOps = "";
  int freeSpotY = 0;
  int freeSpotX = 0;
  int haltNum = -2;
  //go through every instruction
  for(int i = 0; i < instructionMemory.size(); i++){
    currentInstr = instructionMemory.at(i);
    //schedule that instruction
    for(int s = 0; s <5; s++){
      schedule[freeSpotX+s][freeSpotY] = i;
    }
    trackSetOps += "0";
    //skip next line if SET fp value
    if(currentInstr.substr(0,5)=="00000"){
      trackSetOps += "1";
      i ++;
    }
    //do nothing for a cycle to allow for LOAD forwarding
    else if(currentInstr.substr(0,5) == "00001"){
      freeSpotX ++;
      freeSpotY ++;
    }
    //instruction number to halt program at
    else if((currentInstr.substr(0,5) == "10110")&&(haltNum == -2)){
      haltNum = i;
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

  //////////////////////////////////////
  //IN PROGRESS ////////////////////////
  //////////////////////////////////////
  
  //execute schedule
  int stageNum = 0; //FDXMW
  for(int x = scheduleSizeX; x<scheduleSizeX; x++){
    //loop through each clock cycle
    for(int y = scheduleSizeY; y<scheduleSizeY; y++){
      if((schedule[x][y] != -1)&&(schedule[x][y] != haltNum)){
	//determine the current stage
	stageNum = 0;
	for(int q = 0; q < 5; q++){
	  if((x+q)<scheduleSize){
	     if(schedule[x][y] == schedule[x+q][y]){
	       stageNum ++;
	     }
	  }
	}
	stageNum = 6 - stageNum;
	//execute based on current stage
	if(stageNum == 1){
	  run_fetch(instructionMemory, p1_reg, schedule[x][y], trackSetOps);
	  cout << "FETCH" << endl;
	  //printReg(p1_reg);
	}
	else if(stageNum == 2){
	  run_decode(registers, p1_reg);
	  cout << "DECODE" << endl;
	  //printReg(p1_reg);
	}
	else if(stageNum == 3){
	  run_execute(p1_reg);
	  cout << "EXECUTE" << endl;
	  //printReg(p1_reg);
	}
	else if(stageNum == 4){
	  run_memory(p1_reg, memory);
	  cout << "MEMORY" << endl;
	  //printReg(p1_reg);
	}
	else if(stageNum == 5){
	  run_writeback(p1_reg, registers);
	  cout << "WRITEBACK" << endl;
	  //printReg(p1_reg);
	}
      }
      //if HALT, exit program
      else if(schedule[x][y] == haltNum){
	x = scheduleSize;
	y = scheduleSize;
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
