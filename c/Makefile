SRCDIR=./src
LIBDIR=$(SRCDIR)/lib
APPDIR=$(SRCDIR)/app
INCDIR=./include
OBJDIR=./obj
OUTDIR=./bin
TESTDIR=./tests

CC=gcc
CFLAGS=-I$(INCDIR)

# core library files
LIB_SOURCES := $(wildcard $(LIBDIR)/*.c)
LIB_OBJ := $(patsubst $(LIBDIR)/%.c, $(OBJDIR)/lib/%.o, $(LIB_SOURCES))

# entry point files
MAIN_SOURCES := $(wildcard $(APPDIR)/*.c)
MAIN_OBJ := $(patsubst $(APPDIR)/%.c,$(OBJDIR)/app/%.o,$(MAIN_SOURCES))

# test files
TEST_SOURCES := $(wildcard $(TESTDIR)/*.c)
TEST_OBJ:= $(patsubst $(TESTDIR)/%.c, $(OBJDIR)/tests/%.o,$(TEST_SOURCES))

# === targets ===
default: client server

client: $(OUTDIR)/main_client
	
server: $(OUTDIR)/main_server

#=== binary linking ===
# Build % with %.o and library objs
$(OUTDIR)/%: $(OBJDIR)/app/%.o $(LIB_OBJ)
	mkdir -p $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

#=== compilation ===

# Build entry point(s)
$(OBJDIR)/app/%.o: $(APPDIR)/%.c
	mkdir -p $(OBJDIR)/app
	$(CC) -o $@ -c $^ $(CFLAGS)

# Build library objects
$(OBJDIR)/lib/%.o: $(LIBDIR)/%.c
	mkdir -p $(OBJDIR)/lib
	$(CC) -c $< -o $@ $(CFLAGS)

# Build test objects
$(OBJDIR)/tests/%.o: $(TESTDIR)/%.c
	mkdir -p $(OBJDIR)/tests
	$(CC) -c $< -o $@ $(CFLAGS)
	
debug:
	: $(MAIN_OBJ) -- $(LIB_OBJ)


test: $(TEST_OBJ) $(LIB_OBJ)
	mkdir -p $(OUTDIR)
	$(CC) -o $(OUTDIR)/run_tests $^ $(CFLAGS) 

.PHONY: clean

clean:
	rm -rf $(OBJDIR) $(OUTDIR)