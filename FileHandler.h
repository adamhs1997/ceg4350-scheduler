//Flie reader lets you read in the info files for the processes

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class FileHandler {

private:
	int* processArray; //to store the final process info array
	vector<int> accum; //vector for easy internal handling
public:
	int* parseData(string filename);
	int getNumberProcesses();

};

//Extract all data from input file, compact into int array
int* FileHandler::parseData(string filename) {
	//Read each line from file, place in vector
	ifstream openFile(filename);
	if (!openFile) {
		cout << "File name invalid! Aborting...\n";
		return nullptr;
	}
	int nextNumber;
	while (openFile) {
		openFile >> nextNumber;
		accum.push_back(nextNumber);
	}

	//Pop off erroneous last digit in vector
	accum.pop_back();

	//Convert vector to array
	processArray = &accum[0];

	return processArray;
}

//Get the number of processes to be scheduled
int FileHandler::getNumberProcesses() {
	return accum.size() / 3;
}

