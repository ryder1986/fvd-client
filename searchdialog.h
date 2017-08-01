#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QtNetwork>
namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0);
    ~SearchDialog();
    void search()
    {
        while(skt->hasPendingDatagrams()){

             datagram.resize((skt->pendingDatagramSize()));
             skt->readDatagram(datagram.data(),datagram.size());
             qDebug()<<"get"<<datagram.data();
        }
    }

private slots:
    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::SearchDialog *ui;
      QStandardItemModel *model;
      QUdpSocket *skt;
     QByteArray datagram;
};

#endif // SEARCHDIALOG_H
