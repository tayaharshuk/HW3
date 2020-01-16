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


        /*class LicensePlateFilter: public UniqueArray<Vehicle, CompareVehicle>::Filter {
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
        */
        class ticketFilter: public UniqueArray<Vehicle,CompareVehicle>::Filter{

            Time inspectionTime;
            bool operator()(const Vehicle &element) const override {
                unsigned int numOfTickets = element.getNumOfTickets();
                Time entranceTime = element.getEntranceTime(); //todo:const
                unsigned int totalHours = (inspectionTime-entranceTime).toHours();
                return ((numOfTickets==0) && (totalHours>24));
            }
        };
        ticketFilter filter;
    public:

        explicit ParkingLot(unsigned int parkingBlockSizes[]) :
                motorParkingBlock(parkingBlockSizes[MOTORBIKE]),
                carParkingBlock(parkingBlockSizes[CAR]),
                handicappedParkingBlock(parkingBlockSizes[HANDICAPPED]) {};

        ~ParkingLot() = default;


        ParkingResult enterParking(VehicleType vehicleType, LicensePlate& licensePlate,
                     Time entranceTime) {

            switch (vehicleType){
                case MOTORBIKE:
                    return enterMotor(licensePlate,entranceTime);

                case CAR:
                    return enterCar(licensePlate,entranceTime);

                case HANDICAPPED:
                    return  enterHandicapped(licensePlate,entranceTime);
            }
        }


        //todo
        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);

        ParkingResult getParkingSpot(LicensePlate licensePlate,
                                     ParkingSpot &parkingSpot) const;



        void inspectParkingLot(Time inspectionTime){};


        friend ostream &operator<<(ostream &os, const ParkingLot &parkingLot);


    private:

        ParkingResult enterMotor( LicensePlate& licensePlate, Time& time);
        ParkingResult enterCar( LicensePlate& licensePlate, Time& time);
        ParkingResult enterHandicapped( LicensePlate& licensePlate,Time& time);
        bool vehicleAlreadyExists(LicensePlate& licensePlate, Time& time, VehicleType& parkingBlockType,
                                  unsigned int& place) const; //todo:const



    };
    //end of parkingLot class








#endif //MTMPARKINGLOT_PARKINGLOT_H
