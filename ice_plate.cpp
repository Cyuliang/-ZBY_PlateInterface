#include "ice_plate.h"

ICE_Plate *ICE_Plate::pThis=nullptr;

ICE_Plate::ICE_Plate(QObject *parent)
{
    this->setParent(parent);

    ICE_Plate::pThis=this;

    autoLink=new QTimer(this);
    connect(autoLink,&QTimer::timeout,this,&ICE_Plate::slotAutoLink);
    autoLink->start(10000);

    handle=0;

    ICE_IPCSDK_Init();
    ICE_IPCSDK_SetDeviceEventCallBack(handle,ICE_IPCSDK_OnDeviceEvent_call,&param);
}

ICE_Plate::~ICE_Plate()
{
    ICE_IPCSDK_Fini();
}

void ICE_Plate::ICE_IPCSDK_OnDeviceEvent_call(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, ICE_U32 u32EventData1, ICE_U32 u32EventData2, ICE_U32 u32EventData3, ICE_U32 u32EventData4)
{
    Q_UNUSED(pvParam)
    Q_UNUSED(u32EventData1)
    Q_UNUSED(u32EventData2)
    Q_UNUSED(u32EventData3)
    Q_UNUSED(u32EventData4)

    QString event="";
    if(u32EventType==0){
        /*****************************
        * @brief:相机离线
        ******************************/
        event="Camera offline";
    }
    if(u32EventType==1){
        /*****************************
        * @brief:相机在线
        ******************************/
        event="Camera online";
    }

    emit pThis->SignalPlateConnect(QString::fromLocal8Bit(static_cast<const char*>(pcIP)),u32EventType);

    if(u32EventType==2){
        /*****************************
        * @brief:相机IO输出
        ******************************/
        event="IO output";
    }
    emit pThis->SignalMessage(QString("camera:%1 event[%2]").arg(QString::fromLocal8Bit(static_cast<const char*>(pcIP)),event));
}

void ICE_Plate::ICE_IPCSDK_OnPlate_call(void *pvParam, const ICE_CHAR *pcIP, const ICE_CHAR *pcNumber, const ICE_CHAR *pcColor, ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *pcCloseUpPicData, ICE_U32 u32CloseUpPicLen, ICE_S16 s16Speed, ICE_S16 s16VehicleType, ICE_S16 s16FalsePlate, ICE_S16 s16Reserved2, ICE_FLOAT fPlateConfidence, ICE_U32 u32VehicleColor, ICE_U32 u32PlateType, ICE_U32 u32VehicleDir, ICE_U32 u32AlarmType, ICE_U32 u32SerialNum, ICE_U32 uCapTime, ICE_U32 u32ResultHigh, ICE_U32 u32ResultLow)
{
    Q_UNUSED(pvParam)
    Q_UNUSED(pcCloseUpPicData)
    Q_UNUSED(u32CloseUpPicLen)
    Q_UNUSED(s16Speed)
    Q_UNUSED(s16VehicleType)
    Q_UNUSED(s16FalsePlate)
    Q_UNUSED(s16Reserved2)
    Q_UNUSED(fPlateConfidence)
    Q_UNUSED(u32VehicleColor)
    Q_UNUSED(u32PlateType)
    Q_UNUSED(u32VehicleDir)
    Q_UNUSED(u32AlarmType)
    Q_UNUSED(u32SerialNum)
    Q_UNUSED(uCapTime)
    Q_UNUSED(u32ResultHigh)
    Q_UNUSED(u32ResultLow)

    emit pThis->SignalMessage(QString("camera:%1 Trigger recognition result[%2|%3]").arg(QString::fromLocal8Bit(static_cast<const char*>(pcIP)),QString::fromLocal8Bit(static_cast<const char*>(pcNumber)),QString::fromLocal8Bit(static_cast<const char*>(pcColor))));

    QString time=QDateTime::currentDateTime().toString("yyyyMMddhhmmss");

    QByteArray arrImg(reinterpret_cast<const char*>(pcPicData),u32PicLen);

    QPixmap pix;
    pix.loadFromData(arrImg);
    pix.save(QString("c:\\tmp\\%1.jpg").arg(time));


    QString tmpData = QString("[U|%1|%2|%3|%4]").arg(QString::number(0),time,QString::fromLocal8Bit(static_cast<const char*>(pcNumber)),QString::fromLocal8Bit(static_cast<const char*>(pcColor)));
    QByteArray tmpArr=tmpData.toLocal8Bit();
    //arrImg=tmpArr.append(arrImg);

    emit pThis->SignalPlateResults(QString::fromLocal8Bit(static_cast<const char*>(pcIP)),tmpArr);

    tmpArr.clear();
    arrImg.clear();
}

void ICE_Plate::loginCamera(QString address,uint32_t HWND)
{
    handle = ICE_IPCSDK_OpenPreview(address.toLatin1().data(),1,0,HWND,ICE_IPCSDK_OnPlate_call,nullptr);
    if(handle!=nullptr){
        emit SignalMessage(QString("camera:%1 License plate camera link successful").arg(address));

        HandleMap.insert(address,handle);
        loginFaildeMap.remove(address);
    }
    else {
        emit SignalMessage(QString("camera:%1 License plate camera link error").arg(address));
        loginFaildeMap.insert(address,HWND);
    }
}

void ICE_Plate::slotAutoLink()
{
    foreach(QString address,loginFaildeMap.keys()){
        QtConcurrent::run(this,&ICE_Plate::loginCamera,address,loginFaildeMap.value(address));
    }
}

void ICE_Plate::SlotLoginCamera(QString address,uint32_t HWND)
{
    QtConcurrent::run(this,&ICE_Plate::loginCamera,address,HWND);
}

void ICE_Plate::SlotTrigger(QString address)
{
    if(ICE_IPCSDK_TriggerExt(HandleMap.value(address))==1){
        emit SignalMessage(QString("camera:%1 Trigger recognition sucessful").arg(address));
    }
    else {
        emit SignalMessage(QString("camera:%1 Trigger recognition failde").arg(address));
    }
}

void ICE_Plate::SlotRestart(QString address)
{
    if(ICE_IPCSDK_Reboot(HandleMap.value(address))==1){
        emit SignalMessage(QString("camera:%1 Restart  sucessful").arg(address));
    }
    else {
        emit SignalMessage(QString("camera:%1 Restart failde").arg(address));
    }
}

void ICE_Plate::SlotSimulationCapture(QString addr)
{
    if(ICE_IPCSDK_TriggerExt(HandleMap.value(addr))==1){
        emit SignalMessage(QString("camera:%1 Trigger recognition sucessful").arg(addr));
    }
    else {
        emit SignalMessage(QString("camera:%1 Trigger recognition failde").arg(addr));
    }

}
