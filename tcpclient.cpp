#include "tcpclient.h"

TcpClient::TcpClient(QObject *parent, QString address, int port):QTcpSocket(parent)
{
    this->setParent(parent);

    autoLink=true;
    isConnected=false;
    this->address=address;
    this->port=port;

    pTimerLinkState=new QTimer(this);
    pTimerAutoLink=new QTimer(this);

    connect(this,&QIODevice::readyRead,this,&TcpClient::receiveDataSlot);
    connect(this,&QAbstractSocket::connected,this,&TcpClient::connectedSlot);
    connect(this,&QAbstractSocket::disconnected,this,&TcpClient::disconnectedSlot);
    connect(this,QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),this,&TcpClient::displayErrorSlot);
    connect(pTimerAutoLink,&QTimer::timeout,this,&TcpClient::startLinkSlot);
    connect(pTimerLinkState,&QTimer::timeout,this,&TcpClient::heartbeatSlot);

    pTimerAutoLink->start(15000);
    pTimerLinkState->start(10000);
}

void TcpClient::startLinkSlot()
{
    if(!isConnected && autoLink){
        this->close();
        this->abort();
        this->connectToHost("127.0.0.1",port);
    }
}

void TcpClient::heartbeatSlot()
{
    if(this->isOpen()){
        this->write("[H]");/* 心跳包数据 */
    }
}

void TcpClient::connectedSlot()
{
    isConnected=true;

    if(!pTimerLinkState->isActive()){
        pTimerLinkState->start(15000);
    }

    emit SignalPlateConnect(address,isConnected);
}

void TcpClient::receiveDataSlot()
{
    /*****************************
    * @brief:服务器主动取结果
    ******************************/
    QByteArray buf=readAll();
    if(buf.trimmed().startsWith("[Capture]")){
        emit SIgnalSimulationCapture(address);
    }
    buf.clear();
}

void TcpClient::disconnectedSlot()
{
    isConnected=false;
    emit SignalPlateConnect(address,isConnected);
}

void TcpClient::displayErrorSlot(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)

    isConnected=false;

    emit SignalPlateConnect(address,isConnected);
}

void TcpClient::SlotPlateConnect(QString addr,bool state)
{
    if(address!=addr){
        return;
    }

    if(state){
        autoLink=true;
    }
    else {
        this->close();
        this->abort();

        isConnected=false;
        autoLink=false;
    }
}

void TcpClient::SlotPlateResults(QString addr,QByteArray arr)
{
    if(address!=addr){
        return;
    }

    if(this->isOpen()){
         this->write(arr);
    }
}
