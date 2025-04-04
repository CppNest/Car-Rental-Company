#include "ElectricCar.h"

// Constructor
ElectricCar::ElectricCar(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, int range, float chargingTime, const QString &photo)
    : Car(model, type, costPerDay, seats, transmission, photo), range(range), chargingTime(chargingTime){}

// Getters
int ElectricCar::getRange() const { return range; }
float ElectricCar::getChargingTime() const { return chargingTime; }
