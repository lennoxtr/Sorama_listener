# Install script for directory: C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/pkgs/yasm_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/x64-windows-dbg/yasm.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/x64-windows-dbg/yasm.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libyasm" TYPE FILE FILES
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/arch.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/assocdat.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/bitvect.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/bytecode.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/compat-queue.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/coretype.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/dbgfmt.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/errwarn.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/expr.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/file.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/floatnum.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/hamt.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/insn.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/intnum.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/inttree.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/linemap.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/listfmt.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/md5.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/module.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/objfmt.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/parser.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/phash.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/preproc.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/section.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/symrec.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/valparam.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/src/d25248d823-5776a3607f.clean/libyasm/value.h"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/yasm/x64-windows-dbg/libyasm/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
