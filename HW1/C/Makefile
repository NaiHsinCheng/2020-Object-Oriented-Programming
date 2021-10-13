CC = gcc
t1 = stack
t2 = main
t3 = main2
all:
	$(CC) -c $(t1).c
	$(CC) -c $(t2).c
	$(CC) -c $(t3).c
	$(CC) -o $(t2) $(t2).o $(t1).o 
	$(CC) -o $(t3) $(t3).o $(t1).o 
clean:
	rm -f $(t1)
	rm -f $(t2)
	rm -f $(t3)
	rm -f *.o


