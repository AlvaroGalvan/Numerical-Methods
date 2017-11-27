// Numerical Diferentiation Method Program V 1.1.0 // Programa del metodo de diferenciacion numerica V 1.1.0
// Version Notes: User interface presentation changed,
// "Activar" slot optimization, now the table widget adds the row number according to the slected combo box value.
// Also, the Table widget shows Vertical header labels with each interval value.
// Warning added with instructions for the user, when the table have empty items.
#include "difnum.h"
#include "ui_difnum.h"
#include <QTableWidget>
#include <QTableWidgetItem>// Class for allow the use of Items from Table Widget.
#include <QString>// Class for allow the use of text strings.
#include <QMessageBox>// Class for allow the use of Message Box.

DifNum::DifNum(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DifNum)
{
    ui->setupUi(this);
    setWindowTitle("Metodo de Diferenciacion Numerica");// Prints the method's name at window title.
    // Connections between push button or combo box signals and slots.
    connect(ui->Inicia,SIGNAL(clicked()),this,SLOT(ejecutar()));// Start button with slot for run the method.
    connect(ui->Carga,SIGNAL(clicked()),this,SLOT(cargar()));// Load button with slot for save data.
    connect(ui->Limpia,SIGNAL(clicked()),this,SLOT(limpiar()));// Clear button with slot for clear fields.
    connect(ui->Casos,SIGNAL(activated(int)),this,SLOT(activar()));// Item activated signal and slot for activate the Table Widget.
    ui->Inicia->setDisabled(true);// Disables the start button till the user press the Load button.
    ui->Limpia->setDisabled(true);// Disables the clear button till the user press the Load button.
    ui->Tablain->setDisabled(true);// Disables the first Table Widget till the user choose an item from combo box.
    ui->Carga->setDisabled(true);// Disables the Load button till the user choose an item from combo box.
    ui->Incremento->setDisabled(true);// Disables the increment double spinbox till the user choose an item from combo box.
}
void DifNum::activar(){// This slot will activate the Table widget when the user choose an item from combo box.
    npuntos=0;// This variable starts from zero.
    k=ui->Casos->currentIndex();// Collects the current Index value from combo box and save it on "k".
    QStringList A;
    if(k!=0){// This condition activates the table widget when the current index is different to zero.
        ui->Tablain->setDisabled(false);// Enables the Table Widget.
        ui->Carga->setDisabled(false);// Enables the Load button.
        ui->Incremento->setDisabled(false);// Enables the increment double spin box.
        switch(k){// Assigns a points number and a start value depending of the current index
        case 1:// The first option, for run the method with three points.
            npuntos=3, j=4;
            A << "X-1" << "X0" << "X+1";
            break;
        case 2:// The secound option, for run the method with five points.
            npuntos=5, j=3;
            A << "X-2" << "X-1" << "X0" << "X+1" << "X+2";
            break;
        case 3:// The third option, for run the method with seven points.
            npuntos=7, j=2;
            A << "X-3" << "X-2" << "X-1" << "X0" << "X+1" << "X+2" << "X+3";
            break;
        case 4:// The fourth option, for run the method with nine points.
            npuntos=9, j=1;
            A << "X-4" << "X-3" << "X-2" << "X-1" << "X0" << "X+1" << "X+2" << "X+3" << "X+4";
            break;
        case 5:// The fifth option, for run the method with eleven points.
            npuntos=11, j=0;
            A << "X-5" << "X-4" << "X-3" << "X-2" << "X-1" << "X0" << "X+1" << "X+2" << "X+3" << "X+4" <<  "X+5";
            break;
        }
        ui->Tablain->setRowCount(npuntos);
        ui->Tablain->setVerticalHeaderLabels(A);
    }
    else{// If the current index is zero:
        ui->Tablain->setDisabled(true);// Disables the Table Widget.
    }
}

