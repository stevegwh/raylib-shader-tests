# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-src"
  "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-build"
  "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix"
  "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/tmp"
  "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
  "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src"
  "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/steve/git/raylib-shader-tests/cmake-build-debug/_deps/raylib-subbuild/raylib-populate-prefix/src/raylib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
