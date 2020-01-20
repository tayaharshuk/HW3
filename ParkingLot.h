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

        //ParkingLotPrinter::printVehicle();

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
        /**
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
         * enters the car to its own parking block.
         * @param licensePlate
         * @param time
         * @return
         * NO_EMPTY_SPOT- if there is not any place to park the car.
         * SUCCESS - if the car was parked successfully.
         */
        ParkingResult enterCar(LicensePlate &licensePlate, Time &time);

        ParkingResult enterHandicapped(LicensePlate &licensePlate, Time &time);

        bool vehicleAlreadyExists(LicensePlate &licensePlate,
                                  ParkingSpot* parkingSpot) const; //todo:const

        const Vehicle* getVehicle(const ParkingSpot& parkingSpot,
                                      const LicensePlate& licensePlate) const ;
    };
    //end of parkingLot class

    class ticketFilter :
            public UniqueArray<Vehicle, CompareVehicle>::Filter {

        Time inspectionTime;
    public:
        explicit ticketFilter(const Time &inspectionTime);

        bool operator()(const Vehicle &element) const override;
    };



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
}

#endif //MTMPARKINGLOT_PARKINGLOT_H
