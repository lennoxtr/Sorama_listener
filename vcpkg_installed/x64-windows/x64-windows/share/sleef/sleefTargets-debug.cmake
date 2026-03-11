#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "sleef::sleef" for configuration "Debug"
set_property(TARGET sleef::sleef APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(sleef::sleef PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/sleef.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/sleef.dll"
  )

list(APPEND _cmake_import_check_targets sleef::sleef )
list(APPEND _cmake_import_check_files_for_sleef::sleef "${_IMPORT_PREFIX}/debug/lib/sleef.lib" "${_IMPORT_PREFIX}/debug/bin/sleef.dll" )

# Import target "sleef::sleefdft" for configuration "Debug"
set_property(TARGET sleef::sleefdft APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(sleef::sleefdft PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/sleefdft.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_DEBUG "sleef::sleef"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/sleefdft.dll"
  )

list(APPEND _cmake_import_check_targets sleef::sleefdft )
list(APPEND _cmake_import_check_files_for_sleef::sleefdft "${_IMPORT_PREFIX}/debug/lib/sleefdft.lib" "${_IMPORT_PREFIX}/debug/bin/sleefdft.dll" )

# Import target "sleef::sleefquad" for configuration "Debug"
set_property(TARGET sleef::sleefquad APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(sleef::sleefquad PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/debug/lib/sleefquad.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/bin/sleefquad.dll"
  )

list(APPEND _cmake_import_check_targets sleef::sleefquad )
list(APPEND _cmake_import_check_files_for_sleef::sleefquad "${_IMPORT_PREFIX}/debug/lib/sleefquad.lib" "${_IMPORT_PREFIX}/debug/bin/sleefquad.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
