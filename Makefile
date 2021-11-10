CFLAGS = -g3  -Wall 
CC = gcc

PROGRAMS =  main_ecosys ecosys

all: $(PROGRAMS)

main_ecosys: ecosys.o main_ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys: ecosys.o main_ecosys.o
	$(CC) -o $@ $(CFLAGS) $^

main_tests.o: main_tests.c
	gcc -c $(CFLAGS) main_tests.c

main_ecosys.o: main_ecosys.c 
	gcc -c $(CFLAGS) main_ecosys.c

#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)

.PHONY:	all clean