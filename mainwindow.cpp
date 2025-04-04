#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SportCar.h"
#include "TruckCar.h"
#include "PassengerCar.h"
#include "ElectricCar.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QPixmap>
#include <QIcon>
#include <QScroller>
#include <QVBoxLayout>
#include <reservationwindow.h>
#include <QScrollBar>
#include <QtGlobal>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->nextButton, &QPushButton::clicked, this, &MainWindow::goToNextPage);
    connect(ui->prevButton, &QPushButton::clicked, this, &MainWindow::goToPreviousPage);
    connect(ui->searchButton, &QPushButton::clicked, this, &MainWindow::searchCars);
    connect(ui->closeButton, &QPushButton::clicked, this, &MainWindow::closeMainWindow);

    noCarsLabel = new QLabel("Brak pojazdów o podanych kryteriach", this);
    noCarsLabel->setAlignment(Qt::AlignCenter);
    noCarsLabel->setStyleSheet("font-size: 24px; color: white;");
    noCarsLabel->setVisible(false);
    noCarsLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->verticalLayout->addWidget(noCarsLabel);

    carDataList = loadCarsFromFile("data.txt");
    setupCarPages();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeMainWindow() {
    this->close();
}

void MainWindow::openReservationWindow(Car* car) {
    ReservationWindow* reservationWindow = new ReservationWindow();
    reservationWindow->setCarDetails(car);
    reservationWindow->showFullScreen();
    this->close();
}

QList<Car*> MainWindow::loadCarsFromFile(const QString &fileName) {
    QList<Car*> cars;
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file.");
        return cars;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.size() >= 8) {
            QString model = fields[0];
            QString type = fields[1];
            int costPerDay = fields[2].toInt();
            int seats = fields[3].toInt();
            QString transmission = fields[4];
            QString photo = fields[7];

            if (type == "Sportowy") {
                float acceleration = fields[5].toFloat();
                int vmax = fields[6].toInt();
                cars.append(new SportCar(model, type, costPerDay, seats, transmission, acceleration, vmax, photo));
            } else if (type == "Przewozowy") {
                int loadCapacity = fields[5].toInt();
                int cargoSpace = fields[6].toInt();
                cars.append(new TruckCar(model, type, costPerDay, seats, transmission, loadCapacity,cargoSpace, photo));
            } else if (type == "Osobowy") {
                QString airConditioning = fields[5];
                float fuelConsumption = fields[6].toFloat();
                cars.append(new PassengerCar(model, type, costPerDay, seats, transmission, airConditioning, fuelConsumption, photo));
            } else if (type == "Elektryczny") {
                int range = fields[5].toInt();
                float chargingTime = fields[6].toFloat();
                cars.append(new ElectricCar(model, type, costPerDay, seats, transmission, range, chargingTime, photo));
            }
        }
    }
    file.close();
    return cars;
}

void MainWindow::setupCarPages() {
    while (ui->carPages->count() > 0) {
        QWidget* widget = ui->carPages->widget(0);
        ui->carPages->removeWidget(widget);
        delete widget;
    }

    int itemsPerPage = 2;
    totalPages = (carDataList.size() + itemsPerPage - 1) / itemsPerPage;

    for (int pageIndex = 0; pageIndex < totalPages; ++pageIndex) {
        QWidget* page = new QWidget;
        QVBoxLayout* pageLayout = new QVBoxLayout(page);

        for (int i = pageIndex * itemsPerPage; i < (pageIndex + 1) * itemsPerPage && i < carDataList.size(); ++i) {
            QWidget* carWidget = createCarWidget(carDataList[i]);
            pageLayout->addWidget(carWidget);
        }

        ui->carPages->addWidget(page);
    }

    currentPageIndex = 0;
    ui->carPages->setCurrentIndex(currentPageIndex);

    if (carDataList.isEmpty()) {
        noCarsLabel->setVisible(true);
        ui->carPages->setVisible(false);
        ui->nextButton->setVisible(false);
        ui->prevButton->setVisible(false);
    } else {
        noCarsLabel->setVisible(false);
        ui->carPages->setVisible(true);
        ui->nextButton->setVisible(true);
        ui->prevButton->setVisible(true);
    }
}

void MainWindow::goToNextPage() {
    int currentIndex = ui->carPages->currentIndex();
    int totalPages = ui->carPages->count();
    if (currentIndex == totalPages - 1) {
        ui->carPages->setCurrentIndex(0);
    } else {
        ui->carPages->setCurrentIndex(currentIndex + 1);
    }
}

void MainWindow::goToPreviousPage() {
    int currentIndex = ui->carPages->currentIndex();
    int totalPages = ui->carPages->count();
    if (currentIndex == 0) {
        ui->carPages->setCurrentIndex(totalPages - 1);
    } else {
        ui->carPages->setCurrentIndex(currentIndex - 1);
    }
}

void MainWindow::addCarToPage(Car* car, QVBoxLayout* pageLayout) {
    QWidget* carWidget = createCarWidget(car);
    pageLayout->addWidget(carWidget);
}

