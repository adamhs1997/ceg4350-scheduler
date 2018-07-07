/*
This will simply utilize existing RR and FCFS algos
During each clock cycle, must check if sthg in higher level queue
If pre-empted, priority remains same-->go to end of queue though
*/

#include "Process.h"
#include <queue>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

class MLFQ {

private:
	//Need three ready queues, one for each priority
	queue<Process> m_p0Queue, m_p1Queue, m_p2Queue;
	int* m_processArray;
	int m_numProcesses;
	int m_currentExecutionTime;
	int m_lastRunQueue;
	vector<Process> m_completedProcesses;
	bool checkCompletion(const int&, int&, int&, int&);
	void checkPreemption(int, int&, int&);

public:
	MLFQ(int* processInfo, int numProcesses);
	void schedule();
	double getTurnaroundTime();
	double getResponseTime();
	double getWaitingTime();

};

MLFQ::MLFQ(int* processInfo, int numProcesses) {
	m_processArray = processInfo;
	m_numProcesses = numProcesses;
	m_currentExecutionTime = 0;
	m_lastRunQueue = 0;
}

//Main MLFQ scheduler, only public function
void MLFQ::schedule() {
	//CanNOT really rely on other RR and FCFS, as these work in batch
	//This will be new batch scheduler, relying on parallel RR/FCFS implementation

	//Create a dummy clock variable
	int clock = 0;

	//Pointer to right index in process array
	//Keeps track of which is next to be born
	int arrayIndex = 1;

	//Track time process spent in RR each queue
	int timeInQ0 = 0, timeInQ1 = 0, timeInQ2 = 0;;

	//Track processes that have been completed
	int numberProcessesComplete = 0;

	//Run the scheduler in a loop until we are out of processes to schedule
	while (numberProcessesComplete != m_numProcesses) {
		//Check to see if any process has arrived yet
		if (clock == m_processArray[arrayIndex]) {
			//If it has, add it to queue 0 (highest priority)
			Process newProcess(m_processArray[arrayIndex - 1],
				m_processArray[arrayIndex + 1], m_processArray[arrayIndex]);
			m_p0Queue.push(newProcess);

			//Increment the array index to next process arrive time
			arrayIndex += 3;
		}

		//Check if any process has finished
		if (checkCompletion(clock, timeInQ0, timeInQ1, timeInQ2))
			numberProcessesComplete++;

		//Check to see if new process will preempt current process
		checkPreemption(clock, timeInQ1, timeInQ2);

		//See if need to preempt q0 to q1
		if (timeInQ0 == 8) {
			cout << "PID " << m_p0Queue.front().getPid()
				<< " is preempted into Queue 1 at time " << clock << " ms\n";
			m_p1Queue.push(m_p0Queue.front());
			m_p0Queue.pop();
			timeInQ0 = 0;
		}

		//See if need to preempt q1 to q2
		if (timeInQ1 == 16) {
			cout << "PID " << m_p1Queue.front().getPid()
				<< " is preempted into Queue 2 at time " << clock << " ms\n";
			m_p2Queue.push(m_p1Queue.front());
			m_p1Queue.pop();
			timeInQ1 = 0;
		}

		//See if anything in q0 to run
		if (!m_p0Queue.empty()) {
			if (timeInQ0 == 0)
				cout << "PID " << m_p0Queue.front().getPid() 
					<< " starts running at time " << clock << " ms\n";
			m_p0Queue.front().setTimeRemaining(m_p0Queue.front().getTimeRemaining() - 1);
			timeInQ0++;
			m_lastRunQueue = 0;
		}

		//See if anything in q1 to run
		else if (!m_p1Queue.empty()) {
			if (timeInQ1 == 0)
				cout << "PID " << m_p1Queue.front().getPid()
					<< " continues running at time " << clock << " ms\n";
			m_p1Queue.front().setTimeRemaining(m_p1Queue.front().getTimeRemaining() - 1);
			timeInQ1++;
			m_lastRunQueue = 1;
		}

		//Otherwise, we run FCFS
		else if (!m_p2Queue.empty()) {
			if (timeInQ2 == 0)
				cout << "PID " << m_p2Queue.front().getPid()
					<< " continues running at time " << clock << " ms\n";
			m_p2Queue.front().setTimeRemaining(m_p2Queue.front().getTimeRemaining() - 1);
			timeInQ2++;
			m_lastRunQueue = 2;
		}

		//Run the clock
		clock++;
		this_thread::sleep_for(chrono::milliseconds(1));
	}

}

