#include "ParkingLot.h"

using namespace MtmParkingLot;

//Parking Lot Class
//C'tor
ParkingLot::ParkingLot(unsigned int *parkingBlockSizes) :
        motorParkingBlock(parkingBlockSizes[MOTORBIKE]),
        carParkingBlock(parkingBlockSizes[CAR]),
        handicappedParkingBlock(parkingBlockSizes[HANDICAPPED]) {}

ParkingResult ParkingLot::enterParking(VehicleType vehicleType,
        LicensePlate &licensePlate, Time entranceTime) {
    Time time;
    ParkingSpot parkingSpot;

    if(vehicleAlreadyExists(licensePlate,&parkingSpot)){

        ParkingLotPrinter::printVehicle(std::cout,
                parkingSpot.getParkingBlock(), licensePlate,
                getVehicle(parkingSpot,licensePlate)->getEntranceTime());
        ParkingLotPrinter::printEntryFailureAlreadyParked(std::cout,
                                                          parkingSpot);
        return VEHICLE_ALREADY_PARKED;
    }

    switch (vehicleType){
        case MOTORBIKE:
            return enterMotor(licensePlate,entranceTime);

        case CAR:
            return enterCar(licensePlate,entranceTime);

        default:
            return enterHandicapped(licensePlate,entranceTime);
    }
}

ParkingResult ParkingLot::exitParking(LicensePlate licensePlate, Time exitTime){
    ParkingSpot parkingSpot;

    if(!vehicleAlreadyExists(licensePlate, &parkingSpot)){
        ParkingLotPrinter::printExitFailure(std::cout,licensePlate);
        return VEHICLE_NOT_FOUND;
    }

    const Vehicle* vehicle = getVehicle(parkingSpot ,licensePlate);
    Vehicle* copy;

    ParkingLotPrinter::printVehicle(std::cout,parkingSpot.getParkingBlock(),
                                    licensePlate,vehicle->getEntranceTime());

    switch (vehicle->getType()){
        case MOTORBIKE:
            copy = new Motorbike(*vehicle);
            break;
        case CAR:
            copy = new Car(*vehicle);
            break;
        default:
            copy = new Handicapped(*vehicle);
            break;
    }


    ParkingLotPrinter::printExitSuccess(std::cout,parkingSpot,exitTime,
                                        copy->getBill(exitTime));

    delete copy;

    switch (parkingSpot.getParkingBlock()){
        case MOTORBIKE:
            motorParkingBlock.remove(*vehicle);
            break;
        case CAR:
            carParkingBlock.remove(*vehicle);
            break;
        case HANDICAPPED:
            handicappedParkingBlock.remove(*vehicle);
            break;
    }

    return SUCCESS;
}


ParkingResult ParkingLot::getParkingSpot(LicensePlate licensePlate,
                                         ParkingSpot &parkingSpot) const {
    if (!vehicleAlreadyExists(licensePlate, &parkingSpot))
        return VEHICLE_NOT_FOUND;

    return SUCCESS;
}

void ParkingLot::inspectParkingLot(Time inspectionTime) {
    ticketFilter filter(inspectionTime);
    int counter = 0;

     for (UniqueArray<Vehicle, CompareVehicle>::Iterator i = motorParkingBlock.begin();
        i!= motorParkingBlock.end(); ++i) {
         if (filter(*i)) {
             (*i).setTicket();
             counter++;
         }
     }
     for(UniqueArray<Vehicle,CompareVehicle>::Iterator j = carParkingBlock.begin();
        j!= carParkingBlock.end();++j) {
         if (filter(*j)) {
             (*j).setTicket();
             counter++;
         }
     }
      for (UniqueArray <Vehicle,CompareVehicle>::Iterator k = handicappedParkingBlock.begin();
           k!= handicappedParkingBlock.end(); ++k) {
          if (filter(*k)) {
              (*k).setTicket();
              counter++;
          }
      }
      ParkingLotPrinter::printInspectionResult(std::cout,inspectionTime,counter);
     }



