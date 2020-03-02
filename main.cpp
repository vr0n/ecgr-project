#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

#include "instrFieldDecode.h"
//#include "instrFieldOp.h"

using namespace std;

	//declare system structure
	string registers[16];
	string memory[4096];
	vector<string> instructionsField;
	

int main(){
	

	//read in all lines from file
	ifstream instructionsFile;
	instructionsFile.open("/home/cherry/Downloads/ecgr-project/test_files/isa_test1.txt", ios::out);
	string line;
	vector<string> instructionsList;
	if(instructionsFile.is_open()){
		while(getline(instructionsFile, line)){
			//store each line into a vector item
			instructionsList.push_back(line);
		}
		instructionsFile.close();
	}
	else{
		cout << "Error: file not found" << endl;
	}
	
	int spaceCount = 0;
	string firstThing = "";
	string secondThing = "";
	string thirdThing = "";
	string fourthThing = "";

	//divide individual lines by spaces
	for(int i = 0; i < instructionsList.size(); i++){
		for(int x = 0; x < instructionsList.at(i).length(); x++){			
			if((int)(instructionsList.at(i))[x] != 32){
				//ignore line if comment
				if((int)(instructionsList.at(i))[x] == 45){
						if(x < (instructionsList.at(i).length()-1)){
							if((int)(instructionsList.at(i))[x+1] == 45){
								x = instructionsList.at(i).length();
							}
						}
				}
				//append char to end of appropriate thing
				else if(spaceCount == 0){
					firstThing = firstThing + instructionsList.at(i)[x];
				}
				else if(spaceCount == 1){
					secondThing = secondThing + instructionsList.at(i)[x];
				}
				else if(spaceCount == 2){
					thirdThing = thirdThing + instructionsList.at(i)[x];
				}
				else if(spaceCount == 3){
					fourthThing = fourthThing + instructionsList.at(i)[x];
				}
			}
			else{
				spaceCount = spaceCount + 1;
			}
		}

		int asciiFirst = (int)firstThing[0];

		//if "<", then insert properly into memory
		if(asciiFirst==60){
			//TODO
			//use stringToDouble
			//also make method for 2's complement binary
			//place in memory file
		}
		//if likely a letter, decode and add to instructions field list
		else if(asciiFirst>=65){
			instructionsField.push_back(oppToCode(firstThing, secondThing, thirdThing, fourthThing));
			//if set instruction, also add IEEE-754 value to instructions field list
			if(firstThing == "Set"){
				instructionsField.push_back(decToBin(stringToDouble(thirdThing)));
			}
		}
		//reset line
		firstThing = "";
		secondThing = "";
		thirdThing = "";
		fourthThing = "";
		spaceCount = 0;

	}
	return 0;
}
