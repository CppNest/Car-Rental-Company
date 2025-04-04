#include "reservationwindow.h"
#include "ui_reservationwindow.h"
#include <QPixmap>
#include <QLabel>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QIntValidator>
#include <mainwindow.h>
#include <QTimer>

ReservationWindow::ReservationWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ReservationWindow)
    , currentCar(nullptr)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->reserveButton, &QPushButton::clicked, this, &ReservationWindow::onReserveButtonClicked);
    connect(ui->daysInput, &QLineEdit::textChanged, this, &ReservationWindow::updateTotalCost);
    connect(ui->closeButton, &QPushButton::clicked, this, &ReservationWindow::closeReservationWindow);

    this->showMaximized();
    validateDaysInput();

    // Alignment
    ui->verticalLayout_2->setAlignment(ui->reserveButton, Qt::AlignCenter);
    ui->horizontalLayout_4->setAlignment(ui->modelLabel, Qt::AlignCenter);
}

ReservationWindow::~ReservationWindow()
{
    delete ui;
}

void ReservationWindow::closeReservationWindow() {
    MainWindow *mainWindow = new MainWindow();
    mainWindow->showFullScreen();
    QTimer::singleShot(0, this, &ReservationWindow::close);
}

void ReservationWindow::setCarDetails(Car* car) {
    if (!car) return;
    currentCar = car;
    QPixmap photo(car->getPhoto());

    if (!photo.isNull()) {
        photo = photo.scaled(ui->photoLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->photoLabel->setPixmap(photo);
        ui->photoLabel->setFixedSize(photo.size());
        ui->photoLabel->setScaledContents(true);
    } else {
        qDebug() << "Failed to load image at path:" << car->getPhoto();
    }

    onReserveButtonClicked();
    ui->modelLabel->setText(car->getModel());
    costPerDay = car->getCostPerDay();
    ui->costPerDayLabel->setText(QString::number(car->getCostPerDay()) + " zł / dzień");
    connect(ui->daysInput, &QLineEdit::textChanged, this, &ReservationWindow::validateDaysInput);
}

void ReservationWindow::updateTotalCost() {
    bool ok;
    int days = ui->daysInput->text().toInt(&ok);

    if (ok) {
        if (days <= 0) {
            ui->totalCostLabel->setText("Błędna liczba dni");
        } else if (days > 500) {
            ui->totalCostLabel->setText("Za duża liczba dni");
        } else {
            double totalCost = days * costPerDay;
            ui->totalCostLabel->setText(QString::number(totalCost) + " zł");
        }
    } else {
        ui->totalCostLabel->setText("Błędna liczba dni");
    }
}

void ReservationWindow::validateDaysInput() {
    bool isInt;
    int days = ui->daysInput->text().toInt(&isInt);
    if (isInt && days > 0 && days <= 500) {
        ui->reserveButton->setEnabled(true);
    } else {
        ui->reserveButton->setEnabled(false);
    }
}

void ReservationWindow::onReserveButtonClicked() {
    if (!currentCar) {
        qDebug() << "currentCar jest pusty!";
        return;
    }

    QString model = currentCar->getModel();
    QFile dataFile("data.txt");
    QFile reservationFile("reservations.txt");

    if (!dataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Nie udało się otworzyć pliku data.txt do odczytu.";
        return;
    }

    QStringList lines;
    QTextStream in(&dataFile);
    bool found = false;
    QString lineToMove;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.contains(model) && !found) {
            lineToMove = line;
            found = true;
        } else {
            lines.append(line);
        }
    }
    dataFile.close();

    if (!found) {
        qDebug() << "Nie znaleziono samochodu o modelu:" << model << "w pliku data.txt.";
        return;
    }

    QString reservationNumber = QString::number(QRandomGenerator::global()->bounded(100000000000, 999999999999));

    bool ok;
    int reservationDays = ui->daysInput->text().toInt(&ok);
    if (!ok || reservationDays < 0) {
        qDebug() << "Błędna liczba dni wprowadzona.";
        ui->totalCostLabel->setText("Błędna liczba dni");
        return;
    }

    double reservationCost = reservationDays * costPerDay;

    if (!reservationFile.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Nie udało się otworzyć pliku reservations.txt do zapisu.";
        return;
    }

    QTextStream outReservation(&reservationFile);
    outReservation << reservationNumber << ";"
                   << QString::number(reservationCost, 'f', 2) << ";"
                   << QString::number(reservationDays) << ";"
                   << lineToMove << "\n";
    reservationFile.close();

    if (!dataFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Nie udało się otworzyć pliku data.txt do zapisu.";
        return;
    }

    QTextStream outData(&dataFile);
    for (const QString &line : qAsConst(lines)) {
        outData << line << "\n";
    }
    dataFile.close();

    QMessageBox::information(this, "Numer Rezerwacji", "Rezerwacja została zapisana!\nTwój numer rezerwacji:\n" + reservationNumber);

    this->close();
}

