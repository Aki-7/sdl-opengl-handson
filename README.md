# SDL OpenGL Hands-on

## Platform

I confirmed this worked with

- macOS 12.1 (Intel core i9 / AMD Radeon Pro 5500M)

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

A window painted in red will be displayed.
