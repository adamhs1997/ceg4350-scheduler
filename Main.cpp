/*
Adam Horvath-Smith
CEG 4350-01
Dr. Yong Pei
Project 1
*/

//Driver program for the scheduler simulation

#include "FileHandler.h"
#include "Process.h"

int main(int argc, char** argv) {
	//Read data from the input file
	//TODO: Change this from the hard-set processes file to the cmd arg
	FileHandler mfh;
	int* arr = mfh.parseData("processes.txt");
        cout << "# processes " << mfh.getNumberProcesses() << "\n";
	for (int i = 0; i < mfh.getNumberProcesses() * 3; i++) {
		cout << arr[i] << " ";
	}

	//PROCESSES WILL BE CREATED IN EACH SCHEDULER ALGO
	//TODO: Make switch stmt that goes by whatever algo passed in


	//Test code for process class...
	cout << "\n";
	Process testProcess(1, 3);
	cout << testProcess.getTimeRemaining() << "\n";
	cout << testProcess.getBurstTime() << "\n";
	cout << testProcess.hasArrived() << "\n";
	cout << testProcess.getPid() << "\n";

	return 0;
}
