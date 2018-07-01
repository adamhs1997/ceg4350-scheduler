// Flie reader
// Lets you read in the info files for the processes

#include <string>
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

int* FileHandler::parseData(string filename) {
	//Read each line from file, place in vector
	ifstream openFile(filename);
	string line;
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

int FileHandler::getNumberProcesses() {
	return accum.size() / 3;
}

