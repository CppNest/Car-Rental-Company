#include "PassengerCar.h"

// Constructor
PassengerCar::PassengerCar(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, const QString &airConditioning, float fuelConsumption, const QString &photo)
    : Car(model, type, costPerDay, seats, transmission, photo), airConditioning(airConditioning), fuelConsumption(fuelConsumption){}

// Getters
QString PassengerCar::getAirConditioning() const { return airConditioning; }
float PassengerCar::getFuelConsumption() const { return fuelConsumption; }
