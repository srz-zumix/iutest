if (CMAKE_GENERATOR MATCHES Xcode)
  # Get the Xcode version
  execute_process(COMMAND xcodebuild -version
    OUTPUT_VARIABLE XCODE_VERSION_STRING
    ERROR_QUIET
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  string(REGEX MATCH "Xcode [0-9\\.]+" XCODE_VERSION "${XCODE_VERSION_STRING}")
  string(REGEX REPLACE "Xcode ([0-9\\.]+)" "\\1" XCODE_VERSION "${XCODE_VERSION}")
  message(STATUS "XCODE_VERSION: ${XCODE_VERSION}")
endif()
