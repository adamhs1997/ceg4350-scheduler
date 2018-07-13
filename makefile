build: main.o
	$(CXX) main.o -o schedulesim

main.o: Main.cpp FileHandler.h Process.h FCFS.h RR.h MLFQ.h
	$(CXX) -c Main.cpp
