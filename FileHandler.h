//Flie reader lets you read in the info files for the processes

#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

class FileHandler {

private:
	int* processArray; //to store the final process info array
	vector<int> accum; //vector for easy internal handling
	vector<int> timeSort(vector<int> processes);

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

	//Sort the processes by arrival time
	accum = timeSort(accum);

	//Convert vector to array
	processArray = &accum[0];

	return processArray;
}

//Get the number of processes to be scheduled
int FileHandler::getNumberProcesses() {
	return accum.size() / 3;
}

//Bubble sorts the process array
vector<int> FileHandler::timeSort(vector<int> processes) {
	vector<int> sortedProcesses;
	while (!processes.empty()) {
		//Find smallest arrive time
		int currentSmallest = 999999;
		int currentSmallestIndex = -1;
		for (size_t i = 1; i < processes.size(); i += 3) {
			if (processes.at(i) < currentSmallest) {
				currentSmallest = processes.at(i);
				currentSmallestIndex = i;
			}
		}

		//Store the sorted processes
		sortedProcesses.push_back(processes.at(currentSmallestIndex - 1));
		sortedProcesses.push_back(processes.at(currentSmallestIndex));
		sortedProcesses.push_back(processes.at(currentSmallestIndex + 1));

		//Get rid of the stored processes
		for (size_t i = 0; i < 3; i++)
			processes.erase(processes.begin() + (currentSmallestIndex - 1));
		
	}

	return sortedProcesses;

}

