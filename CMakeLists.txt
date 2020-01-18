cmake_minimum_required(VERSION 3.15)
project(HW3)

set(CMAKE_CXX_STANDARD 11)

add_executable(HW3_UA UniqueArray.h UniqueArrayImp.h UniqueArrayExceptions.h main2.cpp)
add_executable(HW3 UniqueArray.h UniqueArrayImp.h UniqueArrayExceptions.h
        ParkingSpot.h ParkingLot.h Time.h MtmParkingLot.cpp ParkingLotPrinter.cpp
        ParkingLotPrinter.h ParkingLotTypes.h ParkingSpot.cpp Time.cpp Vehicle.cpp
        Vehicle.h ParkingLot.cpp)