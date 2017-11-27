// Numerical Methods System V 1.0.0
// Created and designed by Metodos Numericos >> Seccion 2017 >> Equipo 01.
#ifndef NUMETHODS_H
#define NUMETHODS_H
#include <QTimer>// Class for allow the use of time counter.
#include <QMainWindow>
// Includes the header files from each method program.
#include <punto.h>// Fixed point iteration method.
#include <newson.h>// Newton - Raphson method.
#include <gausss.h>// Simple Gaussian Elimination method.
#include <gausei.h>// Gauss - Seidel method.
#include <ilagrange.h>// Lagrange's Interpolation method.
#include <reglin.h>// Linear Regression method.
#include <regmul.h>// Multiple Regression method.
#include <difnum.h>// Numerical Diferentiation method.
#include <integnum.h>// Numerical Integration method.
#include <meuler.h>// Euler's method.
// Also, includes a new program for last method.
#include <runtta.h>// Runge - Kutta method.

namespace Ui {
class NuMethods;
}

class NuMethods : public QMainWindow
{
    Q_OBJECT

public:
    explicit NuMethods(QWidget *parent = 0);
    ~NuMethods();
    // Variables declaration. Creates a variable program type for each method.
    Punto *RPunto;// Fixed point iteration method.
    Newson *RNewson;// Newton - Raphson method.
    Gausss *RGauss;// Simple Gaussian Elimination method.
    GauSei *RGauSei;// Gauss - Seidel method.
    ILagrange *RILagrange;// Lagrange's Interpolation method.
    RegLin *RRegLin;// Linear Regression method.
    RegMul *RRegMul;// Multiple Regression method.
    DifNum *RDifNum;// Numerical Diferentiation method.
    IntegNum *RIntegNum;// Numerical Integration method.
    MEuler *REuler;// Euler's method.
    Runtta *RRungeKutta;// Runge - Kutta method.
    QTimer *contador;// Creates a variable QTimer type for count secounds.
    int k;// This integer variable will count the current index from a Stacked Widget.
public slots:
    // Slots declaration.
    void CuentayCambia();// This slot will change the page from Stacked widget automatically every 15 secounds.
    void Anterior();// This slot will change the page to previous one from Stacked widget.
    void Siguiente();// This slot will change the page to next one from Stacked widget.
    void Ejecutar();// This slot will run the present program showed at Stacked widget.
    void Salir();// This slot will close the main window and delete the programs.
private:
    Ui::NuMethods *ui;
};

#endif // NUMETHODS_H
