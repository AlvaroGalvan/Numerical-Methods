// Euler's Method Program V 1.0.0 / Programa del Metodo de Euler V 1.0.0
#ifndef MEULER_H
#define MEULER_H

#include <QMainWindow>

namespace Ui {
class MEuler;
}

class MEuler : public QMainWindow
{
    Q_OBJECT

public:
    explicit MEuler(QWidget *parent = 0);
    ~MEuler();
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
    Ui::MEuler *ui;
};

#endif // MEULER_H
