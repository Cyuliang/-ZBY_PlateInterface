#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSharedPointer>
#include <QComboBox>
#include <QDateTime>
#include <QLabel>

#include "settingdialog.h"
#include "ice_plate.h"
#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ///
    /// \brief initMaineWindow 初始化窗口
    ///
    void initMaineWindow();

    ///
    /// \brief initCamera 初始化相机
    ///
    void initCamera();

    ///
    /// \brief loadParmenter 加载参数
    ///
    void loadParmenter();

private slots:
    ///
    /// \brief on_actionSetting_triggered 设置参数
    ///
    void on_actionSetting_triggered();

    ///
    /// \brief on_actionPreview_triggered 预览车牌相机
    ///
    void on_actionPreview_triggered();

    ///
    /// \brief on_plainTextEdit_textChanged 信息页面
    ///
    void on_plainTextEdit_textChanged();

    ///
    /// \brief on_actionCapture_triggered 软触发
    ///
    void on_actionCapture_triggered();

    ///
    /// \brief on_actionRestart_triggered 重启相机
    ///
    void on_actionRestart_triggered();

    ///
    /// \brief SlotMessage 相机日志信息
    /// \param msg
    ///
    void SlotMessage(QString msg);

    ///
    /// \brief SlotPlateConnect 相机链接状态
    /// \param address
    /// \param state
    ///
    void SlotPlateConnect(QString addr, bool state);

signals:
    ///
    /// \brief SignalLoginCamera 登录车牌相机
    /// \param address
    ///
    void SignalLoginCamera(QString address,uint32_t HWND);

    ///
    /// \brief SignalTrigger 软触发
    /// \param address
    ///
    void SignalTrigger(QString address);

    ///
    /// \brief SignalRestart 重启相机
    /// \param address
    ///
    void SignalRestart(QString address);

    ///
    /// \brief SignalPlateConnect 相机链接状态
    /// \param address
    /// \param state
    ///
    void SignalPlateConnect(QString address,bool state);

    ///
    /// \brief SignalPlateResults 车牌识别结果
    /// \param arr
    ///
    void SignalPlateResults(QString address,QByteArray arr);

    ///
    /// \brief SignalStartLink 链接到服务器,客户端模式
    ///
    void SignalStartLink();

private:
    Ui::MainWindow *ui;

    QComboBox *comBox;
    QLabel *control1,*control2;
    ICE_Plate *Plate;

    QMap<QString,TcpClient*> clientMap;

    QString address1,address2,tcpAddr1,tcpAddr2;
    int tcpPort1,tcpPort2;

    TcpClient *client1,*client2;

    ///
    /// \brief startTime 开始时间戳
    ///
    QString startTime;
};
#endif // MAINWINDOW_H
