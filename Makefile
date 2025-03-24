.PHONY: build run test clean

build: clean-build
	mkdir build
	g++ -o build/main main.cpp

run: clean-build
	mkdir build
	g++ -o build/main main.cpp
	./build/main

test:
	./build/*_test

clean-build:
	rm -rf ./build/
