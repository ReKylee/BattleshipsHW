# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-src"
  "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-build"
  "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-subbuild/ftxui-populate-prefix"
  "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-subbuild/ftxui-populate-prefix/tmp"
  "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp"
  "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-subbuild/ftxui-populate-prefix/src"
  "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/mnt/c/Users/ido54/OneDrive - Shenkar College/Documents/College/Year 2 Semester 1/Programming 3/BattleShipsHW/cmake-build-debug-wsl/_deps/ftxui-subbuild/ftxui-populate-prefix/src/ftxui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
