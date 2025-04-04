#include "SportCar.h"

// Constructor
SportCar::SportCar(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, float acceleration, int vmax, const QString &photo)
    : Car(model, type, costPerDay, seats, transmission, photo), acceleration(acceleration), vmax(vmax){}

// Getters
float SportCar::getAcceleration() const { return acceleration; }
int SportCar::getVmax() const { return vmax; }
