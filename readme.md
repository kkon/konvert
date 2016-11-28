# Konvert

**Konvert** is header-only c++ library that offers a **faster alternative to type conversion functions** offered by the standard library.



### Benchmark

Execution times on *3.41GHz corei7-6700 osx clang*, -O3 optimisation level, 10M executions

##### int parsing performance

"42"           | rel. time | time       | ops/sec
---------------|-----------|------------|--------
*konvert::atoi*| 1         |**0.018 s** |**55.5e7**
atoi           | x11.87    | 0.214 s    | 4.7e7
strtol         | x12.10    | 0.218 s    | 4.6e7
scanf          | x37.54    | 0.676 s    | 1.5e7
 

"-502345535"   | rel. time |time        | ops/sec
---------------|-----------|------------|-------
*konvert::atoi*| 1         |**0.056 s** |**178.1e5**
atoi           | x5.85     | 0.3287 s   | 30.4e5
strtol         | x6.03     | 0.3388 s   | 29.5e5
scanf          | x19.75    | 1.1091 s   |  9.0e5

##### double parsing performance

"-6.66"        | rel. time |time        | ops/sec
---------------|-----------|------------|--------
*konvert::atof*| 1         |**0.064 s** |**156.66e6**
strtod         | x4.28     | 0.273 s    | 36.64e6
atof           | x4.37     | 0.279 s    | 35.83e6
scanf          | x19.64    | 1.254 s    |  7.97e6


"10.28455535"  | rel. time |time        | ops/sec
---------------|-----------|------------|--------
*konvert::atof*| 1         |**0.114 s** |**87.6e6**
strtod         | x3.66     |0.417 s     |  23.9e6
atof           | x3.75     |0.427 s     |  23.4e6
scanf          | x13.92    |1.588 s     |   6.2e6



## Installation

Use CMake to import the library into your project, e.g.
```cmake
include(ExternalProject)

externalproject_add(
  konvert
  PREFIX "${PROJECT_BINARY_DIR}/external/konvert"
  URL "https://github.com/kkon/konvert/archive/master.zip"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  BUILD_IN_SOURCE 0
  INSTALL_COMMAND ""
)

externalproject_get_property(konvert SOURCE_DIR)
set(KONVERT_INCLUDE_DIR "${SOURCE_DIR}/include")
include_directories(./ ${KONVERT_INCLUDE_DIR} )
```



## Usage

Use *konvert::* namespaced functions in place of std ones

```cpp
#include <konvert.h>

int main(){
  const char *strnum = "42.42424242";
  int val     = konvert::atoi(strnum); // val = 42
  double dval = konvert::atof(strnum); // dval = 42.42424242
}
```



## Contributing

You need CMake in order to build tests:
```
git clone https://github.com/kkon/konvert.git
cd konvert
make clean test
```

`make clean bench` will run benchmark of performance of konvert vs ato\*, strto\* and sscanf 



## License

The MIT License (MIT)

Copyright (c) 2016 Konstantin Konyakhin
