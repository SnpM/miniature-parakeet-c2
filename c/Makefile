IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

SRCDIR=./src
ODIR=./obj
LDIR=./lib
OUTDIR=./bin

LIBS=-lm

_DEPS = client.h  executor.h  main_client.h  main_server.h  networker.h  server.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_LIB_OBJ = client.o  executor.o  networker.o  server.o

_CLIENT_OBJ = main_client.o $(_LIB_OBJ)
CLIENT_OBJ = $(patsubst %,$(ODIR)/%,$(_CLIENT_OBJ))

_SERVER_OBJ = main_server.o $(_LIB_OBJ)
SERVER_OBJ = $(patsubst %,$(ODIR)/%,$(_SERVER_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

default: client server

client: $(CLIENT_OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(CFLAGS) $(LIBS)

server: $(SERVER_OBJ)
	$(CC) -o $(OUTDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(OUTDIR)/*