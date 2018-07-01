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

public:
	MLFQ(int* processInfo, int numProcesses);
	void schedule();

};

MLFQ::MLFQ(int* processInfo, int numProcesses) {
	m_processArray = processInfo;
	m_numProcesses = numProcesses;
}

void MLFQ::schedule() {
}
