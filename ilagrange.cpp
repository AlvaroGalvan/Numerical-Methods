// Lagrange's Interpolation Method Program V 1.1.0 // Programa del método de interpolación de Lagrange V 1.1.0
// Version Notes: User interface presentation changed.
// Warning added with instructions for the user, when points number been lower than 2.
#include "ilagrange.h"
#include "ui_ilagrange.h"
#include <QTableWidgetItem>// Class for allow the use of Items from Table Widget.
#include <QMessageBox>// Class for allow the use of Message Box.

ILagrange::ILagrange(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ILagrange)
{
    ui->setupUi(this);
    setWindowTitle("Método de Interpolacion de Lagrange");// Prints the method's name at window title.
    // Connections between signals and slots:
    connect(ui->inicia,SIGNAL(clicked()),this,SLOT(ejecutar()));// Start button with slot for run the method.
    connect(ui->limpia,SIGNAL(clicked()),this,SLOT(limpiar()));// Clear button with slot for clear fields.
    connect(ui->carga,SIGNAL(clicked()),this,SLOT(cargar()));// Load button for save the data from table widget.
    ui->inicia->setDisabled(true);// Disables the start button till the user press the Load button.
    ui->limpia->setDisabled(true);// Disables the clear button till the user press the Load button.
    ui->valorx->setDisabled(true);// Disable the double spinbox for "x value" till the user press the Load button.
}
void ILagrange::cargar(){// This slot will save the data from table widget to arrays, when the Load button been clicked.
    npuntos=0, x=0;// The point counter and the "x value" starts from zero.
    ui->Tabla->setDisabled(true);// Disables the table widget.
    for(i=0;i<5;i++){// This cycle saves data from table widget items to two arrays:
        QTableWidgetItem* posicionx=ui->Tabla->item(i,0);// Creates a temporal variable for save each item value from the first table column.
        if(!posicionx){// If the table widget item isn't null (empty), the cycle continues.
            continue;
        }
        puntox[i]=posicionx->text().toDouble();// Saves the value from item in an array position, converted to double.
        QTableWidgetItem* posiciony=ui->Tabla->item(i,1);// Creates a temporal variable for save each item value from the secound table column.
        puntoy[i]=posiciony->text().toDouble();// Saves the value from item in an array position, converted to double.
        npuntos++;// Sums one number to the points counter.
        }
    if(npuntos<2){// If the user introduced less than 2 points:
        ui->Tabla->setDisabled(false);// The table keeps activate, till the user adds at least 2 points.
        QMessageBox::warning(this,"Advertencia","Debe introducir al menos dos puntos.");
    }
    else{// If the user added at least 2 points:
        ui->carga->setDisabled(true);// Disables the Load button.
        ui->valorx->setDisabled(false);// Enables the double spinbox for x value.
        ui->inicia->setDisabled(false);// Enables the Start button.
        ui->valorx->setMinimum(puntox[0]);// For the "x value" double spinbox, sets as minimum value the first point introduced.
        ui->valorx->setMaximum(puntox[npuntos-1]);// For the "x value" double spinbox, sets as maximum value the last point introduced.
    }
    ui->limpia->setDisabled(false);// Enables the Clear button.
}

void ILagrange::ejecutar(){// This slot will run the method, when the Start button been clicked after data introduction.
    x=ui->valorx->value();// Collects the value from "x value" double spinbox, and saves it on "x".
    //The method starts.
    for(k=1;k<npuntos;k++){// This cycle controls the polinomys grade, depending from the points number.
        fxi=0, yp=0;// These variables starts from zero, for preventing accumulation.
        for(i=0;i<=k;i++){// This cycle controls the summation.
            fx1=1;// This variable starts from 1, for preventing accumulation.
            for(j=0;j<=k;j++){// This cycle controls the multiplications number.
                if(j!=i){// This condition prevents that i and j got the same value.
                    fxi=(x-puntox[j])/(puntox[i]-puntox[j]);// Calculates each term, and save it on "fxi".
                    fx1=fxi*fx1;// Multiplies calculated terms, and saves it on "fx1"
                }
            }
            fx1=fx1*puntoy[i];//Multiplies the saved value on fx1 and each f(x) point provided by the user.
            yp=yp+fx1;// Sums the products.
            fx[i]=yp;// This array saves each summation in a different position.
        }
        // Shows the found results in a secound table widget possition, depending the polinomy's grade.
        ui->Tabres->setItem(k-1,0,new QTableWidgetItem(QString::number(fx[k])));
    }
    // The method finishes.
}
void ILagrange::limpiar(){// This slot will clear all user interface fields, when the Clear button been clicked.
    // Clears both table widgets.
    ui->Tabla->clearContents();
    ui->Tabres->clearContents();
    ui->valorx->setMinimum(0);// Sets as minimum value cero, for the "x value" double spinbox.
    ui->valorx->setValue(0.0);// Set an initial value, for the "x value" double spinbox.
    ui->valorx->setDisabled(true);// Disables the "x value" double spinbox.
    ui->Tabla->setDisabled(false);// Enables the first table widget.
    ui->carga->setDisabled(false);// Enables the Load button.
    ui->inicia->setDisabled(true);// Disables the Start button.
    ui->limpia->setDisabled(true);// Disables the Clear button.
}

ILagrange::~ILagrange()
{
    delete ui;
}
