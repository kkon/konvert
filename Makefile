default_target: all

all:
	mkdir -p build;
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make

test: all
	cd build && ctest ..; cd ..; ./build/test/konvert-test

bench: all
	./build/bench/konvert-bench

clean:
	rm -rf ./build;

.PHONY : default_target test clean bench all
