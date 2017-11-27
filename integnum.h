//Numerical Integration Method Program V 1.1.0 / Programa del metodo de Integracion Numerica V 1.1.0
#ifndef INTEGNUM_H
#define INTEGNUM_H

#include <QMainWindow>

namespace Ui {
class IntegNum;
}

class IntegNum : public QMainWindow
{
    Q_OBJECT

public:
    explicit IntegNum(QWidget *parent = 0);
    ~IntegNum();
    // Variables declaration.
    double ainf, bsup, h;// These variables will save the value for lower and higher limits provided by user, and the calculated increment.
    int n, i;// "n" will save the intervals number and "i" is an auxiliar variable for cycles.
    double integral, producto, sumas, error;// These variables will save the found results.
    double puntosfx[100];// This array will save the points provided by the user (100 as maximum).
public slots:
    // Slots declaration.
    void ejecutar();// Slot for run the method.
    void cargar();// Slot for save data from table widget.
    void activarTabla();// Slot for enable and configure the table.
    void activarSpin();// Slot for enable the "points number" spinbox.
    void limpiar();// Slot for clear all user interface fields.
private:
    Ui::IntegNum *ui;
};

#endif // INTEGNUM_H
