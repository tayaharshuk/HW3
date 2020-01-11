#include "ParkingLot.h"

using namespace MtmParkingLot;

ParkingResult MtmParkingLot::ParkingLot::enterMotor(const LicensePlate &licensePlate,
        Time &time) {
    unsigned int place;
    if (motorParkingBlock.getIndex(Motorbike(licensePlate, Time()),
                                   place)) {
        ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE, licensePlate,
                                        time);
        ParkingSpot parkingSpot(MOTORBIKE, place);
        ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                          parkingSpot);
        return VEHICLE_ALREADY_PARKED;
    }
    try {
        place = motorParkingBlock.insert(Motorbike(licensePlate, time));
    }
    catch (UniqueArray<Motorbike,CompareVehicle>::UniqueArrayIsFullException& e) {
        ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE, licensePlate,
                                        time);
        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
        return NO_EMPTY_SPOT;
    }
    ParkingSpot parkingSpot(MOTORBIKE, place);
    ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE, licensePlate, time);
    ParkingLotPrinter::printEntrySuccess(std::cout, parkingSpot);
}
