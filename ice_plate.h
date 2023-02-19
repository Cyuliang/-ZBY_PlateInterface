#ifndef ICE_PLATE_H
#define ICE_PLATE_H

#include <QObject>
#include <QDebug>
#include <QtConcurrent>
#include <QTimer>
#include <QDateTime>
#include <QPixmap>

#include "ice_ipcsdk.h"

class ICE_Plate:public QObject
{
    Q_OBJECT

public:
    ICE_Plate(QObject *parent=nullptr);
    ~ICE_Plate();

private:

    /*****************************
    * @brief:.相机连接回调
    * 参数：
    1. 相 机 连 接 回 调 参 数 ， 用 于 区 分 不 同 相 机 连 接 事 件 （ 输 出 ，
    ICE_IPCSDK_SetDeviceEventCallBack 传入的最后一个参数）
    2.相机 ip（输出）
    3.事件类型 0：离线 1：在线 2：IO 变化（输出）
    4.事件数据 1（事件类型为 0 或者 1 时，代表回调句柄;事件类型为 2 时，代表 IO1 的状态;）
    （输出）
    5.事件数据 2（事件类型为 2 时，代表 IO2 的状态）（输出）
    6.事件数据 3（事件类型为 2 时，代表 IO3 的状态）（输出）
    7.事件数据 4（事件类型为 2 时，代表 IO4 的状态）（输出）

    ******************************/
    static void  ICE_IPCSDK_OnDeviceEvent_call(
    void *pvParam,
    const ICE_CHAR *pcIP,
    ICE_U32 u32EventType,
    ICE_U32 u32EventData1,
    ICE_U32 u32EventData2,
    ICE_U32 u32EventData3,
    ICE_U32 u32EventData4);

    /*****************************
    * @brief:识别结果回调函数
    ******************************/
    static void ICE_IPCSDK_OnPlate_call(
    void *pvParam,
    const ICE_CHAR *pcIP,
    const ICE_CHAR *pcNumber,
    const ICE_CHAR *pcColor,
    ICE_CHAR *pcPicData,
    ICE_U32 u32PicLen,
    ICE_CHAR *pcCloseUpPicData,
    ICE_U32 u32CloseUpPicLen,
    ICE_S16 s16Speed,
    ICE_S16 s16VehicleType,
    ICE_S16 s16FalsePlate,
    ICE_S16 s16Reserved2,
    ICE_FLOAT fPlateConfidence,
    ICE_U32 u32VehicleColor,
    ICE_U32 u32PlateType,
    ICE_U32 u32VehicleDir,
    ICE_U32 u32AlarmType,
    ICE_U32 u32SerialNum,
    ICE_U32 uCapTime,
    ICE_U32 u32ResultHigh,
    ICE_U32 u32ResultLow
    );


    ///
    /// \brief loginCamera 登录相机
    /// \param address
    /// \param HWND
    ///
    void loginCamera(QString address,uint32_t HWND);

private:
    static ICE_Plate *pThis;
    QTimer *autoLink;

    ICE_HANDLE handle;
    QMap<QString,ICE_HANDLE> HandleMap;

    QString param;
    QMap<QString,uint32_t> loginFaildeMap;

private slots:

    ///
    /// \brief slotAutoLink 自动重连
    ///
    void slotAutoLink();

public slots:

    ///
    /// \brief SlotLoginCamera 登录车牌相机
    /// \param address
    /// \return
    ///
    void SlotLoginCamera(QString address,uint32_t HWND);

    ///
    /// \brief SlotTrigger 软触发
    /// \param address
    ///
    void SlotTrigger(QString address);

    ///
    /// \brief SlotRestart 重启相机
    /// \param address
    ///
    void SlotRestart(QString address);

    ///
    /// \brief SlotSimulationCapture 模拟抓拍
    ///
    void SlotSimulationCapture(QString addr);

signals:

    ///
    /// \brief SignalMessage 相机日志信息
    /// \param msg
    ///
    void SignalMessage(QString msg);

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
};

#endif // ICE_PLATE_H
