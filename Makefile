LIB := -lpthread
CCFLAG := -O2
CC := g++

pthread : pthread_demo.o
	$(CC) -o test $< $(LIB)

pthread_demo.o : pthread_demo.cpp
	$(CC) -c $< $(CCFLAG)

const : const.cpp
	$(CC) -o test $<

.PHONY : clean
clean :
	-rm *.o test
