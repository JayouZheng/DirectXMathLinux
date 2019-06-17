CC = gcc
CXX = g++
AR = ar
# Utils
MKDIR_P = mkdir -p
# Linker Static libs
LINKCMD_LIB = $(AR) -r "$@"
# Linker Executeables
LINKCMD_EXE = $(CXX) $(LDFLAGS) -o "$@"

# Flags
CFLAGS = -m64 -O3 -Wall
CXXFLAGS = -m64 -O3 -Wall -std=c++17
LDFLAGS =  -m64 -s

# Options
DEFINES = -DNDEBUG
INCLUDES = 

TARGETDIR = .
TARGET = $(TARGETDIR)/test
SOURDEDIR = .
OBJDIR = obj
SRC_FILES = \
	$(SOURDEDIR)/test.cpp \

CXXFLAGS += $(DEFINES) $(INCLUDES)

OBJ_FILES := $(patsubst $(SOURDEDIR)/%.cpp, $(OBJDIR)/%.o, $(SRC_FILES))

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	@$(MKDIR_P) $(@D)
	$(LINKCMD_EXE) $(OBJ_FILES) $(LIBS)

$(OBJDIR)/%.o: $(SOURDEDIR)/%.cpp
	@$(MKDIR_P) $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

-include $(OBJ_FILES:.o=.d)

.PHONY: clean
clean:
	rm -f $(OBJ_FILES) $(TARGET)

