// Gauss - Seidel Method Program V 1.1.0 / Programa del metodo de Gauss - Seidel V 1.1.0
#ifndef GAUSEI_H
#define GAUSEI_H

#include <QMainWindow>

namespace Ui {
class GauSei;
}

class GauSei : public QMainWindow
{
    Q_OBJECT

public:
    explicit GauSei(QWidget *parent = 0);
    ~GauSei();
    // Variables declaration
    double errorac;// This variable will save the accepted error provided by the user.
    double x1,x2,x3,x4;// These four variables will save the found values.
    double matrix[4][4];// Main matrix, will save the value of 16 numbers provided by the user.
    double indep[4][1];// This matrix will save 4 independent values, provided by the user.
    double tempo[1][4];// This temporal matrix will save rows for the exchange.
    double tempo2[1][4];// This another temporal matrix will save rows for the exchange.
    double ind1,ind2;// These variables will save independent values for the exchange.
    int itera, icont;// The "itera" variable will save the iterations maximum provided by the user. Them "icont" is an iterations counter.
    int i,j;// These variables will control the row and column number in the matrix and the table.
    int h;
public slots:
    // Slots declaration
    void ejecutar();// Slot for start the method.
    void limpiar();// Slot for clear the user interface fields.
    void agregar();// Slot for add data provided by the user.
private:
    Ui::GauSei *ui;
};

#endif // GAUSEI_H
