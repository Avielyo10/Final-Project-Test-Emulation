CXX=g++
CXXFLAGS=-std=c++17 -Wall -g 

all: compileTest

Strategy.o: src/strategies/Strategy.cpp
	@$(CXX) $(CXXFLAGS) -c src/strategies/Strategy.cpp -o Strategy.o
	
CompleteSearchStrategy.o: src/strategies/CompleteSearchStrategy.cpp
	@$(CXX) $(CXXFLAGS) -c src/strategies/CompleteSearchStrategy.cpp -o CompleteSearchStrategy.o

DPStrategy2Machines.o: src/strategies/DPStrategy2Machines.cpp
	@$(CXX) $(CXXFLAGS) -c src/strategies/DPStrategy2Machines.cpp -o DPStrategy2Machines.o

Worker.o: src/Worker.cpp
	@$(CXX) $(CXXFLAGS) -c src/Worker.cpp -o Worker.o

test.o: test/test.cpp
	@$(CXX) $(CXXFLAGS) -c test/test.cpp -o test.o

compileTest: Strategy.o CompleteSearchStrategy.o DPStrategy2Machines.o Worker.o test.o
	@$(CXX) $(CXXFLAGS) -o emulation.out Strategy.o CompleteSearchStrategy.o DPStrategy2Machines.o Worker.o test.o
	@./emulation.out

clean:
	@rm -f emulation.out *.o
