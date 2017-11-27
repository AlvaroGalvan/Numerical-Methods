// Lagrange's Interpolation Method Program V 1.1.0 // Programa del método de interpolación de Lagrange V 1.1.0
#ifndef ILAGRANGE_H
#define ILAGRANGE_H

#include <QMainWindow>

namespace Ui {
class ILagrange;
}

class ILagrange : public QMainWindow
{
    Q_OBJECT

public:
    explicit ILagrange(QWidget *parent = 0);
    ~ILagrange();
    // Variables declaration
    double puntox[5], puntoy[5];// These arrays will save the points provided by the user.
    double fx[5];// This array will save the found points for each polinomy grade.
    int i,j,k,npuntos;// i,j & k will control cycles, and "npuntos" is a points counter.
    double x, yp;// "x" will save the point to value provided by the user, and "yp" the final value.
    double fxi, fx1;// These variables will save calculated values in cycles.
public slots:
    // Slots declaration
    void ejecutar();// Slot for start the method.
    void limpiar();// Slot for clear all user interface fields.
    void cargar();// Slot for save the points from a table widget.
private:
    Ui::ILagrange *ui;
};

#endif // ILAGRANGE_H
