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

# === targets ===
default: client server

client: $(OUTDIR)/client
	
server: $(OUTDIR)/server

#=== binary linking ===
# Build % with %.o and library objs
$(OUTDIR)/%: $(OBJDIR)/app/%.o $(LIB_OBJ)
	$(CC) -o $@ -c $^ $(CFLAGS)

#=== compilation ===

# Build entry point(s)
$(OBJDIR)/app/%.o: $(APPDIR)/%.c
	$(CC) -o $@ -c $^ $(CFLAGS)

# Build library objects
$(OBJDIR)/lib/%.o: $(LIBDIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
	

debug:
	: $(MAIN_OBJ)


test: $(TEST_OBJ) 
	$(CC) -o $(OUTDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCDIR)/*~ $(OUTDIR)/*