QWidget* MainWindow::createCarWidget(Car* car) {
    const QString &carName = car->getModel();
    const QString &carType = car->getType();
    const QString &costPerDay = QString::number(car->getCostPerDay());
    const QString &seats = QString::number(car->getSeats());
    const QString &transmission = car->getTransmission();
    const QString &photoPath = car->getPhoto();

    QWidget *carWidget = new QWidget(this);
    carWidget->setFixedHeight(260);
    QHBoxLayout *mainLayout = new QHBoxLayout(carWidget);

    // Photo
    QLabel *photoLabel = new QLabel;
    QPixmap photo(photoPath);
    if (!photo.isNull()) {
        photoLabel->setPixmap(photo.scaled(400, 250, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        photoLabel->setFixedSize(400,250);
    } else {
        photoLabel->setText("Brak zdjęcia");
        photoLabel->setFixedSize(400, 250);
    }
    photoLabel->setStyleSheet("border: 5px solid white; border-radius: 10px;");
    mainLayout->addWidget(photoLabel);

    // Right side layout
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->setContentsMargins(50,0,0,0);

    // Model label
    QLabel *modelLabel = new QLabel("<b style='font-size: 40px; color: white;'>" + carName + "</b>");
    rightLayout->addWidget(modelLabel);

    // Columns and button layout
    QHBoxLayout *columnsAndButtonLayout = new QHBoxLayout;
    columnsAndButtonLayout->setContentsMargins(0,0,30,40);

    QVBoxLayout *leftColumn = new QVBoxLayout;
    QVBoxLayout *rightColumn = new QVBoxLayout;

    // Type, costPerDay and seats labels
    QStringList types = { carType, costPerDay + " zł / dzień", seats };
    QStringList icons = { "./icons/type.png", "./icons/costPerDay.png", "./icons/seats.png" };

    for (int i = 0; i < types.size(); ++i) {
        QLabel *combinedLabel = new QLabel(this);
        QString text = "<img src='" + icons[i] + "' width='24' height='24' style='vertical-align:middle;'/> " + types[i];
        combinedLabel->setText(text);
        combinedLabel->setStyleSheet("color: white; font-size: 18px;");
        leftColumn->addWidget(combinedLabel);
    }

    // Transmission label
    QLabel *transmissionLabel = new QLabel(this);
    QString transmissionText = "<img src='./icons/transmission.png' width='24' height='24' style='vertical-align:middle;'/> " + transmission;
    transmissionLabel->setText(transmissionText);
    transmissionLabel->setStyleSheet("color: white; font-size: 18px;");
    rightColumn->addWidget(transmissionLabel);

    // Specific details for different car types
    if (PassengerCar* passengerCar = dynamic_cast<PassengerCar*>(car)) {
        QLabel *acLabel = new QLabel(this);
        QString acText = "<img src='./icons/airConditioning.png' width='24' height='24' style='vertical-align:middle;'/> " + passengerCar->getAirConditioning();
        acLabel->setText(acText);
        acLabel->setStyleSheet("color: white; font-size: 18px;");
        rightColumn->addWidget(acLabel);

        QLabel *fuelLabel = new QLabel(this);
        QString fuelText = "<img src='./icons/fuelConsumption.png' width='24' height='24' style='vertical-align:middle;'/> "
                           + QString::number(passengerCar->getFuelConsumption()) + " L / 100km";
        fuelLabel->setText(fuelText);
        fuelLabel->setStyleSheet("color: white; font-size: 18px;");
        rightColumn->addWidget(fuelLabel);
    } else if (SportCar* sportCar = dynamic_cast<SportCar*>(car)) {
        QLabel *accelerationLabel = new QLabel(this);
        QString accelerationText = "<img src='./icons/acceleration.png' width='24' height='24' style='vertical-align:middle;'/> "
                                   + QString::number(sportCar->getAcceleration()) + " s do 100 km/h";
        accelerationLabel->setText(accelerationText);
        accelerationLabel->setStyleSheet("color: white; font-size: 18px;");
        rightColumn->addWidget(accelerationLabel);

        QLabel *vmaxLabel = new QLabel(this);
        QString vmaxText = "<img src='./icons/vmax.png' width='24' height='24' style='vertical-align:middle;'/> "
                           + QString::number(sportCar->getVmax()) + " km/h";
        vmaxLabel->setText(vmaxText);
        vmaxLabel->setStyleSheet("color: white; font-size: 18px;");
        rightColumn->addWidget(vmaxLabel);
    } else if (TruckCar* truckCar = dynamic_cast<TruckCar*>(car)) {
        QLabel *capacityLabel = new QLabel(this);
        QString capacityText = "<img src='./icons/capacity.png' width='24' height='24' style='vertical-align:middle;'/> "
                               + QString::number(truckCar->getCapacity()) + " kg";
        capacityLabel->setText(capacityText);
        capacityLabel->setStyleSheet("color: white; font-size: 18px;");
        rightColumn->addWidget(capacityLabel);

        QLabel *cargoSpaceLabel = new QLabel(this);
        QString cargoSpaceText = "<img src='./icons/cargoSpace.png' width='24' height='24' style='vertical-align:middle;'/> "
                                 + QString::number(truckCar->getCargoSpace()) + " m³";
        cargoSpaceLabel->setText(cargoSpaceText);
        cargoSpaceLabel->setStyleSheet("color: white; font-size: 18px;");
        rightColumn->addWidget(cargoSpaceLabel);
    } else if (ElectricCar* electricCar = dynamic_cast<ElectricCar*>(car)) {
        QLabel *rangeLabel = new QLabel(this);
        QString rangeText = "<img src='./icons/range.png' width='24' height='24' style='vertical-align:middle;'/> "
                            + QString::number(electricCar->getRange()) + " km";
        rangeLabel->setText(rangeText);
        rangeLabel->setStyleSheet("color: white; font-size: 18px;");
        rightColumn->addWidget(rangeLabel);

        QLabel *chargingTimeLabel = new QLabel(this);
        QString chargingTimeText = "<img src='./icons/chargingTime.png' width='24' height='24' style='vertical-align:middle;'/> "
                                   + QString::number(electricCar->getChargingTime()) + " h";
        chargingTimeLabel->setText(chargingTimeText);
        chargingTimeLabel->setStyleSheet("color: white; font-size: 18px;");
        rightColumn->addWidget(chargingTimeLabel);
    }

    columnsAndButtonLayout->addLayout(leftColumn);
    columnsAndButtonLayout->addLayout(rightColumn);

    // Reserve button
    QPushButton *reserveButton = new QPushButton("Rezerwuj");
    reserveButton->setFixedSize(200, 80);
    reserveButton->setStyleSheet("QPushButton {"
                                 "    background-color: #007FFF;"
                                 "    border: none;"
                                 "    border-radius: 10px;"
                                 "    color: white;"
                                 "    font-size: 16px;"
                                 "} QPushButton:hover {"
                                 "    background-color: #004c9e;"
                                 "}");
    connect(reserveButton, &QPushButton::clicked, this, [this, car]() {
        openReservationWindow(car);
    });

    columnsAndButtonLayout->addWidget(reserveButton);

    rightLayout->addLayout(columnsAndButtonLayout);

    mainLayout->addLayout(rightLayout);

    return carWidget;
}

void MainWindow::filterCarList(const QList<Car*>& filteredCars) {
    while (ui->carPages->count() > 0) {
        QWidget* widget = ui->carPages->widget(0);
        ui->carPages->removeWidget(widget);
        delete widget;
    }

    if (filteredCars.isEmpty()) {
        noCarsLabel->setVisible(true);
        ui->carPages->setVisible(false);
        ui->nextButton->setVisible(false);
        ui->prevButton->setVisible(false);
    } else {
        noCarsLabel->setVisible(false);
        ui->carPages->setVisible(true);
        ui->nextButton->setVisible(true);
        ui->prevButton->setVisible(true);

        int itemsPerPage = 2;
        int totalPages = (filteredCars.size() + itemsPerPage - 1) / itemsPerPage;

        for (int pageIndex = 0; pageIndex < totalPages; ++pageIndex) {
            QWidget* page = new QWidget;
            QVBoxLayout* pageLayout = new QVBoxLayout(page);

            // Add cars to the page
            for (int i = pageIndex * itemsPerPage; i < (pageIndex + 1) * itemsPerPage && i < filteredCars.size(); ++i) {
                QWidget* carWidget = createCarWidget(filteredCars[i]);
                pageLayout->addWidget(carWidget);
            }

            ui->carPages->addWidget(page);
        }
    }
}

void MainWindow::searchCars() {
    QString searchText = ui->carNameSearch->text();
    QString selectedType = ui->typeComboBox->currentText();
    QString selectedSeats = ui->seatsComboBox->currentText();
    QString selectedSortOrder = ui->priceSortComboBox->currentText();

    QList<Car*> filteredCars;

    for (Car* car : carDataList) {
        bool matchesName = car->getModel().contains(searchText, Qt::CaseInsensitive);
        bool matchesType = (selectedType == "Wszystkie" || car->getType().startsWith(selectedType.left(6), Qt::CaseInsensitive));
        bool matchesSeats = (selectedSeats == "Wszystkie" || (selectedSeats == "8+" && car->getSeats() >= 8) || QString::number(car->getSeats()) == selectedSeats);
        if (matchesName && matchesType && matchesSeats) {
            filteredCars.append(car);
        }
    }

    std::sort(filteredCars.begin(), filteredCars.end(), [selectedSortOrder](Car* a, Car* b) {
        return selectedSortOrder == "Od najniższej" ? a->getCostPerDay() < b->getCostPerDay() : a->getCostPerDay() > b->getCostPerDay();
    });

    filterCarList(filteredCars);
}

