testme: testme.c
	gcc -o testme testme.c -coverage -fpic -lm
	./testme
	gcov ./testme -b

all: testme

clean:
	rm testme *.gcda *.gcno
