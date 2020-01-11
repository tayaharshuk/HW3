#ifndef HW3_VEHICLE_H
#define HW3_VEHICLE_H

#include "ParkingLotTypes.h"
#include "Time.h"

using namespace ParkingLotUtils;

namespace MtmParkingLot {
    class Vehicle {
    protected:
        LicensePlate licensePlate;
        Time entranceTime;
        unsigned int numOfTickets;

    public:
        Vehicle(const LicensePlate &licensePlate, const Time &entranceTime)
                : licensePlate(licensePlate), entranceTime(entranceTime),
                  numOfTickets(0) {}

        const LicensePlate &getLicensePlate() const {
            return licensePlate;
        }

        unsigned int getNumOfTickets() const {
            return numOfTickets;
        }

        void incrementNumOfTickets() {
            numOfTickets++;
        }

        void checkForTicket(Time &checkTime) {
            if ((checkTime - entranceTime).toHours() >= 24)
                incrementNumOfTickets();
        }

        virtual int getBill(Time &exitTime) = 0;
    };

//TODO: Taya CompareVehicle
    class CompareVehicle {
    };

    class Motorbike : public Vehicle {

    public:
        Motorbike(const LicensePlate &licensePlate, const Time &entranceTime);

        int getBill(Time &exitTime) override;
    };

    class Car : public Vehicle {

    public:
        Car(const LicensePlate &licensePlate, const Time &entranceTime);

        int getBill(Time &exitTime) override;
    };

    class Handicapped : public Car {

    public:
        Handicapped(const LicensePlate &licensePlate, const Time &entranceTime);

        int getBill(Time &exitTime) override;
    };
}
#endif //HW3_VEHICLE_H
