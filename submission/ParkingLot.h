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
        UniqueArray<Vehicle, CompareVehicle> motorParkingBlock;
        UniqueArray<Vehicle, CompareVehicle> carParkingBlock;
        UniqueArray<Vehicle, CompareVehicle> handicappedParkingBlock;

    public:
        explicit ParkingLot(unsigned int parkingBlockSizes[]);
        ~ParkingLot() = default;


        ParkingResult enterParking(VehicleType vehicleType,
                LicensePlate &licensePlate, Time entranceTime);


        ParkingResult exitParking(LicensePlate licensePlate, Time exitTime);

        ParkingResult getParkingSpot(LicensePlate licensePlate,
                                     ParkingSpot &parkingSpot) const;

        void inspectParkingLot(Time inspectionTime);

        friend ostream &operator<<(ostream &os, const ParkingLot &parkingLot){
        ParkingLotPrinter::printParkingLotTitle(std::cout);


        for (UniqueArray<Vehicle, CompareVehicle>::Iterator i = parkingLot.motorParkingBlock.begin();
            i != parkingLot.motorParkingBlock.end(); ++i) {
            unsigned int index;
            parkingLot.motorParkingBlock.getIndex((*i),index);
            ParkingSpot parkingSpot(MOTORBIKE,index);
            ParkingLotPrinter::printVehicle(os,MOTORBIKE,
                    (*i).getLicensePlate(),(*i).getEntranceTime());
            ParkingLotPrinter::printParkingSpot(os,parkingSpot);
        }

        for (UniqueArray<Vehicle, CompareVehicle>::Iterator i = parkingLot.handicappedParkingBlock.begin();
             i != parkingLot.handicappedParkingBlock.end(); ++i) {
            unsigned int index;
            parkingLot.handicappedParkingBlock.getIndex((*i),index);
            ParkingSpot parkingSpot(HANDICAPPED,index);
            ParkingLotPrinter::printVehicle(os,HANDICAPPED,
                                            (*i).getLicensePlate(),(*i).getEntranceTime());
            ParkingLotPrinter::printParkingSpot(os,parkingSpot);

        }

        for (UniqueArray<Vehicle, CompareVehicle>::Iterator i = parkingLot.carParkingBlock.begin();
             i != parkingLot.carParkingBlock.end(); ++i) {
            unsigned int index;
            parkingLot.carParkingBlock.getIndex((*i),index);
            ParkingSpot parkingSpot(CAR,index);
            ParkingLotPrinter::printVehicle(os,(*i).getType(),
                                            (*i).getLicensePlate(),(*i).getEntranceTime());
            ParkingLotPrinter::printParkingSpot(os,parkingSpot);
        }

        return os;
    }


    private:
        /**checks for an empty place and if there is- enters the motorbike into its own
         * parking block.
         *
         * @param licensePlate
         * @param time
         * @return parking result
         * NO_EMPTY_SPOT- if there is not any place to park the motorbike.
         * SUCCESS - if the motorbike was parked successfully.
         *
         */
        ParkingResult enterMotor(LicensePlate &licensePlate, Time &time);
        /**
         *checks for an empty place and if there is- enters the car into its own
         * parking block.
         * @param licensePlate
         * @param time
         * @return
         * NO_EMPTY_SPOT- if there is not any place to park the car.
         * SUCCESS - if the car was parked successfully.
         */
        ParkingResult enterCar(LicensePlate &licensePlate, Time &time);

        /**checks for an empty place and if there is- enters the handicapped into its own
         * parking block.
         *
         * @param licensePlate
         * @param time
         * @return
         * NO_EMPTY_SPOT- if there is not any place to park the handicapped.(checks
         * for the car parking block too)
         * SUCCESS - if the handicapped was parked successfully.
         */
        ParkingResult enterHandicapped(LicensePlate &licensePlate, Time &time);

        /**
         * checks if the vehicle exists in the parking lot.(doesn't matter in which block)
         * @param licensePlate
         * @param parkingSpot
         * @return
         * true - if the vehicle exists
         * false - if the vehicle does not exist in the parking lot
         */
        bool vehicleAlreadyExists(LicensePlate &licensePlate,
                                  ParkingSpot* parkingSpot) const;
        /**
         * searches for a specific vehicle in the parking lot by its license
         * @param parkingSpot
         * @param licensePlate
         * @return a pointer to the wanted vehicle
         *
         */
        const Vehicle* getVehicle(const ParkingSpot& parkingSpot,
                                      const LicensePlate& licensePlate) const ;
    };
    //end of parkingLot class


    /** ticketFilter
     * function object that derives from UniqueArray filter
     * the class will help get only the vehicles that need to be tickets.
     */
    class ticketFilter :
            public UniqueArray<Vehicle, CompareVehicle>::Filter {

        Time inspectionTime;
    public:
        explicit ticketFilter(const Time &inspectionTime);

        bool operator()(const Vehicle &element) const override;
    };

}

#endif //MTMPARKINGLOT_PARKINGLOT_H
