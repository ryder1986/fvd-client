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
#if 0
    void read_msg()
    {
        qDebug()<<"reading msg";
//        in.setDevice(tcpSocket);
//       bool ok= tcpSocket->open(QIODevice::ReadOnly);
//       if(ok==false)
//           return ;
//        in.setVersion(QDataStream::Qt_4_0);
       QString s= QString("123456789");
        //    int ret=in.readRawData(bf,1000);
        quint16 size=0;
        in>>size;
        QString str;
        in>>str;
        qDebug()<<"get"<<str;
//    char buf[100];
//    memset(buf,0,100);
//       QByteArray ba;
//       ba.resize(100);
//       int sz=ba.size();
//        ba=tcpSocket->readAll();
//       sz=ba.size();
//       ba.remove(0,6);
//       static char buf[100];
//       memcpy(buf,ba,10);
//       memcpy(buf,(void *)&s,10);
//       QString str=QString(ba);
//       qDebug()<<str;
    }
#endif
#if 0
    void read_msg()
    {
        qDebug()<<"reading msg";
//        in.setDevice(tcpSocket);
//       bool ok= tcpSocket->open(QIODevice::ReadOnly);
//       if(ok==false)
//           return ;
//        in.setVersion(QDataStream::Qt_4_0);

        //    int ret=in.readRawData(bf,1000);
//        quint16 size=0;
//        in>>size;
//        QString str;
//        in>>str;
//        qDebug()<<"get"<<str;
//    char buf[100];
//    memset(buf,0,100);
         QByteArray ba;
//       ba.resize(100);
//       int sz=ba.size();
         ba=tcpSocket->readAll();
         QString str=QString(ba);
         qDebug()<<str;
//       sz=ba.size();
//       ba.remove(0,6);
//       static char buf[100];
//       memcpy(buf,ba,10);
//       memcpy(buf,(void *)&s,10);
//       QString str=QString(ba);
//       qDebug()<<str;
    }
#endif
#if 1
    void read_msg()
    {
        qDebug()<<"reading msg";
//        in.setDevice(tcpSocket);
//       bool ok= tcpSocket->open(QIODevice::ReadOnly);
//       if(ok==false)
//           return ;
//        in.setVersion(QDataStream::Qt_4_0);

        //    int ret=in.readRawData(bf,1000);
//        quint16 size=0;
//        in>>size;
//        QString str;
//        in>>str;
//        qDebug()<<"get"<<str;
//    char buf[100];
//    memset(buf,0,100);
         QByteArray ba;
//       ba.resize(100);
//       int sz=ba.size();
         ba=tcpSocket->read(sizeof(quint16));
         int len=ba.toInt();
      //   QString str=QString(ba);
       //  qDebug()<<str;
         ba=tcpSocket->read(len);
//           str=QString(ba);
//         qDebug()<<str;
         msg_read=ba;

//       sz=ba.size();
//       ba.remove(0,6);
//       static char buf[100];
//       memcpy(buf,ba,10);
//       memcpy(buf,(void *)&s,10);
//       QString str=QString(ba);
//       qDebug()<<str;
    }
#endif
signals:

public slots:
    void request_msg()
    {
        qDebug()<<"ask for msg";
        tcpSocket->connectToHost("192.168.1.216",12345);

    }

    void request_msg(QByteArray b)
    {
        qDebug()<<"ask for msg";

        tcpSocket->connectToHost("192.168.1.216",12345);
          if(tcpSocket->waitForConnected(1000))
              tcpSocket->write(b);
          else
              qDebug()<<QString("err in connecting");
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
        char bf[1000];
        QByteArray msg_read;
};

#endif // CLIENT_H
