CFLAGS = -std=c11 -pedantic -Wvla

all : erot13 derot13 epolybe depolybe

erot13 : encrypt.c rot13.o
	cc $(CFLAGS) -o erot13 encrypt.c rot13.o

derot13 : decrypt.c rot13.o
	cc $(CFLAGS) -o derot13 decrypt.c rot13.o

epolybe : encrypt.c polybe.o
	cc $(CFLAGS) -o epolybe encrypt.c polybe.o

depolybe : decrypt.c polybe.o
	cc $(CFLAGS) -o depolybe decrypt.c polybe.o

rot13.o : rot13.c crypt.h
	cc $(CFLAGS) -c rot13.c

polybe.o : polybe.c crypt.h
	cc $(CFLAGS) -c polybe.c