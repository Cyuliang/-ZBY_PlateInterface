#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTimer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>

class TcpClient:public QTcpSocket
{
    Q_OBJECT

public:
    TcpClient(QObject *parent,QString address,int port);

private:

    ///
    /// \brief isConnected 客户端链接状态
    ///
    bool isConnected;

    ///
    /// \brief address 地址
    ///
    QString address;

    ///
    /// \brief port 端口
    ///
    quint16 port;

    ///
    /// \brief autoLink 是否启动自动链接
    ///
    bool autoLink;

    /// \brief pTimerAutoLink 定时自动链接
    ///
    QTimer *pTimerAutoLink;

    ///
    /// \brief pTimerLinkState 定时心跳包检测
    ///
    QTimer *pTimerLinkState;

private slots:

    ///
    /// \brief connectedSlot 链接成功
    ///
    void connectedSlot();

    ///
    /// \brief receiveDataSlot 接收数据
    ///
    void receiveDataSlot();

    ///
    /// \brief disconnectedSlot 链接断开
    ///
    void disconnectedSlot();

    ///
    /// \brief displayErrorSlot 链接错误
    /// \param socketError 链接状态码
    ///
    void displayErrorSlot(QAbstractSocket::SocketError socketError);

    ///
    /// \brief heartbeatSlot 检查链接状态
    ///
    void heartbeatSlot();

public slots:

    ///
    /// \brief startLinkSlot 链接到服务器,客户端模式
    ///
    void startLinkSlot();

    ///
    /// \brief SlotPlateConnect 相机链接状态
    /// \param address
    /// \param state
    ///
    void SlotPlateConnect(QString addr, bool state);

    ///
    /// \brief SlotPlateResults 车牌识别结果
    /// \param arr
    ///
    void SlotPlateResults(QString addr, QByteArray arr);

signals:

    ///
    /// \brief SignalPlateConnect 链接状态
    /// \param address
    /// \param state
    ///
    void SignalPlateConnect(QString address,bool state);

    ///
    /// \brief SignalMessage 相机日志信息
    /// \param msg
    ///
    void SignalMessage(QString msg);

    ///
    /// \brief SIgnalSimulationCapture 模拟抓拍
    ///
    void SIgnalSimulationCapture(QString address);

};

#endif // TCPCLIENT_H
