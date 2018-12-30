CFLAGS=-std=c11 -pedantic 

tp : app.o biblio.o
	cc $(CFLAGS) -o tp app.o biblio.o

app.o : app.c 
	cc $(CFLAGS) -c app.c

biblio.o : biblio.h biblio.c
	cc $(CFLAGS) -c biblio.c

clean :
	rm *.o
	rm tp