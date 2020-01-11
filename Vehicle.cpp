//
// Created by jonat on 11/01/2020.
//

#include "Vehicle.h"
#include "cassert"


#define MOTOR_PRICE_FIRST 10
#define TICKET 250
//TODO

using namespace MtmParkingLot;

Motorbike::Motorbike(const LicensePlate &licensePlate, const Time &entranceTime)
        : Vehicle(licensePlate, entranceTime) {}

Car::Car(const LicensePlate &licensePlate, const Time &entranceTime) : Vehicle(
        licensePlate, entranceTime) {}

Handicapped::Handicapped(const LicensePlate &licensePlate,
                         const Time &entranceTime) : Car(licensePlate,
                                                             entranceTime) {}

int Motorbike::getBill(Time& exitTime) {
    Time parkingTime = exitTime-entranceTime;
    unsigned int timeInHours = parkingTime.toHours();
    assert(timeInHours>0); //TODO
    if(timeInHours == 1){
        return 10;
    }else if(timeInHours<6){
        return 10+5*(timeInHours-1);
    }else{
        return 10+5*5 + 250*numOfTickets;
    }

    if (timeInHours == 1){
        return 10;
    }
    for(int i = 2 ; i < 6; i++){
        if (timeInHours == i){
            return 10 +(i-1)*5;
        }
    }
    if(timeInHours >=6 && timeInHours <=24){
        return 10+5*5;
    }
    if(timeInHours>24){
        return 250+10+5*5;
    }
    return 0; // in case the car wasn't in the parking lot.

}

int Car::getBill(Time& exitTime) {
    Time parkingTime = exitTime-entranceTime;
    unsigned int timeInHours = parkingTime.toHours();
    if (timeInHours == 1){
        return 20;
    }
    for(int i = 2 ; i < 6; i++){
        if (timeInHours == i){
            return 20 +(i-1)*5;
        }
    }
    if(timeInHours >=6 && timeInHours <=24){
        return 20+5*5;
    }
    if(timeInHours>24){
        return 250+20+5*5;
    }
    return 0; // in case the car wasn't in the parking lot.

}

int Handicapped::getBill(Time& exitTime) {
    Time parkingTime = exitTime-entranceTime;
    unsigned int timeInHours = parkingTime.toHours();
    if (timeInHours<=24){
        return 15;
    }
    return 265;
}
