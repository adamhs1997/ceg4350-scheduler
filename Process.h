#ifndef HEADER_H
#define HEADER_H

//Class to create "process" from input file

class Process {

public:
	Process(int pid, int burstTime, int arrivalTime);
	enum ProcessState{READY, RUNNING, TERMINATED};
	const int& getTimeRemaining();
	const int& getBurstTime();
	const bool& hasRun();
	const int& getPid();
	void setTimeRemaining(int newTime);
	void setHasRun();
	void setState(Process::ProcessState state);
	void setCompletionTime(int arrivalTime);
	void setInitialRunTime(int initialRunTime);
	const int& getCompletionTime();
	const int& getArriveTime();
	const int& getInitialRunTime();
	Process::ProcessState getState();

private:
	int m_burstTime, m_pid, m_timeRemaining;
	int m_completionTime;
	int m_arrivalTime;
	int m_initialRunTime;
	bool m_hasRun;
	Process::ProcessState m_state;

};

Process::Process(int pid, int burstTime, int arrivalTime) {
	m_pid = pid;
	m_burstTime = burstTime;
	m_timeRemaining = burstTime;
	m_arrivalTime = arrivalTime;
	m_hasRun = false;
	m_state = ProcessState::READY;
}

const int& Process::getTimeRemaining() {
	return m_timeRemaining;
}

const int& Process::getBurstTime() {
	return m_burstTime;
}

const int& Process::getPid() {
	return m_pid;
}

const int& Process::getCompletionTime() {
	return m_completionTime;
}

const int& Process::getArriveTime() {
	return m_arrivalTime;
}

const int& Process::getInitialRunTime() {
	return m_initialRunTime;
}

const bool& Process::hasRun() {
	return m_hasRun;
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

void Process::setInitialRunTime(int initialRunTime) {
	m_initialRunTime = initialRunTime;
}

void Process::setHasRun() {
	m_hasRun = true;
}

Process::ProcessState Process::getState() {
	return m_state;
}

#endif
