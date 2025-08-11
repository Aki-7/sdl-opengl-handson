deps_handson_util = [
  dep_gl,
  dep_glew,
  dep_sdl,
]

srcs_handson_util = [
  'shader-compiler.c',
]

lib_handson_util = static_library(
  'handson-util',
  srcs_handson_util,
  install: false,
  dependencies: deps_handson_util,
  include_directories: public_inc,
)

dep_handson_util = declare_dependency(
  link_with: lib_handson_util,
  include_directories: public_inc,
)