void DifNum::cargar(){// This slot will save the points from table widget to an array.
    countp=0;// This variable counts points, and compares his value with the points number assigned in previous slot.
    h=ui->Incremento->value();// Collects the increment value from double spin box and save it on "h".
    for(i=0;i<npuntos;i++){// This cycle will save the points provided by the user from the table widget into a array.
        QTableWidgetItem *posiciony=ui->Tablain->item(i,0);// Creates a temporal variable for save each item value from the first table column.
        if(!posiciony){// If the table widget item isn't null (empty), the cycle continues.
            continue;
        }
        puntosy[i]=posiciony->text().toDouble();// Saves the value from table item to an array position.
        countp++;// Sums one to the point counter.
    }
    if((countp==npuntos)&&(h!=0)){// If points number is the same and the increment value is different to zero:
        ui->Inicia->setDisabled(false);// Enables the Start button.
        ui->Carga->setDisabled(true);// Disables the Load button.
        ui->Tablain->setDisabled(true);// Disables the table widget.
        ui->Incremento->setDisabled(true);// Disables the increment double spinbox.
    }
    else{
        QMessageBox::warning(this,"Advertencia","Es necesario que llene la tabla con datos.\n(Para posiciones vacias agregue un cero).");
    }
    ui->Limpia->setDisabled(false);// Enables the Clear button.
}
void DifNum::ejecutar(){// This slot will run the method, when the Start button been clicked after data introduction.
    for(i=0;i<8;i++){// This cycle analyzes rows.
        for(int z=0;z<2;z++){// This cycle analyzes columns.
            atras[i][z]=0;// Clears each rear derivative matrix position.
            centro[i][z]=0;// Clears each central derivative matrix position.
            adelante[i][z]=0;// Clears each front derivative matrix position.
        }
    } // The next conditions calculates each derivative for each direction, and saves it on a different matrix position
    if(npuntos>=3){// If the points number is equal or higher than 3:
        // Calculates the first derivative with error O(h).
        atras[0][0]=((puntosy[1])-(puntosy[0]))/h;
        centro[0][0]=((puntosy[2])-(puntosy[0]))/(2*h);
        adelante[0][0]=((puntosy[2])-(puntosy[1]))/h;
    }
    if(npuntos>=5){// If the points number is equal or higher than 5:
        // Calculates the first derivative with error O(h^2) or O(h^4) and the secound derivative O(h) or O(h^2).
        atras[1][0]=((3*puntosy[2])-(4*puntosy[1])+(puntosy[0]))/(2*h);
        atras[2][0]=((puntosy[2])-(2*puntosy[1])+(puntosy[0]))/(h*h);
        centro[1][0]=(-(puntosy[4])+(8*puntosy[3])-(8*puntosy[1])+(puntosy[0]))/(12*h);
        centro[2][0]=((puntosy[3])-(2*puntosy[2])+(puntosy[1]))/(h*h);
        adelante[1][0]=(-(puntosy[4])+(4*puntosy[3])-(3*puntosy[2]))/(2*h);
        adelante[2][0]=((puntosy[4])-(2*puntosy[3])+(puntosy[2]))/(h*h);
    }
    if(npuntos>=7){// If the points number is equal or higher than 7:
        // Calculates the secound derivative with error O(h^2) or O(h^4) and the third derivative O(h) or O(h^2).
        atras[3][0]=((2*puntosy[3])-(5*puntosy[2])+(4*puntosy[1])-(puntosy[0]))/(h*h);
        atras[4][0]=((puntosy[3])-(3*puntosy[2])+(3*puntosy[1])-(puntosy[0]))/(h*h*h);
        centro[3][0]=((-puntosy[5])+(16*puntosy[4])-(30*puntosy[3])+(16*puntosy[2])-(puntosy[1]))/(12*(h*h));
        centro[4][0]=((puntosy[5])-(2*puntosy[4])+(2*puntosy[2])-(puntosy[1]))/(2*(h*h*h));
        adelante[3][0]=(-(puntosy[6])+(4*puntosy[5])-(5*puntosy[4])+(2*puntosy[3]))/(h*h);
        adelante[4][0]=((puntosy[6])-(3*puntosy[5])+(3*puntosy[4])-(puntosy[3]))/(h*h*h);
    }
    if(npuntos>=9){// If the points number is equal or higher than 9:
        // Calculates the third derivative with error O(h^2) or O(h^4) and the fourth derivative O(h) or O(h^2).
        atras[5][0]=((5*puntosy[4])-(18*puntosy[3])+(24*puntosy[2])-(14*puntosy[1])+(3*puntosy[0]))/(2*(h*h*h));
        atras[6][0]=(puntosy[4]-(4*puntosy[3])+(6*puntosy[2])-(4*puntosy[1])+(puntosy[0]))/(h*h*h*h);
        centro[5][0]=(-(puntosy[7])+(8*puntosy[6])-(13*puntosy[5])+(13*puntosy[3])-(8*puntosy[2])+(puntosy[1]))/(8*(h*h*h));
        centro[6][0]=((puntosy[6])-(4*puntosy[5])+(6*puntosy[4])-(4*puntosy[3])+(puntosy[2]))/(h*h*h*h);
        adelante[5][0]=(-(3*puntosy[8])+(14*puntosy[7])-(24*puntosy[6])+(18*puntosy[5])-(5*puntosy[4]))/(2*(h*h*h));
        adelante[6][0]=((puntosy[8])-(4*puntosy[7])+(6*puntosy[6])-(4*puntosy[5])+(puntosy[4]))/(h*h*h*h);
    }
    if(npuntos==11){// If the points number is equal than 11:
        // Calculates the fourth derivative with error O(h^2) or O(h^4).
        atras[7][0]=((3*puntosy[5])-(14*puntosy[4])+(26*puntosy[3])-(24*puntosy[2])+(11*puntosy[1])-(2*puntosy[0]))/(h*h*h*h);
        centro[7][0]=((-puntosy[8])+(12*puntosy[7])-(39*puntosy[6])+(56*puntosy[5])-(39*puntosy[4])+(12*puntosy[3])-(puntosy[2]))/(6*(h*h*h*h));
        adelante[7][0]=((-2*puntosy[10])+(11*puntosy[9])-(24*puntosy[8])+(26*puntosy[7])-(14*puntosy[6])+(3*puntosy[5]))/(h*h*h*h);
    }
    for(i=0;i<npuntos-2;i++){// This cycle calculates the error for each derivative, and save it on a different matrix position.
        atras[i][1]=100*std::abs((atras[i][0]-centro[i][0])/(atras[i][0]));// Error for each rear derivative.
        centro[i][1]=100*std::abs((centro[i][0]-centro[i][0])/(centro[i][0]));// Error for each central derivative.
        adelante[i][1]=100*std::abs((adelante[i][0]-centro[i][0])/(adelante[i][0]));// Error for each front derivative.
    }
    for(i=0;i<npuntos-2;i++){// This cycle analyzes rows.
        for(int z=0;z<2;z++){// This cycle analyzes columns.
            // Shows each derivative and error value at his respective table position.
            ui->TablaAtras->setItem(i,z,new QTableWidgetItem(QString::number(atras[i][z])));
            ui->TablaCentro->setItem(i,z,new QTableWidgetItem(QString::number(centro[i][z])));
            ui->TablaAdelante->setItem(i,z,new QTableWidgetItem(QString::number(adelante[i][z])));
        }
    }
}
void DifNum::limpiar(){// This slot will clear all user interface fields, when the Clear button been clicked.
    // Clears the contents of each table widget.
    ui->Tablain->clearContents();
    ui->TablaAtras->clearContents();
    ui->TablaCentro->clearContents();
    ui->TablaAdelante->clearContents();
    ui->Incremento->setValue(0.0);// Clears the increment double spinbox.
    ui->Carga->setDisabled(true);// Enables the Load button.
    ui->Inicia->setDisabled(true);// Disables the Start button.
    ui->Limpia->setDisabled(true);// Disables the Clear button.
    ui->Tablain->setDisabled(true);// Disables the first table widget.
    ui->Incremento->setDisabled(false);// Disables the increment double spinbox.
}

DifNum::~DifNum()
{
    delete ui;
}
