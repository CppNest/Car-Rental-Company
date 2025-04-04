#ifndef RESERVATIONWINDOW_H
#define RESERVATIONWINDOW_H

#include <QWidget>
#include "Car.h"

namespace Ui {
class ReservationWindow;
}

class ReservationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ReservationWindow(QWidget *parent = nullptr);
    ~ReservationWindow();
    void setCarDetails(Car* car); //needed to add it to public

private:
    // UI Elements
    Ui::ReservationWindow *ui;
    Car* currentCar;
    double costPerDay;

    // Functions
    void updateTotalCost();
    void onReserveButtonClicked();
    void validateDaysInput();
    void closeReservationWindow();
};

#endif // RESERVATIONWINDOW_H
