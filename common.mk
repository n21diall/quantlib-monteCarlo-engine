
.PHONY: all build test

all: build test

build: main

test: main
	./main

main: *.hpp *.cpp
	g++ *.cpp -std=c++17 -I/opt/homebrew/Cellar/boost/1.75.0_2/include/ -I/opt/homebrew/Cellar/quantlib/1.21/include/ -I. -g0 -O3 -L/opt/homebrew/Cellar/quantlib/1.21/lib -lQuantLib -o main

