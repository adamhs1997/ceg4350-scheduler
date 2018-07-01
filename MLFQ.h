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
	void checkCompletion();
	void scheduleRR8();
	void scheduleRR16();
	void scheduleFCFS();

public:
	MLFQ(int* processInfo, int numProcesses);
	void schedule();

};

MLFQ::MLFQ(int* processInfo, int numProcesses) {
	m_processArray = processInfo;
	m_numProcesses = numProcesses;
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

	//Track the current burst time
	int burstTimeRemaining = 0;

	//Track processes that have been completed
	int numberProcessesComplete = 0;

	//Track our currently running process
	//Initialize to "null" process with pid -1
	Process current(-1, 0);

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

		//See if anything in q0 to run
		if (!m_p0Queue.empty())
			scheduleRR8();

		//See if anything in q1 to run
		else if (!m_p1Queue.empty())
			scheduleRR16();

		//Otherwise, we run FCFS
		else
			scheduleFCFS();

		//Run the clock, update time remaining
		clock++;
		burstTimeRemaining--;
		this_thread::sleep_for(chrono::milliseconds(1));
	}

}

//Use to see if any process finished on last cycle
void MLFQ::checkCompletion() {
	queue<Process> queues[] = { m_p0Queue, m_p1Queue, m_p2Queue };

	//Loop across each queue, look for heads that are complete
	for (auto queue : queues) {
		//NOTE: Must reassign queue.front with current for this to work
		if (queue.front().getTimeRemaining() == 0)
			queue.pop();
	}
}
