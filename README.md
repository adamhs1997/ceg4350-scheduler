# ceg4350-scheduler (schedulesim)

**Adam Horvath-Smith, 7-15-2018**

_This is a course project for Wright State University CEG 4350, Summer 2018._

This is a simple scheduling simulator implementing three basic CPU scheduling algorithms: first-come first-served, round-robin, and multi-level feedback queue. The round-robin algorithm is implemented using a static time quantum of 8 ms. The multi-level feedback queue is implemented using three levels. The first is highest priority, running round-robin for 8 ms. The second is round-robin with quantum 16 ms. The third level is implemented first-come first-served. The multi-level feedback queue is preemptive, meaning that if a higher priority process arrives when a lower priority process is running, the current process is preempted.

# Getting Started

Follow the simple instructions below to get schedulesim running.

## Prerequisites

Building schedulesim requires a C++ compiler capable of compiling C++14 or later. g++ is the recommended compiler option and can be installed through your package manager. On Ubuntu, for example, use

```
sudo apt install g++
```
Make can also be used to build the project. This, like g++, can be installed through your package manager. Installing git also makes it convenient to clone this repository.

## Installation

Assuming git, make, and a compatible C++ compiler are installed, the following instructions can be used to build schedulesim:

```
git clone https://github.com/adamhs1997/ceg4350-scheduler.git
cd ceg4350-scheduler
make
```

# Usage

./schedulesim &lt;input\_file\_name&gt; &lt;[FCFS | RR | MLFQ]&gt;

- Parameter &lt;input\_file\_name&gt; is a text file listing the PID, Arrival time, and Burst time for each given process. Each of these values is whitespace separated. These values should be integer digits (no decimals). The file should be placed in the same directory as the schedulesim executable; otherwise, the absolute file path must be provided.
- Parameter &lt;[FCFS | RR | MLFQ]&gt; is the user&#39;s chosen scheduling algorithm.
- Both the above parameters are required. Failing to provide one of the parameters or giving a bad parameter (including a bad/non-existent file name) will cause an error to be thrown.

## Usage Examples

Consider the file ```longer_processes.txt```, which contains the following data:

```
0       0       13
1       2       24
2       3       28
3       5       17
```

Running ```./schedulesim longer_processes.txt fcfs``` produces the following output:
```
Selected scheduling algorithm: FCFS
PID 0 starts running at time 0 ms
PID 0 has finished at time 13 ms
PID 1 starts running at time 13 ms
PID 1 has finished at time 37 ms
PID 2 starts running at time 37 ms
PID 2 has finished at time 65 ms
PID 3 starts running at time 65 ms
PID 3 has finished at time 82 ms
============================================
Average waiting time: 26.25 ms
Average response time: 26.25 ms
Average turnaround time: 46.75 ms
============================================
```

Similarly, running  ```./schedulesim longer_processes.txt rr``` produces the following output:
```
Selected scheduling algorithm: RR
PID 0 starts running at time 0 ms
PID 0 is preempted at time 8 ms
PID 1 starts running at time 8 ms
PID 1 is preempted at time 16 ms
PID 2 starts running at time 16 ms
PID 2 is preempted at time 24 ms
PID 3 starts running at time 24 ms
PID 3 is preempted at time 32 ms
PID 0 starts running at time 32 ms
PID 0 has finished at time 37 ms
PID 1 starts running at time 37 ms
PID 1 is preempted at time 45 ms
PID 2 starts running at time 45 ms
PID 2 is preempted at time 53 ms
PID 3 starts running at time 53 ms
PID 3 is preempted at time 61 ms
PID 1 starts running at time 61 ms
PID 1 has finished at time 69 ms
PID 2 starts running at time 69 ms
PID 2 is preempted at time 77 ms
PID 3 starts running at time 77 ms
PID 3 has finished at time 78 ms
PID 2 starts running at time 78 ms
PID 2 has finished at time 82 ms
============================================
Average waiting time: 43.5 ms
Average response time: 9.5 ms
Average turnaround time: 64 ms
============================================
```

Running ```./schedulesim longer_processes.txt mlfq``` produces the following output:
```
Selected scheduling algorithm: MLFQ
PID 0 starts running at time 0 ms
PID 0 is preempted into Queue 1 at time 8 ms
PID 1 starts running at time 8 ms
PID 1 is preempted into Queue 1 at time 16 ms
PID 2 starts running at time 16 ms
PID 2 is preempted into Queue 1 at time 24 ms
PID 3 starts running at time 24 ms
PID 3 is preempted into Queue 1 at time 32 ms
PID 0 continues running at time 32 ms
PID 0 has finished at time 37 ms
PID 1 continues running at time 37 ms
PID 1 has finished at time 53 ms
PID 2 continues running at time 53 ms
PID 2 is preempted into Queue 2 at time 69 ms
PID 3 continues running at time 69 ms
PID 3 has finished at time 78 ms
PID 2 continues running at time 78 ms
PID 2 has finished at time 82 ms
============================================
Average waiting time: 39.5 ms
Average response time: 9.5 ms
Average turnaround time: 60 ms
============================================
```

# Acknowledgements
Special thanks to Dr. Yong Pei, Wright State University, for developing this project. It was a pleasure!
