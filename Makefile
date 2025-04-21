.PHONY: build run clean-build generate test

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
	./build/generator $(N)

make test:
	@g++ -o build/main main.cpp
	@g++ -o build/stable_sort stable_sort.cpp
	@echo "Testing std::stable_sort..."
	@./build/stable_sort $(ARGS)
	@echo "Testing countSort..."
	@./build/main $(ARGS)