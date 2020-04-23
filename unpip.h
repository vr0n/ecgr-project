#include <iostream>
#include <cmath>
#include <bits/stdc++.h>

#include "stage_fetch.h"
#include "stage_decode.h"
#include "stage_execute.h"
#include "stage_memory.h"
#include "stage_writeback.h"

using namespace std;
  

void executeUnpip(string registers[16], string memory[4096], vector<string> instructionMemory, int scheduleSize, string p1_reg[5][20]){

  //set default schedule values
  int schedule[scheduleSize][scheduleSize];
  string currentInstr = "";
  for(int y = 0; y<scheduleSize; y++){
    for(int x = 0; x<scheduleSize; x++){
      schedule[x][y] = -1;
    }
  }

  string trackSetOps = "";
  int freeSpot = 0;
  int haltNum = -2;
  //go through every instruction
  for(int i = 0; i < instructionMemory.size(); i++){
    currentInstr = instructionMemory.at(i);
    //schedule that instruction
    for(int s = 0; s <5; s++){
      schedule[freeSpot+s][freeSpot] = i;
    }
    trackSetOps += "0";
    //skip next line if SET fp value
    if(currentInstr.substr(0,5)=="00000"){
      trackSetOps += "1";
      i ++;
    }
    //instruction number to halt program at
    else if((currentInstr.substr(0,5) == "10110")&&(haltNum == -2)){
      haltNum = i;
    }
    //go to next possible scheduling location
    freeSpot += 5;
  }
  
  
  printInstructionMemory(instructionMemory);
  //print schedule
  cout << "////////////////////////// SCHEDULE //////////////////////////" << endl;
  for(int y = 0; y<scheduleSize; y++){
    for(int x = 0; x<scheduleSize; x++){
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
  

  //execute schedule
  int stageNum = 0;
  for(int x = 0; x<scheduleSize; x++){
    //loop through each clock cycle
    for(int y = 0; y<scheduleSize; y++){
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
	  //determine next instruction number
	  int jump = binUnsignedToDecInt(p1_reg[0][1]);
	  //find first stage of desired line number
	  for(int xx = 0; xx<scheduleSize; xx++){
	    for(int yy = 0; yy<scheduleSize; yy++){
	      if(schedule[xx][yy] == jump){
		//move there
		x = xx-1;
		y = yy-1;
		xx = scheduleSize;
		yy = scheduleSize;
	      }
	    }
	  }
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
  
  //change cutoff value (ex: 800) if printing memory larger than 200th address
  //will not affect execution, just printing
  //max cutoff value: 4096
  printMemory(memory, 140);
}
