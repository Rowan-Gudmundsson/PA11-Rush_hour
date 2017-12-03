all: Timer Rush driver
	g++ -o driver driver.o Rush.o Timer.o

Timer: Timer.cpp Timer.h
	g++ -c Timer.cpp

Rush: Rush.cpp Rush.h
	g++ -c Rush.cpp

driver: driver.cpp
	g++ -c driver.cpp

clean:
	rm *.o
