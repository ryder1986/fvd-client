#include "dialogaddroad.h"
#include "ui_dialogaddroad.h"
#include <QDebug>
DialogAddRoad::DialogAddRoad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddRoad)
{
    ui->setupUi(this);
}

DialogAddRoad::~DialogAddRoad()
{
    delete ui;
}



void DialogAddRoad::on_buttonBox_accepted()
{
   //  qDebug()<<ui->lineEdit->text();
     emit ok_clicked(ui->lineEdit->text());

}
//void DialogAddRoad::ok_clicked(QString roadname)
//{
//     qDebug()<<ui->lineEdit->text();

//}
