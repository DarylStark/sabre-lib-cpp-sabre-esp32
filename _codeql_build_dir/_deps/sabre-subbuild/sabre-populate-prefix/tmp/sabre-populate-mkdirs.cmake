# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-src")
  file(MAKE_DIRECTORY "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-src")
endif()
file(MAKE_DIRECTORY
  "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-build"
  "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-subbuild/sabre-populate-prefix"
  "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-subbuild/sabre-populate-prefix/tmp"
  "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-subbuild/sabre-populate-prefix/src/sabre-populate-stamp"
  "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-subbuild/sabre-populate-prefix/src"
  "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-subbuild/sabre-populate-prefix/src/sabre-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-subbuild/sabre-populate-prefix/src/sabre-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/runner/work/sabre-lib-cpp-sabre-esp32/sabre-lib-cpp-sabre-esp32/_codeql_build_dir/_deps/sabre-subbuild/sabre-populate-prefix/src/sabre-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
