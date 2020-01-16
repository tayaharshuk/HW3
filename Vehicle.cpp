//
// Created by jonat on 11/01/2020.
//

#include "Vehicle.h"

#define MOTOR_PRICE_FIRST 10
#define MOTOR_PRICE 5
#define CAR_PRICE_FIRST 20
#define CAR_PRICE 10
#define HANDICAPPED_PRICE 15
#define TICKET 250
#define MAX_HOURS_TO_PAY 6
//TODO

using namespace MtmParkingLot;

//C'tors
Motorbike::Motorbike(const LicensePlate &licensePlate, const Time &entranceTime)
        : Vehicle(licensePlate, entranceTime,MOTOR_PRICE_FIRST,MOTOR_PRICE) {}

Car::Car(const LicensePlate &licensePlate, const Time &entranceTime)
        : Vehicle(licensePlate, entranceTime,CAR_PRICE_FIRST,CAR_PRICE) {}

Handicapped::Handicapped(const LicensePlate &licensePlate,const Time &entranceTime)
             : Car(licensePlate, entranceTime) {}

/** getBill
 * return the bill of the vehicle based on times and ticket
 * Handicapped vehicle will override this function *
 * @param exitTime
 * @return
 */
unsigned int Vehicle::getBill(Time &exitTime) {
    unsigned int timeInHours = (exitTime-entranceTime).toHours();
    if(timeInHours == 0){
        return 0;
    }
    else if(timeInHours == 1){
        return priceForFirstHour;
    }else if(timeInHours<MAX_HOURS_TO_PAY){
        return priceForFirstHour+priceForHour*(timeInHours-1);
    }else{
        return priceForFirstHour+priceForHour*(MAX_HOURS_TO_PAY-1) + TICKET*numOfTickets;
    }
}

const LicensePlate &Vehicle::getLicensePlate() const {
    return licensePlate;
}

unsigned int Vehicle::getNumOfTickets() const {
    return numOfTickets;
}

void Vehicle::setTicket() {
    numOfTickets = 1;
}

void Vehicle::checkForTicket(Time &inspectionTime) {
    if ((inspectionTime - entranceTime).toHours() >= 24) //todo: >= or > ?
        setTicket();
}

const Time &Vehicle::getEntranceTime() {
    return entranceTime;
}


//Override getBill for handicapped
unsigned int Handicapped::getBill(Time &exitTime) {
    return HANDICAPPED_PRICE + TICKET*numOfTickets;
}