bool ticketFilter::operator()(const Vehicle &element) const {
    unsigned int numOfTickets = element.getNumOfTickets();
    Time entranceTime = element.getEntranceTime();
    unsigned int totalHours = (inspectionTime-entranceTime).toHours();
    return ((numOfTickets==0) && (totalHours>24));
}

ticketFilter::ticketFilter(const Time &inspectionTime) : inspectionTime(
        inspectionTime) {}


// === Private Functions ===
ParkingResult MtmParkingLot::ParkingLot::enterMotor(LicensePlate &licensePlate,
                                                    Time &time) {
    unsigned int place;
    try {
        place = motorParkingBlock.insert(Motorbike(licensePlate, time));
    }
    catch (UniqueArray<Vehicle,CompareVehicle>
            ::UniqueArrayIsFullException& e){
        ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE,
                licensePlate, time);
        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
        return NO_EMPTY_SPOT;
    }
    ParkingSpot parkingSpot(MOTORBIKE, place);
    ParkingLotPrinter::printVehicle(std::cout, MOTORBIKE,
            licensePlate, time);
    ParkingLotPrinter::printEntrySuccess(std::cout, parkingSpot);
    return SUCCESS;
}

ParkingResult ParkingLot::enterCar( LicensePlate &licensePlate, Time &time) {
    unsigned int place;

    try {
        place = carParkingBlock.insert(Car(licensePlate,time));
    }
    catch(UniqueArray<Vehicle,CompareVehicle>::UniqueArrayIsFullException& e){
        ParkingLotPrinter::printVehicle(std::cout,CAR,licensePlate,time);
        ParkingLotPrinter::printEntryFailureNoSpot(std::cout);
        return NO_EMPTY_SPOT;
    }
    ParkingSpot parkingSpot(CAR,place);
    ParkingLotPrinter::printVehicle(std::cout,CAR,licensePlate,time);
    ParkingLotPrinter::printEntrySuccess(std::cout,parkingSpot); //TODO: why is it undeclard?
    return SUCCESS;
}

ParkingResult ParkingLot::enterHandicapped( LicensePlate &licensePlate,
                                            Time &time) {
    unsigned int place;
    VehicleType parkingBlock;
    try {
        place = handicappedParkingBlock.insert(Handicapped(licensePlate,time));
        parkingBlock = HANDICAPPED;
    }
    catch(UniqueArray<Vehicle,CompareVehicle>::UniqueArrayIsFullException& e){
        try {
            place = carParkingBlock.insert(Handicapped(licensePlate,time));
            parkingBlock = CAR;
        }
        catch (UniqueArray<Vehicle,CompareVehicle>::UniqueArrayIsFullException& e){//todo: Handicapped or car
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
bool ParkingLot::vehicleAlreadyExists(LicensePlate& licensePlate,
                                      ParkingSpot* parkingSpot) const{
    unsigned int index;
    Time time;

    if (motorParkingBlock.getIndex(Motorbike(licensePlate, Time()),index)){
        *parkingSpot = ParkingSpot(MOTORBIKE, index);
        return true;
    }
    else if (carParkingBlock.getIndex(Car(licensePlate,Time()),index)){
        *parkingSpot = ParkingSpot(CAR, index);
        return true;
    }
    else if (handicappedParkingBlock.getIndex(Handicapped(licensePlate,Time()),index)){
        *parkingSpot = ParkingSpot(HANDICAPPED, index);
        return true;
    }
    return false;
}


const Vehicle* ParkingLot::getVehicle(const ParkingSpot& parkingSpot,
                                      const LicensePlate& licensePlate) const{
    switch (parkingSpot.getParkingBlock()){
        case MOTORBIKE:
            return motorParkingBlock[Motorbike(licensePlate,Time())];
        case CAR:
            return carParkingBlock[Car(licensePlate,Time())];
        case HANDICAPPED:
            return handicappedParkingBlock[Handicapped(licensePlate,Time())];
    }
    return nullptr;
}
//Filter class
