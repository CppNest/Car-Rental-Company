#ifndef TRUCKCAR_H
#define TRUCKCAR_H

#include "Car.h"

class TruckCar : public Car
{
public:
    // Constructor
    TruckCar(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, int capacity, int cargoSpace, const QString &photo);

    // Getters
    int getCapacity() const;
    int getCargoSpace() const;

private:
    // Properties
    int capacity;
    int cargoSpace;
};

#endif // TRUCKCAR_H
