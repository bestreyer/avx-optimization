# AVX OPTIMIZATION
SHOULD NOT USE IT IN PRODUCTION
Experimental open source project for testing INTEL AVX2 instructions

##Building
Create build directory and move to the build directory
``` mkdir build && cd build```

build
```cmake ../ && make```

build with tests
```cmake -Dtest=1 ../ && make```

run tests
``` make tests ```
