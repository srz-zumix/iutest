# - Try to find iutest include dirs
#
# Usage of this module as follows:
#
#     find_package(IUTEST)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  IUTEST_ROOT_DIR          Set this variable to the root installation of
#                            iutest if the module has problems finding the
#                            proper installation path.
#
# Variables defined by this module:
#
#  IUTEST_FOUND             System has iutest, include dirs found
#  IUTEST_INCLUDE_DIR       The iutest include directories.

find_path(IUTEST_ROOT_DIR
        NAMES include/iutest.hpp
        HINTS 
            ENV IUTEST_ROOT
        )

find_path(IUTEST_INCLUDE_DIR
        NAMES iutest.hpp
        HINTS 
            ${IUTEST_ROOT_DIR}/include
        )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(IUTEST DEFAULT_MSG
    IUTEST_INCLUDE_DIR
)
