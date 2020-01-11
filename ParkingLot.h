#ifndef MTMPARKINGLOT_PARKINGLOT_H
#define MTMPARKINGLOT_PARKINGLOT_H

#include "ParkingLotTypes.h"
#include "Time.h"
#include "ParkingSpot.h"
#include "UniqueArray.h"
#include "Vehicle.h"
#include <cstring>
#include "ParkingLotPrinter.h"


namespace MtmParkingLot {

    using namespace ParkingLotUtils;
    using std::ostream;

    class ParkingLot {
        UniqueArray<Motorbike, CompareVehicle> motorParkingBlock;
        UniqueArray<Car, CompareVehicle> carParkingBlock;
        UniqueArray<Handicapped, CompareVehicle> handicappedParkingBlock;

        class LicensePlateFilter
                : public UniqueArray<Vehicle, CompareVehicle>::Filter {
            LicensePlate licensePlate;
        public:
            const LicensePlate &getLicensePlate() const {
                return licensePlate;
            }

            void setLicensePlate(const LicensePlate &_licensePlate) {
                licensePlate = _licensePlate;
            }


            bool operator()(const Vehicle &element) const override {
                return licensePlate == element.getLicensePlate();
            }
        };

        LicensePlateFilter filter;

    public:

        explicit ParkingLot(unsigned int parkingBlockSizes[]) :
                motorParkingBlock(parkingBlockSizes[MOTORBIKE]),
                carParkingBlock(parkingBlockSizes[CAR]),
                handicappedParkingBlock(parkingBlockSizes[HANDICAPPED]) {};

        ~ParkingLot() = default;


        ParkingResult
        enterParking(VehicleType vehicleType, LicensePlate licensePlate,
                     Time entranceTime) {

            unsigned int index;
            ParkingSpot newSpot;
            switch (vehicleType):

            case MOTORBIKE:

                break;
            case CAR:

                carParkingBlock.insert(Car(licensePlate, entranceTime));
            break;
            case HANDICAPPED:
                handicappedParkingBlock.insert(
                        Handicapped(licensePlate, entranceTime));
            carParkingBlock.insert(Handicapped(licensePlate, entranceTime));
            break;
        }//TODO: read about errors - Parking is full, car already exists
        //TODO: What if License Plate already exists as other vehicle.


        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);

        ParkingResult getParkingSpot(LicensePlate licensePlate,
                                     ParkingSpot &parkingSpot) const;

        void inspectParkingLot(Time inspectionTime);

        friend ostream &operator<<(ostream &os, const ParkingLot &parkingLot);


    private:
        ParkingResult enterMotor(const LicensePlate& licensePlate, Time& time);

    };
    //end of parkingLot class


}





#endif //MTMPARKINGLOT_PARKINGLOT_H
