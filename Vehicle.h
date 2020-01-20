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
        VehicleType type;

    public:
        Vehicle(const LicensePlate& licensePlate, const Time& entranceTime,
                unsigned int priceForFirstHour, unsigned int priceForHour, VehicleType type);

        virtual ~Vehicle() = default;

        const LicensePlate& getLicensePlate() const;

        const Time& getEntranceTime() const;

        unsigned int getNumOfTickets() const;

        void setTicket();

        void checkForTicket(Time& inspectionTime);

        virtual unsigned int getBill(Time& exitTime) const;

        VehicleType getType() const;
    };



    class CompareVehicle {
      public:
       bool operator()(const MtmParkingLot::Vehicle& vehicle1, const MtmParkingLot::Vehicle& vehicle2) const{
           return vehicle1.getLicensePlate() == vehicle2.getLicensePlate();
       }
    };

    class Motorbike : public Vehicle {
    public:
        Motorbike(const LicensePlate &licensePlate, const Time &entranceTime);
        Motorbike(const Vehicle& v);
    };

    class Car : public Vehicle {
    public:
        Car(const LicensePlate &licensePlate, const Time &entranceTime);
        Car(const Vehicle& c);
    };

    class Handicapped : public Car {
    public:
        Handicapped(const LicensePlate &licensePlate, const Time &entranceTime);
        Handicapped(const Vehicle& v);
        unsigned int getBill(Time &exitTime) const override;
    };
}
#endif //HW3_VEHICLE_H
