#Parameters and Flags
CC	:= g++-13
CFLAGS := -std=c++20 -Wall -g -fno-elide-constructors
LFLAGS := -shared

# Directory Paths
SRCDIR := src
BUILDDIR := build
LIBDIR := ../Internal_lib/lib

# Sub-directory Paths under src and alias. E.g. src/Timer/. & Timer
SUBPATH := $(wildcard **/Timer/.)
SUBDIR := $(patsubst $(SRCDIR)/%/,%,$(basename $(SUBPATH)))

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -maxdepth 1 -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

# Evaluate Target output based on existance of main.cpp
ifneq ("$(wildcard $(SRCDIR)/main.cpp)","")
	TARGET := main
else
	TARGET := $(notdir $(basename $(OBJECTS)))
endif

# Include and Linker options
INCLUDE := -I /home/admin/External_lib/boost_lib/include # Specify custom include paths
LIBRARY := # Specify custom library paths
LINKING := -l pthread # Specify custom libraries to include (.so (dynamic) or .a (static)).  E.g. -l mine = libmine.so

# all: library.cpp main.cpp
# $@ evaluates all output objects "all"
# $< evaluates the first upcoming file "library.cpp"
# $^ evaluates all cpp files "library.cpp main.cpp"

all: $(SUBDIR) $(TARGET)

ifeq ($(TARGET), main)
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	$(CC) -o $@ $^ $(LIBRARY) $(LINKING)
else
%: $(BUILDDIR)/%.o
	@echo " Linking..."
	$(CC) -o $@ $< $(LIBRARY) $(LINKING)
endif

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
		$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

# Calling makefile of subdirectory Timer
$(SUBDIR):
	@$(MAKE) lib -C $(SUBPATH)

lib: $(OBJECTS)
	@echo " Creating shared library..."
	@mkdir -p $(LIBDIR)
		$(CC) $(LFLAGS) -o $(LIBDIR)/lib$(TARGET).so $^

clean:
	@echo " Cleaning...";
		$(RM) -r $(BUILDDIR) $(TARGET)
		$(RM) -r $(LIBDIR)/lib$(TARGET).so

# Executing makefile of subdirectory with alias of subdirectory name. E.g. SUBPATH = src/Timer/ and SUBDIR = Timer
$(SUBDIR)_clr:
	@$(MAKE) clean -C $(SUBPATH)

.PHONY: all $(SUBDIR)