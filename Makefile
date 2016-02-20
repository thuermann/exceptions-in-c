#
# $Id: Makefile,v 1.1 2016/02/20 06:28:28 urs Exp $
#

RM = rm -f

.PHONY: all
all: ex

ex: ex.o except.o
	$(CC)  $(LDFLAGS) -o $@ ex.o except.o

.PHONY: clean
clean:
	$(RM) ex *.o core
