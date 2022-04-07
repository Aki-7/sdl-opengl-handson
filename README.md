# SDL OpenGL Hands-on

## Platform

I confirmed this worked with

- macOS 12.1
  - Intel core i9
  - AMD Radeon Pro 5500M)
  - OpenGL Version: 4.1 ATI-4.7.101

- Ubuntu 20.04
  - Intel Core) i7-8700K
  - GEFORCE RTX 3060
  - OpenGL Version: 4.6.0 NVIDIA 470.103.01

## Dependencies

Install [meson](https://mesonbuild.com/index.html) and [ninja](https://ninja-build.org/).

## Build

```shell
meson build
ninja -C build
```

## Run

```shell
./build/app
```

A window painted in blue will be displayed.
