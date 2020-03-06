CXX=g++
CXXFLAGS=-std=c++17

all:compileTest clean

compileTest:
	@$(CXX) $(CXXFLAGS) test/test.cpp
	@./a.out

clean:
	@rm a.out
