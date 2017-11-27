// Runge - Kutta Method Program V 1.0.0 / Metodo de Runge - Kutta V 1.0.0
#ifndef RUNTTA_H
#define RUNTTA_H

#include <QMainWindow>

namespace Ui {
class Runtta;
}

class Runtta : public QMainWindow
{
    Q_OBJECT

public:
    explicit Runtta(QWidget *parent = 0);
    ~Runtta();
    // Variables decalration
    double xinf, xsup, h;// These variables will save the lower and higher limits, and the increment provided by the user.
    int i,j,intervalos;// Auxiliar variables for cycles (i and j). The last variable will save the calculated intervals number.
    double x(double f);// This function will return the differential equation.
    double y(double g);// This function will return the integrated equation.
public slots:
    // Slots declaration
    void activara();// Slot for activate increment spinbox.
    void activarb();// Slot for activate the Start button.
    void ejecutar();// Slot for run the method.
    void limpiar();// Slot for clear all user interface fileds.

private:
    Ui::Runtta *ui;
};

#endif // RUNTTA_H
