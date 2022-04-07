project(
  'opengl-handson', 'c',
  version: '0.0.1',
  license: 'Apache-2.0',
  meson_version: '>= 0.52.1',
  default_options:  [ 'warning_level=3', 'werror=true', 'optimization=2', 'c_std=gnu11' ],
)

public_inc = include_directories('include')

# dependencies
dep_sdl = dependency('sdl2')
dep_opengl = dependency('appleframeworks', modules: 'OpenGL')

dependencies = [
  dep_sdl,
  dep_opengl,
]

sources = [
  'main.c'
]

executable(
  'app',
  sources,
  install: false,
  dependencies: dependencies,
)
