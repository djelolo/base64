IDIR=./include
SRC=./src
CC=gcc
MKDIR=mkdir -p
CFLAGS=-I$(IDIR)

.DEFAULT_GOAL := all

ODIR=./obj

_DEPS = base64.h utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = base64.o utils.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: directories base64

base64: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

.PHONY: directories

directories:
	$(MKDIR) $(ODIR)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rmdir $(ODIR)

cleanall: clean
	rm base64

run:
	./base64 -e
