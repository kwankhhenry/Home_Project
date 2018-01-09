#Parameters and Flags
CC	:= g++
CFLAGS := -Wall #-v #-g
SRCDIR := src
BUILDDIR := build
TARGET := main

SRCEXT := cpp
SOURCES := $(shell find -type f -name '*.$(SRCEXT)')
OBJECTS := $(patsubst ./%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
INC := -I/usr/include/mysql -I/usr/include/mysql++
LIB := -L/usr/lib
LNK := -lmysqlpp -lmysqlclient

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) -o $(TARGET) $^ $(LNK)"; 
		$(CC) -o $(TARGET) $^ $(LNK)

$(BUILDDIR)/%.o: ./%.$(SRCEXT)
	@echo " Building..."
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $<"; 
		$(CC) $(CFLAGS) $(INC) $(LIB) -o $@ -c $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; 
		$(RM) -r $(BUILDDIR) $(TARGET)
