# schedulesim

**Adam Horvath-Smith, 7-15-2018**

_This is a course project for Wright State University CEG 4350, Summer 2018._

# About

This is a simple scheduling simulator implementing three basic CPU scheduling algorithms: first-come first-served, round-robin, and multi-level feedback queue. The round-robin algorithm is implemented using a static time quantum of 8 ms. The multi-level feedback queue is implemented using three levels. The first is highest priority, running round-robin for 8 ms. The second is round-robin with quantum 16 ms. The third level is implemented first-come first-served. The multi-level feedback queue is preemptive, meaning that if a higher priority process arrives when a lower priority process is running, the current process is preempted.

# Build Instructions

To build from source, simply clone this project to your machine and run make. Note that you will need to first install the g++ compiler capable of compiling at least C++14.

# Usage

./schedulesim &lt;input\_file\_name&gt; &lt;[FCFS | RR | MLFQ]&gt;

- Parameter &lt;input\_file\_name&gt; is a text file listing the PID, Arrival time, and Burst time for each given process. Each of these values is whitespace separated. These values should be integer digits (no decimals). The file should be placed in the same directory as the schedulesim executable; otherwise, the absolute file path must be provided.
- Parameter &lt;[FCFS | RR | MLFQ]&gt; is the user&#39;s chosen scheduling algorithm.
- Both the above parameters are required. Failing to provide one of the parameters or giving a bad parameter (including a bad/non-existent file name) will cause an error to be thrown.

# Usage Examples

#TODO: Generate examples, paste example output
