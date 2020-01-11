#ifndef HW3_VEHICLE_H
#define HW3_VEHICLE_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "cassert"

using namespace ParkingLotUtils;

namespace MtmParkingLot {

    /** Vehicle
     *
     */
    class Vehicle {
    protected:
        LicensePlate licensePlate;
        Time entranceTime;
        unsigned int numOfTickets;
        unsigned int priceForFirstHour;
        unsigned int priceForHour;

    public:
        Vehicle(const LicensePlate& licensePlate, const Time& entranceTime,
                unsigned int priceForFirstHour, unsigned int priceForHour) //constructor
                : licensePlate(licensePlate), entranceTime(entranceTime),
                  numOfTickets(0), priceForFirstHour(priceForFirstHour),
                  priceForHour(priceForHour) {}

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

        virtual unsigned int getBill(Time& exitTime);;
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
    };

    class Car : public Vehicle {
    public:
        Car(const LicensePlate &licensePlate, const Time &entranceTime);
    };

    class Handicapped : public Car {
    public:
        Handicapped(const LicensePlate &licensePlate, const Time &entranceTime);
        unsigned int getBill(Time &exitTime) override;
    };
}
#endif //HW3_VEHICLE_H
