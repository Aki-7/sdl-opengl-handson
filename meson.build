project(
  'opengl-handson', 'c',
  version: '0.0.1',
  license: 'Apache-2.0',
  meson_version: '>= 0.52.1',
  default_options:  [ 'warning_level=3', 'werror=true', 'optimization=2', 'c_std=gnu11' ],
)

public_inc = include_directories('include')

# dependencies
dep_sdl = dependency('sdl2', fallback: ['sdl2', 'sdl2_dep'], default_options: ['werror=false'])
dep_cglm = dependency('cglm', fallback : ['cglm', 'cglm_dep'], default_options: ['werror=false'])
dep_glew = dependency('glew', fallback: ['glew', 'glew_dep'], default_options: ['werror=false'])
dep_m = meson.get_compiler('c').find_library('m')

system = host_machine.system()
if system == 'darwin'
  dep_gl = dependency('appleframeworks', modules: 'OpenGL')
elif system == 'linux'
  dep_gl = dependency('gl')
else
  assert(false, f'unsupported system: @system@')
endif

subdir('handson-util')
subdir('sample00')
subdir('sample01')
subdir('sample02')
