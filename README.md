# AVX OPTIMIZATION #

[![Build Status](https://travis-ci.org/bestreyer/avx-optimization.svg?branch=master)](https://travis-ci.org/bestreyer/avx-optimization)

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
``` make test ```

## Resources
[Division by Invariant Integers using Multiplication](https://gmplib.org/~tege/divcnst-pldi94.pdf)
