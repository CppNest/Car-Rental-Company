#ifndef PASSENGERCAR_H
#define PASSENGERCAR_H

#include "Car.h"

class PassengerCar : public Car
{
public:
    // Constructor
    PassengerCar(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, const QString &airConditioning, float fuelConsumption, const QString &photo);

    // Getters
    QString getAirConditioning() const;
    float getFuelConsumption() const;

private:
    // Properties
    QString airConditioning;
    float fuelConsumption;
};

#endif // PASSENGERCAR_H
