CFLAGS = -std=c11 -pedantic -Wvla

all : measures analyzer

measures : measures.c temperature.o
	cc $(CFLAGS) -o measures measures.c temperature.o

analyzer : analyzer.c temperature.o
	cc $(CFLAGS) -o analyzer analyzer.c temperature.o

temperature.o : temperature.c temperature.h
	cc $(CFLAGS) -c temperature.c

clean :
	rm *.o


