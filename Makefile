# kompilator c
CCOMP = gcc

# konsolidator
LOADER = gcc

# opcje optymalizacji:
# wersja do debugowania
#OPT = -g -DEBUG 
# wersja zoptymalizowana do mierzenia czasu
OPT = -O3

# pliki naglowkowe
INC = 

# biblioteki
LIB =  -lm -lpthread -lrt

zad2: zad2.o 
	$(LOADER) $(OPT) zad2.o -o zad2 $(LIB)

zad2.o: zad2.c 
	$(CCOMP) -c $(OPT) zad2.c $(INC) 

zad1: zad1.o 
	$(LOADER) $(OPT) zad1.o -o zad1 $(LIB)

zad1.o: zad1.c 
	$(CCOMP) -c $(OPT) zad1.c $(INC)

test: test.o 
	$(LOADER) $(OPT) test.o -o test $(LIB)

test.o: test.c 
	$(CCOMP) -c $(OPT) test.c $(INC)

clean:
	rm -f *.o
