#ifndef ELECTRICCAR_H
#define ELECTRICCAR_H

#include "Car.h"

class ElectricCar : public Car
{
public:
    // Constructor
    ElectricCar(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, int range, float chargingTime, const QString &photo);

    // Getters
    int getRange() const;
    float getChargingTime() const;

private:
    // Properties
    int range;
    float chargingTime;
};

#endif // ELECTRICCAR_H
