#include "AllReservationsWindow.h"
#include "ui_AllReservationsWindow.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QMessageBox>
#include <QPushButton>

AllReservationsWindow::AllReservationsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllReservationsWindow)
{
    ui->setupUi(this);

    // Connect button
    connect(ui->closeButton, &QPushButton::clicked, this, &AllReservationsWindow::closeAllReservationsWindow);

    contentLayout = new QVBoxLayout();
    ui->verticalLayout->addLayout(contentLayout);
    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->setContentsMargins(0, 0, 0, 20);
    headerLayout->addWidget(ui->closeButton, 0, Qt::AlignTop | Qt::AlignLeft);
    headerLayout->addStretch(1);
    headerLayout->addWidget(ui->mainLabel, 0, Qt::AlignCenter);
    headerLayout->addStretch(1);

    contentLayout->addLayout(headerLayout);
    contentLayout->addWidget(ui->tableWidget);

    tableWidget = ui->tableWidget;
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setColumnCount(9);
    QStringList headers = { "Numer rezerwacji", "Całkowity koszt", "Liczba dni", "Model pojazdu",
                           "Rodzaj", "Koszt za dzień", "Liczba miejsc", "Skrzynia biegów", "Anuluj" };
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->hideColumn(5);
    tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QFont headerFont = tableWidget->horizontalHeader()->font();
    headerFont.setPointSize(12);
    tableWidget->horizontalHeader()->setFont(headerFont);

    loadReservations("reservations.txt");
}

AllReservationsWindow::~AllReservationsWindow()
{
    delete ui;
}

void AllReservationsWindow::closeAllReservationsWindow() {
    this->close();
}

void AllReservationsWindow::loadReservations(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open reservations file.");
        return;
    }

    QTextStream in(&file);

    if (in.atEnd()) {
        ui->tableWidget->hide();
        ui->mainLabel->hide();

        QLayoutItem *child;
        while ((child = contentLayout->takeAt(0)) != nullptr) {
            delete child;
        }

        QLabel *noReservationsLabel = new QLabel("Nie dodano żadnej rezerwacji", this);
        noReservationsLabel->setObjectName("noReservationsLabel");
        noReservationsLabel->setAlignment(Qt::AlignCenter);
        noReservationsLabel->setFont(QFont("Arial", 42, QFont::Bold));

        QSpacerItem *verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QSpacerItem *verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        contentLayout->addItem(verticalSpacerTop);
        contentLayout->addWidget(noReservationsLabel, 0, Qt::AlignCenter);
        contentLayout->addItem(verticalSpacerBottom);

        noReservationsLabel->show();
        return;
    }

    ui->tableWidget->show();
    ui->mainLabel->show();

    int row = 0;
    QFont cellFont;
    cellFont.setPointSize(12);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");

        if (fields.size() < 8) continue;

        tableWidget->insertRow(row);

        for (int col = 0; col < 8; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(fields[col]);
            item->setTextAlignment(Qt::AlignCenter);
            item->setFont(cellFont);
            tableWidget->setItem(row, col, item);
        }

        QPushButton *deleteButton = new QPushButton("Anuluj");
        deleteButton->setStyleSheet(
            "background-color: #ff3131;"
            "border: none;"
            "border-radius: 5px;"
            "font-size: 14px;"
            "color: white;"
            "padding: 5px;"
            "}"
            "QPushButton:hover {"
            "background-color: #be2222;"
            "}"
            );

        connect(deleteButton, &QPushButton::clicked, this, [=]() { deleteReservation(row, filePath); });
        tableWidget->setCellWidget(row, 8, deleteButton);

        row++;
    }

    file.close();
}

void AllReservationsWindow::deleteReservation(int /* unused */, const QString &reservationsFilePath)
{
    QPushButton *deleteButton = qobject_cast<QPushButton *>(sender());
    if (!deleteButton) {
        qDebug() << "Error: Delete button not identified.";
        return;
    }

    int row = -1;
    for (int i = 0; i < tableWidget->rowCount(); ++i) {
        if (tableWidget->cellWidget(i, 8) == deleteButton) {
            row = i;
            break;
        }
    }

    if (row == -1) {
        qDebug() << "Error: Button row not found.";
        return;
    }

    QString reservationNumber = tableWidget->item(row, 0)->text();
    qDebug() << "Deleting reservation with number:" << reservationNumber;

    QFile reservationsFile(reservationsFilePath);
    if (!reservationsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Cannot open reservations file.");
        return;
    }

    QStringList lines;
    QString lineToAdd;
    QTextStream in(&reservationsFile);

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith(reservationNumber + ";")) {
            QStringList fields = line.split(";");
            if (fields.size() > 3) {
                lineToAdd = fields.mid(3).join(";");
            }
        } else {
            lines.append(line);
        }
    }
    reservationsFile.close();

    if (!lineToAdd.isEmpty()) {
        QFile dataFile("data.txt");
        if (dataFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&dataFile);
            out << lineToAdd << '\n';
            dataFile.close();
        } else {
            QMessageBox::warning(this, "Error", "Cannot open data file for writing.");
        }
    }

    if (!reservationsFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QMessageBox::warning(this, "Error", "Cannot open reservations file for writing.");
        return;
    }
    QTextStream out(&reservationsFile);
    for (const QString &line : lines) {
        out << line << '\n';
    }
    reservationsFile.close();

    tableWidget->removeRow(row);

    if (tableWidget->rowCount() == 0) {
        ui->tableWidget->hide();
        ui->mainLabel->hide();

        QLayoutItem *child;
        while ((child = contentLayout->takeAt(0)) != nullptr) {
            delete child;
        }

        QLabel *noReservationsLabel = findChild<QLabel*>("noReservationsLabel");
        if (!noReservationsLabel) {
            noReservationsLabel = new QLabel("Nie dodano żadnej rezerwacji", this);
            noReservationsLabel->setObjectName("noReservationsLabel");
            noReservationsLabel->setAlignment(Qt::AlignCenter);
            noReservationsLabel->setFont(QFont("Arial", 42, QFont::Bold));
        }

        QSpacerItem *verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QSpacerItem *verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        contentLayout->addItem(verticalSpacerTop);
        contentLayout->addWidget(noReservationsLabel, 0, Qt::AlignCenter);
        contentLayout->addItem(verticalSpacerBottom);

        noReservationsLabel->show();
    }

    QMessageBox::information(this, "Powodzenie", "Poprawnie anulowano rezerwację");
}
