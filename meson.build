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

dependencies = [
  dep_sdl,
]

system = host_machine.system()
if system == 'darwin'
  dependencies += dependency('appleframeworks', modules: 'OpenGL')
elif system == 'linux'
  dependencies += dependency('gl')
endif

sources = [
  'main.c'
]

executable(
  'app',
  sources,
  install: false,
  dependencies: dependencies,
)
