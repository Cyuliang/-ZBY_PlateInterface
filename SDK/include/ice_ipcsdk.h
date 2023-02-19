#ifndef  ICE_IPCSDK__H_
#define  ICE_IPCSDK__H_

#include "ice_com_type.h"
#include "ice_base_type.h"
#include "ice_vd_config.h"
/*#include "ice_clbr_config.h"
#include "ice_dtca_config.h"
#include "ice_tcnt_interface.h"
#include "ice_hcnt_config.h"
#include "ice_ipg_config.h"*/
#include "ice_vdc_config.h"
#include "ice_vdc_result.h"
#include "ice_vlpr_result.h"
#include "ice_comdef.h"
#include <time.h>

//下面2种调用约定方式，只能二选一
//#define ICE_IPCSDK_TYPE _stdcall //少量客户在用，如VB6调用DLL开发
#define ICE_IPCSDK_TYPE _cdecl   //默认开启，大多数客户在用

#ifdef ICE_IPCSDK_EXPORTS
#define ICE_IPCSDK_API __declspec(dllexport) 
#else
#define ICE_IPCSDK_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
#define USEUPDATE        1    //打包给demo使用放开升级接口  1demo要  0 ocx不要    
#define USE_FFMPEG		 1    //  0 ocx不要
//#define WIN32_SAVE_JPG        //抓流 保存jpg 32位采用
//#define TEST_TOOL         // 去掉时间同步

/**
* @brief  相机事件枚举类型
*/
typedef enum
{
	ICE_DEVICE_OFFLINE,		//离线
	ICE_DEVICE_ONLINE,		//在线
	ICE_DEVICE_IO_CHANGED			//IO状态改变
} ICE_DEVICE_EVENT_TYPE;

typedef enum
{
	ICE_PORT_BASICSETTING,	//基本设置端口
	ICE_PORT_OFFLINEPAY		//脱机计费设置端口
}E_ICEPORT;

/**
*  @brief  网络流回调接口，当网络上有数据时，sdk会回调该接口
*  @param  [OUT] pvParam        为用户自定义参数，用来区分不同的sdk使用者，类似于线程入口函数的参数
*  @param  [OUT] u8PayloadType  为payload类型，取值为上面所定义的宏
*  @param  [OUT] u32Timestamp   为时间戳
*  @param  [OUT] pvData         为收到的数据地址
*  @param  [OUT] s32Len         为收到的数据长度
*/
typedef void (__stdcall * ICE_IPCSDK_OnStream)(void *pvParam, 
	ICE_U8 u8PayloadType, ICE_U32 u32Timestamp, 
	void *pvData, ICE_S32 s32Len);


/**
*  @brief  图像帧回调接口，当解码出一帧图像时，sdk会回调该接口
*  @param  [OUT] pvParam        为用户自定义参数，用来区分不同的sdk使用者，类似于线程入口函数的参数
*  @param  [OUT] u32Timestamp   为时间戳
*  @param  [OUT] pu8Data        为图像数据地址数组，分别存放y，u和v
*  @param  [OUT] s32Linesize    为每扫描行数据长度数组，分别存放y，u和v的每扫描行长度
*  @param  [OUT] s32Width       为图像宽度
*  @param  [OUT] s32Height      为图像高度
*/
typedef void (__stdcall * ICE_IPCSDK_OnFrame)(
	void *pvParam, ICE_U32 u32Timestamp, 
	ICE_U8 *pu8Data[], ICE_S32 s32Linesize[], 
	ICE_S32 s32Width, ICE_S32 s32Height, 
	ICE_U8 *rawdata, ICE_S32 rawlen);

/**
*  @brief  脱机计费规则 回调上报数据
*  @param  [OUT] pvParam        为用户自定义参数，用来区分不同的sdk使用者，类似于线程入口函数的参数
*/
typedef void (__stdcall * ICE_IPCSDK_Payrule)(void *param, ICE_U32 type, void *data, ICE_U32 len);

/*#define REQ_TYPE_H264 0x01	//请求h264码流
#define REQ_TYPE_JPEG 0x02	//请求抓拍图像
#define REQ_TYPE_ALGO 0x04	//请求算法数据*/

/**
*  @brief  全局初始化
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Init();
/**
*  @brief  全局释放
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Fini();

/**
*  @brief  连接ipc相机接口
*  @param  [IN] pcIP                相机ip地址
*  @param  [IN] u8OverTCP           是否使用tcp模式(1为使用，0为不使用）
*  @param  [IN] u16RTSPPort         rtsp端口（554）
*  @param  [IN] u16ICEPort          私有协议对应的端口（8117）
*  @param  [IN] u16OnvifPort        onvif端口（8080）
*  @param  [IN] u8MainStream        是否请求主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] pfOnStream          网络流回调地址，可以为NULL
*  @param  [IN] pvStreamParam       网络流回调参数，能区分开不同的使用者即可
*  @param  [IN] pfOnFrame           图像帧回调地址，可以为NULL，只有当u8ReqType包含了REQ_TYPE_H264时才有意义
*  @param  [IN] pvFrameParam        图像帧回调参数，能区分开不同的使用者即可
*  @return sdk句柄(连接不成功时,返回值为null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_Open(const ICE_CHAR *pcIP, ICE_U8 u8OverTCP, 
	ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, ICE_U16 u16OnvifPort, ICE_U8 u8MainStream, 
	ICE_IPCSDK_OnStream pfOnStream, void *pvStreamParam, 
	ICE_IPCSDK_OnFrame pfOnFrame, void *pvFrameParam);

/**
*  @brief  连接相机（使用密码连接）
*  @param  [IN] pcIP                  相机ip地址
*  @param  [IN] pcPasswd              连接密码
*  @param  [IN] u8OverTCP             是否使用tcp模式(1为使用，0为不使用）
*  @param  [IN] u16RTSPPort           rtsp端口(554)
*  @param  [IN] u16ICEPort            私有协议对应的端口(8117)
*  @param  [IN] u16OnvifPort          onvif端口（8080）
*  @param  [IN] u8MainStream          是否请求主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] pfOnStream            网络流回调地址，可以为NULL
*  @param  [IN] pvStreamParam         网络流回调参数，能区分开不同的使用者即可
*  @param  [IN] pfOnFrame             图像帧回调地址，可以为NULL，只有当u8ReqType包含了REQ_TYPE_H264时才有意义
*  @param  [IN] pvFrameParam          图像帧回调参数，能区分开不同的使用者即可
*  @return sdk句柄(连接不成功时,返回值为null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_Open_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
	ICE_U8 u8OverTCP, ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
	ICE_U16 u16OnvifPort, ICE_U8 u8MainStream, 
	ICE_IPCSDK_OnStream pfOnStream, void *pvStreamParam, 
	ICE_IPCSDK_OnFrame pfOnFrame, void *pvFrameParam);


ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_Open_Passwd_Ex(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
												 ICE_U8 u8OverTCP, 
												 ICE_U16 u16RTSPPort=554, 
												 ICE_U16 u16ICEPort=8117, 
												 ICE_U16 u16OnvifPort=8080, 
												 ICE_U16 u16ProxyPort23=23,
												 ICE_U16 u16ProxyPort69=69,
												 ICE_U16 u16ProxyPort80=80,
												 ICE_U16 u16ProxyPort8000=8000,
												 ICE_U16 u16ProxyPort8200=8200,
												 ICE_U16 u16ProxyPort8227=8227,
												 ICE_U16 u16ProxyPort8300=8300,
												 ICE_U8 u8MainStream=1, 
												 ICE_IPCSDK_OnStream pfOnStream=NULL, void *pvStreamParam=NULL, 
												 ICE_IPCSDK_OnFrame pfOnFrame=NULL, void *pvFrameParam=NULL);

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_Open_Passwd_Ex2(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
																	ICE_U8 u8OverTCP, 
																	ICE_U16 u16RTSPPort=554, 
																	ICE_U16 u16ICEPort=8117, 
																	ICE_U16 u16OnvifPort=8080, 
																	ICE_U16 u16ProxyPort23=23,
																	ICE_U16 u16ProxyPort69=69,
																	ICE_U16 u16ProxyPort80=80,
																	ICE_U16 u16ProxyPort8000=8000,
																	ICE_U16 u16ProxyPort8200=8200,
																	ICE_U16 u16ProxyPort8227=8227,
																	ICE_U16 u16ProxyPort8300=8300,
																	ICE_U8 u8MainStream=1, 
																	ICE_IPCSDK_OnStream pfOnStream=NULL, void *pvStreamParam=NULL, 
																	ICE_IPCSDK_OnFrame pfOnFrame=NULL, void *pvFrameParam=NULL);

/**
*  @brief  抓拍数据回调接口
*  @param  [OUT] pvParam                 回调参数，能区分开不同的使用者即可（open传入的最后一个参数）
*  @param  [OUT] pcIP                    相机ip
*  @param  [OUT] pcNumber                车牌号
*  @param  [OUT] pcColor                 车牌颜色）（"蓝色","黄色","白色","黑色",“绿色”）
*  @param  [OUT] pcPicData               全景数据
*  @param  [OUT] u32PicLen               全景数据长度
*  @param  [OUT] pcCloseUpPicData        车牌数据
*  @param  [OUT] u32CloseUpPicLen        车牌数据长度
*  @param  [OUT] s16Speed                速度
*  @param  [OUT] s16VehicleType          车辆类型
*  @param  [OUT] s16FalsePlate           虚假车牌
*  @param  [OUT] s16Reserved2            预留参数2
*  @param  [OUT] fPlateConfidence        车牌打分值 详解：SDK输出的范围大于IE界面设置的车牌阈值，上限是28，例如：IE设置的是10，范围：10-28
*                                                   作用：sdk输出的车牌打分值是用在双相机方案，sdk收到两个相机的车牌信息，可以通过车牌
*                                                   打分值来选择哪个信息更加可靠作为最终的输出结果
*  @param  [OUT] u32VehicleColor         车身颜色
*  @param  [OUT] u32PlateType            车牌类型
*  @param  [OUT] u32VehicleDir           车辆方向
*  @param  [OUT] u32AlarmType            报警类型
*  @param  [OUT] u32SerialNum            抓拍的序号（从相机第一次抓拍开始计数，相机重启后才清零）
*  @param  [OUT] uCapTime                实时抓拍时间，从1970年1月1日零点开始的秒数
*  @param  [OUT] u32ResultHigh           车牌识别数据结构体(ICE_VDC_PICTRUE_INFO_S)指针高8位
*  @param  [OUT] u32ResultLow            车牌识别数据结构体(ICE_VDC_PICTRUE_INFO_S)指针低8位
*/
typedef void (__stdcall * ICE_IPCSDK_OnPlate)(void *pvParam, const ICE_CHAR *pcIP, 
	const ICE_CHAR *pcNumber, const ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *pcCloseUpPicData, ICE_U32 u32CloseUpPicLen, 
	ICE_S16 s16Speed, ICE_S16 s16VehicleType, ICE_S16 s16FalsePlate, ICE_S16 s16Reserved2, 
	ICE_FLOAT fPlateConfidence, ICE_U32 u32VehicleColor, ICE_U32 u32PlateType, ICE_U32 u32VehicleDir, 
	ICE_U32 u32AlarmType, ICE_U32 u32SerialNum, ICE_U32 uCapTime, ICE_U32 u32ResultHigh, ICE_U32 u32ResultLow);

/**
*  @brief  抓拍数据回调接口
*  @param  [OUT] pvParam                 回调参数，能区分开不同的使用者即可（open传入的最后一个参数）
*  @param  [OUT] pcIP                    相机ip
*  @param  [OUT] pcNumber                车牌号
*  @param  [OUT] u32SerialNum            抓拍的序号（从相机第一次抓拍开始计数，相机重启后才清零）
*  @param  [OUT] uCapTime                实时抓拍时间，从1970年1月1日零点开始的秒数
*  @param  [OUT] ptSrv					 预留
*/
typedef void (__stdcall * ICE_IPCSDK_OnFastPlate)(void *pvParam, const ICE_CHAR *pcIP, 
											  const ICE_CHAR *pcNumber,  ICE_U32 u32SerialNum, ICE_U32 uCapTime, 
											  ICE_VDC_PICTRUE_INFO_S *ptSrv);


typedef void (*ICE_IPCSDK_OnPlate_Cdecl)(void *pvParam, const ICE_CHAR *pcIP, 
	const ICE_CHAR *pcNumber, const ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *pcCloseUpPicData, ICE_U32 u32CloseUpPicLen, 
	ICE_S16 s16PlatePosLeft, ICE_S16 s16PlatePosTop, ICE_S16 s16PlatePosRight, ICE_S16 s16PlatePosBottom, 
	ICE_FLOAT fPlateConfidence, ICE_U32 u32VehicleColor, ICE_U32 u32PlateType, ICE_U32 u32VehicleDir, 
	ICE_U32 u32AlarmType, ICE_U32 u32SerialNum, ICE_U32 u32Reserved2, ICE_U32 u32ResultHigh, ICE_U32 u32ResultLow);

/**
*  @brief  勾选虚假车牌过滤时，虚假车牌回调接口
*  @param  [OUT] pvParam                 回调参数，能区分开不同的使用者即可（ICE_IPCSDK_SetFlasePlateCallback传入的最后一个参数）
*  @param  [OUT] pcIP                    相机ip
*  @param  [OUT] pcPicData               全景数据
*  @param  [OUT] u32PicLen               全景数据长度
*  @param  [OUT] strPlateNum			 车牌号码
*  @param  [OUT] u32CapTime				 抓拍时间
*  @param  [OUT] strVehLogName           车款名称
*  @param  [OUT] strResrv1				 预留参数1
*  @param  [OUT] u32VehType				 车辆类型
*  @param  [OUT] u32Resrv2				 预留参数2
*  @param  [OUT] u32ResultHigh           车牌识别数据结构体(ICE_VDC_PICTRUE_INFO_S)指针高8位
*  @param  [OUT] u32ResultLow            车牌识别数据结构体(ICE_VDC_PICTRUE_INFO_S)指针低8位
*/
typedef void (__stdcall * ICE_IPCSDK_OnFlasePlate)(void *pvParam, const ICE_CHAR *pcIP, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *strResrv1, ICE_U32 u32Resrv1, 
	ICE_CHAR *strResrv2, ICE_CHAR *strResrv3, ICE_U32 u32Resrv2, ICE_U32 u32Resrv3, ICE_U32 u32ResultHigh, ICE_U32 u32ResultLow);

