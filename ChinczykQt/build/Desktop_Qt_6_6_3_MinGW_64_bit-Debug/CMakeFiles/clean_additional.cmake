# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ChinczykQt_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ChinczykQt_autogen.dir\\ParseCache.txt"
  "ChinczykQt_autogen"
  )
endif()
