build: main.o
	$(CXX) -std=c++11 Main.o -o schedulesim

main.o: Main.cpp FileHandler.h Process.h FCFS.h RR.h MLFQ.h
	$(CXX) -std=c++11 -c Main.cpp
