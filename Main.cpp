/*
Adam Horvath-Smith
CEG 4350-01
Dr. Yong Pei
Project 1
*/

//Driver program for the scheduler simulation
//NOTE: See README for complete usage details

#include "FileHandler.h"
#include "Process.h"
#include "FCFS.h"
#include "RR.h"
#include "MLFQ.h"

//Forward declaration for test function below
//Use this to test each algorithm without command line args
void test();

int main(int argc, char** argv) {

	//Uncomment this to run test segment below
	//test();

	//Ensure proper number of args are passed
	if (argc != 3) {
		cout << "This program takes exactly two command line arguments. Usage:\n";
		cout << "\tschedulesim <input_file_name> <[FCFS | RR | MLFQ]>\n";
		return 1;
	}

	//Get data from the input file
	FileHandler fh;
	int* processData = fh.parseData(argv[1]);
	cout << "# processes " << fh.getNumberProcesses() << "\n";
	for (int i = 0; i < fh.getNumberProcesses() * 3; i++) {
		cout << processData[i] << " ";
	}

	return 0;
}

void test() {
	//Read data from the input file
	FileHandler mfh;
	int* arr = mfh.parseData("longer_processes.txt");
	int numberProcesses = mfh.getNumberProcesses();
	cout << "# processes " << mfh.getNumberProcesses() << "\n";
	for (int i = 0; i < mfh.getNumberProcesses() * 3; i++) {
		cout << arr[i] << " ";
	}

	//Test code for process class...
	cout << "\n";
	Process testProcess(1, 3, -1);
	cout << testProcess.getTimeRemaining() << "\n";
	cout << testProcess.getBurstTime() << "\n";
	cout << testProcess.hasRun() << "\n";
	cout << testProcess.getPid() << "\n";

	//PROCESSES WILL BE CREATED IN EACH SCHEDULER ALGO

	//Testing the FCFS algo
	cout << "\nFCFS:\n";
	FCFS fcfs_scheduler(arr, numberProcesses);
	fcfs_scheduler.schedule();
	cout << "Average turnaround time: " <<
		fcfs_scheduler.getTurnaroundTime() << " ms\n";
	cout << "Average execution time: " <<
		fcfs_scheduler.getExecutionTime() << " ms\n";
	cout << "Average waiting time: " <<
		fcfs_scheduler.getWaitingTime() << " ms\n";
	cout << "Average response time: " <<
		fcfs_scheduler.getResponseTime() << " ms\n";

	//Test RR algo
	cout << "RR:\n";
	RR rr_scheduler(arr, numberProcesses, 8);
	rr_scheduler.schedule();
	cout << "Average turnaround time: " <<
		rr_scheduler.getTurnaroundTime() << " ms\n";
	cout << "Average execution time: " <<
		rr_scheduler.getExecutionTime() << " ms\n";
	cout << "Average response time: " <<
		rr_scheduler.getResponseTime() << " ms\n";
	cout << "Average waiting time: " <<
		rr_scheduler.getWaitingTime() << " ms\n";

	//Test MLFQ
	cout << "MLFQ:\n";
	MLFQ mlfq_scheduler(arr, numberProcesses);
	mlfq_scheduler.schedule();
	cout << "Average turnaround time: " <<
		mlfq_scheduler.getTurnaroundTime() << " ms\n";
	cout << "Average execution time: " <<
		mlfq_scheduler.getExecutionTime() << " ms\n";
	cout << "Average response time: " <<
		mlfq_scheduler.getResponseTime() << " ms\n";
	cout << "Average waiting time: " <<
		mlfq_scheduler.getWaitingTime() << " ms\n";
}
