
# Directories:
DIR_CUR		= ./src

# Sources:
SRC_CUR		= $(wildcard $(DIR_CUR)/*.cpp)

### set variables before include make.rules
# debug ?= 1
# quiet ?= 1

out_executable  = sudokuresolver
include_dirs    = $(DIR_CUR)
cpp_sources     = $(SRC_CUR)

CXXFLAGS		+= -Wno-invalid-offsetof -Wno-deprecated -g

include make.rules
