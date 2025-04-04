#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QWidget>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private:
    // UI Elements
    Ui::MenuWindow *ui;

    // Functions
    void openMainWindow();
    void openAllReservationsWindow();
    void closeMenu();
};

#endif // MENUWINDOW_H
