#ifndef ALLRESERVATIONSWINDOW_H
#define ALLRESERVATIONSWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>

namespace Ui {
class AllReservationsWindow;
}

class AllReservationsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AllReservationsWindow(QWidget *parent = nullptr);
    ~AllReservationsWindow();

private:
    // UI Elements
    Ui::AllReservationsWindow *ui;
    QVBoxLayout *contentLayout;
    QTableWidget *tableWidget;

    // Functions
    void loadReservations(const QString &filePath);
    void closeAllReservationsWindow();
    void deleteReservation(int row, const QString &filePath);
};

#endif // ALLRESERVATIONSWINDOW_H
