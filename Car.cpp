#include "Car.h"

// Constructor
Car::Car(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, const QString &photo)
    : model(model), type(type), costPerDay(costPerDay), seats(seats), transmission(transmission), photo(photo){}

// Getters
QString Car::getModel() const { return model; }
QString Car::getType() const { return type; }
int Car::getCostPerDay() const { return costPerDay; }
int Car::getSeats() const { return seats; }
QString Car::getTransmission() const { return transmission; }
QString Car::getPhoto() const { return "./cars/"+photo; }
