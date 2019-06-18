make: exe
	./exe
exe: driver.o list.o
	gcc -o exe list.o driver.o
list.o: list.c list.h
	gcc -c list.c
driver.o: driver.c list.h
	gcc -c driver.c
clean:
	rm *.o exe
