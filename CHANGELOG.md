# [2.5.0](https://github.com/JonasMuehlmann/ggmath/compare/v2.4.0...v2.5.0) (2021-04-15)


### Features

* **vec:** add additional using-directives for double and int vector ([e119961](https://github.com/JonasMuehlmann/ggmath/commit/e11996184b7fadbbebc6336f2a15851d657cead9))

# [2.4.0](https://github.com/JonasMuehlmann/ggmath/compare/v2.3.0...v2.4.0) (2021-04-14)


### Bug Fixes

* **vec:** fix clang error from using `auto` as template parameter ([9c45b6d](https://github.com/JonasMuehlmann/ggmath/commit/9c45b6d052fb6c8c3838a1a224d7eadf9cb4cd6c))
* **vec:** fix constructor with initializer list ([27e302d](https://github.com/JonasMuehlmann/ggmath/commit/27e302de5edea03604c84b1f5bde8de7657dbe8e))
* **vec:** fix stream output for vector of character types ([9826c68](https://github.com/JonasMuehlmann/ggmath/commit/9826c68c9ab2dbdd073d781297743f357b85b716))


### Features

* **types:** implement concepts  for (non)character types ([66fcfde](https://github.com/JonasMuehlmann/ggmath/commit/66fcfdebdabc27c28c8372c920e4b0974086aed9))
* **vec:** allow copy-construction from different type/length vector ([31201f6](https://github.com/JonasMuehlmann/ggmath/commit/31201f637aa59b41ea8ddd042ba1383e576167cf))

# [2.3.0](https://github.com/JonasMuehlmann/ggmath/compare/v2.2.0...v2.3.0) (2021-04-09)


### Bug Fixes

* **vec:** fix rename of function `vec::debug::throw_if_not_unit()` ([65435a4](https://github.com/JonasMuehlmann/ggmath/commit/65435a4ef4c5b3f40b5cb2d6969655b3bc78ba58))


### Features

* **util:** implement radian/degrees conversion ([1abda9e](https://github.com/JonasMuehlmann/ggmath/commit/1abda9e7a4d9a251843dacadef61c22ecae3093e))
* **vec:** implement `angle_between_unit()` ([0fe8599](https://github.com/JonasMuehlmann/ggmath/commit/0fe8599d6cc2263a42c71b0f8472d5f4c8a05a91))
* **vec:** implement concepts for variadic concept/type checking ([0700b61](https://github.com/JonasMuehlmann/ggmath/commit/0700b61828aaceccd515c86d56970f993af95141))
* **vec:** implement function for accurate comparison of floating point values ([ac103e3](https://github.com/JonasMuehlmann/ggmath/commit/ac103e360b6529dad8863833869327a6734e52cd))

# [2.2.0](https://github.com/JonasMuehlmann/ggmath/compare/v2.1.0...v2.2.0) (2021-04-08)


### Features

* **vec:** implement macro `GGMATH_DEBUG` which, when defined, enables strict checks ([702ceb9](https://github.com/JonasMuehlmann/ggmath/commit/702ceb9bcb223b59e5b09ce0ba1aeba040ee7c58))

# [2.1.0](https://github.com/JonasMuehlmann/ggmath/compare/v2.0.0...v2.1.0) (2021-04-06)


### Bug Fixes

* **vec:** moved false constructor from vec<T, 2> to vec<T, 3> ([225729a](https://github.com/JonasMuehlmann/ggmath/commit/225729acff2d4899a498eaa9b337553937a76530))


### Features

* **vec:** implement iterator and fix copy and move constructor ([3fb4f94](https://github.com/JonasMuehlmann/ggmath/commit/3fb4f94752ccc3f216e70a00a2762391882be281))

# [2.0.0](https://github.com/JonasMuehlmann/ggmath/compare/v1.2.0...v2.0.0) (2021-04-04)


### Bug Fixes

* **vec:** fix vec::lerp() implementation ([512909b](https://github.com/JonasMuehlmann/ggmath/commit/512909b1e0b05bef7d9e595fa05946d20da1d2ec))
* **vec:** improve accuracy of vec::perpendicular ([a59b7f4](https://github.com/JonasMuehlmann/ggmath/commit/a59b7f43284efd9075511581bde7c7612125e5fb))


### chore

* **vec:** remove vec::collinear() ([d5714c6](https://github.com/JonasMuehlmann/ggmath/commit/d5714c6ea36a1a10b781ac585615f16d25c77a8e))


### BREAKING CHANGES

* **vec:** remove vec::collinear(), it is redundant with vec::parallel()

# 1.0.0 (2021-04-01)


### Bug Fixes

* **vec:** specialize template for vec::cross() ([54e95e6](https://github.com/JonasMuehlmann/ggmath/commit/54e95e6ae8a5e794395f408ab4c23fb5259c3cdc))


### Features

* **vec:** overload operator% for cross product(vec::cross()) ([cd912dd](https://github.com/JonasMuehlmann/ggmath/commit/cd912dd0ca67ed78a768bf6544e41178aecea479))
