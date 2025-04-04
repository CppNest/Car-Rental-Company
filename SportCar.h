#ifndef SPORTCAR_H
#define SPORTCAR_H

#include "Car.h"

class SportCar : public Car
{
public:
    // Constructor
    SportCar(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, float acceleration, int vmax, const QString &photo);

    // Getters
    float getAcceleration() const;
    int getVmax() const;

private:
    // Properties
    float acceleration;
    int vmax;
};

#endif // SPORTCAR_H
