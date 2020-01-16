#include "ParkingLot.h"

using namespace MtmParkingLot;

ParkingResult MtmParkingLot::ParkingLot::enterMotor(LicensePlate &licensePlate,
        Time &time) {
    unsigned int place;
    VehicleType parkingBlockType;
    if (vehicleAlreadyExists(licensePlate,time,parkingBlockType,place)){

        ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE, licensePlate,
                                        time);
        ParkingSpot parkingSpot(parkingBlockType,place);
        ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                          parkingSpot);
        return VEHICLE_ALREADY_PARKED;
    }

    try {
        place = motorParkingBlock.insert(Motorbike(licensePlate, time));
    }
    catch (UniqueArray<Motorbike,CompareVehicle>::UniqueArrayIsFullException& e) { //todo: what about full memory exceptions
        ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE, licensePlate,
                                        time);
        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
        return NO_EMPTY_SPOT;
    }
    ParkingSpot parkingSpot(MOTORBIKE, place);
    ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE, licensePlate, time);
    ParkingLotPrinter::printEntrySuccess(std::cout, parkingSpot);
    return SUCCESS;
}

ParkingResult ParkingLot::enterCar( LicensePlate &licensePlate, Time &time) {
    unsigned int place;
    VehicleType parkingBlockType;
    if (vehicleAlreadyExists(licensePlate,time,parkingBlockType,place){
        ParkingLotPrinter::printVehicle(std::cout, CAR, licensePlate,
                                        time);
        ParkingSpot parkingSpot(parkingBlockType,place);
        ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,parkingSpot);
        return VEHICLE_ALREADY_PARKED;
    }
    try {
        place = carParkingBlock.insert(Car(licensePlate,time));
    }
    catch(UniqueArray<Car,CompareVehicle>::UniqueArrayIsFullException& e){
        ParkingLotPrinter::printVehicle(std::cout,CAR,licensePlate,time);
        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
        return NO_EMPTY_SPOT;
    }
    ParkingSpot parkingSpot(CAR,place);
    ParkingLotPrinter::printVehicle(std::cout,CAR,licensePlate,time);
    ParkingLotPrinter::printEntrySuccess(std::cout,parkingSpot); //TODO: why is it undeclard?
    return SUCCESS;
}


ParkingResult
ParkingLot::enterHandicapped( LicensePlate &licensePlate, Time &time) {
    unsigned int place;
    VehicleType parkingBlockType;
    if (vehicleAlreadyExists(licensePlate,time,parkingBlockType,place)){

        ParkingLotPrinter::printVehicle(std::cout, HANDICAPPED, licensePlate,
                                        time);
        ParkingSpot parkingSpot(parkingBlockType,place);
        ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                          parkingSpot);
        return VEHICLE_ALREADY_PARKED;
    }
    VehicleType parkingBlock;
    try {
        place = handicappedParkingBlock.insert(Handicapped(licensePlate,time));
        parkingBlock = HANDICAPPED;
    }
    catch(UniqueArray<Handicapped,CompareVehicle>::UniqueArrayIsFullException& e){
        try {
            place = carParkingBlock.insert(Handicapped(licensePlate,time));
            parkingBlock = CAR;
        }
        catch (UniqueArray<Handicapped,CompareVehicle>::UniqueArrayIsFullException& e){//todo: Handicapped or car
            ParkingLotPrinter::printVehicle(std::cout,HANDICAPPED,licensePlate,time);
            ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
            return NO_EMPTY_SPOT;
        }
    }
    ParkingSpot parkingSpot(parkingBlock,place);
    ParkingLotPrinter::printVehicle(std::cout,HANDICAPPED,licensePlate,time);
    ParkingLotPrinter::printEntrySuccess(std::cout,parkingSpot);
    return SUCCESS;
}

/*checks if the vehicle already exists at any parking block besides it is own, by
checking its license plate
*/
bool ParkingLot::vehicleAlreadyExists(LicensePlate& licensePlate, Time &time,
                                      VehicleType &parkingBlockType,
                                      unsigned int &place) const{

    if (motorParkingBlock.getIndex(Motorbike(licensePlate, Time()),
                                   place)){
        parkingBlockType = MOTORBIKE;
        return true;
    }
    if (carParkingBlock.getIndex(Car(licensePlate,Time()),place)){
        parkingBlockType = CAR;
        return true;
    }
    else if (handicappedParkingBlock.getIndex(Handicapped(licensePlate,Time()),place)){
        parkingBlockType = HANDICAPPED;
        return true;
    }
    return false;
}

ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime) {
    unsigned int place;
    VehicleType parkingBlockType;
    Time entranceTime;

    /* entrance time doesn't matter in order to check id the vehicle exists.
    because the compare vehicle func uses the license plate to compare*/

    if(vehicleAlreadyExists(licensePlate,entranceTime,parkingBlockType,place)){
        switch (parkingBlockType){
            case MOTORBIKE:{
                const Motorbike* motor = motorParkingBlock[Motorbike(licensePlate,entranceTime)];
                motorParkingBlock.remove(*motor);

            }
            case CAR:{
                const Car* car = carParkingBlock[Car(licensePlate,entranceTime)];
                carParkingBlock.remove(*car);
            }

            case HANDICAPPED:{
                const Handicapped* handicapped = handicappedParkingBlock[Handicapped(licensePlate,entranceTime)];
                handicappedParkingBlock.remove(*handicapped);
            }
        }
        ParkingLotPrinter::printVehicle(std::cout,parkingBlockType,licensePlate,)
        ParkingLotPrinter::printExitSuccess();
        return SUCCESS;
    }
    ParkingLotPrinter::printExitFailure(std::cout,licensePlate);
    return VEHICLE_NOT_FOUND;
}

ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate,
                                         ParkingSpot &parkingSpot) const {
    Time time;
    VehicleType parkingBlock;
    unsigned place;
    if(vehicleAlreadyExists(licensePlate,time,parkingBlock,place)){
        parkingSpot(parkingBlock,place); //todo
        return SUCCESS;
    }
    return VEHICLE_NOT_FOUND;
}
