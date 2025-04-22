# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ChatClient_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ChatClient_autogen.dir\\ParseCache.txt"
  "ChatClient_autogen"
  )
endif()
