CXX=g++
all: main.cpp
	$(CXX) -std=c++14 -O3 main.cpp -o main 

debug: main.cpp
	$(CXX) -std=c++14 -DDEBUG -g main.cpp -o main 

copy: 
	cat main.cpp | pbcopy

