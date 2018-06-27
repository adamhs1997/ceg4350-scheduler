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
private:
	int m_burstTime, m_pid, m_timeRemaining;
	bool m_hasArrived;

public:
	Process(int pid, int burstTime);
	const int& getTimeRemaining();
	const int& getBurstTime();
	bool hasArrived();
	const int& getPid();
	void setTimeRemaining(int newTime);
	void setHasArrived();
};

Process::Process(int pid, int burstTime) {
	m_pid = pid;
	m_burstTime = burstTime;
	m_timeRemaining = burstTime;
	m_hasArrived = false;
}

const int & Process::getTimeRemaining() {
	return m_timeRemaining;
}

const int & Process::getBurstTime() {
	return m_burstTime;
}

bool Process::hasArrived() {
	return m_hasArrived;
}

const int & Process::getPid() {
	return m_pid;
}

void Process::setTimeRemaining(int newTime) {
	m_timeRemaining = newTime;
}

void Process::setHasArrived() {
	m_hasArrived = true;
}


