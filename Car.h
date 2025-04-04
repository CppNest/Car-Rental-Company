#ifndef CAR_H
#define CAR_H

#include <QString>

class Car
{
public:
    // Constructor
    Car(const QString &model, const QString &type, int costPerDay, int seats, const QString &transmission, const QString &photo);

    // Getters
    QString getModel() const;
    QString getType() const;
    int getCostPerDay() const;
    int getSeats() const;
    QString getTransmission() const;
    QString getPhoto() const;

    virtual ~Car() = default;

protected:
    // Properties
    QString model;
    QString type;
    int costPerDay;
    int seats;
    QString transmission;
    QString photo;
};

#endif // CAR_H
