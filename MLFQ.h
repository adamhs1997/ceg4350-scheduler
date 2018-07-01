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

using namespace std;

class MLFQ {

private:
	//Need three ready queues, one for each priority
	queue<Process> m_p0Queue, m_p1Queue, m_p2Queue;
	int* m_processArray;
	int m_numProcesses;
	int m_currentExecutionTime;
	void checkCompletion();

public:
	MLFQ(int* processInfo, int numProcesses);
	void schedule();

};

MLFQ::MLFQ(int* processInfo, int numProcesses) {
	m_processArray = processInfo;
	m_numProcesses = numProcesses;
	m_currentExecutionTime = 0;
}

//Main MLFQ scheduler, only public function
void MLFQ::schedule() {
	//CanNOT really rely on other RR and FCFS, as these work in batch
	//This will be new batch scheduler, relying on parallel RR/FCFS implementation

	//Start running a clock
	//See if new processes have arrived
	//Add any new process to q0
	//Run anything in q0 1ms
	//"" q1 (else)
	//"" q2 (else)

	//Create a dummy clock variable
	int clock = 0;

	//Pointer to right index in process array
	//Keeps track of which is next to be born
	int arrayIndex = 1;

	//Track time process spent in RR each queue
	int timeInQ0, timeInQ1;

	//Track processes that have been completed
	int numberProcessesComplete = 0;

	//Run the scheduler in a loop until we are out of processes to schedule
	while (numberProcessesComplete != m_numProcesses) {
		//Check to see if any process has arrived yet
		if (clock == m_processArray[arrayIndex]) {
			//If it has, add it to queue 0 (highest priority)
			Process newProcess(m_processArray[arrayIndex - 1],
				m_processArray[arrayIndex + 1]);
			m_p0Queue.push(newProcess);

			//Increment the array index to next process arrive time
			arrayIndex += 3;
		}

		//Check if any process has finished
		checkCompletion();

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
			cout << "PID " << m_p0Queue.front().getPid()
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
		}

		//See if anything in q1 to run
		else if (!m_p1Queue.empty()) {
			if (timeInQ1 == 0)
				cout << "PID " << m_p1Queue.front().getPid()
					<< " continues running at time " << clock << " ms\n";
			m_p1Queue.front().setTimeRemaining(m_p1Queue.front().getTimeRemaining() - 1);
			timeInQ1++;
		}

		//Otherwise, we run FCFS
		else {
			//TODO: figure out how to print sthg for first time here
			m_p2Queue.front().setTimeRemaining(m_p2Queue.front().getTimeRemaining() - 1);
		}

		//Run the clock
		clock++;
		this_thread::sleep_for(chrono::seconds(1));
	}

}

//Use to see if any process finished on last cycle
void MLFQ::checkCompletion() {
	queue<Process> queues[] = { m_p0Queue, m_p1Queue, m_p2Queue };

	//Loop across each queue, look for heads that are complete
	for (auto queue : queues) {
		if (queue.front().getTimeRemaining() == 0) {
			cout << "PID " << queue.front().getPid()
				<< " has finished at time " << clock << " ms\n";
			queue.pop();
		}
	}
}
