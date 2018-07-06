#ifndef HEADER_H
#define HEADER_H

//Class to create "process" from input file

/*
Plan here:
The system will read in file info
From array produced, will create a array of these processes in each scheduler routine
When a process arrives, set a flag indicating so
--Will only be scheduled if "has arrived"
Probably could create processes on the fly
--Run a continuous clock, incrementing forward each process and
  checking in array if sthg new has arrived
*/


class Process {

public:
	Process(int pid, int burstTime, int arrivalTime);
	enum ProcessState{READY, RUNNING, TERMINATED};
	const int& getTimeRemaining();
	const int& getBurstTime();
	bool hasArrived();
	const int& getPid();
	void setTimeRemaining(int newTime);
	void setHasArrived();
	void setState(Process::ProcessState state);
	void setCompletionTime(int arrivalTime);
	const int& getCompletionTime();
	Process::ProcessState getState();

private:
	int m_burstTime, m_pid, m_timeRemaining;
	int m_completionTime;
	int m_arrivalTime;
	Process::ProcessState m_state;

};

Process::Process(int pid, int burstTime, int arrivalTime) {
	m_pid = pid;
	m_burstTime = burstTime;
	m_timeRemaining = burstTime;
	m_arrivalTime = arrivalTime;
	m_state = ProcessState::READY;
}

const int & Process::getTimeRemaining() {
	return m_timeRemaining;
}

const int & Process::getBurstTime() {
	return m_burstTime;
}

const int & Process::getPid() {
	return m_pid;
}

const int& Process::getCompletionTime() {
	return m_completionTime;
}

void Process::setTimeRemaining(int newTime) {
	m_timeRemaining = newTime;
}

void Process::setState(Process::ProcessState state) {
	m_state = state;
}

void Process::setCompletionTime(int arrivalTime) {
	m_completionTime = arrivalTime;
}

Process::ProcessState Process::getState() {
	return m_state;
}

#endif
