/*
FCFS algo:
Will need to take in the process array as param
Begin some "clock" to monitor arrival times
When each process arrives, create it and place in queue
When current running process finishes, mark terminated
Pick up and finish next process
**RUN INFINITELY, LET USER KILL SCHEDULER (jic)**
*/

#include "Process.h"
#include <queue>
#include <iostream>

using namespace std;

class FCFS {
private:
	queue<Process> m_readyQueue;
	int* m_processArray;
	void schedule();

public:
	FCFS(int* processInfo); // Array is to make all necc processes
		
};

//Build the FCFS scheduler object
FCFS::FCFS(int* processInfo) {
	m_processArray = processInfo;
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

	//Track our currently running process
	//Initialize to "null" process with pid -1
	Process current(-1, 0);

	//Run the scheduler in a loop until we are out of processes
	//to schedule
	while (true) { //TODO: make not a forever loop
		//Check to see if any process has arrived yet
		if (clock == m_processArray[arrayIndex]) {
			//If it has, add it to ready queue
			Process newProcess(m_processArray[arrayIndex - 1],
				m_processArray[arrayIndex + 1]);
			m_readyQueue.push(newProcess);

			//Increment the array index to next process arrive time
			//TODO: keep from running off array
			arrayIndex += 3;
		}

		//See if we've finished any process that is running
		if (current.getPid() != -1 && burstTimeRemaining == 0) {
			current.setState(current.TERMINATED);
			cout << "PID " << current.getPid() << " has finished at time "
				<< clock << " ms";
			current = Process(-1, 0);
		}
		
		//Get us a new process if nothing else going on
		if (current.getPid() == -1 && m_readyQueue.size() != 0) {
			current = m_readyQueue.front();
		}
			//If not, pull the first one out of the queue
			//If so, continue
			//If no more processes and last one finished, kill
		//Sleep 1ms for the heck of it, make it realistic
	}
}