/**
*  @brief  视频接入
*  @param  [IN] pcIP                    相机ip
*  @param  [IN] u8OverTCP               是否使用tcp模式（1：使用tcp 0：不使用tcp，使用udp）
*  @param  [IN] u8MainStream            是否请求主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] hWnd                    预览视频的窗口句柄
*  @param  [IN] pfOnPlate               车牌回调
*  @param  [IN] pvPlateParam            车牌回调参数，能区分开不同的使用者即可
*  @return sdk句柄(连接不成功时,返回值为null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview(const ICE_CHAR *pcIP, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  视频接入
*  @param  [IN] pcDeveloperID			开发者ID
*  @param  [IN] pcKey					开发者Key
*  @param  [IN] pcSN					设备序列号
*  @param  [IN] u8OverTCP               是否使用tcp模式（1：使用tcp 0：不使用tcp，使用udp）
*  @param  [IN] u8MainStream            是否请求主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] hWnd                    预览视频的窗口句柄
*  @param  [IN] pfOnPlate               车牌回调
*  @param  [IN] pvPlateParam            车牌回调参数，能区分开不同的使用者即可
*  @return sdk句柄(连接不成功时,返回值为null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_P2P(const ICE_CHAR *pcDeveloperID, 
													 const ICE_CHAR *pcKey, 
													 const ICE_CHAR *pcSN, 
													 ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
													 ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  视频接入(使用密码连接)
*  @param  [IN] pcIP                    相机ip
*  @param  [IN] pcPasswd                连接密码
*  @param  [IN] u8OverTCP               是否使用tcp模式（1：使用tcp 0：不使用tcp，使用udp）
*  @param  [IN] u8MainStream            是否请求主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] hWnd                    预览视频的窗口句柄
*  @param  [IN] pfOnPlate               车牌回调
*  @param  [IN] pvPlateParam            车牌回调参数，能区分开不同的使用者即可
*  @return sdk句柄(连接不成功时,返回值为null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  视频接入(使用密码连接)
*  @param  [IN] pcDeveloperID			开发者ID
*  @param  [IN] pcKey					开发者Key
*  @param  [IN] pcSN					设备序列号
*  @param  [IN] pcPasswd                连接密码
*  @param  [IN] u8OverTCP               是否使用tcp模式（1：使用tcp 0：不使用tcp，使用udp）
*  @param  [IN] u8MainStream            是否请求主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] hWnd                    预览视频的窗口句柄
*  @param  [IN] pfOnPlate               车牌回调
*  @param  [IN] pvPlateParam            车牌回调参数，能区分开不同的使用者即可
*  @return sdk句柄(连接不成功时,返回值为null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_Passwd_P2P(const ICE_CHAR *pcDeveloperID, 
															const ICE_CHAR *pcKey, 
															const ICE_CHAR *pcSN,
															const ICE_CHAR *pcPasswd, 
															ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
														    ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  视频接入扩展接口
*  @param  [IN] pcIP                   相机ip
*  @param  [IN] u8OverTCP              是否使用tcp模式(1：使用tcp 0：不使用tcp，使用udp)
*  @param  [IN] u8MainStream           是否请求主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] hWnd                   预览视频的窗口句柄
*  @param  [IN] pfOnPlate              车牌回调
*  @param  [IN] pvPlateParam           车牌回调参数，能区分开不同的使用者即可
*  @param  [IN] u16RTSPPort            rtsp端口
*  @param  [IN] u16ICEPort             私有协议的端口
*  @param  [IN] u16OnvifPort           onvif端口
*  @param  [IN] u16EvtpPort            车牌私有协议端口
*  @return sdk句柄(连接不成功时,返回值为null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreviewExt(const ICE_CHAR *pcIP, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
	ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
	ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort);

/**
*  @brief  视频接入扩展接口（使用密码连接）
*  @param  [IN] pcIP                   相机ip
*  @param  [IN] pcPasswd               密码
*  @param  [IN] u8OverTCP              是否使用tcp模式(1：使用tcp 0：不使用tcp，使用udp)
*  @param  [IN] u8MainStream           是否请求主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] hWnd                   预览视频的窗口句柄
*  @param  [IN] pfOnPlate              车牌回调
*  @param  [IN] pvPlateParam           车牌回调参数，能区分开不同的使用者即可
*  @param  [IN] u16RTSPPort            rtsp端口
*  @param  [IN] u16ICEPort             私有协议的端口
*  @param  [IN] u16OnvifPort           onvif端口
*  @param  [IN] u16EvtpPort            车牌私有协议端口
*  @return sdk句柄(连接不成功时,返回值为null)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreviewExt_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
	ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
	ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort);

ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreviewExt_Passwd_P2P(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
														   ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
														   ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
														   ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
														   ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort,
														   const ICE_CHAR *pcSN,  
														   ICE_U16 u16ProxyPort23,
														   ICE_U16 u16ProxyPort69,
														   ICE_U16 u16ProxyPort80,
														   ICE_U16 u16ProxyPort8000,
														   ICE_U16 u16ProxyPort8300,
														   ICE_U16 u16ProxyPort8227);


ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_Cdecl(const ICE_CHAR *pcIP, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate_Cdecl pfOnPlate, void *pvPlateParam);
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_Cdecl_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate_Cdecl pfOnPlate, void *pvPlateParam);
/**
*  @brief  连接设备，不带视频流
*  @param  [IN] pcIP      ip地址
*  @return sdk句柄(连接不成功时,返回值为null) 
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice(const ICE_CHAR *pcIP);

/**
*  @brief  连接设备，不带视频流
*  @param  [IN] pcDeveloperID 开发者ID
*  @param  [IN] pcKey         开发者Key
*  @param  [IN] pcSN		  设备序列号
*  @return sdk句柄(连接不成功时,返回值为null) 
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN);

/**
*  @brief  连接设备，不带视频流(使用密码连接)
*  @param  [IN] pcIP      ip地址
*  @param  [IN] pcPasswd  连接密码
*  @return sdk句柄(连接不成功时,返回值为null) 
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd);

/**
*  @brief  连接设备，不带视频流(使用密码连接)
*  @param  [IN] pcDeveloperID 开发者ID
*  @param  [IN] pcKey         开发者Key
*  @param  [IN] pcSN		  设备序列号
*  @param  [IN] pcPasswd	  连接密码
*  @return sdk句柄(连接不成功时,返回值为null) 
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_Passwd_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN, const ICE_CHAR *pcPasswd);

/**
*  @brief  连接时只连接rtsp，不连接evtp(车牌识别数据不会上报)
*  @param  [IN] pcIP	        相机ip
*  @param  [IN] u8MainStream    是否请求主码流（1：主码流 0：子码流）
*  @param  [IN] hWnd            预览视频的窗口句柄
*  @return 失败时，返回null；成功时，返回sdk句柄（以视频流连接成功作为返回sdk句柄条件）
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDeviceEx(const ICE_CHAR *pcIP, ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  连接时只连接rtsp，不连接evtp(车牌识别数据不会上报)
*  @param  [IN] pcDeveloperID   开发者ID
*  @param  [IN] pcKey           开发者Key
*  @param  [IN] pcSN            相机SN
*  @param  [IN] u8MainStream    是否请求主码流（1：主码流 0：子码流）
*  @param  [IN] hWnd            预览视频的窗口句柄
*  @return 失败时，返回null；成功时，返回sdk句柄（以视频流连接成功作为返回sdk句柄条件）
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDeviceEx_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN, 
																	  ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  开始视频
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [IN] u8MainStream  是否为主码流（1：主码流 0：子码流, 3：双目第2路主码流, 2：双目第2路子码流）
*  @param  [IN] hWnd          视频播放窗口句柄
*  @return 1 连接视频流成功 0 连接视频流失败 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartStream(ICE_HANDLE hSDK, 
	ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  结束视频
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_StopStream(ICE_HANDLE hSDK);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetVideoWnd(ICE_HANDLE hSDK, ICE_U32 hWnd);

/**
*  @brief  设置网络流回调
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [IN] pfOnStream    网络流回调接口，当网络上有数据时，sdk会回调该接口
*　@param  [IN] pvParam       图像帧回调参数，能区分开不同的使用者即可
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetDataCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnStream pfOnStream, void *pvParam);

/**
*  @brief  软触发扩展接口
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @return 0 失败, 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TriggerExt(ICE_HANDLE hSDK);

/**
*  @brief  图像帧回调
*  @param  [OUT] pvParam              与ICE_IPCSDK_SetFrameCallback对应，用于区分不同的使用者
*  @param  [OUT] u32Timestamp         时间戳
*  @param  [OUT] pu8DataY             图像数据数组，存放y
*  @param  [OUT] pu8DataU             图像数据数组，存放u
*  @param  [OUT] pu8DataV             图像数据数组, 存放v
*  @param  [OUT] s32LinesizeY         每扫描行数据长度数组, 存放y的每扫描行长度
*  @param  [OUT] s32LinesizeU         每扫描行数据长度数组, 存放u的每扫描行长度
*  @param  [OUT] s32LinesizeV         每扫描行数据长度数组, 存放v的每扫描行长度
*  @param  [OUT] s32Width             图像宽度
*  @param  [OUT] s32Height            图像高度
*/
typedef void (__stdcall * ICE_IPCSDK_OnFrame_Planar)(
	void *pvParam, ICE_U32 u32Timestamp, 
	ICE_U8 *pu8DataY, ICE_U8 *pu8DataU, ICE_U8 *pu8DataV, 
	ICE_S32 s32LinesizeY, ICE_S32 s32LinesizeU, ICE_S32 s32LinesizeV, 
	ICE_S32 s32Width, ICE_S32 s32Height);

/**
*  @brief  设置解码图像回调
*  @param  [IN] hSDK           连接相机时返回的sdk句柄
*  @param  [IN] pfOnFrame      图像帧回调地址
*  @param  [IN] pvParam        图像帧回调参数,能区分开不同的使用者即可
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetFrameCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnFrame_Planar pfOnFrame, void *pvParam);

/**
*  @brief  设置抓拍事件回调
*  @param  [IN] hSDK            连接相机时返回的sdk句柄
*  @param  [IN] pfOnPlate       车牌回调
*  @param  [IN] pvParam         车牌回调参数,能区分开不同的使用者即可
*　@return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetPlateCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvParam);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetPlateCallback_Cdecl(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnPlate_Cdecl pfOnPlate, void *pvParam);

/**
*  @brief  设置勾选虚假车牌过滤时，虚假车牌回调
*  @param  [IN] hSDK            连接相机时返回的sdk句柄
*  @param  [IN] pfOnFlasePlate  虚假车牌回调
*  @param  [IN] pvParam         虚假车牌回调参数,能区分开不同的使用者即可
*　@return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetFlasePlateCallback(ICE_HANDLE hSDK,
	ICE_IPCSDK_OnFlasePlate pfOnFlasePlate, void *pvParam);

/**
*  @brief  断开连接
*  @param  [IN] hSDK    连接相机时返回的sdk句柄
*  return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Close(ICE_HANDLE hSDK);

/*
设置算法规则接口

hSDK为ICE_IPCSDK_Open所返回的sdk句柄
pstParam为算法规则结构体指针

返回值为ICE_COM_STATUS_E枚举值，参见ice_com_type.h
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetVDParam(ICE_HANDLE hSDK, 
	const ICE_VD_PARAM_S *pstParam);

/*
获取当前算法规则接口

hSDK为ICE_IPCSDK_Open所返回的sdk句柄
pstParam为算法规则结构体指针

返回值为ICE_COM_STATUS_E枚举值，参见ice_com_type.h
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetVDParam(ICE_HANDLE hSDK, 
	ICE_VD_PARAM_S *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetVDCParam(ICE_HANDLE hSDK, 
	const ICE_VDC_PARAM_S *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetVDCParam(ICE_HANDLE hSDK, 
	ICE_VDC_PARAM_S *pstParam);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetArm(ICE_HANDLE hSDK, ICE_U8 u8Arm);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetArm(ICE_HANDLE hSDK, ICE_U8 *pu8Arm);

/*
设置算法规则接口

hSDK为ICE_IPCSDK_Open所返回的sdk句柄
pstParam为算法规则结构体指针

返回值为ICE_COM_STATUS_E枚举值，参见ice_com_type.h
*/
/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDTCAParam(ICE_HANDLE hSDK, 
	const ICE_CLBR_PARAM *pstCLBRParam, const ICE_DTCA_PARAM_ALGO *pstDTCAParam);*/

/*
获取当前算法规则接口

hSDK为ICE_IPCSDK_Open所返回的sdk句柄
pstParam为算法规则结构体指针

返回值为ICE_COM_STATUS_E枚举值，参见ice_com_type.h
*/
/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDTCAParam(ICE_HANDLE hSDK, 
	ICE_CLBR_PARAM *pstCLBRParam, ICE_DTCA_PARAM_ALGO *pstDTCAParam);*/

/*
设置算法规则接口

hSDK为ICE_IPCSDK_Open所返回的sdk句柄
pstParam为算法规则结构体指针

返回值为ICE_COM_STATUS_E枚举值，参见ice_com_type.h
*/
/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTCNTParam(ICE_HANDLE hSDK, 
	const ICE_TCNT_PARAM_ALGO *pstTCNTParam);*/

