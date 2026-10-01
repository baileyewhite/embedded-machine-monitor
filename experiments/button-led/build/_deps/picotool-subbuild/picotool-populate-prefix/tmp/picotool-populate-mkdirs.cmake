# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-src"
  "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-build"
  "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-subbuild/picotool-populate-prefix"
  "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-subbuild/picotool-populate-prefix/tmp"
  "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp"
  "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-subbuild/picotool-populate-prefix/src"
  "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/whiteb11/embedded-machine-monitor/button-led/build/_deps/picotool-subbuild/picotool-populate-prefix/src/picotool-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
