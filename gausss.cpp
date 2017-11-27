// Simple Gaussian Elimination Method Program V 1.1.0/ Programa del metodo de Eliminacion Gaussiana Simple V 1.1.0
// Version Notes: User interface presentation changed.
// "Agregar" slot optimization, now is easier save the values directly from the table widget.
// "Ejecutar" slot optimization, for high precision results.
// Warning added with instructions for the user, when the table have empty items.
#include "gausss.h"
#include "ui_gausss.h"
#include <QTableWidgetItem>// Class for allow the use of Table Widget items.
#include <QMessageBox>// Class for allow the use of Message box.

Gausss::Gausss(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gausss)
{
    ui->setupUi(this);
    setWindowTitle("Metodo de Eliminacion Gaussiana"); //Prints the method's name at window title.
    // Connections between push buttons and slots
    connect(ui->Inicia,SIGNAL(clicked()),this,SLOT(ejecutar())); //Button and slot for start the method.
    connect(ui->Limpia,SIGNAL(clicked()),this,SLOT(limpiar())); //Button and slot for clear the fields from user interface.
    connect(ui->Guarda,SIGNAL(clicked()),this,SLOT(agregar())); //Button for add items to the table.
    ui->Inicia->setDisabled(true);// Disables the start button till all items from table been added.
    ui->Limpia->setDisabled(true);// Disables the clear button.
}
void Gausss::agregar(){// This slot will save data from table widget to a matrix, when the user clicked the Add button.
    count=0;// This point counter starts from zero.
    for(i=0;i<4;i++){// This cycle analyzes rows
        for(j=0;j<5;j++){// This cycle analyzes columns.
            QTableWidgetItem* posicion=ui->Tabla->item(i,j);// Creates a temporal variable for take each item from table widget.
            if(!posicion){// If the table widget posicion isn't null (empty), the cycle continues.
                continue;
            }
            matriz[i][j]=posicion->text().toDouble();// Saves each item on a different matrix position.
            count++;// Sums one to point counter.
        }
    }
    for(i=4;i>=0;i--){// This cycle analyzes if the first row of the main matrix have zeros.
            if(matriz[0][i]==0){//If it haves zeros:
                // Exchanges row positions for the independent variables.
                ind1=matriz[0][4];// A temporal variable takes the value of first independent variable.
                ind2=matriz[i+1][4];// Another temporal variable takes the value of the next independent variable.
                for(j=0;j<4;j++){// This cycle exchanges row positions for the x variables.
                    tempo[j]=matriz[0][j];// A temporal matrix saves the first row.
                    tempo2[j]=matriz[i+1][j];// Another temporal matrix saves the next row.
                    matriz[i+1][j]=tempo[j];// Puts the first row on the next row.
                    matriz[0][j]=tempo2[j];// Puts the next row on the first row.
                    matriz[i+1][4]=ind1;// Puts the first independent variable on next row.
                    matriz[0][4]=ind2;// Puts the next variable on previous row.
                }
            }
        }
    if(count==20){// If the point counter is equal than 20:
        ui->Inicia->setDisabled(false);//Enables the Start button.
        ui->Guarda->setDisabled(true);// Disables the Add button.
        ui->Tabla->setDisabled(true);// Disables the table widget.
    }
    else{// If the point counter is lower than 20:
        ui->Inicia->setDisabled(true);// Keeps disabled the Start button.
        ui->Guarda->setDisabled(false);// Keeps enabled the Add button.
        ui->Tabla->setDisabled(false);// Keeps enabled the table widget.
        //Shows a warning.
        QMessageBox::warning(this,"Advertencia","Es necesario que llene la tabla con datos.\n(Para posiciones vacias agregue un cero).");
    }
    ui->Limpia->setDisabled(false);// Enables the Clear button.
}
void Gausss::ejecutar(){// This slot will starts the method, when the Start button been clicked after data introduction.
    double producto[4];// Creates a temporal array for save each "zero" product.
    // The method starts.
    for(k=0;k<3;k++){// This cycle turns to zero the matrix positions below the main diagonal.
        for(i=k+1;i<4;i++){// This cycle analyzes rows.
            producto[i]=matriz[i][k]/matriz[k][k];// Calculates each product for turn to zero the mentioned positions.
            for(j=0;j<6;j++){// This cycle analyzes columns.
                matriz[i][j]=matriz[i][j]-(matriz[k][j]*producto[i]);// Calcuates the new matrix value for each position.
            }
        }
    }
    x4=(matriz[3][4]/matriz[3][3]);//Finds the x4 value.
    x3=(matriz[2][4]-(matriz[2][3]*x4))/(matriz[2][2]);//Finds the x3 value, with the previous variable.
    //Finds the x2 variable, with the two previous variables.
    x2=(matriz[1][4]-(matriz[1][3]*x4)-(matriz[1][2]*x3))/(matriz[1][1]);
    //Finds the x1 value, with the three previous variables.
    x1=(matriz[0][4]-(matriz[0][3]*x4)-(matriz[0][2]*x3)-(matriz[0][1]*x2))/(matriz[0][0]);
    //Show all the found values, on a independent LCD number.
    ui->show1->display(x1);
    ui->show2->display(x2);
    ui->show3->display(x3);
    ui->show4->display(x4);
}
void Gausss::limpiar(){
    ui->Tabla->clearContents();// Clears the table widget contents.
    // Clears all the LCD numbers.
    ui->show1->display(0.0);
    ui->show2->display(0.0);
    ui->show3->display(0.0);
    ui->show4->display(0.0);
    ui->Inicia->setDisabled(true);// Disables the start button.
    ui->Limpia->setDisabled(true);
    ui->Guarda->setDisabled(false);// Enables the add button.
    ui->Tabla->setDisabled(false);
}

Gausss::~Gausss()
{
    delete ui;
}
