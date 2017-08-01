#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QStandardItemModel>
SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
    model=NULL;
    skt=new QUdpSocket(this);
    skt->bind(45454,QUdpSocket::ShareAddress);
  //  this->setLayout(ui->gridLayout);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_pushButton_clicked()
{

    if(model==NULL)
    model=new QStandardItemModel();

    model->clear();
   //  QList <QString *>list;
   QString header_str("ip,mask,broadcast");
   QStringList header_list=header_str.simplified().split(",");
 //  list.append(
//    list.append("ip");
//    list.append("port");
//    list.append("path");
    datagram.clear();
    search();
    if(datagram.size()>0){
     QString str=QString::fromStdString(datagram.toStdString());
    QStringList  str_list=str.simplified().split(",");
    QString ip=str_list[0];
    QString mask=str_list[1];
    QString broad=str_list[2];
    model->setHorizontalHeaderLabels(header_list);

    QStandardItem *item_ip=new QStandardItem(ip);
    QStandardItem *item_port=new QStandardItem(mask);
    QStandardItem *item_path=new QStandardItem(broad);
    model->setItem(0,0,item_ip);
    model->setItem(0,1,item_port);
    model->setItem(0,2,item_path);


//   QStandardItem *item1=new QStandardItem("a");
//   QStandardItem *item2=new QStandardItem("b");
//   QStandardItem *item3=new QStandardItem("c");
//   QStandardItem *item4=new QStandardItem("d");
//   QList <QStandardItem *>list;
//   list.append(item3);
//   list.append(item4);
//    model->appendRow(item1);
//   model->appendRow(item2);
   // model->appendColumn(list);
 //  model->appendColumn(item4);
   ui->tableView->setModel(model);

}
}

void SearchDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug()<<"double click "<<index.row();
    this->hide();
}
