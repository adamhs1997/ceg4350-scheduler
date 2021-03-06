//Implementation of the RR scheduling algorithm

#include "Process.h"
#include <queue>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

class RR {

private:
	queue<Process> m_readyQueue;
	int* m_processArray;
	int m_numProcesses;
	int m_quantum;
	vector<Process> m_completedProcesses;

public:
	RR(int* processInfo, int numProcesses, int quantum);
	void schedule();
	double getTurnaroundTime();
	double getResponseTime();
	double getWaitingTime();
	double getExecutionTime();

};

//Build the RR scheduler object
RR::RR(int* processInfo, int numProcesses, int quantum) {
	m_processArray = processInfo;
	m_numProcesses = numProcesses;
	m_quantum = quantum;
}

//The RR master scheduler!!!
void RR::schedule() {
	//Create a dummy clock variable
	int clock = 0;

	//Pointer to right index in process array
	//Keeps track of which is next to be born
	int arrayIndex = 1;

	//Track the current burst time
	int burstTimeRemaining = 0;

	//Track processes that have been completed
	int numberProcessesComplete = 0;

	//Track how long this process has been running
	int currentRunTime = 0;

	//Track our currently running process
	//Initialize to "null" process with pid -1
	Process current(-1, 0, -1);

	//Run the scheduler in a loop until we are out of processes to schedule
	while (numberProcessesComplete != m_numProcesses) {
		//Check to see if any process has arrived yet
		if (arrayIndex < (m_numProcesses * 3) && clock >= m_processArray[arrayIndex]) {
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
			//Note when we finish
			current.setCompletionTime(clock);
			//Officially kill process by putting in terminated vector
			m_completedProcesses.push_back(current);
			//Replace current with dummy
			current = Process(-1, 0, -1);
			//Be kind, rewind
			currentRunTime = 0;
			//Count up the processes we've finished
			numberProcessesComplete++;
		}

		//See if it's time to preempt the current process
		if (current.getPid() != -1 && currentRunTime == m_quantum) {
			current.setState(current.READY);
			cout << "PID " << current.getPid() << " is preempted at time "
				<< clock << " ms\n";
			current.setTimeRemaining(current.getTimeRemaining() - m_quantum);
			m_readyQueue.push(current);
			currentRunTime = 0; //Reset for next process
			current = Process(-1, 0, -1);
		}

		//Get us a new process if nothing else going on
		if (current.getPid() == -1 && m_readyQueue.size() != 0) {
			current.setState(current.RUNNING);
			current = m_readyQueue.front();
			m_readyQueue.pop();
			burstTimeRemaining = current.getTimeRemaining();
			cout << "PID " << current.getPid() << " starts running at time "
				<< clock << " ms\n";

			//Use to meter when process first runs (for response time)
			if (!current.hasRun()) {
				current.setHasRun();
				current.setInitialRunTime(clock);
			}
		}

		//Run the clock, update time remaining
		clock++;
		burstTimeRemaining--;
		currentRunTime++;
		this_thread::sleep_for(chrono::milliseconds(1));
	}
}

//Returns turnaround time
double RR::getTurnaroundTime() {
	int sumOfTurnarounds = 0;
	for (Process p : m_completedProcesses) {
		int arriveTime = p.getArriveTime();
		int completionTime = p.getCompletionTime();
		sumOfTurnarounds += completionTime - arriveTime;
	}

	return sumOfTurnarounds / static_cast<double>(m_numProcesses);
}

//Returns average execution time
double RR::getExecutionTime() {
	int sumBurstTime = 0;
	for (Process p : m_completedProcesses)
		sumBurstTime += p.getBurstTime();

	return sumBurstTime / static_cast<double>(m_numProcesses);
}

//Returns average response time
double RR::getResponseTime() {
	int sumOfResponseTime = 0;
	for (Process p : m_completedProcesses)
		sumOfResponseTime += p.getInitialRunTime() - p.getArriveTime();

	return sumOfResponseTime / static_cast<double>(m_numProcesses);
}

//Return average waiting time
double RR::getWaitingTime() {
	return getTurnaroundTime() - getExecutionTime();
}
