// Numerical Methods System V 1.0.0
// Created and designed by Metodos Numericos >> Seccion 2017 >> Equipo 01.
#include "numethods.h"
#include "ui_numethods.h"
#include <QMessageBox>// Class for allow the use of Message box.

NuMethods::NuMethods(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NuMethods)
{
    ui->setupUi(this);
    setWindowTitle("Metodos Numericos | Seccion 2017 | Equipo 01");// Prints the pogram's name at window title.
    contador = new QTimer(this);// Assigns a new QTimer to secound counter at main window.
    // Assigns a new program to each method variable, resplectly.
    RPunto=new Punto();// Fixed point iteration method.
    RNewson=new Newson();// Newton - Raphson method.
    RGauss=new Gausss();// Simple Gaussian Elimination method.
    RGauSei=new GauSei();// Gauss - Seidel method.
    RILagrange=new ILagrange();// Lagrange's Interpolation method.
    RRegLin=new RegLin();// Linear Regression method.
    RRegMul=new RegMul();// Multiple Regression method.
    RDifNum=new DifNum();// Numerical Diferentiation method.
    RIntegNum=new IntegNum();// Numerical Integration method.
    REuler=new MEuler();// Euler's method.
    RRungeKutta=new Runtta();// And the new Runge - Kutta method.
    // Connections from signals to slots:
    connect(contador,SIGNAL(timeout()),this,SLOT(CuentayCambia()));// Secound counter timeout signal to slot for change automatically the page from stacked widget.
    connect(ui->Anterior,SIGNAL(clicked()),this,SLOT(Anterior()));// Clicked signal from Previous push button to slot for change the previous one page from stacked widget.
    connect(ui->Siguiente,SIGNAL(clicked()),this,SLOT(Siguiente()));// Clicked signal from Next push button to slot for change the next one page from stackes widget.
    connect(ui->Inicia,SIGNAL(clicked()),this,SLOT(Ejecutar()));// Clicked signal from Run button to slot for run the present program.
    connect(ui->Sale,SIGNAL(clicked()),this,SLOT(Salir()));// Clicked signal from Exit button to slot for close main window.
    contador->start(15000);// The secound counter starts to count, with an assigned time of 15,000ms (15 secounds).
    ui->Inicia->setDisabled(true);// Disables the start button.
}
void NuMethods::CuentayCambia(){// This slot will change the page from Stacked widget automatically every 15 secounds.
    k=ui->Ventana->currentIndex();// Takes the current index value from stacked widget and saves it on "k".
    k++;// Sums one to "k".
    if(k>11){// If the current index is higher than 11 (the program only have 11 pages):
        k=0;// "k" goes to zero, for back to main page.
    }
    ui->Ventana->setCurrentIndex(k);// Set the "k+1" value as current index for stacked widget (for show the next page).
    if(k!=0){// If the current index is different to zero (not showing main page):
        ui->Inicia->setDisabled(false);// Enables the run button.
    }
    else{// If the current index is zero (showing the main page):
        ui->Inicia->setDisabled(true);// Disables the run button.
    }
}

