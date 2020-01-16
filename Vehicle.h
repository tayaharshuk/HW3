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
        //TODO: the reason it is marked is because we need to convert it into a string?
    protected:
        LicensePlate licensePlate;
        Time entranceTime;
        unsigned int numOfTickets;
        unsigned int priceForFirstHour;
        unsigned int priceForHour;

    public:
        Vehicle(const LicensePlate& licensePlate, const Time& entranceTime,
                unsigned int priceForFirstHour, unsigned int priceForHour);

        const LicensePlate& getLicensePlate() const;

        const Time& getEntranceTime() const;

        unsigned int getNumOfTickets() const;

        void setTicket();

        void checkForTicket(Time& inspectionTime);

        virtual unsigned int getBill(Time& exitTime) const;
    };



    class CompareVehicle {
      public:
       bool operator() (const MtmParkingLot::Vehicle& vehicle1, const MtmParkingLot::Vehicle& vehicle2){
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
        unsigned int getBill(Time &exitTime);
    };
}
#endif //HW3_VEHICLE_H
