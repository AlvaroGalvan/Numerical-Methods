// Multiple Linear Regression Method Program V 1.1.0 / Programa del metodo de Regresion Lineal Multiple V 1.1.0
#ifndef REGMUL_H
#define REGMUL_H

#include <QMainWindow>

namespace Ui {
class RegMul;
}

class RegMul : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegMul(QWidget *parent = 0);
    ~RegMul();
    // Variables declaration.
    double puntos[6][3];// This matrix will save the points provided by the user.
    double matriz[3][4];// This matrix will save the points summations.
    double dispersion[6][2];// This matrix will save all dispersion results.
    double a0, a1, a2;// These three variables will save the found values for each plane equation term.
    double sr, st, sxy, r, yprom;// These variables will save error values and the "ypoints" average .
    int i,j,k;// Variables for control cycles.
public slots:
    // Slots declaration.
    void ejecutar();// Slot for run the method.
    void cargar();// Slot for save data from a table widget.
    void limpiar();// Slot for clear all user interface fields.
private:
    Ui::RegMul *ui;
};

#endif // REGMUL_H
