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
        Vehicle(const LicensePlate& licensePlate, const Time& entranceTime) //constructor
                : licensePlate(licensePlate), entranceTime(entranceTime),
                  numOfTickets(0) {}

        const LicensePlate& getLicensePlate() const {
            return licensePlate;
        }

        unsigned int getNumOfTickets() const {
            return numOfTickets;
        }

        void setTicket() {
            numOfTickets = 1;
        }

        void checkForTicket(Time& inspectionTime) {
            if ((inspectionTime - entranceTime).toHours() >= 24)
                setTicket();
        }

        virtual int getBill(Time& exitTime) = 0;
    };


    class CompareVehicle {
      public:
       bool operator() (Vehicle& vehicle1, Vehicle& vehicle2){
           return vehicle1.getLicensePlate() == vehicle2.getLicensePlate();
       }
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
