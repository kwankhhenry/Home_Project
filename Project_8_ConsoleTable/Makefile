#Parameters and Flags
CC	:= g++
CFLAGS := -Wall -fPIC#-std=c++11#-g
LFLAGS := -shared
SRCDIR := src
BUILDDIR := build
LIBDIR := ../lib
TARGET := ConsoleTable

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I /usr/include
LIB := -L /usr/lib
LNK := -l 

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) -o $(TARGET) $^ $(LIB)"; 
		$(CC) -o $(TARGET) $^ $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -o $@ -c $<"; 
		$(CC) $(CFLAGS) $(INC) -o $@ -c $<

lib: $(OBJECTS)
	@echo " Creating shared library..."
	@echo " $(CC) $(LFLAGS) -o $(LIBDIR)/lib$(TARGET).so $^";
		$(CC) $(LFLAGS) -o $(LIBDIR)/lib$(TARGET).so $^

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; 
		$(RM) -r $(BUILDDIR) $(TARGET)
	@echo " $(RM) -r $(LIBDIR)/lib$(TARGET).so"; 
		$(RM) -r $(LIBDIR)/lib$(TARGET).so
