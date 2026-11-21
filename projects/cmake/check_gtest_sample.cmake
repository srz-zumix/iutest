execute_process(
  COMMAND "${SAMPLE}" ${SAMPLE_ARG}
  RESULT_VARIABLE result
  OUTPUT_VARIABLE output
  ERROR_VARIABLE error
)

message("${output}${error}")
if (NOT "${result}" STREQUAL "${EXPECTED_EXIT}" OR
    NOT "${output}" MATCHES "${EXPECTED_OUTPUT}")
  message(FATAL_ERROR
    "Expected exit ${EXPECTED_EXIT} and output matching '${EXPECTED_OUTPUT}'; got exit ${result}")
endif()
