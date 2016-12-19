default_target: all

all:
	mkdir -p build;
	cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make

test: all
	cd build && ctest ..; cd ..; ./build/test/konvert-test

profile: all
	valgrind --tool=cachegrind --branch-sim=yes --cachegrind-out-file=build/cache-profile.txt ./build/test/konvert-pf
	cg_annotate --auto=yes build/cache-profile.txt
	qcachegrind build/cache-profile.txt

bench: all
	./build/bench/konvert-bench

clean:
	rm -rf ./build;

.PHONY : default_target test clean bench all
