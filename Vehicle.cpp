//
// Created by jonat on 11/01/2020.
//

#include "Vehicle.h"

using namespace MtmParkingLot;

Motorbike::Motorbike(const LicensePlate &licensePlate, const Time &entranceTime)
        : Vehicle(licensePlate, entranceTime) {}

Car::Car(const LicensePlate &licensePlate, const Time &entranceTime) : Vehicle(
        licensePlate, entranceTime) {}

Handicapped::Handicapped(const LicensePlate &licensePlate,
                         const Time &entranceTime) : Car(licensePlate,
                                                             entranceTime) {}

int Motorbike::getBill(Time& exitTime) {
    return (exitTime-entranceTime)*15;
}

int Car::getBill(Time& exitTime) {
    return (exitTime-entranceTime)*20;
}

int Handicapped::getBill(Time& exitTime) {
    return (exitTime-entranceTime)*15;
}
