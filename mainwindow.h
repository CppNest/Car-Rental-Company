#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Car.h"
#include <QListWidgetItem>
#include <QList>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // UI Elements
    Ui::MainWindow *ui;
    QLabel* noCarsLabel;
    QList<Car*> carDataList;
    QWidget* createCarWidget(Car* car);

    // Functions
    int currentPageIndex;
    int totalPages;
    void closeMainWindow();
    void goToNextPage();
    void goToPreviousPage();
    void searchCars();
    void setupCarPages();
    void openReservationWindow(Car* car);
    void addCarToPage(Car* car,QVBoxLayout* pageLayout);
    void filterCarList(const QList<Car*> &filteredCars);
    QList<Car*> loadCarsFromFile(const QString &fileName);
};

#endif // MAINWINDOW_H
