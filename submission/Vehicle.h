#ifndef HW3_VEHICLE_H
#define HW3_VEHICLE_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "cassert"

using namespace ParkingLotUtils;

namespace MtmParkingLot {
    /** Vehicle
     *  A class which contains all the needed information for any vehicle which
     *  exists in the parking lot. Vehicle is a basic class, means that all the three
     *  existing vehicle types are going to be inherited from it.
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

        virtual unsigned int getBill(Time& exitTime) const;

        VehicleType getType() const;
    };


    /** function object class for the uniqeArray. Used to compares two given vehicles
     * by their license plate.
    *
    */
    class CompareVehicle {
      public:
       bool operator()(const MtmParkingLot::Vehicle& vehicle1, const MtmParkingLot::Vehicle& vehicle2) const{
           return vehicle1.getLicensePlate() == vehicle2.getLicensePlate();
       }
    };

    /**
     * Represents motorbike vehicles, inherits from vehicle class. Its getBill function
     * is adjusted to motorbike parking prices
     */
    class Motorbike : public Vehicle {
    public:
        Motorbike(const LicensePlate &licensePlate, const Time &entranceTime);
        Motorbike(const Vehicle& v);
    };

    /**
     * Represents car vehicles, inherits from vehicle class. Its getBill function
     * is adjusted to car parking prices
     */
    class Car : public Vehicle {
    public:
        Car(const LicensePlate &licensePlate, const Time &entranceTime);
        Car(const Vehicle& c);
    };

    /**
     * Represents handicapped vehicles, inherits from car class. Its getBill function
     * is adjusted to handicapped parking prices
     */
    class Handicapped : public Car {
    public:
        Handicapped(const LicensePlate &licensePlate, const Time &entranceTime);
        Handicapped(const Vehicle& v);
        unsigned int getBill(Time &exitTime) const override;
    };
}
#endif //HW3_VEHICLE_H
