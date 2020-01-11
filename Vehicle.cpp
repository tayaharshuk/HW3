//
// Created by jonat on 11/01/2020.
//

#include "Vehicle.h"

int Motorbike::getBill(Time& exitTime) {
    return (exitTime-entranceTime)*15;
}

int Car::getBill(Time& exitTime) {
    return (exitTime-entranceTime)*20;
}

int Handicapped::getBill(Time& exitTime) {
    return (exitTime-entranceTime)*15;
}
