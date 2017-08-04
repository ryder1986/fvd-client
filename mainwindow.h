#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "datamanager.h"
#include "dialogaddroad.h"
#include <qstandarditemmodel.h>
#include "searchdialog.h"
namespace Ui {
class MainWindow;
}
class YuvRender;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void update_devices();
    ~MainWindow();

private slots:
    void on_pushButton_add_road_clicked();
    void add_road(QString );
    void add_new_device_rst();
//    void on_right_button_click(const QPoint &pos);
    void on_treeView_devices_customContextMenuRequested(const QPoint &pos);
    void test(){
        qDebug()<<"test  slot";
    }
    void add_new_device();
    void del_road();
    void on_treeView_devices_doubleClicked(const QModelIndex &index);
    void update_yuv();
private:
    YuvRender *render;
    Ui::MainWindow *ui;
    QStandardItemModel tree_model;
   DialogAddRoad add_road_dialog;
      QModelIndex model_index;
      SearchDialog search_dialog;
      QTimer *timer;

};

#endif // MAINWINDOW_H
