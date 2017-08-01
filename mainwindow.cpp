#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QCheckBox>
#include "yuvrender.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DataManager&  dm=  DataManager::get_instance();
 //   ui->mainToolBar->addWidget(new QPushButton ("123123"));
    ui->mainToolBar->addWidget(new QCheckBox("main stream"));
    ui->mainToolBar->addWidget(new QCheckBox("other stream"));

    render= new YuvRender();

    //center widget
    ui->centralWidget->setLayout(ui->horizontalLayout);
    ui->horizontalLayout->addWidget(render);
    ui->widget_info->setLayout(ui->gridLayout);

    ui->groupBox_1->setLayout(ui->verticalLayout);
    ui->widget_info->setFixedWidth(400);

    connect(&add_road_dialog,SIGNAL(ok_clicked(QString)),this,SLOT(add_road(QString)));
 //   ui->treeView_devices->setContextMenuPolicy(Qt::CustomContextMenu);
//     connect(ui->treeView_devices,SIGNAL(customContextMenuRequested(const QPoint & )),this,SLOT(on_right_button_click(  QPoint &)));

 //   ui->label->setBuddy(ui->pushButton_7);





   // ui->horizontalLayout->addWidget(ui->widget);



//    ui->groupBox->setFixedHeight(300);

 //   ui->gridLayout->SetFixedSize
  //   QWidget *gridwidget=new QWidget();
   //  gridwidget->setLayout(ui->gridLayout);


  //   gridwidget->setFixedWidth(200);
    // render->setFixedWidth(123);

 /*
    ui->pushButton_3->setFixedWidth(22);
    ui->pushButton_2->setFixedWidth(22);
    ui->pushButton->setFixedWidth(22);
   */


     // ui->centralWidget->setFixedWidth(432);
 //    ui->centralWidget->setFixedWidth(123);
   //  this->setFixedWidth(321);
 //   ui->horizontalLayoutWidget->setFixedWidth(200);


  //  ui->groupBox->setLayout(ui->verticalLayout);


 //   ui->horizontalLayout->addLayout(ui->gridLayout);
 //   ui->horizontalLayout->addLayout(ui->);

//    QWidget *gridwidget=new QWidget();

//    gridwidget->setLayout(ui->gridLayout);


//    ui->horizontalLayout->addWidget(gridwidget);

 //  ui->horizontalLayout->addWidget(render);
//   ui->horizontalLayoutWidget->setFixedWidth(800);
    //

  //  ui->horizontalLayout->addLayout(ui->gridLayout);
   // ui->horizontalLayout->addWidget(render);


}

void MainWindow::update_devices()
{
    ui->treeView_devices->setModel(&tree_model);

}

MainWindow::~MainWindow()
{
    delete ui;
}
#include "dialogaddroad.h"
#include "client.h"
void MainWindow::on_pushButton_add_road_clicked()
{
  // add_road_dialog=new DialogAddRoad();
  // add_road_dialog->show();
    add_road_dialog.show();
    client *c=new client();
    c->request_msg();
}

void MainWindow::add_road(QString name)
{
      DataManager&  dm=  DataManager::get_instance();
      m_road rd;
      rd.device_num=0;
      rd.road_name=name;
      dm.roads.append(rd);

      ui->comboBox->addItem(rd.road_name);
    //  ui->comboBox->setCurrentIndex();

      QStandardItem *itm=new QStandardItem(name);
     // tree_model.appendRow(itm);
      QStandardItem *root=tree_model.invisibleRootItem();
      root->appendRow(itm);
//         QStandardItem itm1(name);
//       itm.appendRow(&itm1);
      update_devices();

}

void MainWindow::add_new_device_rst()
{

}

//void MainWindow::on_right_button_click(const QPoint &pos)
//{
//    qDebug()<<"right click";

//}

void MainWindow::on_treeView_devices_customContextMenuRequested(const QPoint &pos)
{

     model_index=ui->treeView_devices->indexAt(pos);

    QMenu *menu=new QMenu(ui->treeView_devices);
    QAction *newAct = new QAction( tr("&New device") ,menu);
    QAction *delAct = new QAction( tr("&Del this road") ,menu);
    connect(delAct, SIGNAL(triggered()), this, SLOT(del_road()));
    connect(newAct, SIGNAL(triggered()), this, SLOT(add_new_device()));
    menu->addAction(newAct);
    menu->addAction(delAct);

    menu->popup(QCursor::pos());

}

void MainWindow::add_new_device()
{
      qDebug()<<"adding new device";
    //  search_dialog.setParent(this);

 //     QDesktopWidget *pDesk = QApplication::desktop();

//       search_dialog.move((pDesk->width() - search_dialog.width()) / 2, (pDesk->height() - search_dialog.height()) / 2);
    search_dialog.show();

}

void MainWindow::del_road()
{
  qDebug()<<"deling this road ";
//  tree_model.removeRow(0,model_index);
//  tree_model.clear();
  tree_model.removeRow(model_index.row());
}
