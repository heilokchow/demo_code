LIB := -lpthread
CCFLAG := -O2
TARGETS := test
OBJECTS := pthread_demo.o
CC := g++

$(TARGETS) : $(OBJECTS)
	$(CC) -o $@ $< $(LIB)

pthread_demo.o : pthread_demo.cpp
	$(CC) -c $< $(CCFLAG)

.PHONY : clean
clean :
	-rm $(TARGETS) $(OBJECTS)
