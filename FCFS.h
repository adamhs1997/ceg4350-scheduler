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
#include <Queue>

using namespace std;

class FCFS {
private:
	queue<Process> m_readyQueue;
	int* m_processInfo;
	void schedule();

public:
	FCFS(int* processInfo); // Array is to make all necc processes
		
};

//Build the FCFS scheduler object
FCFS::FCFS(int* processInfo) {
	m_processInfo = processInfo;
}

//The FCFS master scheduler!!!
void FCFS::schedule() {

}

