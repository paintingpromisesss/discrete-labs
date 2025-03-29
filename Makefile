.PHONY: build run clean-build generate time clean-run

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
	g++ -o build/generator generator.cpp
	./build/generator

time:
	time -f "./build/main %U user %S system %P cpu %e total" ./build/main $(ARGS)