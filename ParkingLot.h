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
        explicit ParkingLot(unsigned int parkingBlockSizes[]);;
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

            for (UniqueArray<Vehicle, CompareVehicle>::Iterator i = parkingLot.carParkingBlock.begin();
                 i != parkingLot.carParkingBlock.end(); ++i) {
                unsigned int index;
                parkingLot.carParkingBlock.getIndex((*i),index);
                ParkingSpot parkingSpot(CAR,index);
                ParkingLotPrinter::printVehicle(os,CAR,
                                                (*i).getLicensePlate(),(*i).getEntranceTime());
                ParkingLotPrinter::printParkingSpot(os,parkingSpot);

            }

            for (UniqueArray<Vehicle, CompareVehicle>::Iterator i = parkingLot.handicappedParkingBlock.begin();
                 i != parkingLot.handicappedParkingBlock.end(); ++i) {
                unsigned int index;
                parkingLot.handicappedParkingBlock.getIndex((*i),index);
                ParkingSpot parkingSpot(CAR,index);
                ParkingLotPrinter::printVehicle(os,CAR,
                                                (*i).getLicensePlate(),(*i).getEntranceTime());
                ParkingLotPrinter::printParkingSpot(os,parkingSpot);

            }
            return os;
        }


    private:

        ParkingResult enterMotor(LicensePlate &licensePlate, Time &time);

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