//Use to see if any process finished on last cycle
bool MLFQ::checkCompletion(const int& clock, int& timeInQ0, int&timeInQ1, int& timeInQ2) {
	queue<Process>* queues[] = { &m_p0Queue, &m_p1Queue, &m_p2Queue };

	//Loop across each queue, look for heads that are complete
	for (auto queue : queues) {
		if (!queue->empty() && queue->front().getTimeRemaining() == 0) {
			//Note completion time
			queue->front().setCompletionTime(clock);
			cout << "PID " << queue->front().getPid()
				<< " has finished at time " << clock << " ms\n";

			//Push completed process into completed list
			m_completedProcesses.push_back(queue->front());

			//Get completed process out of queue
			queue->pop();

			//Reset queue timers
			timeInQ0 = 0;
			timeInQ1 = 0;
			timeInQ2 = 0;

			//Return true if something is done
			return true;
		}
	}

	//False if nothing removed
	return false;
}

//Use to see if a higher-priority process preempts current process
void MLFQ::checkPreemption(int clock, int& timeInQueue1, int& timeInQueue2) {
	//If we were running in q1 and sthg in q0, put it back to start
	if (m_lastRunQueue == 1 && !m_p0Queue.empty()) {
		//Print message to tell user process preempted
		cout << "PID " << m_p1Queue.front().getPid()
			<< " was preempted back into Queue 1 at time " << clock << " ms";
		m_p1Queue.push(m_p1Queue.front());
		m_p1Queue.pop();
		//Reset queue timer
		timeInQueue1 = 0;
	}

	//If we were running in q2 and sthg in q0, put it back to start
	if (m_lastRunQueue == 2 && !m_p0Queue.empty()) {
		//Print message to tell user process preempted
		cout << "PID " << m_p2Queue.front().getPid()
			<< " was preempted back into Queue 2 at time " << clock << " ms";
		m_p2Queue.push(m_p2Queue.front());
		m_p2Queue.pop();
		//Reset queue timer
		timeInQueue2 = 0;
	}

	//If we were running in q2 and sthg in q1, put it back to start
	if (m_lastRunQueue == 2 && !m_p1Queue.empty()) {
		//Print message to tell user process preempted
		cout << "PID " << m_p2Queue.front().getPid()
			<< " was preempted back into Queue 2 at time " << clock << " ms";
		m_p2Queue.push(m_p2Queue.front());
		m_p2Queue.pop();
		//Reset queue timer
		timeInQueue2 = 0;
	}
}

//Returns turnaround time
double MLFQ::getTurnaroundTime() {
	int sumOfTurnarounds = 0;
	for (Process p : m_completedProcesses) {
		int arriveTime = p.getArriveTime();
		int completionTime = p.getCompletionTime();
		sumOfTurnarounds += completionTime - arriveTime;
	}

	return sumOfTurnarounds / static_cast<double>(m_numProcesses);
}

//Returns average response time
double MLFQ::getResponseTime() {
	int sumBurstTime = 0;
	for (Process p : m_completedProcesses)
		sumBurstTime += p.getBurstTime();

	return sumBurstTime / static_cast<double>(m_numProcesses);
}

//Return average waiting time
double MLFQ::getWaitingTime() {
	return getTurnaroundTime() - getResponseTime();
}
