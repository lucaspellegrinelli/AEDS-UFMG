
CC := g++
SRCDIR := src
BUILDDIR := build
TESTDIR := test
TARGET := bin/game

TESTER := third_party/tester.cpp

CFLAGS := -g -Wall -O3 -std=c++11
INC := -I include/ -I third_party/

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TSTSOURCES := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
TSTOBJECTS := $(filter-out build/main.o, $(OBJECTS))

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(dir $@)
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

tests: $(TSTOBJECTS)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INC) $(TESTER) $(TSTSOURCES) $^ -o bin/tester
	./bin/tester

clean:
	@echo "Removendo build/";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
	@echo " $(RM) -r bin/tester"; $(RM) -r $(BUILDDIR) bin/tester

.PHONY: clean
