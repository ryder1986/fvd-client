#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QMessageBox>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
class client : public QObject
{
    Q_OBJECT
public:
    explicit client(QObject *parent = 0);
    void read_msg()
    {
//        in.setDevice(tcpSocket);
//        in.setVersion(QDataStream::Qt_4_0);
//        in.startTransaction();

       static  char buf[100];

    //    int len=3;
      //  in.readBytes(buf,len);
  int ret=  in.readRawData((char *)buf,3);
     //   int ret=  in.readBytes((char &)buf,len);

       // QString nextFortune;
        //in >> nextFortune;
       qDebug()<<QString::fromRawData((QChar *)buf,3);
//        if (!in.commitTransaction())
//            return;

    }
signals:

public slots:
    void request_msg()
    {
        tcpSocket->connectToHost("192.168.1.216",12345);
    }



    void  displayError(QAbstractSocket::SocketError socketError)
    {
        switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
            break;
        case QAbstractSocket::HostNotFoundError:
       qDebug()<<"1";
            break;
        case QAbstractSocket::ConnectionRefusedError:
       qDebug()<<"1";
            break;
        default:
           qDebug()<<"1";
        }

      //  getFortuneButton->setEnabled(true);
    }

private:
    QTcpSocket *tcpSocket;
        QDataStream in;
        QFile *f;
};

#endif // CLIENT_H
