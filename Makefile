SRC := $(wildcard examples/*.cpp)
OUT := $(patsubst examples/%.cpp, bin/%, $(SRC_FILES))

.PHONY: examples

examples:
	mkdir -p bin

	c++ -c $(SRC) -ldl -lGL -lSDL2main -lSDL2 -Iglass -std=c++17

clean:
	rm -rf "bin/"

install:
	sudo cp -rf glass/ /usr/include/glass/