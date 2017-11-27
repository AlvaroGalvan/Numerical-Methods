// Simple Gaussian Elimination Method Program V 1.1.0/ Programa del metodo de Eliminacion Gaussiana Simple V 1.1.0
#ifndef GAUSSS_H
#define GAUSSS_H

#include <QMainWindow>

namespace Ui {
class Gausss;
}

class Gausss : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gausss(QWidget *parent = 0);
    ~Gausss();
    // Variables declaration.
    double x1, x2, x3, x4;// This variables will save the found values.
    double matriz[4][5];// Main matrix, will save the value of 16 numbers provided by the user.
    double indep[4][1];// This matrix will save 4 independent values, provided by the user.
    double tempo[4];// This temporal array will save rows for the exchange.
    double tempo2[4];// This another temporal array will save rows for the exchange.
    double ind1, ind2;// These variables will save independent values for the exchange.
    int i,j,k,count;// These variables will controll the row and column number in the matix and the table.
public slots:
    // Slots declaration.
    void ejecutar();// Slot for start the method.
    void limpiar();// Slot for clear the user interface fields.
    void agregar();// Slot for add data provided by the user.
private:
    Ui::Gausss *ui;
};

#endif // GAUSSS_H
