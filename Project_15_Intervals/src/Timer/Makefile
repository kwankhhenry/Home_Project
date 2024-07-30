#Parameters and Flags
CC	:= g++-13
CFLAGS := -std=c++20 -Wall -g -fno-elide-constructors
LFLAGS := -shared

# Directory Paths
SRCDIR := src
BUILDDIR := build
LIBDIR := /home/admin/Home_Project/lib

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%, $(BUILDDIR)/%, $(SOURCES:.$(SRCEXT)=.o))

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

lib: $(OBJECTS)
	@echo " Creating shared library..."
	@mkdir -p $(LIBDIR)
		$(CC) $(LFLAGS) -o $(LIBDIR)/lib$(TARGET).so $^

clean:
	@echo " Cleaning...";
		$(RM) -r $(BUILDDIR) $(TARGET)
		$(RM) -r $(LIBDIR)/lib$(TARGET).so
