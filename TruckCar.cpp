#include "TruckCar.h"

// Constructor
TruckCar::TruckCar(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, int capacity, int cargoSpace, const QString &photo)
    : Car(model, type, costPerDay, seats, transmission, photo), capacity(capacity), cargoSpace(cargoSpace){}

// Getters
int TruckCar::getCapacity() const { return capacity; }
int TruckCar::getCargoSpace() const { return cargoSpace; }
