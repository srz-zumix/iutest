# for apple
if (APPLE)
	if(NOT OSX_ARCHITECTURES OR OSX_ARCHITECTURES STREQUAL "")
		if(_CMAKE_OSX_MACHINE MATCHES "ppc")
			set(OSX_ARCHITECTURES
				"ppc;ppc64"
				CACHE
				STRING
				"Build architectures for OS X"
				FORCE)
		else()
			set(OSX_ARCHITECTURES
				"x86_64"
				CACHE
				STRING
				"Build architectures for OS X"
				FORCE)
		endif()
  endif()
	if(NOT CMAKE_OSX_ARCHITECTURES OR CMAKE_OSX_ARCHITECTURES STREQUAL "")
    set(CMAKE_OSX_ARCHITECTURES ${OSX_ARCHITECTURES} CACHE STRING "Build architectures for OS X" FORCE)
  endif()
  message(STATUS "CMAKE_OSX_ARCHITECTURES: ${CMAKE_OSX_ARCHITECTURES}")
  # CMAKE_MACOSX_BUNDLE is needed to avoid the error "target specifies product type 'com.apple.product-type.tool'
  set(CMAKE_MACOSX_BUNDLE YES)
endif()
