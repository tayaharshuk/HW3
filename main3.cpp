//
// Created by Jonathan Joseph on 11/01/2020.
//
#include "ParkingLot.h"
#include <cassert>

using namespace MtmParkingLot;

//Create parkingLot + enterParking + exitParking
void test1(){
    unsigned int sizes[] = {1,1,1};
    Time time(0,0,0);
    ParkingLot parkingLot(sizes);
    parkingLot.inspectParkingLot(time);

    assert(parkingLot.enterParking(CAR,"car1",time) == SUCCESS);
    assert(parkingLot.enterParking(CAR,"car1",time) == NO_EMPTY_SPOT);
    assert(parkingLot.enterParking(MOTORBIKE,"car1",time) == VEHICLE_ALREADY_PARKED);
    assert(parkingLot.enterParking(MOTORBIKE,"bike1",time) == SUCCESS);
    assert(parkingLot.enterParking(MOTORBIKE,"bike1",time) == NO_EMPTY_SPOT);

    time+=60;

    assert(parkingLot.enterParking(CAR,"bike1",time) == NO_EMPTY_SPOT);
    assert(parkingLot.enterParking(HANDICAPPED,"bike1",time) == VEHICLE_ALREADY_PARKED);
    assert(parkingLot.enterParking(HANDICAPPED,"car1",time) == VEHICLE_ALREADY_PARKED);
    assert(parkingLot.enterParking(HANDICAPPED,"handicapped1",time) == SUCCESS);

    ParkingLot parkingLot2(sizes);

    assert(parkingLot2.enterParking(HANDICAPPED, "handicapped1",time)==SUCCESS);
    assert(parkingLot2.enterParking(HANDICAPPED, "handicapped1",time)==VEHICLE_ALREADY_PARKED);
    assert(parkingLot2.enterParking(HANDICAPPED, "handicapped2",time)==SUCCESS);
    assert(parkingLot2.enterParking(HANDICAPPED, "handicapped2",time)==NO_EMPTY_SPOT);
    assert(parkingLot2.enterParking(MOTORBIKE, "handicapped2",time)==VEHICLE_ALREADY_PARKED);
    assert(parkingLot2.enterParking(CAR, "handicapped2",time)==NO_EMPTY_SPOT);

    time += 120;

    assert(parkingLot2.enterParking(CAR,"car1",time) == NO_EMPTY_SPOT);
    assert(parkingLot2.enterParking(HANDICAPPED,"handicapped3",time) == NO_EMPTY_SPOT);
    assert(parkingLot2.enterParking(MOTORBIKE,"motor1",time) == SUCCESS);
    assert(parkingLot2.enterParking(MOTORBIKE,"motor1",time) == NO_EMPTY_SPOT);

    //exitParkingLot
    assert(parkingLot.exitParking("car1",time) == SUCCESS);
    assert(parkingLot.exitParking("car1",time) == VEHICLE_NOT_FOUND);
    time+=24*60;
    assert(parkingLot.exitParking("motor1",time) == SUCCESS);
    assert(parkingLot.exitParking("motor1",time) == VEHICLE_NOT_FOUND);
    assert(parkingLot.exitParking("justPlayingWithYou...",time) == VEHICLE_NOT_FOUND);
    assert(parkingLot.enterParking(HANDICAPPED,"handicapped2",time) == SUCCESS);
    assert(parkingLot.exitParking("handicapped2",time) == SUCCESS);
    assert(parkingLot.exitParking("handicapped1",time) == SUCCESS);
}








int main(){

}

