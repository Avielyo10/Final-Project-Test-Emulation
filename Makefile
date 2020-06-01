CXX=g++
CXXFLAGS=-std=c++17 -Wall -g 

all: compileTest clean

strategy.o: src/strategies/strategy.cpp
	@$(CXX) $(CXXFLAGS) -c src/strategies/strategy.cpp -o strategy.o
	
completeSearchStrategy.o: src/strategies/completeSearchStrategy.cpp
	@$(CXX) $(CXXFLAGS) -c src/strategies/completeSearchStrategy.cpp -o completeSearchStrategy.o

worker.o: src/worker.cpp
	@$(CXX) $(CXXFLAGS) -c src/worker.cpp -o worker.o

test.o: test/test.cpp
	@$(CXX) $(CXXFLAGS) -c test/test.cpp -o test.o

compileTest: strategy.o completeSearchStrategy.o worker.o test.o
	@$(CXX) $(CXXFLAGS) -o emulation.out strategy.o completeSearchStrategy.o worker.o test.o
	@./emulation.out

clean:
	@rm emulation.out *.o
