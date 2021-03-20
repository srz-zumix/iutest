IUTEST_CXX_STRICT_FLAGS+= \
	-Wformat=2 -Wcast-qual -Wcast-align \
	-Wwrite-strings -Wpointer-arith -Wundef -Wunused-macros

# IUTEST_CXX_STRICT_FLAGS+= -Wfloat-equal
# Necessary for peep class operator
# IUTEST_CXX_STRICT_FLAGS+= -Wconversion