void NuMethods::Anterior(){// This slot will change the page to previous one from Stacked widget, when the "Previous" push button been clicked.
    contador->start(15000);// Re-starts the secound counter, for stay in page 15 secounds.
    k=ui->Ventana->currentIndex();// Takes the current index value from stacked widget and saves it on "k".
    k=k-1;// Subtracts one to current index.
    if(k<0){// If the current index is lower than zero (zero is the main page):
        k=11;// "k" goes to 11, for show last page.
    }
    ui->Ventana->setCurrentIndex(k);// Set the "k-1" value as current index for stacked widget (for show the previous page).
    if(k!=0){// If the current index is different to zero (not showing main page):
        ui->Inicia->setDisabled(false);// Enables the run button.
    }
    else{// If the current index is zero (showing the main page):
        ui->Inicia->setDisabled(true);// Disables the run button.
    }
}
void NuMethods::Siguiente(){// This slot will change the page to next one from Stacked widget, when the "Next" push button been clicked.
    contador->start(15000);// Re-starts the secound counter, for stay in page 15 secounds.
    k=ui->Ventana->currentIndex();// Takes the current index value from stacked widget and saves it on "k".
    k=k+1;// Sums one to "k".
    if(k>11){// If the current index is higher than 11 (the program only have 11 pages):
        k=0;// "k" goes to zero, for back to main page.
    }
    ui->Ventana->setCurrentIndex(k);// Set the "k+1" value as current index for stacked widget (for show the next page).
    if(k!=0){// If the current index is different to zero (not showing main page):
        ui->Inicia->setDisabled(false);// Enables the run button.
    }
    else{// If the current index is zero (showing the main page):
        ui->Inicia->setDisabled(true);// Disables the run button.
    }
}
void NuMethods::Ejecutar(){// This slot will run the present program showed at Stacked widget, when "Run" button been clicked.
    k=ui->Ventana->currentIndex();// Takes the current index value from stacked widget and saves it on "k".
    if(k!=0){// Even if the current index been different to zero:
        switch(k){// Switch the current index, there haves 11 possible cases:
        case 1:// For the first case, and page one:
            RPunto->show();// Shows at a new window the Fixed Point Itreation method program.
            break;// The case breaks.
        case 2:// For the second case, and page two:
            RNewson->show();// Shows at a new window the Newton - Raphson method program.
            break;// The case breaks.
        case 3:// For third case, and page three:
            RGauss->show();// Shows at a new window the Simple Gaussian Elimination method program.
            break;// The case breaks.
        case 4:// For fourth case, and page four:
            RGauSei->show();// Shows at a new window the Gauss - Seidel method program.
            break;// The case breaks.
        case 5:// For fifth case, and page five:
            RILagrange->show();// Shows at a new window the Lagrange's Interpolation method program.
            break;// The case breaks.
        case 6:// For sixth case, adn page six:
            RRegLin->show();// Shows at a new windows the Linear Regression method program.
            break;// The case breaks.
        case 7:// For seventh case, and page seven:
            RRegMul->show();// Shows at a new window the Multiple Regression method program.
            break;// The case breaks.
        case 8:// For eighth case, and page eight:
            RDifNum->show();// Shows at a new window the Numerical Differentiation method program.
            break;// The case breaks.
        case 9:// For ninth case, and page nine:
            RIntegNum->show();// Show at a new window the Numerical Integration method program.
            break;// The case breaks.
        case 10:// For tenth case, and page ten:
            REuler->show();// Shows at a new window the Euler's method program.
            break;// The case breaks.
        case 11:// For elevenst case, and page eleven:
            RRungeKutta->show();// Shows at a new window the Runge - Kutta method program.
            break;// The case breaks.
        }
    }
}
void NuMethods::Salir(){// This slot will close the main window and delete the programs, when exit button been clicked.
    QMessageBox::StandardButton respuesta;// Creates a Message box named "respuesta", with standart buttons.
    // Assigns to "respuesta" a message box question type, at main window, with the question: Are you sure to want to exit?,
    // and with two possible answers: Yes and No. The answer will save at "respuesta".
    respuesta= QMessageBox::question(this,"Accion Salir","¿Seguro que desea salir?",QMessageBox::Yes | QMessageBox::No);
    if(respuesta==QMessageBox::Yes){// If the answer is Yes:
        // Deletes each program variable.
        delete RPunto;// Fixed point iteration method.
        delete RNewson;// Newton - Raphson method.
        delete RGauss;// Simple Gaussian Elimination method.
        delete RGauSei;// Gauss - Seidel method.
        delete RILagrange;// Lagrange's Interpolation method.
        delete RRegLin;// Linear Regression method.
        delete RRegMul;// Multiple Regression method.
        delete RDifNum;// Numerical Diferentiation method.
        delete RIntegNum;// Numerical Integration method.
        delete REuler;// Euler's method.
        delete RRungeKutta;// Runge - Kutta method.
        contador->stop();// Stops the second counter.
        close();// Close the main window.
    }// If the answer is No, the program stay opened.
}

NuMethods::~NuMethods()
{
    delete ui;
}
// Equipo 01:
// Huesca de Rosario Miriam Guadalupe.
// Montes Mendoza Eliot.
// Galván Aguilar Álvaro Martín.
