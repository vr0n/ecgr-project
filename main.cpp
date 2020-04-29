#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

#include "unpip.h"
#include "pip.h"

using namespace std;

string oppPartsTo32bInstr(string opp, string second, string third, string fourth);

	//declare system structure
	string registers[16];
	string memory[4096];
	vector<string> instructionMemory;
//TODO Rachel create corresponding flags

string p1_reg[5][20];
string p2_reg[5][20];
string p3_reg[5][20];
string p4_reg[5][20];
string p5_reg[5][20];


	

int main(){


	//read in all lines from file
	ifstream instructionsFile;
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	// CHANGE TEST FILE LOCATION HERE ////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////
	
	instructionsFile.open("/home/cherry/Downloads/ecgr-project/test_files/isa_test6.txt", ios::out); //this is the line to change
	string line;
	vector<string> rawInstructionsList;
	if(instructionsFile.is_open()){
		while(getline(instructionsFile, line)){
			//store each line into a vector item
			rawInstructionsList.push_back(line);
		}
		instructionsFile.close();
	}
	else{
		cout << "Error: file not found" << endl;
		return 1;
	}
	
	int spaceCount = 0;
	string firstThing = "";
	string secondThing = "";
	string thirdThing = "";
	string fourthThing = "";

	int asciiFirst = 0;
	bool isComment = false;

	//divide individual lines by spaces
	for(int i = 0; i < rawInstructionsList.size(); i++){
		for(int x = 0; x < rawInstructionsList.at(i).length(); x++){
			//keep going if not space			
			if((int)(rawInstructionsList.at(i))[x] != 32){
				//ignore line if comment
				if((int)(rawInstructionsList.at(i))[x] == 45){
						if(x < (rawInstructionsList.at(i).length()-1)){
							if((int)(rawInstructionsList.at(i))[x+1] == 45){
							  isComment = true;
								x = rawInstructionsList.at(i).length();
							}
						}
				}
				//append char to end of appropriate thing
				if(!isComment){
				  if(spaceCount == 0){
				    firstThing = firstThing + rawInstructionsList.at(i)[x];
				  }
				  else if(spaceCount == 1){
				    secondThing = secondThing + rawInstructionsList.at(i)[x];
				  }
				  else if(spaceCount == 2){
				    thirdThing = thirdThing + rawInstructionsList.at(i)[x];
				  }
				  else if(spaceCount == 3){
				    fourthThing = fourthThing + rawInstructionsList.at(i)[x];
				  }
				}
			}
			//divide by spaces
			else{
				spaceCount = spaceCount + 1;
			}
		}

		asciiFirst = (int)firstThing[0];

		//if "<", then insert properly into memory
		if(asciiFirst==60){
		  string address = "";
		  string value = "";
		  int charVal = 0;
		  bool foundSplit = false;
		  for(int c = 1; c < firstThing.length(); c++){
		    charVal = (int)firstThing[c];
		    if((charVal == 60)||(charVal == 62)){
		      if(!foundSplit){
		  	foundSplit = true;
		      }
		    }
		    else if(!foundSplit){
		      address = address + firstThing[c];
		    }
		    else if(foundSplit){
		      value = value + firstThing[c];
		    }
		  }

		  address = decIntToBinUnsigned((int)stringRawToDecDouble(address), 8);
		  value = decDoubleToBinFloat(stringRawToDecDouble(value));

		  writeMem(value, address, memory);
		}
		//if likely a letter, decode and add to instructions field list
		else if(asciiFirst>=65){
			instructionMemory.push_back(oppPartsTo32bInstr(firstThing, secondThing, thirdThing, fourthThing));
			
			//if set instruction, also add IEEE-754 value to instructions field list
			if(firstThing == "SET"){
				instructionMemory.push_back(stringRawToBinFloat(thirdThing));
			}
		}
		//reset line
		firstThing = "";
		secondThing = "";
		thirdThing = "";
		fourthThing = "";
		spaceCount = 0;
		asciiFirst = 0;
		isComment = false;

	}

	//////////////////////////////////////////////////////////////////////
	// CHANGE UNPIPLINED/ PIPLINED EXECUTION HERE ////////////////////////
	//////////////////////////////////////////////////////////////////////
	
	int scheduleSize = instructionMemory.size();
	executeUnpip(registers, memory, instructionMemory, (scheduleSize*5), p1_reg); // this is the line to comment/ uncomment
	//executePip(registers, memory, instructionMemory, scheduleSize, p1_reg, p2_reg, p3_reg, p4_reg, p5_reg); //this is the other line to comment/ uncomment
	return 0;
}
	

//combine into instruction depending on which instruction it is
string oppPartsTo32bInstr(string opp, string second, string third, string fourth){
	string translated = "";
	if(opp == "SET"){
		translated = "00000";
		translated += decodeRegister(second);
		translated += addZeros((4+4+15));
	}
	else if(opp == "LOAD"){
		translated = "00001";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros((4+15));
	}
	else if(opp == "STORE"){
		translated = "00010";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros((4+15));
	}
	else if(opp == "MOVE"){
		translated = "00011";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros((4+15));
	}
	else if(opp == "FADD"){
		translated = "00100";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "FSUB"){
		translated = "00101";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "FNEG"){
		translated = "00110";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros((4+15));
	}
	else if(opp == "FMUL"){
		translated = "00111";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "FDIV"){
		translated = "01000";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "FLOOR"){
		translated = "01001";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "CEIL"){
		translated = "01010";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "ROUND"){
		translated = "01011";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "FABS"){
		translated = "01100";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "MIN"){
		translated = "01101";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "MAX"){
		translated = "01110";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += decodeRegister(fourth);
		translated += addZeros(15);
	}
	else if(opp == "POW"){
		translated = "01111";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4);
		translated += decIntToBinSigned((int)stringRawToDecDouble(fourth), 15);
	}
	else if(opp == "EXP"){
		translated = "10000";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	else if(opp == "SQRT"){
		translated = "10001";
		translated += decodeRegister(second);
		translated += decodeRegister(third);
		translated += addZeros(4+15);
	}
	//TODO: was changed; update in ISA specifications
	else if(opp == "B"){
		translated = "10010";
		translated += addZeros(4+4+4);
		translated += decIntToBinUnsigned((int)stringRawToDecDouble(second), 15);
	}
	else if(opp == "BZ"){
		translated = "10011";
		translated += decodeRegister(second);
		translated += addZeros(4+4);
		translated += decIntToBinUnsigned((int)stringRawToDecDouble(third), 15);
	}
	else if(opp == "BN"){
		translated = "10100";
		translated += decodeRegister(second);
		translated += addZeros(4+4);
		translated += decIntToBinUnsigned((int)stringRawToDecDouble(third), 15);
	}
	else if(opp == "NOP"){
		translated = "10101";
		translated += addZeros(4+4+4+15);
	}
	else{
		translated = "10110";
		translated += addZeros(4+4+4+15);
	}
	return translated;
}
