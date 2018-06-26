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
public:
	int* parseData(string filename);
	int getNumberProcesses();
};

int* FileHandler::parseData(string filename) {
	vector<string> accum;
	string line;
	ifstream openFile(filename);
	getline(openFile, line); //elim header row
	while (getline(openFile, line)) {
		accum.push_back(line);
		cout << line << "\n";
	}

	//TODO: parse digits from strings in vector

	int abc = 6;
	return &abc;
}

int FileHandler::getNumberProcesses() {
	return 0;
}

int main() {
	FileHandler mfh;
	mfh.parseData("processes.txt");
	system("pause"); //remove on linux
	return 0;
}

