#include "client.h"
#include <qglobal.h>
client::client(QObject *parent) : QObject(parent)
{
    tcpSocket=new QTcpSocket();

    connect(tcpSocket, &QIODevice::readyRead, this, &client::read_msg);
  //  f->open(tcpSocket,QFile::ReadOnly);

    in.setDevice(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
//! [2] //! [4]
 //   connect(tcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),  this, &client::displayError);
}

