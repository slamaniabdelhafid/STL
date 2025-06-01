.PHONY: all build test docs clean

all: build test

build:
	mkdir -p build
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
	cd build && make

debug:
	mkdir -p build
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug
	cd build && make

test: build
	cd build && ctest --output-on-failure

docs:
	mkdir -p build
	cd build && cmake .. -DBUILD_TESTING=OFF
	cd build && make docs

clean:
	rm -rf build docs
