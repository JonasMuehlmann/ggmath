# ggmath (graphics and game math)

[![Build Status](https://travis-ci.com/JonasMuehlmann/ggmath.svg?branch=master)](https://travis-ci.com/JonasMuehlmann/ggmath) ![img](https://img.shields.io/badge/semver-2.0.0-green) [![Conventional Commits](https://img.shields.io/badge/Conventional%20Commits-1.0.0-yellow.svg)](https://conventionalcommits.org) [![pre-commit](https://img.shields.io/badge/pre--commit-enabled-brightgreen?logo=pre-commit&logoColor=white)](https://github.com/pre-commit/pre-commit)

This is my personal math library for my upcoming graphics and game programming projects. Other motivations and goals for
the development of this library are:

- Learning modern c++ (especially c++20)
- Building a good c++ project template/structure/workflow
- Learning new math and reinforcing old knowledge
- Building things from scratch is fun and a good learning resource
- Improve my unit testings skills using google test
- Learn proper micro benchmarking with google benchmark
- Learn about optimization (with the use of disassembly)
- Demonstrate my skills and my interest in learning

## API documentation and usage

Since the project is still small, the [test cases](tests/) and [source files](src/) themselves should suffice for now.

The code is tested for clang 11 and gcc 10, at least clang 11 or gcc 10 are required for compilation.

The sources compile into a static library, which you can link against your project.

The following macros can be defined when compiling:

- GGMATH_DEBUG: Enables strict checks for debugging purposes(e.g. Throwing an exception when a function requiring a
  unit-vector does not receive one).

## Contributing

This project serves mostly a personal learning experience, but I still appreciate bug reports, suggestions or similar

## Acknowledgement

This project and it's development use:

- [google test](https://github.com/google/googletest)
- [google benchmark](https://github.com/google/benchmark)
- [Matt Godbolt's compiler explorer](https://godbolt.org/)
- [pre-commit hooks](https://github.com/pre-commit/pre-commit-hooks)
- [semantic release](https://github.com/semantic-release/semantic-release)
- [commitlint](https://github.com/conventional-changelog/commitlint)
- [Travis CI](https://github.com/semantic-release/semantic-release)

## License

Copyright (C) 2021 [Jonas Muehlmann](https://github.com/JonasMuehlmann)

The project is licensed under the terms of the MIT license, you can view it [here](LICENSE.md).