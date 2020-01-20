#defines
CC =  g++
DNDEBUG_FLAG = -DNDEBUG
LINKER_FLAGS= -L. -lm -lmtm
EXEC = MtmParkingLot
ADT = UniqueArray
COMP_FLAGS = -std=c++11 -Wall -Werror -pedantic-errors -g
PARK_O_FILES = MtmParkingLot.o ParkingLot.o ParkingLotPrinter.o \
ParkingSpot.o Time.o Vehicle.o UniqueArray.o
UNIQUE_O_FILES = UniqueArrayTest.o

$(EXEC): $(PARK_O_FILES)
	$(CC) $(PARK_O_FILES) -o $@

$(ADT): $(UNIQUE_O_FILES)
	$(CC) $(UNIQUE_O_FILES) -o $@

MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h \
 ParkingLotPrinter.h ParkingSpot.h ParkingLot.h UniqueArray.h \
 UniqueArrayExceptions.h UniqueArrayImp.h Vehicle.h
	$(CC) -c $(COMP_FLAGS) $*.cpp

ParkingLot.o: ParkingLot.cpp ParkingLot.h ParkingLotTypes.h Time.h \
 ParkingSpot.h UniqueArray.h UniqueArrayExceptions.h UniqueArrayImp.h \
 Vehicle.h ParkingLotPrinter.h
	$(CC) -c $(COMP_FLAGS) $*.cpp

ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h Time.h \
 ParkingSpot.h ParkingLotTypes.h
	$(CC) -c $(COMP_FLAGS) $*.cpp

ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h
	$(CC) -c $(COMP_FLAGS) $*.cpp

Time.o: Time.cpp Time.h
	$(CC) -c $(COMP_FLAGS) $*.cpp

Vehicle.o: Vehicle.cpp Vehicle.h ParkingLotTypes.h Time.h
	$(CC) -c $(COMP_FLAGS) $*.cpp

UniqueArrayTest.o: tests/UniqueArrayTest.cpp UniqueArray.h UniqueArrayExceptions.h UniqueArrayImp.h
	$(CC) -c $(COMP_FLAGS) tests/UniqueArrayTest.cpp
	
UniqueArray.o: UniqueArray.cpp UniqueArray.h UniqueArrayExceptions.h UniqueArrayImp.h
	$(CC) -c $(COMP_FLAGS) UniqueArray.cpp
	
clean:
	rm -f $(PARK_O_FILES) $(EXEC)
	rm -f $(UNIQUE_O_FILES) $(ADT)
	
run_tests:
	valgrind --leak-check=full ./$(EXEC)<tests/input1.txt>tests/output_test1.txt
	valgrind --leak-check=full ./$(EXEC)<tests/input2.txt>tests/output_test2.txt
	valgrind --leak-check=full ./$(EXEC)<tests/input3.txt>tests/output_test3.txt