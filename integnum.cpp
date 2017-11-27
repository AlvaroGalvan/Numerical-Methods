//Numerical Integration Method Program V 1.1.0 / Programa del metodo de Integracion Numerica V 1.1.0
// Version Notes: User interface presentation changed.
// Warning added with instructions for the user, when the table have empty items.
#include "integnum.h"
#include "ui_integnum.h"
#include <QTableWidget> // Class for allow the table widget configuration.
#include <QTableWidgetItem> // Class for allow the table widget items use.
#include <QString> // Class for allow the Strings use.
#include <QMessageBox> // Class for allow the use of Message Box.

IntegNum::IntegNum(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IntegNum)
{
    ui->setupUi(this);
    setWindowTitle("Metodo de Integracion Numerica");// Prints the method's name at window title.
    // Connections between push button clicked signals or spinbox value changed signals to slots.
    connect(ui->Inferior,SIGNAL(valueChanged(double)),this,SLOT(activarSpin()));// Lower limit (A) double spinbox with slot for enable the intervals spinbox.
    connect(ui->Superior,SIGNAL(valueChanged(double)),this,SLOT(activarSpin()));// Higher limit (B) double spinbox with slot for enable the intervals spinbox.
    connect(ui->Intervalos,SIGNAL(valueChanged(int)),this,SLOT(activarTabla()));// Intervals spinbox with slot for enable and configure the table widget.
    connect(ui->Carga,SIGNAL(clicked()),this,SLOT(cargar()));// Load button with slot for save data.
    connect(ui->Inicia,SIGNAL(clicked()),this,SLOT(ejecutar()));// Start button with slot for run the method.
    connect(ui->Limpia,SIGNAL(clicked()),this,SLOT(limpiar()));// Clear button with slot for clear fields.
    ui->Intervalos->setDisabled(true);// Disables the intervals spinbox till the user introduce A and B values.
    ui->Tablapuntos->setDisabled(true);// Disables the Table widget till the user introduce an intervals number.
    ui->Carga->setDisabled(true);// Disables the Load button till the user introduce an intervals number.
    ui->Inicia->setDisabled(true);// Disables the Start button till the user click the Load button.
    ui->Limpia->setDisabled(true);// Disables the Clear button till the user click the Load button.
}
void IntegNum::activarSpin(){// This slot will enable the intervals spinbox.
    ainf=ui->Inferior->value();// Collects the value of lower limit (A) and saves it on "ainf".
    bsup=ui->Superior->value();// Collects the value of higher limit (B) and saves it on "bsup".
    if(ainf!=bsup){// If A and B values are different:
        ui->Intervalos->setDisabled(false);// Enables the intervals spinbox.
    }
    else{// If A and B gets the same values:
        ui->Intervalos->setDisabled(true);// Keeps disabled the intervals spinbox.
    }
}
void IntegNum::activarTabla(){// This slot will enable and configure the Table widget for data introduction.
    QStringList A;// Creates a String List, that will save all intervals values.
    QString temporal;// Creates a temporal string, that will save each interval value.
    n=ui->Intervalos->value();// Collects the value from intervals spinbox and saves it on "n".
    if(n!=0){// If the intervals number is different to zero:
        h=(bsup-ainf)/n;// Calculates the increment value with higher and lower limits and the intervals number.
        double puntos[n];// Creates a temporal array, that will save each calculated interval value.
        puntos[0]=ainf, puntos[n]=bsup;// The first aray position takes the value from lower limit, and the last array position takes the value from higher limit.
        A <<temporal.setNum(puntos[0]);// The string list saves first interval value.
        for(i=1;i<n;i++){// This cycle will calculate the middle values for intervals.
            puntos[i]=puntos[i-1]+h;// Calculates each middle interval value, with previous value and the calculated increment.
            A << temporal.setNum(puntos[i]);// The string list saves each calculated interval value.
        }
        A << temporal.setNum(puntos[n]);// The string list saves the last interval value.
        ui->Tablapuntos->setRowCount(n+1);// Set the rows number for table widget, with the value provided by user +1.
        ui->Tablapuntos->setDisabled(false);// Enables the table widget.
        ui->Tablapuntos->setVerticalHeaderLabels(A);// Set vertical headers for table widget, with the saved values in string list.
        ui->Carga->setDisabled(false);// Enables the Load button.
    }
    else{// If the intervals number is zero:
        ui->Tablapuntos->setDisabled(true);// Keeps the table widget disabled.
    }
}

void IntegNum::cargar(){// This slot will save the points from table widget to an array, when the Load button been clicked.
    int npuntos=0;// Creates a temporal variable for count points.
    for(i=0;i<=n;i++){// This cycle will save the points provided by the user from the table widget into an array.
        QTableWidgetItem *posicion=ui->Tablapuntos->item(i,0);// Creates a temporal variable for save each item value from each table row.
        if(!posicion){// If the table widget item isn't null (empty), the cycle continues.
            continue;
        }
        puntosfx[i]=posicion->text().toDouble();// Saves the value from table item to an array position.
        npuntos++;// Sums one to temporal point counter.
    }
    if(npuntos==n+1){// If the temporal point counter gets the same value than the intervals number provided by user +1:
        ui->Inicia->setDisabled(false);// Enables the Start button.
        ui->Carga->setDisabled(true);// Disables the Load button.
        ui->Inferior->setDisabled(true);// Disables the lower limit (A) double spinbox.
        ui->Superior->setDisabled(true);// Disables the higher limit (B) double spinbox.
    }
    else{
        QMessageBox::warning(this,"Advertencia","Es necesario que llene la tabla con datos.\n(Para posiciones vacias agregue un cero).");
    }
    ui->Limpia->setDisabled(false);// Enables the Clear button.
}
void IntegNum::ejecutar(){// This slot will run the method, when the Start button been clicked after data introduction.
    integral=0, producto=0, sumas=0, error=0;// These four variables starts from zero.
    QString tempo1,tempo2,tempo3;// Creates temporal strings for show results.
    for(i=1;i<n;i++){// This cycle calculates each product from first position to "n-1" position.
        producto=(2*puntosfx[i]);// Calculates each product.
        sumas=sumas+producto;// Sums all products.
    }
    integral=(h/2)*(puntosfx[0]+puntosfx[n]+sumas);// Calculates the integral value.
    error=integral-(((bsup-ainf)/2)*(puntosfx[0]+puntosfx[n]));// Calculates the error value.
    // Creates a string with the found integral and error results.
    tempo1.append("El resultado de la integral (I)=").append(tempo2.setNum(integral)).append
            (" Unidades cuadradas\n El error calculado (E)=").append(tempo3.setNum(error));
    ui->Resultado->setText(tempo1);// Shows the string at text browser.
}
void IntegNum::limpiar(){// This slot will clear all user interface fields, when the Clear button been clicked.
    ui->Tablapuntos->clearContents();// Clear contents from table widget.
    ui->Tablapuntos->setRowCount(0);// Set zero rows for table widget.
    ui->Inferior->setValue(0.0);// Set initial value for lower limit (A) double spinbox.
    ui->Superior->setValue(0.0);// Set initial value for higher limit (B) double spinbox.
    ui->Intervalos->setValue(0);// Set initial value for intervals spinbox.
    ui->Inicia->setDisabled(true);//Disables the Start button.
    ui->Inferior->setDisabled(false);// Enables A and B spinboxes.
    ui->Superior->setDisabled(false);
    ui->Resultado->clear();// Clears results text browser.
}

IntegNum::~IntegNum()
{
    delete ui;
}
