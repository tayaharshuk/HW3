#ifndef HW3_VEHICLE_H
#define HW3_VEHICLE_H

#include "ParkingLotTypes.h"
#include "Time.h"

using namespace ParkingLotUtils;


class Vehicle {
protected:
    LicensePlate licensePlate;
    Time entranceTime;
    unsigned int numOfTickets;

public:
    unsigned int getNumOfTickets() const {
        return numOfTickets;
    }

    void incrementNumOfTickets() {
        numOfTickets++;
    }

    void checkForTicket(Time& checkTime){
        if((checkTime-entranceTime).toHours() >= 24)
            incrementNumOfTickets();
    }

    virtual int getBill(Time& exitTime) = 0;
};

class Motorbike: public Vehicle{

public:
    int getBill(Time& exitTime) override;
};

class Car: public Vehicle{

public:
    int getBill(Time& exitTime) override;
};

class Handicapped: public Vehicle{

public:
    int getBill(Time& exitTime) override;
};
#endif //HW3_VEHICLE_H
