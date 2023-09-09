#Parameters and Flags
CC	:= g++
CFLAGS := -std=c++11 -Wall -g -fno-elide-constructors
LFLAGS := -shared

# Directory Paths
SRCDIR := src
BUILDDIR := build
LIBDIR := ../lib

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Evaluate Target output based on existance of main.cpp
ifneq ("$(wildcard $(SRCDIR)/main.cpp)","")
	TARGET := main
else
	TARGET := $(notdir $(basename $(OBJECTS)))
endif

# Include and Linker options
INCLUDE := -I include	# Specify custom include paths
LIBRARY := -L lib		# Specify custom library paths
LINKING := 		# Specify custom libraries to include (.so (dynamic) or .a (static)).  E.g. -l mine = libmine.so

# all: library.cpp main.cpp
# $@ evaluates all output objects "all"
# $< evaluates the first upcoming file "library.cpp"
# $^ evaluates all cpp files "library.cpp main.cpp"

all: $(TARGET)

ifeq ($(TARGET), main)
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) -o $@ $^ $(LIBRARY) $(LINKING)"; 
	$(CC) -o $@ $^ $(LIBRARY) $(LINKING)
else
%: $(BUILDDIR)/%.o
	@echo " Linking..."
	@echo " $(CC) -o $@ $< $(LIBRARY) $(LINKING)"; 
	$(CC) -o $@ $< $(LIBRARY) $(LINKING)
endif

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)"; 
		$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

lib: $(OBJECTS)
	@echo " Creating shared library..."
	@mkdir -p $(LIBDIR)
	@echo " $(CC) $(LFLAGS) -o $(LIBDIR)/lib$(TARGET).so $^";
		$(CC) $(LFLAGS) -o $(LIBDIR)/lib$(TARGET).so $^

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; 
		$(RM) -r $(BUILDDIR) $(TARGET)
	@echo " $(RM) -r $(LIBDIR)/lib$(TARGET).so"; 
		$(RM) -r $(LIBDIR)/lib$(TARGET).so
