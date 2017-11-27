// Gauss - Seidel Method Program V 1.1.0 / Programa del metodo de Gauss - Seidel V 1.1.0
// Version Notes: User interface presentation changed,
// "Agregar" slot optimization, now is easier save the values directly from the table widget.
// Warning added with instructions for the user, when the table have empty items.
#include "gausei.h"
#include "ui_gausei.h"
#include <QTableWidgetItem>// Class for allow the use of items from Table Widget.
#include <QMessageBox>// Class for allow the use of Message Box.

GauSei::GauSei(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GauSei)
{
    ui->setupUi(this);
    setWindowTitle("Metodo de Gauss - Seidel");// Prints the method's name at window title.
    //Connections between push buttons and slots:
    connect(ui->Inicia,SIGNAL(clicked()),this,SLOT(ejecutar()));// Button and slot for start the method.
    connect(ui->Limpia,SIGNAL(clicked()),this,SLOT(limpiar()));// Button and slot for clear the fields from user interface.
    connect(ui->Carga,SIGNAL(clicked()),this,SLOT(agregar()));// Button for add items to the table.
    // Connections between spinboxes value changed signal and the "agregar" slot:
    connect(ui->errora,SIGNAL(valueChanged(double)),this,SLOT(agregar()));
    connect(ui->imax,SIGNAL(valueChanged(int)),this,SLOT(agregar()));
    ui->Inicia->setDisabled(true);// Disables the start button till all items from table been added.
    ui->Limpia->setDisabled(true);// Disables the clear button.
    ui->errora->setDisabled(true);// Disable the accepted error spinbox till all items from table been added.
    ui->imax->setDisabled(true);// Disable the iterations spinbox till all items from table been added.
}
void GauSei::agregar(){// This slot will save data from table widget to a matrix, when the Load button been clicked.
    int countp=0;// Ceates a temporal counter, that strats from zero.
    //ui->Tabla->setDisabled(true);
    for(i=0;i<4;i++){// This cycle analyzes rows.
        for(j=0;j<4;j++){// This cycle analyzes columns.
            QTableWidgetItem* posicion=ui->Tabla->item(i,j);// Creates a temporal variable for take each item (dependent variables).
            QTableWidgetItem* pindep=ui->Tabla->item(i,4);// Creates a temporal variable for take each item (independent variables).
            if((!posicion)||(!pindep)){// If the position isn't null (empty), the cycle continues.
                continue;
            }
            matrix[i][j]=posicion->text().toDouble();// Saves each dependent variables item in a different matrix position.
            indep[i][0]=pindep->text().toDouble();// Saves each independent variables item in a new matrix with different position.
            countp++;// Sums one to counter.
        }
    }
    for(i=0;i<4;i++){// This cycle analyzes if the main diagonal of the main matrix have zeros.
        if(matrix[i][i]==0){// If it haves zeros:
            for(j=0;j<4;j++){// This cycle exchanges row positions for the x variables.
                if(i<3){// If isn't the last row:
                    h=i+1;// Sums one to "h", for exchange h rows.
                }
                if(i==3){// If is the last row.
                    h=i-1;// Subtracts one to "h", for exchange h rows.
                }
                ind1=indep[i][0];// A temporal variable takes the value of the detected row independent variable.
                ind2=indep[h][0];// Another temporal variable takes the value of the next independent variable.
                indep[h][0]=ind1;// Puts the detected row independent variable on next row.
                indep[i][0]=ind2;// Puts the next variable on previous row.
                tempo[0][j]=matrix[i][j];// A temporal matrix saves the detected row.
                tempo2[0][j]=matrix[h][j];// Another temporal matrix saves the next row.
                matrix[h][j]=tempo[0][j];// Puts the detected row on the next row.
                matrix[i][j]=tempo2[0][j];// Puts the next row on the previous row.
            }
        }
    }
    ui->Limpia->setDisabled(false);// Disables the Clear button.
    ui->errora->setDisabled(false);// Enables the accepted error double spinbox.
    ui->imax->setDisabled(false);// Enables the iterations spinbox.
    if(countp==16){// If the counter is equal than 16:
        ui->Carga->setDisabled(true);// Disables the Loas button.
        errorac=ui->errora->value();// Collects the value of accepted error provided by the user and saves it on "errorac".
        itera=ui->imax->value();// Collects the iterations maximum provided by user, and saves it on "itera".
        if((errorac==0)||(itera==0)){// If one of the spinboxes gets a zero:
            ui->Inicia->setDisabled(true);// Disables the start button.
        }
        else{ // If both spinboxes are different of zero:
            ui->Inicia->setDisabled(false);// Enables the start button.
        }
    }
    else {// If the counter is lower than 16:
        ui->Inicia->setDisabled(true);// Keeps disabled the Start button.
        ui->Carga->setDisabled(false);// Keeps enabled the Load button.
        // Shows a warning.
        QMessageBox::warning(this,"Advertencia","Es necesario que llene la tabla con datos.\n(Para posiciones vacias agregue un cero).");
    }
}
void GauSei::ejecutar(){
    double x=0, y=0, z=0, w=0;// Creates temporal variables, for save previous calculated values on method.
    double ex1=100, ex2=100, ex3=100, ex4=100;// Creates temporal variables ,for independent variables error.
    // The method starts with a cycle, and will stop when the independent calculated errors been small than the accepted error provided by the user.
    // Or when the iterations maximum been reached.
    while((ex1>errorac)&&(ex2>errorac)&&(ex3>errorac)&&(ex4>errorac)||(icont<itera)){
        x1=(indep[0][0]-(matrix[0][1]*x2)-(matrix[0][2]*x3)-(matrix[0][3]*x4))/(matrix[0][0]);// Calulates the value for x1.
        ex1=100*std::abs(x1-x)/(x1);// Calculates the error for the found value.
        x=x1;// A temporal variable saves the found value, it will be use in the next error calculation.
        x2=(indep[1][0]-(matrix[1][0]*x1)-(matrix[1][2]*x3)-(matrix[1][3]*x4))/(matrix[1][1]);// Calulates the value for x2.
        ex2=100*std::abs(x2-y)/(x2);// Calculates the error for the found value.
        y=x2;// A temporal variable saves the found value, it will be use in the next error calculation.
        x3=(indep[2][0]-(matrix[2][0]*x1)-(matrix[2][1]*x2)-(matrix[2][3]*x4))/(matrix[2][2]);// Calulates the value for x3.
        ex3=100*std::abs(x3-z)/(x3);// Calculates the error for the found value.
        z=x3;// A temporal variable saves the found value, it will be use in the next error calculation.
        x4=(indep[3][0]-(matrix[3][0]*x1)-(matrix[3][1]*x2)-(matrix[3][2]*x3))/(matrix[3][3]);// Calulates the value for x4.
        ex4=100*std::abs(x4-w)/(x4);// Calculates the error for the found value.
        w=x4;// A temporal variable saves the found value, it will be use in the next error calculation.
        icont++;// Sums one number to the iterations counter.
    } // The method finishes.
    ui->show1->display(x);// Show the last calculated value for x1;
    ui->show2->display(y);// Show the last calculated value for x2;
    ui->show3->display(z);// Show the last calculated value for x3;
    ui->show4->display(w);// Show the last calculated value for x4;
    ui->showi->display(icont);// Show the used iterations number.
}
void GauSei::limpiar(){
    ui->Tabla->clearContents();// Clears the table widget contents.
    ui->Tabla->setDisabled(false);
    // Clears all the LCD numbers.
    ui->show1->display(0.0);
    ui->show2->display(0.0);
    ui->show3->display(0.0);
    ui->show4->display(0.0);
    ui->showi->display(0.0);
    ui->Inicia->setDisabled(true);// Disables the start button.
    ui->Limpia->setDisabled(true);
    ui->Carga->setDisabled(false);// Enables the add button.
    ui->imax->setDisabled(true);
    ui->errora->setDisabled(true);
}

GauSei::~GauSei()
{
    delete ui;
}
