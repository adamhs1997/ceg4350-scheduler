/*
Adam Horvath-Smith
CEG 4350-01
Dr. Yong Pei
Project 1
*/

//Driver program for the scheduler simulation

#include "FileHandler.h"
#include "Process.h"
#include "FCFS.h"
#include "RR.h"
#include "MLFQ.h"

int main(int argc, char** argv) {
	//Read data from the input file
	//TODO: Change this from the hard-set processes file to the cmd arg
	FileHandler mfh;
	int* arr = mfh.parseData("mlfq_ex_processes.txt");
	int numberProcesses = mfh.getNumberProcesses();
    	cout << "# processes " << mfh.getNumberProcesses() << "\n";
	for (int i = 0; i < mfh.getNumberProcesses() * 3; i++) {
		cout << arr[i] << " ";
	}

	//PROCESSES WILL BE CREATED IN EACH SCHEDULER ALGO
	//TODO: Make switch stmt that goes by whatever algo passed in

	//Testing the FCFS algo
	cout << "\nFCFS:\n";
	FCFS fcfs_scheduler(arr, numberProcesses);
	fcfs_scheduler.schedule();
	cout << "Average turnaround time: " <<
		fcfs_scheduler.getTurnaroundTime() << " ms\n";
	cout << "Average response time: " <<
		fcfs_scheduler.getResponseTime() << " ms\n";
	cout << "Average waiting time: " <<
		fcfs_scheduler.getWaitingTime() << " ms\n";

	//Test RR algo
	cout << "RR:\n";
	RR rr_scheduler(arr, numberProcesses, 8);
	rr_scheduler.schedule();
	cout << "Average turnaround time: " <<
		rr_scheduler.getTurnaroundTime() << " ms\n";
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
	cout << "Average response time: " <<
		mlfq_scheduler.getResponseTime() << " ms\n";
	cout << "Average waiting time: " <<
		mlfq_scheduler.getWaitingTime() << " ms\n";

	//Test code for process class...
	cout << "\n";
	//Process testProcess(1, 3);
	//cout << testProcess.getTimeRemaining() << "\n";
	//cout << testProcess.getBurstTime() << "\n";
	//cout << testProcess.hasArrived() << "\n";
	//cout << testProcess.getPid() << "\n";

	return 0;
}
