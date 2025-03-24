.PHONY: build run clean

build: clean-build
	mkdir build
	g++ -o build/main main.cpp

run: build
	./build/main $(ARGS)

clean-build:
	rm -rf ./build/

generate:
	rm -rf ./data/
	mkdir data
	g++ -o data/generator generator.cpp
	./data/generator

time:
	time -f "./build/main %U user %S system %P cpu %e total" ./build/main