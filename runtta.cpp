// Runge - Kutta Method Program V 1.0.0 / Metodo de Runge - Kutta V 1.0.0
#include "runtta.h"
#include "ui_runtta.h"
#include <QTableWidgetItem>

Runtta::Runtta(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Runtta)
{
    ui->setupUi(this);
    setWindowTitle("Metodo de Runge - Kutta");
    // Connections between double spinbox value changed signals and slots.
    connect(ui->Inferior,SIGNAL(valueChanged(double)),this,SLOT(activara()));// Lower limit (A) double spinbox with slot for enable the intervals spinbox.
    connect(ui->Superior,SIGNAL(valueChanged(double)),this,SLOT(activara()));// Higher limit (B) double spinbox with slot for enable the intervals spinbox.
    connect(ui->Incremento,SIGNAL(valueChanged(double)),this,SLOT(activarb()));// Intervals spinbox with slot for enable the Start button.
    // Connections between push buttons cliked signals and slots.
    connect(ui->Inicia,SIGNAL(clicked()),this,SLOT(ejecutar()));// Start button with slot for run the method.
    connect(ui->Limpia,SIGNAL(clicked()),this,SLOT(limpiar()));// Clear button with slot for clear fields.
    ui->Inicia->setDisabled(true);// Disables the Start button till the user changes values from spinboxes.
    ui->TablaY->setDisabled(true);// Disables the results table widget, till the user click the Start button.
    ui->Incremento->setDisabled(true);// Disables the increment double spinbox, till the user introduce A and B values.
}
double Runtta::x(double f){// Function that saves the differential equation.
    return((-2*(f*f*f))+(12*(f*f))-(20*(f))+8.5);// Returns the valued equation.
}
double Runtta::y(double g){// Function that saves the integrated equation.
    return(-(0.5*(g*g*g*g))+(4*(g*g*g))-(10*(g*g))+(8.5*g)+1);// Returns the valued equation.
}

void Runtta::activara(){// This slot will activate the increment double spinbox, when the user add values for A and B.
    xinf=ui->Inferior->value();// Takes the value from lower limit (A) double spinbox and saves it on "xinf".
    xsup=ui->Superior->value();// Takes the value from higher limit (B) double spinbox and saves it on "xsup".
    if(xinf!=xsup){// If A and B gets different values:
        ui->Incremento->setDisabled(false);// Enables the increment double spinbox.
    }
    else{// If A and B gets the same values:
        ui->Incremento->setDisabled(true);// Keeps disabled the increment double spinbox.
    }
}
void Runtta::activarb(){// This slot will activate the Start button when the user add an increment value.
    h=ui->Incremento->value();// Takes the value from increment double spinbox and saves it on "h".
    if(h!=0){// If the increment is different than zero:
        ui->Inicia->setDisabled(false);// Enables the Start button.
    }
    else{// If the increment is equal than zero:
        ui->Inicia->setDisabled(true);// Keeps disabled the Start button.
    }
}
void Runtta::ejecutar(){// This slot will run the method, when the user click the Start button.
    double inum=0;// Creates a temporal variable of double type for correct intervals number.
    QStringList A;// Creates a temporal string list, that will save all intervals values.
    QString temporal;// Creates a temporal string, that will save each interval value for add it to string list.
    inum=((xsup-xinf)/h);// Calculates the intervals number.
    intervalos=inum;// A variable type int takes the calculated intervals number.
    double puntosx[intervalos];// Creates a temporal array for x points.
    double k1[intervalos], k2[intervalos];// Creates two temporal arrays for save each k1 and k2 values.
    double yi[intervalos];// Creates a temporal array for yi results.
    double yreal[intervalos];// Creates a temporal array for real y values.
    double diferencia[intervalos];// Crates a temporal array for save the differences values.
    puntosx[0]=xinf, puntosx[intervalos]=xsup;// The first "x points" aray position takes the value from lower limit, and the last array position takes the value from higher limit.
    yi[0]=y(xinf), yreal[0]=y(xinf);// The first "yi" array position takes the value from integrated function valued with lower limit.
    diferencia[0]=yi[0]-yreal[0];// Calculates first difference.
    for(i=1;i<=intervalos;i++){//
        puntosx[i]=puntosx[i-1]+h;// Calculates each interval (x point), and saves it on a different array position.
        temporal.setNum(puntosx[i]);// Converts the point to string.
        A << temporal;// Adds the found point to string list.
        k1[i]=x(puntosx[i-1])*h;// Calculates each k1.
        k2[i]=x(puntosx[i])*h;// Calculates each k2.
        yi[i]=yi[i-1]+(0.5*(k1[i]+k2[i]));// Calculates each value for "yi".
        yreal[i]=y(puntosx[i]);// Calculates each real y value, and saves it on a different array position.
        diferencia[i]=yi[i]-yreal[i];// Calculates each difference between "yi" and "real y".
    }
    temporal.setNum(xsup);// Converts the higher limit (B) to string.
    A << temporal;// Adds the last "x point" to string list.
    ui->TablaY->setDisabled(false);// Enables the table widget results.
    ui->TablaY->setRowCount(intervalos);// Sets the rows number for table widget.
    ui->TablaY->setVerticalHeaderLabels(A);// Shows each x point saved in string list at table vertical headers.
    for(i=0;i<intervalos;i++){// This cycle analyzes rows, for show the all the calculated vaues.
        ui->TablaY->setItem(i,0,new QTableWidgetItem(QString::number(yi[i+1])));//  Shows each "yi" at first table column.
        ui->TablaY->setItem(i,1,new QTableWidgetItem(QString::number(yreal[i+1])));// Shows each "real y" at second table column.
        ui->TablaY->setItem(i,2,new QTableWidgetItem(QString::number(diferencia[i+1])));// Shows each difference between yian real y, at third table column.
    }
}
void Runtta::limpiar(){// This slot will clear all user interface fields, when clicked the Clear button.
    ui->Incremento->setValue(0.0);// Clears the increment double spinbox.
    ui->Inferior->setValue(0.0);// Clears the lower limit (A) double spinbox.
    ui->Superior->setValue(0.0);// Clears the higher limit (B) double spinbox.
    ui->TablaY->clearContents();// Clears the table widget contents.
}

Runtta::~Runtta()
{
    delete ui;
}
