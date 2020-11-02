IDIR=./include
SRC=./src
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj

_DEPS = base64.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = base64.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRC)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


base64: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 


run:
	base64
