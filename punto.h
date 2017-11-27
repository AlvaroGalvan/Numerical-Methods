//Fixed Point Iteration Program V 1.1.0 / Programa de Iteracion de Punto Fijo V 1.1.0
#ifndef PUNTO_H
#define PUNTO_H

#include <QMainWindow>
#include <cmath> //Library for allow mathematical functions in the method

namespace Ui {
class Punto;
}

class Punto : public QMainWindow
{
    Q_OBJECT

public:
    explicit Punto(QWidget *parent = 0);
    ~Punto();
    //Variables declaration
    double x; //This variable will save the initial value provided by the user
    double xr; //This variable will save the result of the valued function
    double ea; //This variable save the accepted error provided by the user
    double ei; // Initial error, it starts from 100 percent
    int i; //This variable will count the iterations
    double g(double d); //Function declaration
public slots:
    //Slots declaration
    void activar(); // Slot for activate the Start button.
    void ejecutar(); //Slot for start the method
    void limpiar(); //Slot for clear the user interface parameters

private:
    Ui::Punto *ui;
};

#endif // PUNTO_H
