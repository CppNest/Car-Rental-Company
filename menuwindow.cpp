#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "mainwindow.h"
#include "allreservationswindow.h"

MenuWindow::MenuWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);

    // Connect buttons
    connect(ui->openMainWindowButton, &QPushButton::clicked, this, &MenuWindow::openMainWindow);
    connect(ui->openAllReservationsButton, &QPushButton::clicked, this, &MenuWindow::openAllReservationsWindow);
    connect(ui->closeButton, &QPushButton::clicked, this, &MenuWindow::closeMenu);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::openMainWindow() {
    MainWindow *mainWindow = new MainWindow();
    mainWindow->showFullScreen();
}

void MenuWindow::openAllReservationsWindow() {
    AllReservationsWindow *allReservationsWindow = new AllReservationsWindow();
    allReservationsWindow->showFullScreen();
}

void MenuWindow::closeMenu() {
    this->close();
}