/*
获取当前算法规则接口

hSDK为ICE_IPCSDK_Open所返回的sdk句柄
pstParam为算法规则结构体指针

返回值为ICE_COM_STATUS_E枚举值，参见ice_com_type.h
*/
/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTCNTParam(ICE_HANDLE hSDK, 
	ICE_TCNT_PARAM_ALGO *pstTCNTParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetHCNTParam(ICE_HANDLE hSDK, 
	const ICE_CLBR_PARAM *pstCLBRParam, const ICE_HCNT_PARAM_ALGO *pstHCNTParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetHCNTParam(ICE_HANDLE hSDK, 
	ICE_CLBR_PARAM *pstCLBRParam, ICE_HCNT_PARAM_ALGO *pstHCNTParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetIPGParam(ICE_HANDLE hSDK, const ICE_IPG_PARAM_S *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetIPGParam(ICE_HANDLE hSDK, ICE_IPG_PARAM_S *pstParam);*/

/*
设置曝光接口

hSDK为ICE_IPCSDK_Open所返回的sdk句柄
u32ExpLine为曝光时间
s32AGain为模拟增益
s32DGain为数字增益

返回值为ICE_COM_STATUS_E枚举值，参见ice_com_type.h
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetExpAttr(ICE_HANDLE hSDK, const ICE_ExpAttr_S *pstParam);

/*
获取当前算法规则接口

hSDK为ICE_IPCSDK_TYPE ICE_IPCSDK_Open所返回的sdk句柄
pu32ExpLine为曝光时间
ps32AGain为模拟增益
ps32DGain为数字增益

返回值为ICE_COM_STATUS_E枚举值，参见ice_com_type.h
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetExpAttr(ICE_HANDLE hSDK, ICE_ExpAttr_S *pstParam);

/**
*  @brief  时间同步
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [IN] u16Year       同步时间的年
*  @param  [IN] u8Month       同步时间的月
*  @param  [IN] u8Day         同步时间的日
*  @param  [IN] u8Hour        同步时间的时
*  @param  [IN] u8Min         同步时间的分
*  @param  [IN] u8Sec         同步时间的秒
*  @return 0 失败, 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SyncTime(ICE_HANDLE hSDK, 
	ICE_U16 u16Year, ICE_U8 u8Month, ICE_U8 u8Day, 
	ICE_U8 u8Hour, ICE_U8 u8Min, ICE_U8 u8Sec = 0);

/**
*  @brief  获取时间同步
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [IN] u16Year       同步时间的年
*  @param  [IN] u8Month       同步时间的月
*  @param  [IN] u8Day         同步时间的日
*  @param  [IN] u8Hour        同步时间的时
*  @param  [IN] u8Min         同步时间的分
*  @param  [IN] u8Sec         同步时间的秒
*  @return 0 失败, 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSyncTime(ICE_HANDLE hSDK, tm* devtime);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSnapCamera(ICE_HANDLE hSDK, 
	ICE_SNAP_CAMERA_S *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSnapCamera(ICE_HANDLE hSDK, 
	const ICE_SNAP_CAMERA_S *pstParam);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetFTP(ICE_HANDLE hSDK, ICE_U32 *pu32Enable, 
	ICE_U32 *pu32IP, ICE_S8 *ps8Username, ICE_S8 *ps8Password, ICE_U32 *pu32Interval, 
	ICE_S8 *ps8Path, ICE_U32 *pu32Plate, ICE_U32 *pu32XML);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetFTP(ICE_HANDLE hSDK, ICE_U32 u32Enable, 
	ICE_U32 u32IP, const ICE_S8 *ps8Username, const ICE_S8 *ps8Password, ICE_U32 u32Interval, 
	const ICE_S8 *ps8Path, ICE_U32 u32Plate, ICE_U32 u32XML);

/**
*  @brief  获取相机ip
*  @param  [IN]  hSDK             连接相机时返回的sdk句柄
*  @param  [OUT] pu32IP           相机ip
*  @param  [OUT] pu32Mask         相机掩码
*  @param  [OUT] pu32Gateway      相机网关
*　@return 0 获取失败 1 获取成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetIPAddr(ICE_HANDLE hSDK, 
	ICE_U32 *pu32IP, ICE_U32 *pu32Mask, ICE_U32 *pu32Gateway);

/**
*  @brief  设置相机ip
*  @param  [IN]  hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pu32IP           相机ip
*  @param  [IN] pu32Mask         相机掩码
*  @param  [IN] pu32Gateway      相机网关
*　@return 0 设置失败 1 设置成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetIPAddr(ICE_HANDLE hSDK, 
	ICE_U32 u32IP, ICE_U32 u32Mask, ICE_U32 u32Gateway);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetRelayOutput(
	ICE_HANDLE hSDK, ICE_U8 *pu8IdleState, ICE_U32 *pu32DelayTime);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetRelayOutputSettings(
	ICE_HANDLE hSDK, ICE_U8 u8IdleState, ICE_U32 u32DelayTime);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetRelayOutput2(
	ICE_HANDLE hSDK, ICE_U8 *pu8IdleState, ICE_U32 *pu32DelayTime);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetRelayOutput2Settings(
	ICE_HANDLE hSDK, ICE_U8 u8IdleState, ICE_U32 u32DelayTime);

/**
*  @brief  获取开关量输出配置
*  @param  [IN]  hSDK               连接相机时返回的sdk句柄    
*  @param  [IN] u32Index            IO口(0:表示IO1 1:表示IO2)
*  @param  [OUT] pu32IdleState      常开常闭状态的配置（1 是常开，0是常闭）
*  @param  [OUT] ps32DelayTime      切换状态的时间（-1表示不恢复 单位：s）
*  @param  [OUT] pu32Reserve        预留参数
*  @return 0 获取失败 1 获取成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAlarmOutConfig(
	ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 *pu32IdleState, 
	ICE_S32 *ps32DelayTime, ICE_U32 *pu32Reserve);

/**
*  @brief  设置开关量输出配置
*  @param  [IN]  hSDK               连接相机时返回的sdk句柄    
*  @param  [IN] u32Index            IO口(0:表示IO1 1:表示IO2)
*  @param  [IN] pu32IdleState      常开常闭状态的配置（1 是常开，0是常闭）
*  @param  [IN] s32DelayTime      切换状态的时间（-1表示不恢复 单位：s）
*  @param  [IN] u32Reserve        预留参数
*  @return 0 设置失败 1 设置成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAlarmOutConfig(
	ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 u32IdleState, 
	ICE_S32 s32DelayTime, ICE_U32 u32Reserve);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetEncoderSettings(
	ICE_HANDLE hSDK, ICE_U8 u8MainStream, 
	ICE_U32 *pu32Width, ICE_U32 *pu32Height, 
	ICE_U32 *pu32FrameRate, ICE_U32 *pu32BitRate);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetEncoderSettings(
	ICE_HANDLE hSDK, ICE_U8 u8MainStream, 
	ICE_U32 u32Width, ICE_U32 u32Height, 
	ICE_U32 u32FrameRate, ICE_U32 u32BitRate);

/**
*  @brief  重启相机
*  @param  [IN] hSDK 连接相机时返回的sdk句柄
*  @return 0 重启失败 1 重启成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Reboot(ICE_HANDLE hSDK);

/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetHCNTCfg(ICE_HANDLE hSDK, 
	ICE_S32 *ps32RS485Type, ICE_U32 *pu32DoorType, ICE_U32 *pu32Railway);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetHCNTCfg(ICE_HANDLE hSDK, 
	ICE_S32 s32RS485Type, ICE_U32 u32DoorType, ICE_U32 u32Railway);*/

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAlarmInCfg(
	ICE_HANDLE hSDK, ICE_U32 *pu32IdleState);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAlarmInCfg(
	ICE_HANDLE hSDK, ICE_U32 u32IdleState);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetNTPCfg(
	ICE_HANDLE hSDK, ICE_U32 *pu32Mode, char *pcNTPServer, ICE_U32 *pu32TimeZone);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetNTPCfg(
	ICE_HANDLE hSDK, ICE_U32 u32Mode, const char *pcNTPServer, ICE_U32 u32TimeZone);

/**
*  @brief  获取osd叠加
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pstOSDAttr       OSD结构体(ICE_OSDAttr_S)
*  @return 获取成功 获取失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOSDCfg(ICE_HANDLE hSDK, ICE_OSDAttr_S *pstOSDAttr);

/**
*  @brief  设置osd叠加
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pstOSDAttr       OSD结构体(ICE_OSDAttr_S)
*  @return 设置成功 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOSDCfg(ICE_HANDLE hSDK, const ICE_OSDAttr_S *pstOSDAttr);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSchedCfg(ICE_HANDLE hSDK, 
	ICE_SCHED_TASK_S *pstParam, ICE_U32 *pu32Count);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSchedCfg(ICE_HANDLE hSDK, 
	const ICE_SCHED_TASK_S *pstParam, const ICE_U32 u32Count);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetImagingSettings(
	ICE_HANDLE hSDK, ICE_U32 *pu32Luma, ICE_U32 *pu32Contr, 
	ICE_U32 *pu32Hue, ICE_U32 *pu32Satu);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetImagingSettings(
	ICE_HANDLE hSDK, ICE_U32 u32Luma, ICE_U32 u32Contr, 
	ICE_U32 u32Hue, ICE_U32 u32Satu);

/**
*  @brief  打开道闸
*  @param  [IN] hSDK  连接相机时返回的sdk句柄
*  @return 1 打开成功 0 打开失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_OpenGate(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_OpenGate2(ICE_HANDLE hSDK);

/**
*  @brief  控制道闸(开关量输出)
*  @param  [IN] hSDK            连接相机时返回的sdk句柄
*  @param  [IN] u32Index        控制的IO口(0:表示IO1 1:表示IO2 2:表示IO3 3:表示IO4)
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ControlAlarmOut(ICE_HANDLE hSDK, ICE_U32 u32Index);

/**
*  @brief  开始对讲
*  @param  [IN] hSDK  连接相机时返回的sdk句柄
*  @return 1 成功 0 失败 2 占用
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BeginTalk(ICE_HANDLE hSDK);

/**
*  @brief  开始对讲
*  @param  [IN] hSDK  连接相机时返回的sdk句柄
*  @param  [OUT] stTalkInfo  对讲信息
*  @param  [IN] nResvr1 预留
*  @param  [IN] nResvr2 预留
*  @return 1 成功 0 失败 2 占用
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BeginTalk_Ex(ICE_HANDLE hSDK, ICE_TALK_INFO *stTalkInfo, ICE_U32 nResvr1, ICE_U32 nResvr2);

/**
*  @brief  拒绝对讲
*  @param  [IN] hSDK  连接相机时返回的sdk句柄
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_RefuseTalk(ICE_HANDLE hSDK);

/**
*  @brief  忽略对讲
*  @param  [IN] hSDK  连接相机时返回的sdk句柄
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_IgnoreTalk(ICE_HANDLE hSDK);

/**
*  @brief  结束对讲
*  @param  [IN] hSDK  连接相机时返回的sdk句柄
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_EndTalk(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_IsTalking(ICE_HANDLE hSDK);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Preview(ICE_HANDLE hSDK, ICE_U32 u32Preview);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetPhyChnCfg(ICE_HANDLE hSDK, ICE_PHYCHN_CFG_S *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetPhyChnCfg(ICE_HANDLE hSDK, const ICE_PHYCHN_CFG_S *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetARegCfg(ICE_HANDLE hSDK, ICE_EXP_AREGULATE_PARAM *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetARegCfg(ICE_HANDLE hSDK, const ICE_EXP_AREGULATE_PARAM *pstParam);

/**
*  @brief  获取串口配置
*  @param  [IN]  hSDK             连接相机时返回的sdk句柄
*  @param  [OUT] pstUARTCfg       串口配置参数结构体(ICE_UART_PARAM)
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetUARTCfg(ICE_HANDLE hSDK, ICE_UART_PARAM *pstUARTCfg);

/**
*  @brief  设置串口配置
*  @param  [IN]  hSDK             连接相机时返回的sdk句柄
*  @param  [OUT] pstUARTCfg       串口配置参数
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetUARTCfg(ICE_HANDLE hSDK, const ICE_UART_PARAM *pstUARTCfg);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSDCfg(ICE_HANDLE hSDK, SD_card_param *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSDCfg(ICE_HANDLE hSDK, const SD_card_param *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SDFormat(ICE_HANDLE hSDK, int timeout);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SDFormat_Only(ICE_HANDLE hSDK, int timeout);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SDUnload(ICE_HANDLE hSDK);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetHttpPostCfg(ICE_HANDLE hSDK, ICE_HTTP_POST_PARAM *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetHttpPostCfg(ICE_HANDLE hSDK, const ICE_HTTP_POST_PARAM *pstParam);

/**
*  @brief  设置黑白名单参数
*  @param  [IN] hSDK         连接相机时返回的sdk句柄
*  @param  [IN] mode         白名单模式（0表示断网关联，1表示实时工作,2 不关联开闸或不工作）
*  @param  [IN] match        白名单匹配相似度（范围（70%-100%），默认：80%）
*  @param  [IN] bmode        黑名单模式（0 不关联开闸，1 开闸）
*  @param  [IN] bmatch       黑名单匹配相似度（范围（70%-100%），默认：80%）
*  @param  [IN] tmode        临时车模式（0 不关联开闸，1 开闸）
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetWhiteListParam(ICE_HANDLE hSDK, 
	int mode, int match, int bmode, int bmatch, int tmode);

/**
*  @brief  获取黑白名单参数
*           注意:断网关联：在相机断网的情况下，前端相机才进行白名单的关联匹配和打开道闸的工作。
*                          这种模式主要用于在联网状态下的白名单是由平台来完成的，断网情况下由相机完成的情况。
*                实时工作：无论断网还是联网状态，都由前端相机进行白名单的关联匹配和打开道闸的工作。
*  @param  [IN]  hSDK        连接相机时返回的sdk句柄
*  @param  [OUT] mode        白名单模式（0表示断网关联，1表示实时工作,2 不关联开闸或不工作）
*  @param  [OUT] match       白名单匹配相似度（范围（70%-100%），默认：80%）
*  @param  [OUT] bmode       黑名单模式（0 不关联开闸，1 开闸）
*  @param  [OUT] bmatch      黑名单匹配相似度（范围（70%-100%），默认：80%）
*  @param  [OUT] tmode       临时车模式（0 不关联开闸，1 开闸）
*  @return 1 成功 0 失败 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetWhiteListParam(ICE_HANDLE hSDK, 
	int* mode, int* match, int *bmode, int *bmatch, int *tmode);


/*  @brief  设置黑白名单参数
*           注意:断网关联：在相机断网的情况下，前端相机才进行白名单的关联匹配和打开道闸的工作。
*                          这种模式主要用于在联网状态下的白名单是由平台来完成的，断网情况下由相机完成的情况。
*                实时工作：无论断网还是联网状态，都由前端相机进行白名单的关联匹配和打开道闸的工作。
*  @param  [IN]  hSDK        连接相机时返回的sdk句柄
*  @param  [OUT] whiteList   黑白名单结构体
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetNewWhiteListParam(ICE_HANDLE hSDK, WhiteList_Param* whiteList);

/*  @brief  获取黑白名单参数
*           注意:断网关联：在相机断网的情况下，前端相机才进行白名单的关联匹配和打开道闸的工作。
*                          这种模式主要用于在联网状态下的白名单是由平台来完成的，断网情况下由相机完成的情况。
*                实时工作：无论断网还是联网状态，都由前端相机进行白名单的关联匹配和打开道闸的工作。
*  @param  [IN]  hSDK        连接相机时返回的sdk句柄
*  @param  [IN] whiteList   黑白名单结构体
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetNewWhiteListParam(ICE_HANDLE hSDK,  WhiteList_Param* whiteList);


/**
*  @brief  软触发
*  @param  [IN]  hSDK                连接相机时返回的sdk句柄
*  @param  [OUT] pcNumber            车牌号
*  @param  [OUT] pcColor             车牌颜色（"蓝色","黄色","白色","黑色",“绿色”）
*  @param  [OUT] pcPicData           抓拍图片缓冲区地址
*  @param  [IN]  u32PicSize          抓拍图片缓冲区大小
*  @param  [OUT] pu32PicLen          抓拍图片实际长度
*  @return 1 成功 0 失败 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Trigger(ICE_HANDLE hSDK, ICE_CHAR *pcNumber, ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicSize, ICE_U32 *pu32PicLen);

/**
*  @brief  获取相机状态
*  @param  [IN] hSDK      连接相机时返回的sdk句柄
*  @return 0 离线 1 在线 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetStatus(ICE_HANDLE hSDK);

/**
*  @brief  只抓拍,不识别
*  @param  [IN]  hSDK            连接相机时返回的sdk句柄
*  @param  [IN]  pcPicData       抓拍图片缓冲区地址
*  @param  [IN]  u32PicSize      抓拍图片缓冲区大小
*  @param  [OUT] pu32PicLen      抓拍图片实际长度
*  @return 1 抓拍成功 0 抓拍失败 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Capture(ICE_HANDLE hSDK, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicSize, ICE_U32 *pu32PicLen);

/**
*  @brief  为增加 在流中抓图的接口
*  @param  [IN]  hSDK            连接相机时返回的sdk句柄
*  @param  [IN]  filepath        文件路径
*  @return 1 抓拍成功 0 抓拍失败 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Capture_BZ(ICE_HANDLE hSDK, ICE_CHAR *filepath);

/**
*  @brief  透明串口回调函数
*  @param  [OUT] pvParam      串口回调参数，用于区分不同串口（ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack传入的最后一个参数）
*  @param  [OUT] pcIP         相机ip
*  @param  [OUT] pcData       串口数据
*  @param  [OUT] u32Len       数据长度
*/
typedef void (__stdcall * ICE_IPCSDK_OnSerialPort)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  设置透明串口
*  @param  [IN] hSDK                   连接相机时返回的sdk句柄
*  @param  [IN] pfOnSerialPort         ICE_IPCSDK_OnSerialPort回调函数
*  @param  [IN] pvSerialPortParam      串口回调参数，用于区分不同串口
*  @return void 
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  透明串口接收事件回调接口(rs232)
*  @param  [OUT] pvParam      串口回调参数，用于区分不同串口（ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack_RS232传入的最后一个参数）
*  @param  [OUT] pcIP         相机ip
*  @param  [OUT] pcData       串口数据
*  @param  [OUT] u32Len       数据长度
*/
typedef void (__stdcall * ICE_IPCSDK_OnSerialPort_RS232)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  设置透明串口接收事件(rs232)
*  @param  [IN] hSDK                   连接相机时返回的sdk句柄
*  @param  [IN] pfOnSerialPort         ICE_IPCSDK_OnSerialPort_RS232回调函数
*  @param  [IN] pvSerialPortParam      串口回调参数，用于区分不同串口
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack_RS232(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort_RS232 pfOnSerialPort, void *pvSerialPortParam);

typedef void (*ICE_IPCSDK_TYPE ICE_IPCSDK_OnSerialPort_Cdecl)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack_Cdecl(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort_Cdecl pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  发送透明串口(rs485)数据
*  @param  [IN] hSDK      连接相机时返回的sdk句柄
*  @param  [IN] pcData    串口数据
*  @param  [IN] u32Len    数据长度
*  @return 0 发送失败 1 发送成功 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TransSerialPort(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  发送透明串口(rs232)数据
*  @param  [IN] hSDK      连接相机时返回的sdk句柄
*  @param  [IN] pcData    串口数据
*  @param  [IN] u32Len    数据长度
*  @return 0 发送失败 1 发送成功 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TransSerialPort_RS232(ICE_HANDLE hSDK, 
	ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  获取白名单项总数(包括黑白名单)
*          注意事项: 在使用任何白名单操作前,都需调用此接口,用于分配内存
*  @param  [IN]  hSDK         连接相机时返回的sdk句柄
*  @param  [OUT] pu32Count    白名单项总数
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListGetCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  获取白名单项(旧模式,以序列号为索引)
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] s32Index         需要获取的白名单的索引
*  @param  [OUT] pcNumber        白名单项中的车牌号
*  @param  [OUT] pcDateBegin     白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcDateEnd       白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [OUT] pcTimeEnd       白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [OUT] pcType          名单类型 W:白名单 B：黑名单
*  @param  [OUT] pcRsrv2         车牌备注
*  @param  [OUT] pcRsrv3         预留字段3
*  @param  [OUT] pcRsrv4         预留字段4
*  @return 1 获取成功 0 获取失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListGetItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcType, ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  编辑白名单项(以索引号为索引)
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @param  [IN] s32Index          索引号
*  @param  [IN] pcNumber          黑白名单项中的车牌号
*  @param  [IN] pcDateBegin       黑白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [IN] pcDateEnd         黑白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [IN] pcTimeBegin       黑白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [IN] pcTimeEnd         黑白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [IN] pcRsrv1           预留字段1
*  @param  [IN] pcRsrv2           预留字段2
*  @param  [IN] pcRsrv3           预留字段3
*  @param  [IN] pcRsrv4           预留字段4
*  @return 1 编辑成功 0 编辑失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListEditItem(ICE_HANDLE hSDK, ICE_S32 s32Index, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  添加白名单项(以索引号为索引)
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @param  [IN] s32Index          索引号
*  @param  [IN] pcNumber          黑白名单项中的车牌号
*  @param  [IN] pcDateBegin       黑白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [IN] pcDateEnd         黑白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [IN] pcTimeBegin       黑白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [IN] pcTimeEnd         黑白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [IN] pcRsrv1           预留字段1
*  @param  [IN] pcRsrv2           预留字段2
*  @param  [IN] pcRsrv3           预留字段3
*  @param  [IN] pcRsrv4           预留字段4
*  @return 1 添加成功 0 添加失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListInsertItem(ICE_HANDLE hSDK, ICE_S32 s32Index, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  删除白名单项(以索引号为索引)
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @param  [IN] s32Index          索引号
*  @return 1 删除成功 0 删除失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDeleteItem(ICE_HANDLE hSDK, ICE_S32 s32Index);

/**
*  @brief  删除所有白名单项
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @return 1 删除成功 0 删除失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDelAllItems(ICE_HANDLE hSDK);

/**
*  @brief  查找黑白名单项(以索引号为索引)
*  @param  [IN] hSDK               连接相机时返回的sdk句柄
*  @param  [IN] pcNumber           黑白名单项中的车牌号
*  @param  [IN] s32Start           查找的起始索引号
*  @param  [IN] s32Index           查找得到的索引号（可通过该索引号获得对应的白名单项）
*  @return 1 查找成功 0 查找失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListFindItem(ICE_HANDLE hSDK, 
	const ICE_CHAR* pcNumber, ICE_S32 s32Start, ICE_S32 *s32Index);

/**
*  @brief  编辑黑白名单项(以车牌号为索引)
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @param  [IN] pcNumber          黑白名单项中的车牌号
*  @param  [IN] pcDateBegin       黑白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [IN] pcDateEnd         黑白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [IN] pcTimeBegin       黑白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [IN] pcTimeEnd         黑白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [IN] pcType            名单类型（白名单"W"/黑名单"B"）
*  @param  [IN] pcRemark          备注
*  @param  [IN] pcRsrv2           预留字段2
*  @param  [IN] pcRsrv3           预留字段3
*  @param  [IN] pcRsrv4           预留字段4
*  @return 1 编辑成功 0 编辑失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListEditItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, const ICE_CHAR* pcType, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  添加黑白名单项(以车牌号为索引)
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @param  [IN] pcNumber          黑白名单项中的车牌号
*  @param  [IN] pcDateBegin       黑白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [IN] pcDateEnd         黑白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [IN] pcTimeBegin       黑白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [IN] pcTimeEnd         黑白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [IN] pcType            名单类型（白名单"W"/黑名单"B"）
*  @param  [IN] pcRemark          备注
*  @param  [IN] pcRsrv2           预留字段2
*  @param  [IN] pcRsrv3           预留字段3
*  @param  [IN] pcRsrv4           预留字段4
*  @return 1 添加成功 0 添加失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListInsertItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, const ICE_CHAR* pcType, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  删除黑白名单项(以车牌号为索引)
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @param  [IN] pcNumber          要删除的车牌号
*  @return 1 删除成功 0 删除失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDeleteItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  删除所有黑白名单项(以车牌号为索引)
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @return 1 删除成功 0 删除失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDelAllItems_ByNumber(ICE_HANDLE hSDK);

/**
*  @brief  查找黑白名单项(以车牌号为索引)
*  @param  [IN] hSDK               连接相机时返回的sdk句柄
*  @param  [IN] pcNumber           黑白名单项中的车牌号
*  @param  [OUT] pcDateBegin       黑白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcDateEnd         黑白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin       黑白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [OUT] pcTimeEnd         黑白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [OUT] pcType            名单类型（白名单"W"/黑名单"B"）
*  @param  [OUT] pcRemark          备注
*  @param  [OUT] pcRsrv2           预留字段2
*  @param  [OUT] pcRsrv3           预留字段3
*  @param  [OUT] pcRsrv4           预留字段4
*  @return 1 查找成功 0 查找失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListFindItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, ICE_CHAR* pcType, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  通过该回调函数获得断网续传识别数据
*  @param  [OUT] pvParam               用户自定义参数,用来区分不同的sdk使用者,类似于线程入口函数的参数(与设置此回调接口的最后一个参数相同)
*  @param  [OUT] pcIP                  相机ip
*  @param  [OUT] u32CapTime            实时抓拍时间，从1970年1月1日零点开始的秒数
*  @param  [OUT] pcNumber              车牌号
*  @param  [OUT] pcColor               车牌颜色("蓝色","黄色","白色","黑色","绿色")
*  @param  [OUT] pcPicData             全景抓拍图片缓冲区地址
*  @param  [OUT] u32PicLen             全景抓拍图片实际长度
*  @param  [OUT] pcCloseUpPicData      特写抓拍图片缓冲区地址
*  @param  [OUT] u32CloseUpPicLen      特写抓拍图片实际长度
*  @param  [OUT] s16PlatePosLeft       车牌区域左上角横坐标
*  @param  [OUT] s16PlatePosTop        车牌区域左上角纵坐标
*  @param  [OUT] s16PlatePosRight      车牌区域右上角横坐标
*  @param  [OUT] s16PlatePosBottom     车牌区域右上角纵坐标
*  @param  [OUT] fPlateConfidence      车牌打分值
*									   详解：SDK输出的范围大于IE界面设置的车牌阈值，上限是28，例如：IE设置的是10，范围：10-28
*									   作用：sdk输出的车牌打分值是用在双相机方案，sdk收到两个相机的车牌信息，可以通过车牌
*									   打分值来选择哪个信息更加可靠作为最终的输出结果
*  @param  [OUT] u32VehicleColor       车身颜色(车辆特征码相机版本：(-1:未知,0:黑色,1:蓝色,2:灰色,3:棕色,4:绿色,5:夜间深色,6:紫色,7:红色,8:白色,9:黄色)
*                                          其它相机版本：(0:未知,1:红色,2:绿色,3:蓝色,4:黄色,5:白色,6:灰色,7:黑色,8:紫色,9:棕色,10:粉色))
*  @param  [OUT] u32PlateType          车牌类型，详见车牌类型ICE_PLATETYPE_E枚举值
*  @param  [OUT] u32VehicleDir         车辆方向 (0:车头方向,1:车尾方向,2:车头和车尾方向)
*  @param  [OUT] u32AlarmType          报警输出，详见报警输出ICE_VDC_ALARM_TYPE枚举值
*  @param  [OUT] u32Reserved1          预留参数1
*  @param  [OUT] u32Reserved2          预留参数2
*  @param  [OUT] u32Reserved3          预留参数3
*  @param  [OUT] u32Reserved4          预留参数4
*/
typedef void (__stdcall * ICE_IPCSDK_OnPastPlate)(void *pvParam, const ICE_CHAR *pcIP, 
	ICE_U32 u32CapTime, const ICE_CHAR *pcNumber, const ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *pcCloseUpPicData, ICE_U32 u32CloseUpPicLen, 
	ICE_S16 s16PlatePosLeft, ICE_S16 s16PlatePosTop, ICE_S16 s16PlatePosRight, ICE_S16 s16PlatePosBottom, 
	ICE_FLOAT fPlateConfidence, ICE_U32 u32VehicleColor, ICE_U32 u32PlateType, ICE_U32 u32VehicleDir, 
	ICE_U32 u32AlarmType, ICE_U32 u32Reserved1, ICE_U32 u32Reserved2, ICE_U32 u32Reserved3, ICE_U32 u32Reserved4);

/**
*  @brief  设置获得断网续传识别数据的相关回调函数
*  @param  [IN] hSDK               连接相机时返回的sdk句柄
*  @param  [IN] pfOnPastPlate      断网识别数据，通过该回调获得
*  @param  [IN] pvPastPlateParam   回调函数中的参数，能区分开不同的使用者即可
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetPastPlateCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnPastPlate pfOnPastPlate, void *pvPastPlateParam);

typedef void (*ICE_IPCSDK_TYPE ICE_IPCSDK_OnPastPlate_Cdecl)(void *pvParam, const ICE_CHAR *pcIP, 
	ICE_U32 u32CapTime, const ICE_CHAR *pcNumber, const ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *pcCloseUpPicData, ICE_U32 u32CloseUpPicLen, 
	ICE_S16 s16PlatePosLeft, ICE_S16 s16PlatePosTop, ICE_S16 s16PlatePosRight, ICE_S16 s16PlatePosBottom, 
	ICE_FLOAT fPlateConfidence, ICE_U32 u32VehicleColor, ICE_U32 u32PlateType, ICE_U32 u32VehicleDir, 
	ICE_U32 u32AlarmType, ICE_U32 u32Reserved1, ICE_U32 u32Reserved2, ICE_U32 u32Reserved3, ICE_U32 u32Reserved4);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetPastPlateCallBack_Cdecl(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnPastPlate_Cdecl pfOnPastPlate, void *pvPastPlateParam);

/**
*  @brief  通过该回调函数获取相机的连接状态
*  @param  [OUT] pvParam             相机连接回调参数, 用于区分不同相机连接事件(ICE_IPCSDK_SetDeviceEventCallBack传入的最后一个参数)
*  @param  [OUT] pcIP                相机ip
*  @param  [OUT] u32EventType        事件类型 0：离线 1：在线 2:IO变化
*  @param  [OUT] u32EventData1       事件数据1 事件类型为0或者1时，代表回调句柄;事件类型为2时，代表IO1的状态;）
*  @param  [OUT] u32EventData2       事件数据2 （事件类型为2时，代表IO2的状态）
*  @param  [OUT] u32EventData3       事件数据3 （事件类型为2时，代表IO3的状态）
*  @param  [OUT] u32EventData4       事件数据4 （事件类型为2时，代表IO4的状态）
*/
typedef void (__stdcall * ICE_IPCSDK_OnDeviceEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32EventData1, ICE_U32 u32EventData2, ICE_U32 u32EventData3, ICE_U32 u32EventData4);

/**
*  @brief  设置相机连接状态回调事件
*  @param  [IN] hSDK                         连接相机时返回的sdk句柄
*  @param  [IN] pfOnDeviceEvent              相机连接回调
*  @param  [IN] pvDeviceEventParam           相机连接回调参数,用于区分不同相机连接事件
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetDeviceEventCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnDeviceEvent pfOnDeviceEvent, void *pvDeviceEventParam);

/**
*  @brief  获得相机mac地址
*  @param  [IN] hSDK                  连接相机时返回的sdk句柄
*  @param  [OUT] szDevID              相机mac地址
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDevID(ICE_HANDLE hSDK, ICE_CHAR* szDevID);

/**
*  @brief  开始录像
*  @param  [IN] hSDK                 连接相机时返回的sdk句柄
*  @param  [IN] pcFileName           录像文件名
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartRecord(ICE_HANDLE hSDK, const ICE_CHAR *pcFileName);

/**
*  @brief  结束录像
*  @param  [IN] hSDK                 连接相机时返回的sdk句柄
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_StopRecord(ICE_HANDLE hSDK);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetHDTriggerParam(ICE_HANDLE hSDK, HDTrigger_Param *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetHDTriggerParam(ICE_HANDLE hSDK, const HDTrigger_Param *pstParam);

/**
 *  @brief  写入用户数据
 *  @param  [IN] hSDK       由连接相机接口获得的句柄
 *  @parame [IN] pcData     需要写入的用户数据
 *  @return 1表示成功，0表示失败
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WriteUserData(ICE_HANDLE hSDK, const char* pcData);

/**
 *  @brief  读取用户数据
 *  @param  [IN] hSDK       由连接相机接口获得的句柄
 *  @param  [OUT] szData    读取的用户数据
 *  @param  [IN]  nSize     读出的数据的最大长度, 即用户数据分配的大小
 *  @return 1 表示成功，0 表示失败
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ReadUserData(ICE_HANDLE hSDK, char* pcData, int nSize);

/**
*  @brief  写二进制数据
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [IN] pcData      需要写入的数据
*  @param  [IN] nOffset     偏移量
*  @param  [IN] nLen        写入数据的长度
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WriteUserData_Binary(
	ICE_HANDLE hSDK, const char* pcData, ICE_U32 nOffset, ICE_U32 nLen);

/**
*  @brief  读二进制数据
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [OUT] pcData     读取的用户数据
*  @param  [IN] nSize       读出的数据的最大长度,即缓冲区大小
*  @param  [IN] nOffset     偏移量
*  @param  [OUT] nLen       需要读出数据的数量,即第二个参数的大小
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ReadUserData_Binary(
	ICE_HANDLE hSDK, char* pcData, ICE_U32 nSize, ICE_U32 nOffset, ICE_U32 nLen);

/**
*  @brief  获取白名单的总数（不含黑名单）
*  @param  [IN] hSDK              连接相机时返回的sdk句柄
*  @param  [OUT] pu32Count        白名单项总数
*  @param 1 获取成功 0 获取失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetWhiteCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  获取白名单项(不包含黑名单,通过索引号获取)
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] s32Index         需要获取的白名单的索引
*  @param  [OUT] pcNumber        白名单项中的车牌号
*  @param  [OUT] pcDateBegin     白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcDateEnd       白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [OUT] pcTimeEnd       白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [OUT] pcRemark        备注
*  @param  [OUT] pcRsrv2         预留字段2
*  @param  [OUT] pcRsrv3         预留字段3
*  @param  [OUT] pcRsrv4         预留字段4
*  @return 1 获取成功 0 获取失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetWhiteItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  编辑白名单项(不包含黑名单)
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pcNumber        白名单项中的车牌号
*  @param  [IN] pcDateBegin     白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [IN] pcDateEnd       白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [IN] pcTimeBegin     白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [IN] pcTimeEnd       白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [IN] pcRemark        备注
*  @param  [IN] pcRsrv2         预留字段2
*  @param  [IN] pcRsrv3         预留字段3
*  @param  [IN] pcRsrv4         预留字段4
*  @return 1 编辑成功 0 编辑失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EditWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  添加白名单项(不包含黑名单)
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pcNumber        白名单项中的车牌号
*  @param  [IN] pcDateBegin     白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [IN] pcDateEnd       白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [IN] pcTimeBegin     白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [IN] pcTimeEnd       白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [IN] pcRemark        备注
*  @param  [IN] pcRsrv2         预留字段2
*  @param  [IN] pcRsrv3         预留字段3
*  @param  [IN] pcRsrv4         预留字段4
*  @return 1 添加成功 0 添加失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_InsertWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief 获得黑名单总数
*  @param  [IN]  hSDK             连接相机时返回的sdk句柄
*  @param  [OUT] pu32Count        黑名单总数
*  @return 1 获取成功 0 获取失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetBlackCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  获取黑名单项
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] s32Index         需要获取的白名单的索引
*  @param  [OUT] pcNumber        黑名单项中的车牌号
*  @param  [OUT] pcDateBegin     黑名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcDateEnd       黑名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     黑名单项中的开始时间(格式为HH:mm:ss)
*  @param  [OUT] pcTimeEnd       黑名单项中的结束时间(格式为HH:mm:ss)
*  @param  [OUT] pcRemark        备注
*  @param  [OUT] pcRsrv2         预留字段2
*  @param  [OUT] pcRsrv3         预留字段3
*  @param  [OUT] pcRsrv4         预留字段4
*  @return 1 获取成功 0 获取失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetBlackItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  编辑黑名单项
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pcNumber        黑名单项中的车牌号
*  @param  [IN] pcDateBegin     黑名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [IN] pcDateEnd       黑名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [IN] pcTimeBegin     黑名单项中的开始时间(格式为HH:mm:ss)
*  @param  [IN] pcTimeEnd       黑名单项中的结束时间(格式为HH:mm:ss)
*  @param  [IN] pcRemark        备注
*  @param  [IN] pcRsrv2         预留字段2
*  @param  [IN] pcRsrv3         预留字段3
*  @param  [IN] pcRsrv4         预留字段4
*  @return 1 编辑成功 0 编辑失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EditBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  添加黑名单项
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pcNumber        黑名单项中的车牌号
*  @param  [IN] pcDateBegin     黑名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [IN] pcDateEnd       黑名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [IN] pcTimeBegin     黑名单项中的开始时间(格式为HH:mm:ss)
*  @param  [IN] pcTimeEnd       黑名单项中的结束时间(格式为HH:mm:ss)
*  @param  [IN] pcRemark        备注
*  @param  [IN] pcRsrv2         预留字段2
*  @param  [IN] pcRsrv3         预留字段3
*  @param  [IN] pcRsrv4         预留字段4
*  @return 1 添加成功 0 添加失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_InsertBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  删除所有白名单项(不含黑名单)
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @return 0 删除失败 1 删除成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DelAllWhiteItems(ICE_HANDLE hSDK);

/**
*  @brief  删除所有黑名单项(不含白名单)
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @return 0 删除失败 1 删除成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DelAllBlackItems(ICE_HANDLE hSDK);

/**
*  @brief  删除一项白名单项(不含黑名单)
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pcNumber		 需要删除的车牌号
*  @return 0 删除失败 1 删除成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DeleteWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  查找一项白名单项(不含黑名单)
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pcNumber         白名单项中的车牌号
*  @param  [OUT] pcDateBegin     白名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcDateEnd       白名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     白名单项中的开始时间(格式为HH:mm:ss)
*  @param  [OUT] pcTimeEnd       白名单项中的结束时间(格式为HH:mm:ss)
*  @param  [OUT] pcRemark        备注
*  @param  [OUT] pcRsrv2         预留字段2
*  @param  [OUT] pcRsrv3         预留字段3
*  @param  [OUT] pcRsrv4         预留字段4
*  @return 1 查找成功 0 查找失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_FindWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  删除一项黑名单项
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pcNumber		 需要删除的车牌号
*  @return 0 删除失败 1 删除成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DeleteBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  查找黑名单项
*  @param  [IN] hSDK             连接相机时返回的sdk句柄
*  @param  [IN] pcNumber         黑名单项中的车牌号
*  @param  [OUT] pcDateBegin     黑名单项中的开始日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcDateEnd       黑名单项中的结束日期(格式为yyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     黑名单项中的开始时间(格式为HH:mm:ss)
*  @param  [OUT] pcTimeEnd       黑名单项中的结束时间(格式为HH:mm:ss)
*  @param  [OUT] pcRemark        备注
*  @param  [OUT] pcRsrv2         预留字段2
*  @param  [OUT] pcRsrv3         预留字段3
*  @param  [OUT] pcRsrv4         预留字段4
*  @return 1 查找成功 0 查找失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_FindBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAutoRebootParam(ICE_HANDLE hSDK, AutoRebootParam *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAutoRebootParam(ICE_HANDLE hSDK, const AutoRebootParam *pstParam);

/**
*  @brief  语音播报
*  @param  [IN] hSDK       连接相机时返回的sdk句柄
*  @param  [IN] nIndex     语音文件索引
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Broadcast(ICE_HANDLE hSDK, ICE_U16 nIndex);

/**
*  @brief  语音播报
*  @param  [IN] hSDK         连接相机时返回的sdk句柄
*  @param  [IN] u32Index     优先城市的索引号
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetCity(ICE_HANDLE hSDK, ICE_U32 u32Index);

/**
*  @brief  语音组播
*  @param  [IN] hSDK         连接相机时返回的sdk句柄
*  @param  [IN] pcIndex      包含语音序号的字符串
*							 注：中间可以用, ; \t \n或者空格分开；如：1 2 3 4或者1,2,3,4
*  @return 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BroadcastGroup(ICE_HANDLE hSDK, const ICE_CHAR* pcIndex);

/**
*  @brief  搜索设备
*  @param  [IN] szDevs       设备mac地址和ip地址的字符串
*							   设备mac地址和ip地址的字符串，格式为：mac地址 ip地址 例如：
*							   00-00-00-00-00-00 192.168.55.150\r\n
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SearchDev(char* szDevs);

/**
*  @brief  搜索设备
*  @param  [IN] pcDeveloperID 开发者ID
*  @param  [IN] pcKey         开发者Key
*  @param  [IN] pcSN		  设备序列号字符串，例如：XXXXXXXX\r\nYYYYYYYY\r\nZZZZZZZ\r\n
*  @param  [IN] szSNsLen      设备序列号字符串缓存最大长度
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SearchDev_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, char* szSNs, int szSNsLen);

/**
*  @brief  获取DNS
*  @param  [IN] hSDK		连接相机时返回的sdk句柄
*  @param  [OUT] pu32DNS	首选DNS
*  @param  [OUT] pu32DNS2	备选DNS	
*  @return 0 失败 1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDNSAddr(ICE_HANDLE hSDK, ICE_U32 *pu32DNS, ICE_U32 *pu32DNS2);

/**
*  @brief  设置DNS
*  @param  [IN] hSDK		连接相机时返回的sdk句柄
*  @param  [IN] pu32DNS		首选DNS
*  @param  [IN] pu32DNS2	备选DNS	
*  @return 0 失败 1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDNSAddr(ICE_HANDLE hSDK, ICE_U32 u32DNS, ICE_U32 u32DNS2);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLightParam(ICE_HANDLE hSDK, LightParam *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLightParam(ICE_HANDLE hSDK, const LightParam *pstParam);

/**
*  @brief  日志配置
*  @param  [IN] openLog     是否开启日志
*  @param  [IN] logPath     日志路径，默认为D:\
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_LogConfig(int openLog, char *logPath);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_LogConfigEx(ICE_HANDLE hSDK, int openLog, char *logPath);

/**
*  @brief  抓拍信息输出编码配置
*  @param  [IN] hSDK       连接相机时返回的sdk句柄
*  @param  [IN] enable     是否以UTF-8编码输出抓拍信息
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_EnableUTF8(ICE_HANDLE hSDK, int enable);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetReOpenParam(ICE_HANDLE hSDK, ReOpenParam *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetReOpenParam(ICE_HANDLE hSDK, const ReOpenParam *pstParam);

/**  
*  @brief  特征码比较
*  @param  [IN] _pfResFeat1     需要比较的特征码1
*  @param  [IN] _iFeat1Len      特征码1的长度，目前需输入20
*  @param  [IN] _pfReaFeat2     需要比较的特征码2
*  @param  [IN] _iFeat2Len      特征码2的长度，目前需输入20
*  @return  匹配度，范围：0-1，值越大越匹配
*/
ICE_IPCSDK_API ICE_FLOAT ICE_IPCSDK_TYPE ICE_IPCSDK_VBR_CompareFeat(ICE_FLOAT *_pfResFeat1, ICE_U32 _iFeat1Len,
												   ICE_FLOAT *_pfReaFeat2, ICE_U32 _iFeat2Len);

/**
*  @brief 脱机语音播报参数
typdef struct
{
	ICE_U32 u32Mode;//0 不播报，1，只播报欢迎光临/一路顺风 2，播报欢迎光临/一路顺风 + 车牌
	ICE_U32 u32Reserved[16];
}
*/

/**
*  @brief  获取脱机语音播报配置
*  @param  [IN]  hSDK          连接相机时返回的sdk句柄
*  @param  [OUT] pstParam      脱机语音播报参数
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineAoParam(ICE_HANDLE hSDK, OfflineAoParam *pstParam);

/**
*  @brief  获取脱机语音播报配置
*  @param  [IN] hSDK          连接相机时返回的sdk句柄
*  @param  [IN] pstParam      脱机语音播报参数
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineAoParam(ICE_HANDLE hSDK, const OfflineAoParam *pstParam);

/**
*  @brief  通过文件名进行语音播报（单播）
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [IN] pcName      语音播报文件名
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Broadcast_ByName(ICE_HANDLE hSDK, const ICE_CHAR* pcName);

/**
*  @brief  通过文件名进行组播
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [IN] pcName      包含语音文件名的字符串
*							注：中间可以用, ; \t \n或者空格分开；如：1 2 3 4或者1,2,3,4
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BroadcastGroup_ByName(ICE_HANDLE hSDK, const ICE_CHAR* pcName);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetIOState(ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 *pu32IOState, 
												ICE_U32 *pu32Reserve1, ICE_U32 *pu32Reserve2);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLEDParam(ICE_HANDLE hSDK, ICE_LED_PARAM *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLEDParam(ICE_HANDLE hSDK, const ICE_LED_PARAM *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_SDK_GetParam(ICE_HANDLE hSDK, const void* pstData, int len, 
	ICE_U32 u32Req, ICE_U32 u32Rsp, void *pstParam, ICE_U32 u32Size, int timeout_ms);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_SDK_SetParam(ICE_HANDLE hSDK, ICE_U32 u32Req, ICE_U32 u32Rsp, 
	const void *pstParam, ICE_U32 u32Size, int timeout_ms);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLEDPro1Param(ICE_HANDLE hSDK, Led_Display_Pro1_Param *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLEDPro1Param(ICE_HANDLE hSDK, const Led_Display_Pro1_Param *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLEDCard2Param(ICE_HANDLE hSDK, Led_Card_2_total_cfg_param *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLEDCard2Param(ICE_HANDLE hSDK, const Led_Card_2_total_cfg_param *pstParam);

/**
*  @brief  获取强制脱机参数
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [OUT] pcName     强制脱机结构体
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetForceCareraOfflineParam(ICE_HANDLE hSDK, Force_camera_offline_cfg_param *pstParam);

/**
*  @brief  设置强制脱机参数
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [IN] pcName     强制脱机结构体
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetForceCareraOfflineParam(ICE_HANDLE hSDK, const Force_camera_offline_cfg_param *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetStrobeLightParam(ICE_HANDLE hSDK, strobe_light_param_st *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetStrobeLightParam(ICE_HANDLE hSDK, const strobe_light_param_st *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Update(ICE_HANDLE hSDK, const ICE_CHAR *szFilePath);

/**
*  @brief  开启是否加密
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [IN] ucEncId     如果为0则为不加密,如果为其它的则为加密
*  @param  [IN] szPwd       相机密码
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EnableEnc(ICE_HANDLE hSDK, 
	ICE_U32 u32EncId, const char *szPwd);

/**
*  @brief  修改车牌解密密码
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [IN] szOldPwd    车牌解密旧密码
*  @param  [IN] szNewPwd    车牌解密新密码
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ModifyEncPwd(ICE_HANDLE hSDK, 
	const char *szOldPwd, const char *szNewPwd);

/**
*  @brief  设置车牌解密密码
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [IN] szPwd       车牌解密密码
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDecPwd(ICE_HANDLE hSDK, const char *szPwd);


/**
*  @brief  获取系统版本
*  @param  [IN] hSDK        连接相机时返回的sdk句柄
*  @param  [IN] pstSysVersion       系统版本信息
*  @return 0 失败 1 成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetCameraInfo(ICE_HANDLE hSDK, ICE_CameraInfo *pstCameraInfo);

/**
*  @brief  设置自定义校验信息
*  @param  [IN] hSDK           连接相机时返回的sdk句柄
*  @param  [IN] old_lics       旧自定义信息 注:如果是第一次设置时,该参数为空
*  @param  [IN] new_lics       新自定义信息
*  @return 0 失败 1 成功 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLicense(ICE_HANDLE hSDK, char *old_lics, char *new_lics);

/**
*  @brief  校验自定义信息
*  @param  [IN] hSDK           连接相机时返回的sdk句柄
*  @param  [IN] license        需要校验的自定义信息
*  @return 0 失败 1 成功 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CheckLicense(ICE_HANDLE hSDK, char *license);

/**
*  @brief  设置识别区域        注意：绘制时以左下、右上为坐标基点来绘制识别矩形框。
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] nLeft          识别区域左坐标点（以左上角为坐标原点）
*  @param  [IN] nBottom        识别区域下坐标点（以左上角为坐标原点）
*  @param  [IN] nRight         识别区域右坐标点（以左上角为坐标原点）
*  @param  [IN] nTop           识别区域上坐标点（以左上角为坐标原点）
*  @param  [IN] nWidth         坐标是在什么分辨率下取得的，表示宽（如在1280*720下取得的，宽为1280）
*  @param  [IN] nHeight        坐标是在什么分辨率下取得的，表示高（如在1280*720下取得的，高为720）
*  @return 设置状态 1 设置成功 0 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLoop(ICE_HANDLE hSDK, ICE_U32 nLeft, ICE_U32 nBottom, 
	ICE_U32 nRight, ICE_U32 nTop, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  获取识别区域        注意：绘制时以左下、右上为坐标基点来绘制识别矩形框。
*  @param  [IN] hSDK           sdk句柄
*  @param  [OUT] nLeft          识别区域左坐标点（以左上角为坐标原点）
*  @param  [OUT] nBottom        识别区域下坐标点（以左上角为坐标原点）
*  @param  [OUT] nRight         识别区域右坐标点（以左上角为坐标原点）
*  @param  [OUT] nTop           识别区域上坐标点（以左上角为坐标原点）
*  @param  [OUT] nWidth         坐标是在什么分辨率下取得的，表示宽（如在1280*720下取得的，宽为1280）
*  @param  [OUT] nHeight        坐标是在什么分辨率下取得的，表示高（如在1280*720下取得的，宽为720）
*  @return 设置状态 1 获取成功 0 获取失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLoop(ICE_HANDLE hSDK, ICE_U32 *nLeft, ICE_U32 *nBottom, 
	ICE_U32 *nRight, ICE_U32 *nTop, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  设置触发模式
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] u32TriggerMode 触发模式（0：线圈触发 1：视频触发）
*  @return  设置状态 1 设置成功 0 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTriggerMode(ICE_HANDLE hSDK, ICE_U32 u32TriggerMode);

/**
*  @brief  获取触发模式
*  @param  [IN] hSDK           sdk句柄
*  @param  [OUT] u32TriggerMode 触发模式（0：线圈触发 1：视频触发）
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTriggerMode(ICE_HANDLE hSDK, ICE_U32 *pu32TriggerMode);

//接受是否叠加变
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetShowPlate(ICE_HANDLE hSDK,int nEnableShow);


/*
*  @brief  获取耗时
*  @param  [IN] hSDK           sdk句柄
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetNeedTime(ICE_HANDLE hSDK);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDrawLoop(ICE_HANDLE hSDK, int nEnableDraw);


/*
*  @brief  设置LED屏配置信息
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN]                结构体
*  @return  设置状态 1 设置成功 0 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLedCreen_Config(ICE_HANDLE hSDK,ICE_OFFLINE_LED_CONFIG* ledConfig);

/*
*  @brief  获取LED屏配置信息
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN]                结构体
*  @return  获取状态 1 设置成功 0 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLedCreen_Config(ICE_HANDLE hSDK, ICE_OFFLINE_LED_CONFIG* ledConfig);

/*
*  @brief  设置脱机计费规则
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN]                结构体
*  @return  设置状态 1 设置成功 0 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineCharge_Rule(ICE_HANDLE hSDK, ICE_OFFLINE_CHARGE_RULE* charRule);

/*
*  @brief  获取获取脱机计费规则
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN]                结构体
*  @return  获取状态 1 设置成功 0 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineCharge_Rule(ICE_HANDLE hSDK, ICE_OFFLINE_CHARGE_RULE* charRule);


/*
*  @brief  设置脱机组播信息
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN]                结构体
*  @return  设置状态 1 设置成功 0 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineMulticast_Config(ICE_HANDLE hSDK, ICE_OFFLINE_MULTICAST_CONFIG* multiCast);

/*
*  @brief  获取脱机组播信息
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN]                结构体
*  @return  获取状态 1 设置成功 0 设置失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineMulticast_Config(ICE_HANDLE hSDK, ICE_OFFLINE_MULTICAST_CONFIG* multiCast);


/*
*  @brief  设置脱机计费的回调
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN]                回调指针
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartPayrule(ICE_HANDLE hSDK, ICE_IPCSDK_Payrule pfpayrule);

/*
*  @brief  设置脱机计费的回调
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] psVersion      回调指针
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetCustom_Version(ICE_HANDLE hSDK, ICE_DEVICE_INFO* psVersion);

/*
*  @brief  设置脱机计费屏显串口
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstUARTCfg     串口结构体
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOffline_UART(ICE_HANDLE hSDK, const ICE_UART_PARAM *pstUARTCfg);


/*
*  @brief  删除脱机计费所有数据
*  @param  [IN] hSDK           sdk句柄
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Delete_OfflineInfo(ICE_HANDLE hSDK);


/*
*  @brief  删除脱机计费所有数据
*  @param  [IN] hSDK           sdk句柄
*  @param  [OUT] pstParam      参数结构体 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetMainSubModeParam(ICE_HANDLE hSDK, ICE_MAIN_SUB_MODE_INFO *pstParam);


/*
*  @brief  删除脱机计费所有数据
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetMainSubModeParam(ICE_HANDLE hSDK, ICE_MAIN_SUB_MODE_INFO *pstParam);

/*
脱机上报数据请求
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_payrule_send(ICE_HANDLE hSDK);
*/

/*
*  @brief  获取车辆在场信息
*  @param  [IN] hSDK				 sdk句柄
*  @param  [OUT] pcVehicleInfo       车辆在场信息缓冲区地址 
*  @param  [IN] u32PicSize			 车辆在场信息缓冲区地址大小
*  @param  [OUT] pu32PicLen	         车辆在场信息实际长度
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getOfflineVehicleInfo(ICE_HANDLE hSDK, ICE_CHAR * pcVehicleInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  获取指定车牌号的车辆在场信息
*  @param  [IN] hSDK				 sdk句柄
*  @param  [IN] pcPlateNumber		 要查询的车牌号
*  @param  [OUT] pcVehicleInfo       车辆在场信息缓冲区地址 
*  @param  [IN] u32PicSize			 车辆在场信息缓冲区地址大小
*  @param  [OUT] pu32PicLen	         车辆在场信息实际长度
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getOfflineVehicleInfo_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR *pcPlateNumber, 
																 ICE_CHAR * pcVehicleInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  获取脱机计费数据
*  @param  [IN] hSDK				 sdk句柄
*  @param  [OUT] pcVehicleInfo       脱机计费数据缓冲区地址 
*  @param  [IN] u32PicSize			 脱机计费数据缓冲区地址大小
*  @param  [OUT] pu32PicLen	         脱机计费数据实际长度
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  获取所有脱机计费数据（包括脱机计费为0的数据）
*  @param  [IN] hSDK				 sdk句柄
*  @param  [OUT] pcVehicleInfo       脱机计费数据缓冲区地址 
*  @param  [IN] u32PicSize			 脱机计费数据缓冲区地址大小
*  @param  [OUT] pu32PicLen	         脱机计费数据实际长度
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getAllPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/**
*  @brief  通过该回调函数获取相机的IO状态变化
*  @param  [OUT] pvParam             相机连接回调参数, 用于区分不同相机IO事件(ICE_IPCSDK_SetIOEventCallBack传入的最后一个参数)
*  @param  [OUT] pcIP                相机ip
*  @param  [OUT] u32EventType        事件类型 0：IO变化
*  @param  [OUT] u32IOData1       事件数据1 事件类型为0时，代表IO1的状态;）
*  @param  [OUT] u32IOData2       事件数据2 （事件类型为0时，代表IO2的状态）
*  @param  [OUT] u32IOData3       事件数据3 （事件类型为0时，代表IO3的状态）
*  @param  [OUT] u32IOData4       事件数据4 （事件类型为0时，代表IO4的状态）
*/
typedef void (__stdcall * ICE_IPCSDK_OnIOEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32IOData1, ICE_U32 u32IOData2, ICE_U32 u32IOData3, ICE_U32 u32IOData4);

/**
*  @brief  设置相机IO状态变化回调事件
*  @param  [IN] hSDK                     连接相机时返回的sdk句柄
*  @param  [IN] pfOnIOEvent              IO事件回调
*  @param  [IN] pvIOEventParam           IO事件回调参数,用于区分不同IO变化事件
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetIOEventCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnIOEvent pfOnIOEvent, void *pvIOEventParam);

/**
*  @brief  设置无牌车输出，是否支持车款识别
*  @param  [IN] hSDK							连接相机时返回的sdk句柄
*  @param  [IN] s32FilterByPlate				是否输出无牌车（1：过滤，不输出无牌车，0：不过滤，输出无牌车;注意：设置为线圈模式时，此项强制为0）
*  @param  [IN] s32EnableNoPlateVehicleBrand    是否支持无牌车的车款识别(1:输出，0：不输出；注意：当不输出无牌车时，此项强制为0)
*  @param  [IN] s32EnableNoPlateVehicleBrand    是否支持有牌车的车款识别（1：输出，0：不输出）
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetVehicleBrand(ICE_HANDLE hSDK, ICE_S32 s32FilterByPlate, 
	ICE_S32 s32EnableNoPlateVehicleBrand, ICE_S32 s32EnableVehicleBrand);

/**
*  @brief  获取无牌车输出，是否支持车款识别
*  @param  [IN] hSDK							连接相机时返回的sdk句柄
*  @param  [OUT] s32FilterByPlate				是否过滤无牌车（1：过滤，不输出无牌车，0：不过滤，输出无牌车）
*  @param  [OUT] s32EnableNoPlateVehicleBrand    是否支持无牌车的车款识别(1:输出，0：不输出)
*  @param  [OUT] s32EnableNoPlateVehicleBrand    是否支持有牌车的车款识别（1：输出，0：不输出）
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetVehicleBrand(ICE_HANDLE hSDK, ICE_S32 *ps32FilterByPlate, 
	ICE_S32 *ps32EnableNoPlateVehicleBrand, ICE_S32 *ps32EnableVehicleBrand);

/*
*  @brief  获取本机脱机计费信息
*  @param  [IN] hSDK				 sdk句柄
*  @param  [OUT] pcVehicleInfo       脱机计费数据缓冲区地址 
*  @param  [IN] u32PicSize			 脱机计费数据缓冲区地址大小
*  @param  [OUT] pu32PicLen	         脱机计费数据实际长度
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getLocalPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  获取相机信息
*  @param  [IN] hSDK				 sdk句柄
*  @param  [OUT] stDeviceParam       相机信息结构体 
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDeviceParam(ICE_HANDLE hSDK, ICE_DEVICE_PARAM *stDeviceParam);

/*
*  @brief  获取相机类型（82/83）
*  @param  [IN] hSDK				 sdk句柄
*  @param  [OUT] pu32DevType       相机类型（1:82相机，2:83相机）
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDeviceType(ICE_HANDLE hSDK, ICE_U32 *pu32DevType);

/*
*  @brief  获取相机类型（82/83）
*  @param  [IN] hSDK				 sdk句柄
*  @param  [OUT] pcCamType			 相机类型型号
*  @param  [IN] u32StrLen			 pcCamType长度
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDeviceTypeExt(ICE_HANDLE hSDK, ICE_CHAR *pcCamType, ICE_U32 u32StrLen);

/*
*  @brief  Wav语音播报
*  @param  [IN] hSDK	  sdk句柄
*  @param  [IN] pcData    Wav数据
*  @param  [IN] u32Len    数据长度
*  @return  获取状态 1 成功 0 失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BroadcastWav(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len);

/*
*  @brief  批量升级黑白名单，支持csv文件升级
*  @param  [IN] hSDK	  sdk句柄
*  @param  [IN] pFileName 黑白名单文件路径
*  @param  [IN] s32Type   操作类型 0：导入并追加，1导入并覆盖
*  @return  0 网络原因导致升级失败
			1 升级成功
			2 Flash空间不足
			3 校验失败	
			4 超时
			5 文件不存在
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UpdateWhiteListBatch(ICE_HANDLE hSDK, ICE_CHAR *szFilePath, ICE_S32 s32Type);

/*
*  @brief  设置产品型号
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetProductInfoParam(ICE_HANDLE hSDK, T_ProductInfo *pstParam);

/*
*  @brief  获取产品型号
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetProductInfoParam(ICE_HANDLE hSDK, T_ProductInfo *pstParam);

/*
*  @brief  绑定IO输入
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDevAlarmIn(ICE_HANDLE hSDK, T_DevAlarmIn *pstParam);

/*
*  @brief  绑定IO输出
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SeDevAlarmOutBindCfg(ICE_HANDLE hSDK, T_DevAlarmOutBindCfg *pstParam);


/*
*  @brief  增加串口协议
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_AddUartOperPro(ICE_HANDLE hSDK, T_UartOperPro *pstParam);

/*
*  @brief  删除串口协议
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DelUartOperPro(ICE_HANDLE hSDK, T_UartOperPro *pstParam);

/*
*  @brief  绑定串口协议
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UartBindPro(ICE_HANDLE hSDK, T_UartBindPro *pstParam);

/*
*  @brief  获取串口协议列表
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetProtocolList(ICE_HANDLE hSDK, T_ProtocolList *pstParam);

/*
*  @brief  获取额外的报警输入参数
*  @param  [IN] hSDK           sdk句柄
*  @param  [OUT] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAlarmInExt(ICE_HANDLE hSDK, ALARM_IN_EXT *pstParam);

/*
*  @brief  设置额外的报警输入参数
*  @param  [IN] hSDK           sdk句柄
*  @param  [IN] pstParam       参数结构体  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAlarmInExt(ICE_HANDLE hSDK, ALARM_IN_EXT *pstParam);


/**
*  @brief  通过该回调函数获取相机的对讲状态变化
*  @param  [OUT] pvParam             相机连接回调参数, 用于区分不同相机对讲事件(ICE_IPCSDK_SetTalkEventCallBack传入的最后一个参数)
*  @param  [OUT] pcIP                相机ip
*  @param  [OUT] u32EventType        事件类型 0：普通非对讲状态 1：触发对讲 2：正在对讲 3:相机端发起对讲后，被某个管理端拒绝通话 4:通话中断
*  @param  [OUT] pcTalkIp			 事件类型为2时，表示与相机端接通的管理端ip；事件类型为3时，表示拒绝与相机通话的管理端ip
*  @param  [OUT] u32Reserve1		预留1 
*  @param  [OUT] u32Reserve2        预留2 
*  @param  [OUT] u32Reserve3        预留3 
*  @param  [OUT] u32Reserve4        预留4 
*/
typedef void (__stdcall * ICE_IPCSDK_OnTalkEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, const ICE_CHAR *pcTalkIp, 
											   ICE_U32 u32Reserve1, ICE_U32 u32Reserve2, ICE_U32 u32Reserve3, ICE_U32 u32Reserve4);

/**
*  @brief  设置相机对讲状态变化回调事件
*  @param  [IN] hSDK                     连接相机时返回的sdk句柄
*  @param  [IN] pfOnIOEvent              对讲事件回调
*  @param  [IN] pvIOEventParam           对讲事件回调参数,用于区分不同对讲变化事件
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetTalkEventCallBack(ICE_HANDLE hSDK, ICE_IPCSDK_OnTalkEvent pfOnTalkEvent, void *pvTalkEventParam);

/**
*  @brief  获取不规则识别区域
*  @param  [IN]  hSDK                     连接相机时返回的sdk句柄
*  @param  [OUT] stVLoopRect              不规则识别区域结构体
*  @param  [IN]  nWidth					  坐标是在什么分辨率下取得的，表示宽（如在1280*720下取得的，宽为1280）
*  @param  [IN]  nHeight				  坐标是在什么分辨率下取得的，表示高（如在1280*720下取得的，高为720）
*  @return 0失败 1成功
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetQuadRangle(ICE_HANDLE hSDK, ICE_QUADRANGLE_S *stVLoopRect, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  设置不规则识别区域
*  @param  [IN]  hSDK                     连接相机时返回的sdk句柄
*  @param  [IN]  stVLoopRect              不规则识别区域结构体
*  @param  [IN]  nWidth					  坐标是在什么分辨率下取得的，表示宽（如在1280*720下取得的，宽为1280）
*  @param  [IN]  nHeight				  坐标是在什么分辨率下取得的，表示高（如在1280*720下取得的，高为720）
*  @return 0失败 1成功
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetQuadRangle(ICE_HANDLE hSDK, const ICE_QUADRANGLE_S *stVLoopRect, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  获取相机UID
*  @param  [IN]   hSDK                     连接相机时返回的sdk句柄
*  @param  [OUT]  pstParam				   UID参数结构体
*  @return 0失败 1成功
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetUID(ICE_HANDLE hSDK, UID_PARAM *pstParam);

/**
*  @brief  获取相机用户型号
*  @param  [IN]   hSDK                     连接相机时返回的sdk句柄
*  @param  [OUT]  pstParam				   用户型号参数结构体
*  @return 0失败 1成功
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetUserModel(ICE_HANDLE hSDK, UserModelParam *pstParam);

/**
*  @brief  设置相机用户型号
*  @param  [IN]   hSDK                     连接相机时返回的sdk句柄
*  @param  [OUT]  pstParam				   用户型号参数结构体
*  @return 0失败 1成功
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetUserModel(ICE_HANDLE hSDK, UserModelParam *pstParam);

/**
*  @brief  启用旧的升级模式
*  @param  [IN]   hSDK                     连接相机时返回的sdk句柄
*  @return 0失败 1成功
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOldUpdateModeEnable(ICE_HANDLE hSDK);

/**
*  @brief  连接evtp(事件分发协议，车牌识别事件都必须在连接了此协议的基础上才会上报数据)
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pcPasswd		连接密码（密码为null时为不加密连接，不为null为加密连接）
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartEvtp(ICE_HANDLE hSDK, const ICE_CHAR* pcPasswd);

/**
*  @brief  断开evtp连接
*  @param  [IN] hSDK			sdk句柄
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StopEvtp(ICE_HANDLE hSDK);

/**
*  @brief  聚焦操作
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam		聚焦参数结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAFZoom(ICE_HANDLE hSDK, const ICE_IPC_AF_ZOOM *pstParam);

/**
*  @brief  获取镜头是聚焦还是变焦
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pu32LensType	1：定焦 2：变焦
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLensType(ICE_HANDLE hSDK, ICE_U32 *pu32LensType);

/**
*  @brief  设置NTP配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam	    NTP参数结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetNtpCfg(ICE_HANDLE hSDK, T_SntpCfg *pstParam);

/**
*  @brief  获取NTP配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam	    NTP参数结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetNtpCfg(ICE_HANDLE hSDK, T_SntpCfg *pstParam);

/**
*  @brief  设置时区配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam	    时区参数结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTimeZone(ICE_HANDLE hSDK, T_TimeZone *pstParam);

/**
*  @brief  获取时区配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam	    时区参数结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTimeZone(ICE_HANDLE hSDK, T_TimeZone *pstParam);

/**
*  @brief  设置时间
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam	    时区参数结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTime(ICE_HANDLE hSDK, T_TimeCfgInfo *pstParam);

/**
*  @brief  获取时间
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam	    时区参数结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTime(ICE_HANDLE hSDK, T_TimeCfgInfo *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SyncPcTime(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SupportNewNtp(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SupportNewTimeZone(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SupportNewTime(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CgiGet(const char *ip, int port, const char *key, char *data, int size);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CgiSet(const char *ip, int port, const char *key, const char *data, char *rsp);

/**
*  @brief  获取抓拍图片osd叠加配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam	    图片osd叠加配置
*  @return 0失败，1成功，2相机版本不支持
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSnapOsdCfg(ICE_HANDLE hSDK, T_SnapOsdCfg *pstParam);

/**
*  @brief  设置抓拍图片osd叠加配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam	    图片osd叠加配置
*  @return 0失败，1成功，2相机版本不支持
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSnapOsdCfg(ICE_HANDLE hSDK, const T_SnapOsdCfg *pstParam);

/**
*  @brief  设置音量配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam	    音量配置结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetVolumeParam(ICE_HANDLE hSDK, const  ICE_TALK_BACK_VOLUME_PARAM *pstParam);

/**
*  @brief  获取音量配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam	    音量配置结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetVolumeParam(ICE_HANDLE hSDK, ICE_TALK_BACK_VOLUME_PARAM *pstParam);

/**
*  @brief  清空语音文件
*  @param  [IN] hSDK			sdk句柄
*  @return 0失败，1成功
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ClearAudioDir(ICE_HANDLE hSDK);

/**
*  @brief  导入语音文件
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pcFilePath		语音文件路径
*  @return 0失败，1成功,2文件不存在，3文件不符合规范
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UploadAudioFile(ICE_HANDLE hSDK, const char* pcFilePath);

/**
*  @brief  连接新协议的连接（目前黑白名单使用新协议的相机，需要通过此接口连接新协议）
*  @param  [IN] hSDK			sdk句柄
*  @return 0失败，1成功，2已连接
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ConnectNormalSdk(ICE_HANDLE hSDK);

/**
*  @brief  断开新协议的连接（不需要使用黑白名单时，可通过此接口断开连接）
*  @param  [IN] hSDK			sdk句柄
*  @return 0失败，1成功
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DisconnectNormalSdk(ICE_HANDLE hSDK);

/**
*  @brief  是否支持新模式（目前主要用来判断黑白名单使用新模式还是旧模式）
*  @param  [IN] hSDK			sdk句柄
*  @return 0不支持，1支持，2 获取失败，3 sdk未连接，4新协议未连接
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SupportNewMode(ICE_HANDLE hSDK);

/**
*  @brief  设置黑白名单使用新模式还是旧模式
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] mode			0 旧模式（编码为gbk），1新模式（编码为utf8)
*  @return 0相机不支持，1设置成功，2 设置失败，3 sdk未连接，4新协议未连接
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetWBListMode(ICE_HANDLE hSDK, ICE_U32 mode);

/**
*  @brief  获取http post模式5参数
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam		http post参数
*  @param  [OUT] pstExtParam	模式5额外定制参数
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetHttpPostMode5Cfg(ICE_HANDLE hSDK, ICE_HTTP_POST_NEW_PARAM *pstParam, 
																	ICE_HTTP_POST5_EXTPARAM *pstExtParam);

/**
*  @brief  设置http post模式5参数
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam		http post参数
*  @param  [IN] pstExtParam	模式5额外定制参数
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetHttpPostMode5Cfg(ICE_HANDLE hSDK, const ICE_HTTP_POST_NEW_PARAM *pstParam, 
																	const ICE_HTTP_POST5_EXTPARAM *pstExtParam);

/**
*  @brief  ETC扣费请求
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] ptEtcCharge		ETC扣费请求数据
*  @param  [OUT] ptEtcChargeRsp	ETC扣费请求应答数据
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SendEtcCharge(ICE_HANDLE hSDK, const T_EtcCharge *ptEtcCharge, 
																T_EtcChargeRsp *ptEtcChargeRsp);

/**
*  @brief  获取云平台参数
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam		云平台参数
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetCloudCfgParam(ICE_HANDLE hSDK, T_CloudCfgParamExt *pstParam);

/**
*  @brief  设置云平台参数
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam		云平台参数
*  @return 0失败，1成功，2参数不符合规范
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetCloudCfgParam(ICE_HANDLE hSDK, const T_CloudCfgParamExt *pstParam);

/**
*  @brief  获取校时开关配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam		校时开关配置
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSyncTimeParam(ICE_HANDLE hSDK, T_SyncTimeParam *pstParam);

/**
*  @brief  设置校时开关配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam		校时开关配置
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSyncTimeParam(ICE_HANDLE hSDK, const T_SyncTimeParam *pstParam);

/**
*  @brief  获取MQTT参数配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam		MQTT参数配置结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetMqttCfg(ICE_HANDLE hSDK, T_MqttCfgParam *pstParam);

/**
*  @brief  设置MQTT参数配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam		MQTT参数配置结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetMqttCfg(ICE_HANDLE hSDK, const T_MqttCfgParam *pstParam);

/**
*  @brief  获取MQTT参数默认配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam		MQTT参数配置结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetMqttDefCfg(ICE_HANDLE hSDK, T_MqttCfgParam *pstParam);

/**
*  @brief  设置遥控器按键功能
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] pstParam		遥控器按键参数配置结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetRemCtrlCfg(ICE_HANDLE hSDK, const T_RemCtrlCfg *pstParam);

/**
*  @brief  获取遥控器按键功能
*  @param  [IN] hSDK			sdk句柄
*  @param  [OUT] pstParam		遥控器按键参数配置结构体
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetRemCtrlCfg(ICE_HANDLE hSDK, T_RemCtrlCfg *pstParam);

/**
*  @brief  遥控器按键事件
*  @param  [OUT] pvParam		回调上下文
*  @param  [OUT] pcIP			相机ip
*  @param  [OUT] pstParam		遥控器事件结构体
*  @return void
*/
typedef void (__stdcall *ICE_IPCSDK_OnRemCtrlEvent)(void *pvParam, const ICE_CHAR *pcIP, T_RemCtrlData *ptRemCtrlData);

/**
*  @brief  设置遥控器按键事件回调
*  @param  [IN] hSDK				sdk句柄
*  @param  [IN] pfOnRemCtrlEvent	遥控器按键事件
*  @param  [IN] pvParam				回调上下文
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetRemCtrlEventCallBack(ICE_HANDLE hSDK, 
																  ICE_IPCSDK_OnRemCtrlEvent pfOnRemCtrlEvent, void *pvParam);

/**
 *  @brief  设置识别数据快速事件的相关回调函数
 *  @param  [IN] hSDK               连接相机时返回的sdk句柄
 *  @param  [IN] pfFastPlate		识别数据快速事件
 *  @param  [IN] pvFastPlateParam  	回调上下文
 *  @return void
 */
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetFastPlateCallback(ICE_HANDLE hSDK, ICE_IPCSDK_OnFastPlate pfFastPlate, void *pvFastPlateParam);

/**
 *  @brief  获取对讲配置
 *  @param  [IN] hSDK               连接相机时返回的sdk句柄
 *  @param  [OUT] ptTalkBackCfg		对接配置结构体
 *  @return 0失败，1成功
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTalkBackCfg(ICE_HANDLE hSDK, T_TalkBackCfg *ptTalkBackCfg);

/**
 *  @brief  设置对讲配置
 *  @param  [IN] hSDK               连接相机时返回的sdk句柄
 *  @param  [IN] ptTalkBackCfg		对接配置结构体
 *  @return 0失败，1成功
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTalkBackCfg(ICE_HANDLE hSDK, const T_TalkBackCfg *ptTalkBackCfg);
/*************************************************LCD/LED屏相关接口**************************************************/
//LCD屏
/**
*  @brief  连接相机
*  @param  [IN] hSDK			sdk句柄
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ConnectUserApp(ICE_HANDLE hSDK);

/**
*  @brief  设置屏控制模式
*  @param  [IN] hSDK				sdk句柄
*  @param  [IN] uiCtrlMode			屏控制模式 1 主动模式 2 被动模式
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLcdCtrlMode(ICE_HANDLE hSDK, ICE_U32 uiCtrlMode);

/**
*  @brief  设置LCD屏亮度控制
*  @param  [IN] hSDK				sdk句柄
*  @param  [IN] uiLcdBkLight		屏幕亮度，1-10个等级
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLcdBkLight(ICE_HANDLE hSDK, ICE_U32 uiLcdBkLight);

/**
*  @brief  设置LCD屏分屏
*  @param  [IN] hSDK				sdk句柄
*  @param  [IN] uiSplitScreen		1全屏 2分屏 
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*  2种模式中，切为半屏广告显示模式时，需要注意以下几点：
	半屏时的文字，以最后一次更新的文字内容为准
	二维码部分失效，只轮播半屏广告图片

*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSplitScreen(ICE_HANDLE hSDK, ICE_U32 uiSplitScreen);

/**
*  @brief  控制LCD屏显示内容与语音播报
*  @param  [IN] hSDK				sdk句柄
*  @param  [IN] tLcdShowInfo		LCD屏显示信息
*  @param  [IN] uiSetQRCodeUrl		是否设置二维码图片的URL地址，0不设置，1设置
*  @param  [IN] pucQRCodeUrl		二维码图片的URL地址
*  @param  [IN] uiSetVoiceInfo		0：不设置语音信息集 1：设置内置语音信息 2：设置TTS语音
*  @param  [IN] pucVoiceInfo		语音信息集
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*  注：此接口会自动将LCD屏切为半屏显示模式。
	如果带二维码，则广告显示区域一直是二维码图片，不会切为半屏广告图片轮播；
	如果不带二维码，则广告显示区一直轮播半屏广告图片。

*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLcdShowInfo(ICE_HANDLE hSDK, const T_LcdShowInfo *ptLcdShowInfo, 
																ICE_U32 uiSetQRCodeUrl, const ICE_U8 *pucQRCodeUrl, 
																ICE_U32 uiSetVoiceInfo, const ICE_U8 *pucVoiceInfo);

/**
*  @brief  LCD屏文字叠加清空，文字与车牌号OSD全清
*  @param  [IN] hSDK				sdk句柄
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ClearOsd(ICE_HANDLE hSDK);

/**
*  @brief	LCD屏参数配置
*  @param  [IN] hSDK				sdk句柄
*  @param  [IN] ptLcdParam			LCD屏参数结构体
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLcdParam(ICE_HANDLE hSDK, const T_LcdParam *ptLcdParam);

/**
*  @brief	上传广告图片
*  @param  [IN] hSDK				sdk句柄
*  @param  [IN] uiAdPicType			图片类型，1全屏广告图片 2分屏广告图片 3背景图片
*									全屏广告尺寸：DME88-V2001C（768*1366），
*												  DMG88-V2001C（1080*1920），
*												  DMF88-V2001C（768*1024），
*												  DCF88-V2001C（768*1024），
*												  DCE88-V3002C（768*1366），
*												  DCG88-V3002C（1080*1920），
*									分屏广告尺寸：DME88-V2001C（768*672），
*												  DMG88-V2001C（1080*960），
*												  DMF88-V2001C（768*512），
*												  DCF88-V2001C（768*512），
*												  DCE88-V3002C（768*672），
*												  DCG88-V3002C（1080*960），
*									背景图片尺寸：DME88-V2001C（768*694 / 768*704），
*												  DMG88-V2001C（1080*960），
*												  DMF88-V2001C（768*512），
*												  DCF88-V2001C（768*512），
*												  DCE88-V3002C（768*694 / 768*704），
*												  DCG88-V3002C（1080*960），
*  @param  [IN] pcAdPicPath			广告图片路径
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UploadAdvertPic(ICE_HANDLE hSDK, ICE_U32 uiAdPicType, const char *pcAdPicPath);

/**
*  @brief	LCD屏广告图片清空
*  @param  [IN] hSDK				sdk句柄
*  @param  [IN] uiAdPicType			1全屏广告图片 2分屏广告图片 
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ClearAdvertPic(ICE_HANDLE hSDK, UINT32 uiAdPicType);

//LED
/**
*  @brief  LED屏清屏
*  @param  [IN] hSDK			sdk句柄
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ClearLedOsd(ICE_HANDLE hSDK);

/**
*  @brief  设置LED屏配置
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] ptLedCfgInfo	LED屏配置
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLedCfgInfo(ICE_HANDLE hSDK, const T_LedCfgInfo *ptLedCfgInfo);

/**
*  @brief  设置LED屏显示控制
*  @param  [IN] hSDK			sdk句柄
*  @param  [IN] ptLedShowInfo	LED屏显示控制信息
*  @param  [IN] uiSetVoiceInfo	0：不设置语音信息集 1：设置内置语音信息 2：设置TTS语音
*  @param  [IN] pucVoiceInfo	语音信息集 
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLedShowInfo(ICE_HANDLE hSDK, const T_LedShowInfo *ptLedShowInfo,
											  UINT32 uiSetVoiceInfo, const UINT8 *pucVoiceInfo);

/**
*  @brief  断开连接
*  @param  [IN] hSDK	sdk句柄
*  @return 0成功，其他返回值详见E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CloseUserApp(ICE_HANDLE hSDK);

/*************************************************LCD/LED屏相关接口**************************************************/

/*************************************************对讲柱相关接口****************************************************/
/**
*  @brief  连接对讲柱
*  @param  [IN] pcIP		对讲柱IP
*  @param  [IN] pcResrv1	预留
*  @param  [IN] pcResvr2	预留
*  @param  [IN] iResvr		预留
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_RCZ_HANDLE ICE_IPCSDK_TYPE ICE_RCZSDK_Connect(const ICE_CHAR *pcIP, const ICE_CHAR *pcResrv1, const ICE_CHAR *pcResvr2, int iResvr);

/**
*  @brief  对讲柱二维码反扫事件
*  @param  [OUT] param		回调上下文
*  @param  [OUT] pcIP		相机ip
*  @param  [OUT] pacUrl		二维码url
*  @param  [OUT] iUrlLen	二维码url长度
*  @param  [OUT] pacResrv1	预留
*  @param  [OUT] pacResrv2	预留
*  @param  [OUT] iResvr1	预留
*  @param  [OUT] iResvr2	预留
*  @return void
*/
typedef void (__stdcall *ICE_RCZ_OnPayCodeEvent)(void *param, const ICE_CHAR *pcIP, const ICE_CHAR *pacUrl, int iUrlLen, const void *pacResrv1, 
												 const void *pacResrv2, int iResvr1, int iResvr2);

/**
*  @brief  注册对讲柱二维码反扫事件处理函数
*  @param  [IN] hRczSdk				对讲柱SDK句柄
*  @param  [IN] pfOnPayCodeEvent	对讲柱二维码反扫事件
*  @param  [IN] pvParam				回调上下文
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_RegPayCodeEvent(ICE_RCZ_HANDLE hRczSdk, ICE_RCZ_OnPayCodeEvent pfOnPayCodeEvent, void *pvParam);

/**
*  @brief  注销对讲柱二维码反扫事件处理函数
*  @param  [IN] hRczSdk		对讲柱SDK句柄
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_UnregPayCodeEvent(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  语音播报
*  @param  [IN] hRczSdk		对讲柱SDK句柄
*  @param  [IN] pcText		语音播报内容（utf8编码，最大90字节（含结束符））
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_Broadcast(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pcText);

/**
*  @brief  设置控制模式
*  @param  [IN] hRczSdk		对讲柱SDK句柄
*  @param  [IN] uiCtrlMode	控制模式，1.自控模式，2.第三方对接模式
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_SetCtrlMode(ICE_RCZ_HANDLE hRczSdk, ICE_U32 uiCtrlMode);

/**
*  @brief  获取控制模式
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [OUT] puiCtrlMode	控制模式，1.主动模式，2.被动模式
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_GetCtrlMode(ICE_RCZ_HANDLE hRczSdk, ICE_U32 *puiCtrlMode);

/**
*  @brief  设置LCD屏背光亮度
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [IN] uiLcdBkLight	背光亮度，范围：0-10
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_SetLcdBkLight(ICE_RCZ_HANDLE hRczSdk, ICE_U32 uiLcdBkLight);

/**
*  @brief  获取LCD屏背光亮度
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [OUT] puiLcdBkLight	背光亮度，范围：0-10
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_GetLcdBkLight(ICE_RCZ_HANDLE hRczSdk, ICE_U32 *puiLcdBkLight);

/**
*  @brief  LCD屏文字OSD叠加
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [IN] tRczTextOsd		文字叠加结构体
*  @return 0失败，1成功
*  注：当需要同时显示二维码和osd文字时，需要先显示二维码、再叠加osd文字。
*  注：当传入的每一行内容都为空时，接口返回失败
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_SetTextOsd(ICE_RCZ_HANDLE hRczSdk, const T_RczTextOsd *tRczTextOsd);

/**
*  @brief  LCD屏文字叠加清空
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @return 0失败，1成功
*  注：清除文字叠加和二维码显示
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_ClearOsd(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  LCD屏图片删除
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [IN] pacPicName		图片名称，utf8编码
*  @return 0失败，1成功， 2相机返回图片不存在
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_DelPic(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pacPicName);

/**
*  @brief  显示二维码图片
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [IN] pacQrCodeUrl	二维码图片url,utf8编码，最大长度256字节
*  @param  [IN] iPosX			X坐标，范围：0-800
*  @param  [IN] iPosY			Y坐标，范围：0-1280			
*  @return 0失败，1成功，2设置成功但是图片显示会越界
*  注：当需要同时显示二维码和osd文字时，需要先显示二维码、再叠加osd文字。
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_ShowQRCodePic(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pacQrCodeUrl, int iPosX, int iPosY);

/**
*  @brief  上传图片
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [IN] pcAdPicPath		图片路径，utf8编码
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_UploadPic(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pcAdPicPath);

/**
*  @brief  LCD屏图片显示
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [IN] pacPicName		图片名称，utf8编码
*  @return 0失败，1成功， 2相机返回图片不存在
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_PicPlay(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pacPicName);

/**
*  @brief  远程开关闸
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_RemoteSwitch(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  设置音量
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @param  [IN] uiVolumn		音量，范围0-10
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_SetSayVol(ICE_RCZ_HANDLE hRczSdk, ICE_U32 uiVolume);

/**
*  @brief  开始视频
*  @param  [IN] hRczSdk          对讲柱SDK句柄
*  @param  [IN] u8MainStream	是否为主码流（1：主码流 0：子码流）
*  @param  [IN] hWnd          视频播放窗口句柄
*  @return 1 成功 0 失败 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_StartStream(ICE_RCZ_HANDLE hRczSdk, 
															  ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  结束视频
*  @param  [IN] hRczSdk          对讲柱SDK句柄
*  @return 1 成功 0 失败 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_StopStream(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  控制对讲柱自身开闸
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_Switch(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  断开对讲柱连接
*  @param  [IN] hRczSdk			对讲柱SDK句柄
*  @return 0失败，1成功
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_DisConnect(ICE_RCZ_HANDLE hRczSdk);
/*************************************************对讲柱相关接口****************************************************/

#ifdef __cplusplus
}
#endif

#endif