.PHONY: build run clean-build

build: clean-build
	mkdir build
	g++ -o build/main main.cpp

run: build
	./build/main $(ARGS)

clean-build:
	rm -rf ./build/
