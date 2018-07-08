//Implementation of the FCFS scheduling algorithm

#include "Process.h"
#include <queue>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

class FCFS {

private:
	queue<Process> m_readyQueue;
	int* m_processArray;
	int m_numProcesses;
	vector<Process> m_completedProcesses;

public:
	FCFS(int* processInfo, int numProcesses); // Array is to make all necc processes
	void schedule();
	double getTurnaroundTime();
	double getResponseTime();
	double getWaitingTime();
		
};

//Build the FCFS scheduler object
FCFS::FCFS(int* processInfo, int numProcesses) {
	m_processArray = processInfo;
	m_numProcesses = numProcesses;
}

//The FCFS master scheduler!!!
void FCFS::schedule() {
	//Create a dummy clock variable
	int clock = 0;
	
	//Pointer to right index in process array
	//Keeps track of which is next to be born
	int arrayIndex = 1;

	//Track the current burst time
	int burstTimeRemaining = 0;

	//Track processes that have been completed
	int numberProcessesComplete = 0;

	//Track our currently running process
	//Initialize to "null" process with pid -1
	Process current(-1, 0, -1);

	//Run the scheduler in a loop until we are out of processes
	//to schedule
	while (numberProcessesComplete != m_numProcesses) {
		//Check to see if any process has arrived yet
		if (clock == m_processArray[arrayIndex]) {
			//If it has, add it to ready queue
			Process newProcess(m_processArray[arrayIndex - 1],
				m_processArray[arrayIndex + 1], m_processArray[arrayIndex]);
			m_readyQueue.push(newProcess);

			//Increment the array index to next process arrive time
			arrayIndex += 3;
		}

		//See if we've finished any process that is running
		if (current.getPid() != -1 && burstTimeRemaining == 0) {
			//Wrap up the process
			current.setState(current.TERMINATED);
			cout << "PID " << current.getPid() << " has finished at time "
				<< clock << " ms\n";
			//Note time we finish the process
			current.setCompletionTime(clock);
			//Officially kill the process by putting in terminated vector
			m_completedProcesses.push_back(current);
			m_readyQueue.pop();
			//Replace current with dummy
			current = Process(-1, 0, -1);
			//Count up the processes we've finished
			numberProcessesComplete++;
		}
		
		//Get us a new process if nothing else going on
		if (current.getPid() == -1 && m_readyQueue.size() != 0) {
			current.setState(current.RUNNING);
			current = m_readyQueue.front();
			burstTimeRemaining = current.getBurstTime();
			cout << "PID " << current.getPid() << " starts running at time "
				<< clock << " ms\n";
		}

		//Run the clock, update time remaining
		clock++;
		burstTimeRemaining--;
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

//Returns turnaround time
double FCFS::getTurnaroundTime() {
	int sumOfTurnarounds = 0;
	for (Process p : m_completedProcesses) {
		int arriveTime = p.getArriveTime();
		int completionTime = p.getCompletionTime();
		sumOfTurnarounds += completionTime - arriveTime;
	}

	return sumOfTurnarounds / static_cast<double>(m_numProcesses);
}

//Returns average response time
double FCFS::getResponseTime() {
	int sumBurstTime = 0;
	for (Process p : m_completedProcesses)
		sumBurstTime += p.getBurstTime();

	return sumBurstTime / static_cast<double>(m_numProcesses);
}

//Return average waiting time
double FCFS::getWaitingTime() {
	return getTurnaroundTime() - getResponseTime();
}
