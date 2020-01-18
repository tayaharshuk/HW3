#defines
CC =  g++11
DEBUG_FLAG = 
COMP_FLAG =
LINKER_FLAGS -L. -lm -lmtm




MtmParkingLot.o: MtmParkingLot.cpp ParkingLotTypes.h Time.h \
 ParkingLotPrinter.h ParkingSpot.h ParkingLot.h UniqueArray.h \
 UniqueArrayExceptions.h UniqueArrayImp.h Vehicle.h
$(CC)

OurUATests.o: OurUATests.cpp UniqueArray.h UniqueArrayExceptions.h \???
 UniqueArrayImp.h

ParkingLot.o: ParkingLot.cpp ParkingLot.h ParkingLotTypes.h Time.h \
 ParkingSpot.h UniqueArray.h UniqueArrayExceptions.h UniqueArrayImp.h \
 Vehicle.h ParkingLotPrinter.h

ParkingLotPrinter.o: ParkingLotPrinter.cpp ParkingLotPrinter.h Time.h \
 ParkingSpot.h ParkingLotTypes.h

ParkingSpot.o: ParkingSpot.cpp ParkingSpot.h ParkingLotTypes.h

Time.o: Time.cpp Time.h

Vehicle.o: Vehicle.cpp Vehicle.h ParkingLotTypes.h Time.h
