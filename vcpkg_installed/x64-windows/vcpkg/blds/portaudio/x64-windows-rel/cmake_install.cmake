# Install script for directory: C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/pkgs/portaudio_x64-windows")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/portaudio" TYPE FILE FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/README.md")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/doc/portaudio" TYPE FILE FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/LICENSE.txt")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/portaudio-2.0.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/include/portaudio.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/include/pa_win_ds.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/include/pa_win_waveformat.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/include/pa_win_wmme.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/include/pa_win_waveformat.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/include/pa_win_wasapi.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/include/pa_win_waveformat.h"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/src/dfffbcfbb6-ecc2939f93.clean/include/pa_win_wdmks.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/portaudio.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/portaudio.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/portaudio/portaudioTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/portaudio/portaudioTargets.cmake"
         "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/CMakeFiles/Export/90a8b282bce0779409342a760050f91f/portaudioTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/portaudio/portaudioTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/portaudio/portaudioTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/portaudio" TYPE FILE FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/CMakeFiles/Export/90a8b282bce0779409342a760050f91f/portaudioTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/portaudio" TYPE FILE FILES "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/CMakeFiles/Export/90a8b282bce0779409342a760050f91f/portaudioTargets-release.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/portaudio" TYPE FILE FILES
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/cmake/portaudio/portaudioConfig.cmake"
    "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/cmake/portaudio/portaudioConfigVersion.cmake"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "C:/Users/huykh/source/repos/Test_sorama/vcpkg_installed/x64-windows/vcpkg/blds/portaudio/x64-windows-rel/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
