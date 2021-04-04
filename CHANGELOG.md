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
