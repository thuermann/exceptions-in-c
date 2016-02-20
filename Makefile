#
# $Id: Makefile,v 1.2 2016/02/20 06:28:58 urs Exp $
#

RM = rm -f

.PHONY: all
all: example

example: example.o except.o
	$(CC)  $(LDFLAGS) -o $@ example.o except.o

.PHONY: clean
clean:
	$(RM) example *.o core
