CC = g++
t1 = Trace
t2 = test2
t3 = test1
all:
	$(CC) -c $(t1).cpp
	$(CC) -c $(t2).cpp
	$(CC) -c $(t3).cpp
	$(CC) -o $(t2) $(t2).o $(t1).o 
	$(CC) -o $(t3) $(t3).o
clean:
	rm -f $(t1)
	rm -f $(t2)
	rm -f $(t3)
	rm -f *.o


