# SDL OpenGL Hands-on

## Platform

I confirmed this worked with

- macOS 15.5
  - Apple M4
  - OpenGL Version: 4.1

- Ubuntu 20.04
  - Intel Core i7-8700K
  - GEFORCE RTX 3060
  - OpenGL Version: 4.6.0 NVIDIA 470.103.01

## Dependencies

- [meson](https://mesonbuild.com/index.html)
- [ninja](https://ninja-build.org/)

## Build

```shell
meson build
ninja -C build
```

## Run

```shell
./build/sample00/app
```

A window painted in blue will be displayed.
