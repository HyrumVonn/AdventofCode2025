
all: program

program: Day3.o batteryBank.o
	g++ -o program Day3.o batteryBank.o

Day3.o: Day3.cpp batteryBank.hpp
	g++ -c Day3.cpp

batteryBank.o: batteryBank.cpp batteryBank.hpp
	g++ -c batteryBank.cpp

clean:
	rm *.o program