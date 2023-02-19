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

//����2�ֵ���Լ����ʽ��ֻ�ܶ�ѡһ
//#define ICE_IPCSDK_TYPE _stdcall //�����ͻ����ã���VB6����DLL����
#define ICE_IPCSDK_TYPE _cdecl   //Ĭ�Ͽ�����������ͻ�����

#ifdef ICE_IPCSDK_EXPORTS
#define ICE_IPCSDK_API __declspec(dllexport) 
#else
#define ICE_IPCSDK_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

//
#define USEUPDATE        1    //�����demoʹ�÷ſ������ӿ�  1demoҪ  0 ocx��Ҫ    
#define USE_FFMPEG		 1    //  0 ocx��Ҫ
//#define WIN32_SAVE_JPG        //ץ�� ����jpg 32λ����
//#define TEST_TOOL         // ȥ��ʱ��ͬ��

/**
* @brief  ����¼�ö������
*/
typedef enum
{
	ICE_DEVICE_OFFLINE,		//����
	ICE_DEVICE_ONLINE,		//����
	ICE_DEVICE_IO_CHANGED			//IO״̬�ı�
} ICE_DEVICE_EVENT_TYPE;

typedef enum
{
	ICE_PORT_BASICSETTING,	//�������ö˿�
	ICE_PORT_OFFLINEPAY		//�ѻ��Ʒ����ö˿�
}E_ICEPORT;

/**
*  @brief  �������ص��ӿڣ���������������ʱ��sdk��ص��ýӿ�
*  @param  [OUT] pvParam        Ϊ�û��Զ���������������ֲ�ͬ��sdkʹ���ߣ��������߳���ں����Ĳ���
*  @param  [OUT] u8PayloadType  Ϊpayload���ͣ�ȡֵΪ����������ĺ�
*  @param  [OUT] u32Timestamp   Ϊʱ���
*  @param  [OUT] pvData         Ϊ�յ������ݵ�ַ
*  @param  [OUT] s32Len         Ϊ�յ������ݳ���
*/
typedef void (__stdcall * ICE_IPCSDK_OnStream)(void *pvParam, 
	ICE_U8 u8PayloadType, ICE_U32 u32Timestamp, 
	void *pvData, ICE_S32 s32Len);


/**
*  @brief  ͼ��֡�ص��ӿڣ��������һ֡ͼ��ʱ��sdk��ص��ýӿ�
*  @param  [OUT] pvParam        Ϊ�û��Զ���������������ֲ�ͬ��sdkʹ���ߣ��������߳���ں����Ĳ���
*  @param  [OUT] u32Timestamp   Ϊʱ���
*  @param  [OUT] pu8Data        Ϊͼ�����ݵ�ַ���飬�ֱ���y��u��v
*  @param  [OUT] s32Linesize    Ϊÿɨ�������ݳ������飬�ֱ���y��u��v��ÿɨ���г���
*  @param  [OUT] s32Width       Ϊͼ����
*  @param  [OUT] s32Height      Ϊͼ��߶�
*/
typedef void (__stdcall * ICE_IPCSDK_OnFrame)(
	void *pvParam, ICE_U32 u32Timestamp, 
	ICE_U8 *pu8Data[], ICE_S32 s32Linesize[], 
	ICE_S32 s32Width, ICE_S32 s32Height, 
	ICE_U8 *rawdata, ICE_S32 rawlen);

/**
*  @brief  �ѻ��Ʒѹ��� �ص��ϱ�����
*  @param  [OUT] pvParam        Ϊ�û��Զ���������������ֲ�ͬ��sdkʹ���ߣ��������߳���ں����Ĳ���
*/
typedef void (__stdcall * ICE_IPCSDK_Payrule)(void *param, ICE_U32 type, void *data, ICE_U32 len);

/*#define REQ_TYPE_H264 0x01	//����h264����
#define REQ_TYPE_JPEG 0x02	//����ץ��ͼ��
#define REQ_TYPE_ALGO 0x04	//�����㷨����*/

/**
*  @brief  ȫ�ֳ�ʼ��
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Init();
/**
*  @brief  ȫ���ͷ�
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Fini();

/**
*  @brief  ����ipc����ӿ�
*  @param  [IN] pcIP                ���ip��ַ
*  @param  [IN] u8OverTCP           �Ƿ�ʹ��tcpģʽ(1Ϊʹ�ã�0Ϊ��ʹ�ã�
*  @param  [IN] u16RTSPPort         rtsp�˿ڣ�554��
*  @param  [IN] u16ICEPort          ˽��Э���Ӧ�Ķ˿ڣ�8117��
*  @param  [IN] u16OnvifPort        onvif�˿ڣ�8080��
*  @param  [IN] u8MainStream        �Ƿ�������������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] pfOnStream          �������ص���ַ������ΪNULL
*  @param  [IN] pvStreamParam       �������ص������������ֿ���ͬ��ʹ���߼���
*  @param  [IN] pfOnFrame           ͼ��֡�ص���ַ������ΪNULL��ֻ�е�u8ReqType������REQ_TYPE_H264ʱ��������
*  @param  [IN] pvFrameParam        ͼ��֡�ص������������ֿ���ͬ��ʹ���߼���
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_Open(const ICE_CHAR *pcIP, ICE_U8 u8OverTCP, 
	ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, ICE_U16 u16OnvifPort, ICE_U8 u8MainStream, 
	ICE_IPCSDK_OnStream pfOnStream, void *pvStreamParam, 
	ICE_IPCSDK_OnFrame pfOnFrame, void *pvFrameParam);

/**
*  @brief  ���������ʹ���������ӣ�
*  @param  [IN] pcIP                  ���ip��ַ
*  @param  [IN] pcPasswd              ��������
*  @param  [IN] u8OverTCP             �Ƿ�ʹ��tcpģʽ(1Ϊʹ�ã�0Ϊ��ʹ�ã�
*  @param  [IN] u16RTSPPort           rtsp�˿�(554)
*  @param  [IN] u16ICEPort            ˽��Э���Ӧ�Ķ˿�(8117)
*  @param  [IN] u16OnvifPort          onvif�˿ڣ�8080��
*  @param  [IN] u8MainStream          �Ƿ�������������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] pfOnStream            �������ص���ַ������ΪNULL
*  @param  [IN] pvStreamParam         �������ص������������ֿ���ͬ��ʹ���߼���
*  @param  [IN] pfOnFrame             ͼ��֡�ص���ַ������ΪNULL��ֻ�е�u8ReqType������REQ_TYPE_H264ʱ��������
*  @param  [IN] pvFrameParam          ͼ��֡�ص������������ֿ���ͬ��ʹ���߼���
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull)
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
*  @brief  ץ�����ݻص��ӿ�
*  @param  [OUT] pvParam                 �ص������������ֿ���ͬ��ʹ���߼��ɣ�open��������һ��������
*  @param  [OUT] pcIP                    ���ip
*  @param  [OUT] pcNumber                ���ƺ�
*  @param  [OUT] pcColor                 ������ɫ����"��ɫ","��ɫ","��ɫ","��ɫ",����ɫ����
*  @param  [OUT] pcPicData               ȫ������
*  @param  [OUT] u32PicLen               ȫ�����ݳ���
*  @param  [OUT] pcCloseUpPicData        ��������
*  @param  [OUT] u32CloseUpPicLen        �������ݳ���
*  @param  [OUT] s16Speed                �ٶ�
*  @param  [OUT] s16VehicleType          ��������
*  @param  [OUT] s16FalsePlate           ��ٳ���
*  @param  [OUT] s16Reserved2            Ԥ������2
*  @param  [OUT] fPlateConfidence        ���ƴ��ֵ ��⣺SDK����ķ�Χ����IE�������õĳ�����ֵ��������28�����磺IE���õ���10����Χ��10-28
*                                                   ���ã�sdk����ĳ��ƴ��ֵ������˫���������sdk�յ���������ĳ�����Ϣ������ͨ������
*                                                   ���ֵ��ѡ���ĸ���Ϣ���ӿɿ���Ϊ���յ�������
*  @param  [OUT] u32VehicleColor         ������ɫ
*  @param  [OUT] u32PlateType            ��������
*  @param  [OUT] u32VehicleDir           ��������
*  @param  [OUT] u32AlarmType            ��������
*  @param  [OUT] u32SerialNum            ץ�ĵ���ţ��������һ��ץ�Ŀ�ʼ�������������������㣩
*  @param  [OUT] uCapTime                ʵʱץ��ʱ�䣬��1970��1��1����㿪ʼ������
*  @param  [OUT] u32ResultHigh           ����ʶ�����ݽṹ��(ICE_VDC_PICTRUE_INFO_S)ָ���8λ
*  @param  [OUT] u32ResultLow            ����ʶ�����ݽṹ��(ICE_VDC_PICTRUE_INFO_S)ָ���8λ
*/
typedef void (__stdcall * ICE_IPCSDK_OnPlate)(void *pvParam, const ICE_CHAR *pcIP, 
	const ICE_CHAR *pcNumber, const ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *pcCloseUpPicData, ICE_U32 u32CloseUpPicLen, 
	ICE_S16 s16Speed, ICE_S16 s16VehicleType, ICE_S16 s16FalsePlate, ICE_S16 s16Reserved2, 
	ICE_FLOAT fPlateConfidence, ICE_U32 u32VehicleColor, ICE_U32 u32PlateType, ICE_U32 u32VehicleDir, 
	ICE_U32 u32AlarmType, ICE_U32 u32SerialNum, ICE_U32 uCapTime, ICE_U32 u32ResultHigh, ICE_U32 u32ResultLow);

/**
*  @brief  ץ�����ݻص��ӿ�
*  @param  [OUT] pvParam                 �ص������������ֿ���ͬ��ʹ���߼��ɣ�open��������һ��������
*  @param  [OUT] pcIP                    ���ip
*  @param  [OUT] pcNumber                ���ƺ�
*  @param  [OUT] u32SerialNum            ץ�ĵ���ţ��������һ��ץ�Ŀ�ʼ�������������������㣩
*  @param  [OUT] uCapTime                ʵʱץ��ʱ�䣬��1970��1��1����㿪ʼ������
*  @param  [OUT] ptSrv					 Ԥ��
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
*  @brief  ��ѡ��ٳ��ƹ���ʱ����ٳ��ƻص��ӿ�
*  @param  [OUT] pvParam                 �ص������������ֿ���ͬ��ʹ���߼��ɣ�ICE_IPCSDK_SetFlasePlateCallback��������һ��������
*  @param  [OUT] pcIP                    ���ip
*  @param  [OUT] pcPicData               ȫ������
*  @param  [OUT] u32PicLen               ȫ�����ݳ���
*  @param  [OUT] strPlateNum			 ���ƺ���
*  @param  [OUT] u32CapTime				 ץ��ʱ��
*  @param  [OUT] strVehLogName           ��������
*  @param  [OUT] strResrv1				 Ԥ������1
*  @param  [OUT] u32VehType				 ��������
*  @param  [OUT] u32Resrv2				 Ԥ������2
*  @param  [OUT] u32ResultHigh           ����ʶ�����ݽṹ��(ICE_VDC_PICTRUE_INFO_S)ָ���8λ
*  @param  [OUT] u32ResultLow            ����ʶ�����ݽṹ��(ICE_VDC_PICTRUE_INFO_S)ָ���8λ
*/
typedef void (__stdcall * ICE_IPCSDK_OnFlasePlate)(void *pvParam, const ICE_CHAR *pcIP, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *strResrv1, ICE_U32 u32Resrv1, 
	ICE_CHAR *strResrv2, ICE_CHAR *strResrv3, ICE_U32 u32Resrv2, ICE_U32 u32Resrv3, ICE_U32 u32ResultHigh, ICE_U32 u32ResultLow);

/**
*  @brief  ��Ƶ����
*  @param  [IN] pcIP                    ���ip
*  @param  [IN] u8OverTCP               �Ƿ�ʹ��tcpģʽ��1��ʹ��tcp 0����ʹ��tcp��ʹ��udp��
*  @param  [IN] u8MainStream            �Ƿ�������������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] hWnd                    Ԥ����Ƶ�Ĵ��ھ��
*  @param  [IN] pfOnPlate               ���ƻص�
*  @param  [IN] pvPlateParam            ���ƻص������������ֿ���ͬ��ʹ���߼���
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview(const ICE_CHAR *pcIP, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  ��Ƶ����
*  @param  [IN] pcDeveloperID			������ID
*  @param  [IN] pcKey					������Key
*  @param  [IN] pcSN					�豸���к�
*  @param  [IN] u8OverTCP               �Ƿ�ʹ��tcpģʽ��1��ʹ��tcp 0����ʹ��tcp��ʹ��udp��
*  @param  [IN] u8MainStream            �Ƿ�������������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] hWnd                    Ԥ����Ƶ�Ĵ��ھ��
*  @param  [IN] pfOnPlate               ���ƻص�
*  @param  [IN] pvPlateParam            ���ƻص������������ֿ���ͬ��ʹ���߼���
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_P2P(const ICE_CHAR *pcDeveloperID, 
													 const ICE_CHAR *pcKey, 
													 const ICE_CHAR *pcSN, 
													 ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
													 ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  ��Ƶ����(ʹ����������)
*  @param  [IN] pcIP                    ���ip
*  @param  [IN] pcPasswd                ��������
*  @param  [IN] u8OverTCP               �Ƿ�ʹ��tcpģʽ��1��ʹ��tcp 0����ʹ��tcp��ʹ��udp��
*  @param  [IN] u8MainStream            �Ƿ�������������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] hWnd                    Ԥ����Ƶ�Ĵ��ھ��
*  @param  [IN] pfOnPlate               ���ƻص�
*  @param  [IN] pvPlateParam            ���ƻص������������ֿ���ͬ��ʹ���߼���
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  ��Ƶ����(ʹ����������)
*  @param  [IN] pcDeveloperID			������ID
*  @param  [IN] pcKey					������Key
*  @param  [IN] pcSN					�豸���к�
*  @param  [IN] pcPasswd                ��������
*  @param  [IN] u8OverTCP               �Ƿ�ʹ��tcpģʽ��1��ʹ��tcp 0����ʹ��tcp��ʹ��udp��
*  @param  [IN] u8MainStream            �Ƿ�������������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] hWnd                    Ԥ����Ƶ�Ĵ��ھ��
*  @param  [IN] pfOnPlate               ���ƻص�
*  @param  [IN] pvPlateParam            ���ƻص������������ֿ���ͬ��ʹ���߼���
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreview_Passwd_P2P(const ICE_CHAR *pcDeveloperID, 
															const ICE_CHAR *pcKey, 
															const ICE_CHAR *pcSN,
															const ICE_CHAR *pcPasswd, 
															ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
														    ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam);

/**
*  @brief  ��Ƶ������չ�ӿ�
*  @param  [IN] pcIP                   ���ip
*  @param  [IN] u8OverTCP              �Ƿ�ʹ��tcpģʽ(1��ʹ��tcp 0����ʹ��tcp��ʹ��udp)
*  @param  [IN] u8MainStream           �Ƿ�������������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] hWnd                   Ԥ����Ƶ�Ĵ��ھ��
*  @param  [IN] pfOnPlate              ���ƻص�
*  @param  [IN] pvPlateParam           ���ƻص������������ֿ���ͬ��ʹ���߼���
*  @param  [IN] u16RTSPPort            rtsp�˿�
*  @param  [IN] u16ICEPort             ˽��Э��Ķ˿�
*  @param  [IN] u16OnvifPort           onvif�˿�
*  @param  [IN] u16EvtpPort            ����˽��Э��˿�
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull)
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenPreviewExt(const ICE_CHAR *pcIP, 
	ICE_U8 u8OverTCP, ICE_U8 u8MainStream, ICE_U32 hWnd, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvPlateParam, 
	ICE_U16 u16RTSPPort, ICE_U16 u16ICEPort, 
	ICE_U16 u16OnvifPort, ICE_U16 u16EvtpPort);

/**
*  @brief  ��Ƶ������չ�ӿڣ�ʹ���������ӣ�
*  @param  [IN] pcIP                   ���ip
*  @param  [IN] pcPasswd               ����
*  @param  [IN] u8OverTCP              �Ƿ�ʹ��tcpģʽ(1��ʹ��tcp 0����ʹ��tcp��ʹ��udp)
*  @param  [IN] u8MainStream           �Ƿ�������������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] hWnd                   Ԥ����Ƶ�Ĵ��ھ��
*  @param  [IN] pfOnPlate              ���ƻص�
*  @param  [IN] pvPlateParam           ���ƻص������������ֿ���ͬ��ʹ���߼���
*  @param  [IN] u16RTSPPort            rtsp�˿�
*  @param  [IN] u16ICEPort             ˽��Э��Ķ˿�
*  @param  [IN] u16OnvifPort           onvif�˿�
*  @param  [IN] u16EvtpPort            ����˽��Э��˿�
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull)
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
*  @brief  �����豸��������Ƶ��
*  @param  [IN] pcIP      ip��ַ
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull) 
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice(const ICE_CHAR *pcIP);

/**
*  @brief  �����豸��������Ƶ��
*  @param  [IN] pcDeveloperID ������ID
*  @param  [IN] pcKey         ������Key
*  @param  [IN] pcSN		  �豸���к�
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull) 
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN);

/**
*  @brief  �����豸��������Ƶ��(ʹ����������)
*  @param  [IN] pcIP      ip��ַ
*  @param  [IN] pcPasswd  ��������
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull) 
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_Passwd(const ICE_CHAR *pcIP, const ICE_CHAR *pcPasswd);

/**
*  @brief  �����豸��������Ƶ��(ʹ����������)
*  @param  [IN] pcDeveloperID ������ID
*  @param  [IN] pcKey         ������Key
*  @param  [IN] pcSN		  �豸���к�
*  @param  [IN] pcPasswd	  ��������
*  @return sdk���(���Ӳ��ɹ�ʱ,����ֵΪnull) 
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDevice_Passwd_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN, const ICE_CHAR *pcPasswd);

/**
*  @brief  ����ʱֻ����rtsp��������evtp(����ʶ�����ݲ����ϱ�)
*  @param  [IN] pcIP	        ���ip
*  @param  [IN] u8MainStream    �Ƿ�������������1�������� 0����������
*  @param  [IN] hWnd            Ԥ����Ƶ�Ĵ��ھ��
*  @return ʧ��ʱ������null���ɹ�ʱ������sdk���������Ƶ�����ӳɹ���Ϊ����sdk���������
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDeviceEx(const ICE_CHAR *pcIP, ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  ����ʱֻ����rtsp��������evtp(����ʶ�����ݲ����ϱ�)
*  @param  [IN] pcDeveloperID   ������ID
*  @param  [IN] pcKey           ������Key
*  @param  [IN] pcSN            ���SN
*  @param  [IN] u8MainStream    �Ƿ�������������1�������� 0����������
*  @param  [IN] hWnd            Ԥ����Ƶ�Ĵ��ھ��
*  @return ʧ��ʱ������null���ɹ�ʱ������sdk���������Ƶ�����ӳɹ���Ϊ����sdk���������
*/
ICE_IPCSDK_API ICE_HANDLE ICE_IPCSDK_TYPE ICE_IPCSDK_OpenDeviceEx_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, const ICE_CHAR *pcSN, 
																	  ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  ��ʼ��Ƶ
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [IN] u8MainStream  �Ƿ�Ϊ��������1�������� 0��������, 3��˫Ŀ��2·������, 2��˫Ŀ��2·��������
*  @param  [IN] hWnd          ��Ƶ���Ŵ��ھ��
*  @return 1 ������Ƶ���ɹ� 0 ������Ƶ��ʧ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartStream(ICE_HANDLE hSDK, 
	ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  ������Ƶ
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_StopStream(ICE_HANDLE hSDK);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetVideoWnd(ICE_HANDLE hSDK, ICE_U32 hWnd);

/**
*  @brief  �����������ص�
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [IN] pfOnStream    �������ص��ӿڣ���������������ʱ��sdk��ص��ýӿ�
*��@param  [IN] pvParam       ͼ��֡�ص������������ֿ���ͬ��ʹ���߼���
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetDataCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnStream pfOnStream, void *pvParam);

/**
*  @brief  ������չ�ӿ�
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @return 0 ʧ��, 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TriggerExt(ICE_HANDLE hSDK);

/**
*  @brief  ͼ��֡�ص�
*  @param  [OUT] pvParam              ��ICE_IPCSDK_SetFrameCallback��Ӧ���������ֲ�ͬ��ʹ����
*  @param  [OUT] u32Timestamp         ʱ���
*  @param  [OUT] pu8DataY             ͼ���������飬���y
*  @param  [OUT] pu8DataU             ͼ���������飬���u
*  @param  [OUT] pu8DataV             ͼ����������, ���v
*  @param  [OUT] s32LinesizeY         ÿɨ�������ݳ�������, ���y��ÿɨ���г���
*  @param  [OUT] s32LinesizeU         ÿɨ�������ݳ�������, ���u��ÿɨ���г���
*  @param  [OUT] s32LinesizeV         ÿɨ�������ݳ�������, ���v��ÿɨ���г���
*  @param  [OUT] s32Width             ͼ����
*  @param  [OUT] s32Height            ͼ��߶�
*/
typedef void (__stdcall * ICE_IPCSDK_OnFrame_Planar)(
	void *pvParam, ICE_U32 u32Timestamp, 
	ICE_U8 *pu8DataY, ICE_U8 *pu8DataU, ICE_U8 *pu8DataV, 
	ICE_S32 s32LinesizeY, ICE_S32 s32LinesizeU, ICE_S32 s32LinesizeV, 
	ICE_S32 s32Width, ICE_S32 s32Height);

/**
*  @brief  ���ý���ͼ��ص�
*  @param  [IN] hSDK           �������ʱ���ص�sdk���
*  @param  [IN] pfOnFrame      ͼ��֡�ص���ַ
*  @param  [IN] pvParam        ͼ��֡�ص�����,�����ֿ���ͬ��ʹ���߼���
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetFrameCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnFrame_Planar pfOnFrame, void *pvParam);

/**
*  @brief  ����ץ���¼��ص�
*  @param  [IN] hSDK            �������ʱ���ص�sdk���
*  @param  [IN] pfOnPlate       ���ƻص�
*  @param  [IN] pvParam         ���ƻص�����,�����ֿ���ͬ��ʹ���߼���
*��@return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetPlateCallback(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnPlate pfOnPlate, void *pvParam);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetPlateCallback_Cdecl(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnPlate_Cdecl pfOnPlate, void *pvParam);

/**
*  @brief  ���ù�ѡ��ٳ��ƹ���ʱ����ٳ��ƻص�
*  @param  [IN] hSDK            �������ʱ���ص�sdk���
*  @param  [IN] pfOnFlasePlate  ��ٳ��ƻص�
*  @param  [IN] pvParam         ��ٳ��ƻص�����,�����ֿ���ͬ��ʹ���߼���
*��@return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetFlasePlateCallback(ICE_HANDLE hSDK,
	ICE_IPCSDK_OnFlasePlate pfOnFlasePlate, void *pvParam);

/**
*  @brief  �Ͽ�����
*  @param  [IN] hSDK    �������ʱ���ص�sdk���
*  return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Close(ICE_HANDLE hSDK);

/*
�����㷨����ӿ�

hSDKΪICE_IPCSDK_Open�����ص�sdk���
pstParamΪ�㷨����ṹ��ָ��

����ֵΪICE_COM_STATUS_Eö��ֵ���μ�ice_com_type.h
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetVDParam(ICE_HANDLE hSDK, 
	const ICE_VD_PARAM_S *pstParam);

/*
��ȡ��ǰ�㷨����ӿ�

hSDKΪICE_IPCSDK_Open�����ص�sdk���
pstParamΪ�㷨����ṹ��ָ��

����ֵΪICE_COM_STATUS_Eö��ֵ���μ�ice_com_type.h
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
�����㷨����ӿ�

hSDKΪICE_IPCSDK_Open�����ص�sdk���
pstParamΪ�㷨����ṹ��ָ��

����ֵΪICE_COM_STATUS_Eö��ֵ���μ�ice_com_type.h
*/
/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDTCAParam(ICE_HANDLE hSDK, 
	const ICE_CLBR_PARAM *pstCLBRParam, const ICE_DTCA_PARAM_ALGO *pstDTCAParam);*/

/*
��ȡ��ǰ�㷨����ӿ�

hSDKΪICE_IPCSDK_Open�����ص�sdk���
pstParamΪ�㷨����ṹ��ָ��

����ֵΪICE_COM_STATUS_Eö��ֵ���μ�ice_com_type.h
*/
/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDTCAParam(ICE_HANDLE hSDK, 
	ICE_CLBR_PARAM *pstCLBRParam, ICE_DTCA_PARAM_ALGO *pstDTCAParam);*/

/*
�����㷨����ӿ�

hSDKΪICE_IPCSDK_Open�����ص�sdk���
pstParamΪ�㷨����ṹ��ָ��

����ֵΪICE_COM_STATUS_Eö��ֵ���μ�ice_com_type.h
*/
/*ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTCNTParam(ICE_HANDLE hSDK, 
	const ICE_TCNT_PARAM_ALGO *pstTCNTParam);*/

/*
��ȡ��ǰ�㷨����ӿ�

hSDKΪICE_IPCSDK_Open�����ص�sdk���
pstParamΪ�㷨����ṹ��ָ��

����ֵΪICE_COM_STATUS_Eö��ֵ���μ�ice_com_type.h
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
�����ع�ӿ�

hSDKΪICE_IPCSDK_Open�����ص�sdk���
u32ExpLineΪ�ع�ʱ��
s32AGainΪģ������
s32DGainΪ��������

����ֵΪICE_COM_STATUS_Eö��ֵ���μ�ice_com_type.h
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetExpAttr(ICE_HANDLE hSDK, const ICE_ExpAttr_S *pstParam);

/*
��ȡ��ǰ�㷨����ӿ�

hSDKΪICE_IPCSDK_TYPE ICE_IPCSDK_Open�����ص�sdk���
pu32ExpLineΪ�ع�ʱ��
ps32AGainΪģ������
ps32DGainΪ��������

����ֵΪICE_COM_STATUS_Eö��ֵ���μ�ice_com_type.h
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetExpAttr(ICE_HANDLE hSDK, ICE_ExpAttr_S *pstParam);

/**
*  @brief  ʱ��ͬ��
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [IN] u16Year       ͬ��ʱ�����
*  @param  [IN] u8Month       ͬ��ʱ�����
*  @param  [IN] u8Day         ͬ��ʱ�����
*  @param  [IN] u8Hour        ͬ��ʱ���ʱ
*  @param  [IN] u8Min         ͬ��ʱ��ķ�
*  @param  [IN] u8Sec         ͬ��ʱ�����
*  @return 0 ʧ��, 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SyncTime(ICE_HANDLE hSDK, 
	ICE_U16 u16Year, ICE_U8 u8Month, ICE_U8 u8Day, 
	ICE_U8 u8Hour, ICE_U8 u8Min, ICE_U8 u8Sec = 0);

/**
*  @brief  ��ȡʱ��ͬ��
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [IN] u16Year       ͬ��ʱ�����
*  @param  [IN] u8Month       ͬ��ʱ�����
*  @param  [IN] u8Day         ͬ��ʱ�����
*  @param  [IN] u8Hour        ͬ��ʱ���ʱ
*  @param  [IN] u8Min         ͬ��ʱ��ķ�
*  @param  [IN] u8Sec         ͬ��ʱ�����
*  @return 0 ʧ��, 1 �ɹ�
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
*  @brief  ��ȡ���ip
*  @param  [IN]  hSDK             �������ʱ���ص�sdk���
*  @param  [OUT] pu32IP           ���ip
*  @param  [OUT] pu32Mask         �������
*  @param  [OUT] pu32Gateway      �������
*��@return 0 ��ȡʧ�� 1 ��ȡ�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetIPAddr(ICE_HANDLE hSDK, 
	ICE_U32 *pu32IP, ICE_U32 *pu32Mask, ICE_U32 *pu32Gateway);

/**
*  @brief  �������ip
*  @param  [IN]  hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pu32IP           ���ip
*  @param  [IN] pu32Mask         �������
*  @param  [IN] pu32Gateway      �������
*��@return 0 ����ʧ�� 1 ���óɹ�
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
*  @brief  ��ȡ�������������
*  @param  [IN]  hSDK               �������ʱ���ص�sdk���    
*  @param  [IN] u32Index            IO��(0:��ʾIO1 1:��ʾIO2)
*  @param  [OUT] pu32IdleState      ��������״̬�����ã�1 �ǳ�����0�ǳ��գ�
*  @param  [OUT] ps32DelayTime      �л�״̬��ʱ�䣨-1��ʾ���ָ� ��λ��s��
*  @param  [OUT] pu32Reserve        Ԥ������
*  @return 0 ��ȡʧ�� 1 ��ȡ�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAlarmOutConfig(
	ICE_HANDLE hSDK, ICE_U32 u32Index, ICE_U32 *pu32IdleState, 
	ICE_S32 *ps32DelayTime, ICE_U32 *pu32Reserve);

/**
*  @brief  ���ÿ������������
*  @param  [IN]  hSDK               �������ʱ���ص�sdk���    
*  @param  [IN] u32Index            IO��(0:��ʾIO1 1:��ʾIO2)
*  @param  [IN] pu32IdleState      ��������״̬�����ã�1 �ǳ�����0�ǳ��գ�
*  @param  [IN] s32DelayTime      �л�״̬��ʱ�䣨-1��ʾ���ָ� ��λ��s��
*  @param  [IN] u32Reserve        Ԥ������
*  @return 0 ����ʧ�� 1 ���óɹ�
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
*  @brief  �������
*  @param  [IN] hSDK �������ʱ���ص�sdk���
*  @return 0 ����ʧ�� 1 �����ɹ�
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
*  @brief  ��ȡosd����
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pstOSDAttr       OSD�ṹ��(ICE_OSDAttr_S)
*  @return ��ȡ�ɹ� ��ȡʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOSDCfg(ICE_HANDLE hSDK, ICE_OSDAttr_S *pstOSDAttr);

/**
*  @brief  ����osd����
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pstOSDAttr       OSD�ṹ��(ICE_OSDAttr_S)
*  @return ���óɹ� ����ʧ��
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
*  @brief  �򿪵�բ
*  @param  [IN] hSDK  �������ʱ���ص�sdk���
*  @return 1 �򿪳ɹ� 0 ��ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_OpenGate(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_OpenGate2(ICE_HANDLE hSDK);

/**
*  @brief  ���Ƶ�բ(���������)
*  @param  [IN] hSDK            �������ʱ���ص�sdk���
*  @param  [IN] u32Index        ���Ƶ�IO��(0:��ʾIO1 1:��ʾIO2 2:��ʾIO3 3:��ʾIO4)
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ControlAlarmOut(ICE_HANDLE hSDK, ICE_U32 u32Index);

/**
*  @brief  ��ʼ�Խ�
*  @param  [IN] hSDK  �������ʱ���ص�sdk���
*  @return 1 �ɹ� 0 ʧ�� 2 ռ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BeginTalk(ICE_HANDLE hSDK);

/**
*  @brief  ��ʼ�Խ�
*  @param  [IN] hSDK  �������ʱ���ص�sdk���
*  @param  [OUT] stTalkInfo  �Խ���Ϣ
*  @param  [IN] nResvr1 Ԥ��
*  @param  [IN] nResvr2 Ԥ��
*  @return 1 �ɹ� 0 ʧ�� 2 ռ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BeginTalk_Ex(ICE_HANDLE hSDK, ICE_TALK_INFO *stTalkInfo, ICE_U32 nResvr1, ICE_U32 nResvr2);

/**
*  @brief  �ܾ��Խ�
*  @param  [IN] hSDK  �������ʱ���ص�sdk���
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_RefuseTalk(ICE_HANDLE hSDK);

/**
*  @brief  ���ԶԽ�
*  @param  [IN] hSDK  �������ʱ���ص�sdk���
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_IgnoreTalk(ICE_HANDLE hSDK);

/**
*  @brief  �����Խ�
*  @param  [IN] hSDK  �������ʱ���ص�sdk���
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_EndTalk(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_IsTalking(ICE_HANDLE hSDK);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_Preview(ICE_HANDLE hSDK, ICE_U32 u32Preview);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetPhyChnCfg(ICE_HANDLE hSDK, ICE_PHYCHN_CFG_S *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetPhyChnCfg(ICE_HANDLE hSDK, const ICE_PHYCHN_CFG_S *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetARegCfg(ICE_HANDLE hSDK, ICE_EXP_AREGULATE_PARAM *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetARegCfg(ICE_HANDLE hSDK, const ICE_EXP_AREGULATE_PARAM *pstParam);

/**
*  @brief  ��ȡ��������
*  @param  [IN]  hSDK             �������ʱ���ص�sdk���
*  @param  [OUT] pstUARTCfg       �������ò����ṹ��(ICE_UART_PARAM)
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetUARTCfg(ICE_HANDLE hSDK, ICE_UART_PARAM *pstUARTCfg);

/**
*  @brief  ���ô�������
*  @param  [IN]  hSDK             �������ʱ���ص�sdk���
*  @param  [OUT] pstUARTCfg       �������ò���
*  @return 0 ʧ�� 1 �ɹ�
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
*  @brief  ���úڰ���������
*  @param  [IN] hSDK         �������ʱ���ص�sdk���
*  @param  [IN] mode         ������ģʽ��0��ʾ����������1��ʾʵʱ����,2 ��������բ�򲻹�����
*  @param  [IN] match        ������ƥ�����ƶȣ���Χ��70%-100%����Ĭ�ϣ�80%��
*  @param  [IN] bmode        ������ģʽ��0 ��������բ��1 ��բ��
*  @param  [IN] bmatch       ������ƥ�����ƶȣ���Χ��70%-100%����Ĭ�ϣ�80%��
*  @param  [IN] tmode        ��ʱ��ģʽ��0 ��������բ��1 ��բ��
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetWhiteListParam(ICE_HANDLE hSDK, 
	int mode, int match, int bmode, int bmatch, int tmode);

/**
*  @brief  ��ȡ�ڰ���������
*           ע��:�������������������������£�ǰ������Ž��а������Ĺ���ƥ��ʹ򿪵�բ�Ĺ�����
*                          ����ģʽ��Ҫ����������״̬�µİ���������ƽ̨����ɵģ�����������������ɵ������
*                ʵʱ���������۶�����������״̬������ǰ��������а������Ĺ���ƥ��ʹ򿪵�բ�Ĺ�����
*  @param  [IN]  hSDK        �������ʱ���ص�sdk���
*  @param  [OUT] mode        ������ģʽ��0��ʾ����������1��ʾʵʱ����,2 ��������բ�򲻹�����
*  @param  [OUT] match       ������ƥ�����ƶȣ���Χ��70%-100%����Ĭ�ϣ�80%��
*  @param  [OUT] bmode       ������ģʽ��0 ��������բ��1 ��բ��
*  @param  [OUT] bmatch      ������ƥ�����ƶȣ���Χ��70%-100%����Ĭ�ϣ�80%��
*  @param  [OUT] tmode       ��ʱ��ģʽ��0 ��������բ��1 ��բ��
*  @return 1 �ɹ� 0 ʧ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetWhiteListParam(ICE_HANDLE hSDK, 
	int* mode, int* match, int *bmode, int *bmatch, int *tmode);


/*  @brief  ���úڰ���������
*           ע��:�������������������������£�ǰ������Ž��а������Ĺ���ƥ��ʹ򿪵�բ�Ĺ�����
*                          ����ģʽ��Ҫ����������״̬�µİ���������ƽ̨����ɵģ�����������������ɵ������
*                ʵʱ���������۶�����������״̬������ǰ��������а������Ĺ���ƥ��ʹ򿪵�բ�Ĺ�����
*  @param  [IN]  hSDK        �������ʱ���ص�sdk���
*  @param  [OUT] whiteList   �ڰ������ṹ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetNewWhiteListParam(ICE_HANDLE hSDK, WhiteList_Param* whiteList);

/*  @brief  ��ȡ�ڰ���������
*           ע��:�������������������������£�ǰ������Ž��а������Ĺ���ƥ��ʹ򿪵�բ�Ĺ�����
*                          ����ģʽ��Ҫ����������״̬�µİ���������ƽ̨����ɵģ�����������������ɵ������
*                ʵʱ���������۶�����������״̬������ǰ��������а������Ĺ���ƥ��ʹ򿪵�բ�Ĺ�����
*  @param  [IN]  hSDK        �������ʱ���ص�sdk���
*  @param  [IN] whiteList   �ڰ������ṹ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetNewWhiteListParam(ICE_HANDLE hSDK,  WhiteList_Param* whiteList);


/**
*  @brief  ����
*  @param  [IN]  hSDK                �������ʱ���ص�sdk���
*  @param  [OUT] pcNumber            ���ƺ�
*  @param  [OUT] pcColor             ������ɫ��"��ɫ","��ɫ","��ɫ","��ɫ",����ɫ����
*  @param  [OUT] pcPicData           ץ��ͼƬ��������ַ
*  @param  [IN]  u32PicSize          ץ��ͼƬ��������С
*  @param  [OUT] pu32PicLen          ץ��ͼƬʵ�ʳ���
*  @return 1 �ɹ� 0 ʧ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Trigger(ICE_HANDLE hSDK, ICE_CHAR *pcNumber, ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicSize, ICE_U32 *pu32PicLen);

/**
*  @brief  ��ȡ���״̬
*  @param  [IN] hSDK      �������ʱ���ص�sdk���
*  @return 0 ���� 1 ���� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetStatus(ICE_HANDLE hSDK);

/**
*  @brief  ֻץ��,��ʶ��
*  @param  [IN]  hSDK            �������ʱ���ص�sdk���
*  @param  [IN]  pcPicData       ץ��ͼƬ��������ַ
*  @param  [IN]  u32PicSize      ץ��ͼƬ��������С
*  @param  [OUT] pu32PicLen      ץ��ͼƬʵ�ʳ���
*  @return 1 ץ�ĳɹ� 0 ץ��ʧ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Capture(ICE_HANDLE hSDK, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicSize, ICE_U32 *pu32PicLen);

/**
*  @brief  Ϊ���� ������ץͼ�Ľӿ�
*  @param  [IN]  hSDK            �������ʱ���ص�sdk���
*  @param  [IN]  filepath        �ļ�·��
*  @return 1 ץ�ĳɹ� 0 ץ��ʧ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Capture_BZ(ICE_HANDLE hSDK, ICE_CHAR *filepath);

/**
*  @brief  ͸�����ڻص�����
*  @param  [OUT] pvParam      ���ڻص��������������ֲ�ͬ���ڣ�ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack��������һ��������
*  @param  [OUT] pcIP         ���ip
*  @param  [OUT] pcData       ��������
*  @param  [OUT] u32Len       ���ݳ���
*/
typedef void (__stdcall * ICE_IPCSDK_OnSerialPort)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  ����͸������
*  @param  [IN] hSDK                   �������ʱ���ص�sdk���
*  @param  [IN] pfOnSerialPort         ICE_IPCSDK_OnSerialPort�ص�����
*  @param  [IN] pvSerialPortParam      ���ڻص��������������ֲ�ͬ����
*  @return void 
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  ͸�����ڽ����¼��ص��ӿ�(rs232)
*  @param  [OUT] pvParam      ���ڻص��������������ֲ�ͬ���ڣ�ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack_RS232��������һ��������
*  @param  [OUT] pcIP         ���ip
*  @param  [OUT] pcData       ��������
*  @param  [OUT] u32Len       ���ݳ���
*/
typedef void (__stdcall * ICE_IPCSDK_OnSerialPort_RS232)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  ����͸�����ڽ����¼�(rs232)
*  @param  [IN] hSDK                   �������ʱ���ص�sdk���
*  @param  [IN] pfOnSerialPort         ICE_IPCSDK_OnSerialPort_RS232�ص�����
*  @param  [IN] pvSerialPortParam      ���ڻص��������������ֲ�ͬ����
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack_RS232(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort_RS232 pfOnSerialPort, void *pvSerialPortParam);

typedef void (*ICE_IPCSDK_TYPE ICE_IPCSDK_OnSerialPort_Cdecl)(void *pvParam, 
	const ICE_CHAR *pcIP, ICE_CHAR *pcData, ICE_U32 u32Len);

ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetSerialPortCallBack_Cdecl(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnSerialPort_Cdecl pfOnSerialPort, void *pvSerialPortParam);

/**
*  @brief  ����͸������(rs485)����
*  @param  [IN] hSDK      �������ʱ���ص�sdk���
*  @param  [IN] pcData    ��������
*  @param  [IN] u32Len    ���ݳ���
*  @return 0 ����ʧ�� 1 ���ͳɹ� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TransSerialPort(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  ����͸������(rs232)����
*  @param  [IN] hSDK      �������ʱ���ص�sdk���
*  @param  [IN] pcData    ��������
*  @param  [IN] u32Len    ���ݳ���
*  @return 0 ����ʧ�� 1 ���ͳɹ� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_TransSerialPort_RS232(ICE_HANDLE hSDK, 
	ICE_CHAR *pcData, ICE_U32 u32Len);

/**
*  @brief  ��ȡ������������(�����ڰ�����)
*          ע������: ��ʹ���κΰ���������ǰ,������ô˽ӿ�,���ڷ����ڴ�
*  @param  [IN]  hSDK         �������ʱ���ص�sdk���
*  @param  [OUT] pu32Count    ������������
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListGetCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  ��ȡ��������(��ģʽ,�����к�Ϊ����)
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] s32Index         ��Ҫ��ȡ�İ�����������
*  @param  [OUT] pcNumber        ���������еĳ��ƺ�
*  @param  [OUT] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcType          �������� W:������ B��������
*  @param  [OUT] pcRsrv2         ���Ʊ�ע
*  @param  [OUT] pcRsrv3         Ԥ���ֶ�3
*  @param  [OUT] pcRsrv4         Ԥ���ֶ�4
*  @return 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListGetItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcType, ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  �༭��������(��������Ϊ����)
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @param  [IN] s32Index          ������
*  @param  [IN] pcNumber          �ڰ��������еĳ��ƺ�
*  @param  [IN] pcDateBegin       �ڰ��������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcDateEnd         �ڰ��������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcTimeBegin       �ڰ��������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcTimeEnd         �ڰ��������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcRsrv1           Ԥ���ֶ�1
*  @param  [IN] pcRsrv2           Ԥ���ֶ�2
*  @param  [IN] pcRsrv3           Ԥ���ֶ�3
*  @param  [IN] pcRsrv4           Ԥ���ֶ�4
*  @return 1 �༭�ɹ� 0 �༭ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListEditItem(ICE_HANDLE hSDK, ICE_S32 s32Index, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  ��Ӱ�������(��������Ϊ����)
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @param  [IN] s32Index          ������
*  @param  [IN] pcNumber          �ڰ��������еĳ��ƺ�
*  @param  [IN] pcDateBegin       �ڰ��������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcDateEnd         �ڰ��������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcTimeBegin       �ڰ��������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcTimeEnd         �ڰ��������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcRsrv1           Ԥ���ֶ�1
*  @param  [IN] pcRsrv2           Ԥ���ֶ�2
*  @param  [IN] pcRsrv3           Ԥ���ֶ�3
*  @param  [IN] pcRsrv4           Ԥ���ֶ�4
*  @return 1 ��ӳɹ� 0 ���ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListInsertItem(ICE_HANDLE hSDK, ICE_S32 s32Index, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRsrv1, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  ɾ����������(��������Ϊ����)
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @param  [IN] s32Index          ������
*  @return 1 ɾ���ɹ� 0 ɾ��ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDeleteItem(ICE_HANDLE hSDK, ICE_S32 s32Index);

/**
*  @brief  ɾ�����а�������
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @return 1 ɾ���ɹ� 0 ɾ��ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDelAllItems(ICE_HANDLE hSDK);

/**
*  @brief  ���Һڰ�������(��������Ϊ����)
*  @param  [IN] hSDK               �������ʱ���ص�sdk���
*  @param  [IN] pcNumber           �ڰ��������еĳ��ƺ�
*  @param  [IN] s32Start           ���ҵ���ʼ������
*  @param  [IN] s32Index           ���ҵõ��������ţ���ͨ���������Ż�ö�Ӧ�İ������
*  @return 1 ���ҳɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListFindItem(ICE_HANDLE hSDK, 
	const ICE_CHAR* pcNumber, ICE_S32 s32Start, ICE_S32 *s32Index);

/**
*  @brief  �༭�ڰ�������(�Գ��ƺ�Ϊ����)
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @param  [IN] pcNumber          �ڰ��������еĳ��ƺ�
*  @param  [IN] pcDateBegin       �ڰ��������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcDateEnd         �ڰ��������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcTimeBegin       �ڰ��������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcTimeEnd         �ڰ��������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcType            �������ͣ�������"W"/������"B"��
*  @param  [IN] pcRemark          ��ע
*  @param  [IN] pcRsrv2           Ԥ���ֶ�2
*  @param  [IN] pcRsrv3           Ԥ���ֶ�3
*  @param  [IN] pcRsrv4           Ԥ���ֶ�4
*  @return 1 �༭�ɹ� 0 �༭ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListEditItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, const ICE_CHAR* pcType, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  ��Ӻڰ�������(�Գ��ƺ�Ϊ����)
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @param  [IN] pcNumber          �ڰ��������еĳ��ƺ�
*  @param  [IN] pcDateBegin       �ڰ��������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcDateEnd         �ڰ��������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcTimeBegin       �ڰ��������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcTimeEnd         �ڰ��������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcType            �������ͣ�������"W"/������"B"��
*  @param  [IN] pcRemark          ��ע
*  @param  [IN] pcRsrv2           Ԥ���ֶ�2
*  @param  [IN] pcRsrv3           Ԥ���ֶ�3
*  @param  [IN] pcRsrv4           Ԥ���ֶ�4
*  @return 1 ��ӳɹ� 0 ���ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListInsertItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, const ICE_CHAR* pcType, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  ɾ���ڰ�������(�Գ��ƺ�Ϊ����)
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @param  [IN] pcNumber          Ҫɾ���ĳ��ƺ�
*  @return 1 ɾ���ɹ� 0 ɾ��ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDeleteItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  ɾ�����кڰ�������(�Գ��ƺ�Ϊ����)
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @return 1 ɾ���ɹ� 0 ɾ��ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListDelAllItems_ByNumber(ICE_HANDLE hSDK);

/**
*  @brief  ���Һڰ�������(�Գ��ƺ�Ϊ����)
*  @param  [IN] hSDK               �������ʱ���ص�sdk���
*  @param  [IN] pcNumber           �ڰ��������еĳ��ƺ�
*  @param  [OUT] pcDateBegin       �ڰ��������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcDateEnd         �ڰ��������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcTimeBegin       �ڰ��������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcTimeEnd         �ڰ��������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcType            �������ͣ�������"W"/������"B"��
*  @param  [OUT] pcRemark          ��ע
*  @param  [OUT] pcRsrv2           Ԥ���ֶ�2
*  @param  [OUT] pcRsrv3           Ԥ���ֶ�3
*  @param  [OUT] pcRsrv4           Ԥ���ֶ�4
*  @return 1 ���ҳɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WhiteListFindItem_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, ICE_CHAR* pcType, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  ͨ���ûص�������ö�������ʶ������
*  @param  [OUT] pvParam               �û��Զ������,�������ֲ�ͬ��sdkʹ����,�������߳���ں����Ĳ���(�����ô˻ص��ӿڵ����һ��������ͬ)
*  @param  [OUT] pcIP                  ���ip
*  @param  [OUT] u32CapTime            ʵʱץ��ʱ�䣬��1970��1��1����㿪ʼ������
*  @param  [OUT] pcNumber              ���ƺ�
*  @param  [OUT] pcColor               ������ɫ("��ɫ","��ɫ","��ɫ","��ɫ","��ɫ")
*  @param  [OUT] pcPicData             ȫ��ץ��ͼƬ��������ַ
*  @param  [OUT] u32PicLen             ȫ��ץ��ͼƬʵ�ʳ���
*  @param  [OUT] pcCloseUpPicData      ��дץ��ͼƬ��������ַ
*  @param  [OUT] u32CloseUpPicLen      ��дץ��ͼƬʵ�ʳ���
*  @param  [OUT] s16PlatePosLeft       �����������ϽǺ�����
*  @param  [OUT] s16PlatePosTop        �����������Ͻ�������
*  @param  [OUT] s16PlatePosRight      �����������ϽǺ�����
*  @param  [OUT] s16PlatePosBottom     �����������Ͻ�������
*  @param  [OUT] fPlateConfidence      ���ƴ��ֵ
*									   ��⣺SDK����ķ�Χ����IE�������õĳ�����ֵ��������28�����磺IE���õ���10����Χ��10-28
*									   ���ã�sdk����ĳ��ƴ��ֵ������˫���������sdk�յ���������ĳ�����Ϣ������ͨ������
*									   ���ֵ��ѡ���ĸ���Ϣ���ӿɿ���Ϊ���յ�������
*  @param  [OUT] u32VehicleColor       ������ɫ(��������������汾��(-1:δ֪,0:��ɫ,1:��ɫ,2:��ɫ,3:��ɫ,4:��ɫ,5:ҹ����ɫ,6:��ɫ,7:��ɫ,8:��ɫ,9:��ɫ)
*                                          ��������汾��(0:δ֪,1:��ɫ,2:��ɫ,3:��ɫ,4:��ɫ,5:��ɫ,6:��ɫ,7:��ɫ,8:��ɫ,9:��ɫ,10:��ɫ))
*  @param  [OUT] u32PlateType          �������ͣ������������ICE_PLATETYPE_Eö��ֵ
*  @param  [OUT] u32VehicleDir         �������� (0:��ͷ����,1:��β����,2:��ͷ�ͳ�β����)
*  @param  [OUT] u32AlarmType          �������������������ICE_VDC_ALARM_TYPEö��ֵ
*  @param  [OUT] u32Reserved1          Ԥ������1
*  @param  [OUT] u32Reserved2          Ԥ������2
*  @param  [OUT] u32Reserved3          Ԥ������3
*  @param  [OUT] u32Reserved4          Ԥ������4
*/
typedef void (__stdcall * ICE_IPCSDK_OnPastPlate)(void *pvParam, const ICE_CHAR *pcIP, 
	ICE_U32 u32CapTime, const ICE_CHAR *pcNumber, const ICE_CHAR *pcColor, 
	ICE_CHAR *pcPicData, ICE_U32 u32PicLen, ICE_CHAR *pcCloseUpPicData, ICE_U32 u32CloseUpPicLen, 
	ICE_S16 s16PlatePosLeft, ICE_S16 s16PlatePosTop, ICE_S16 s16PlatePosRight, ICE_S16 s16PlatePosBottom, 
	ICE_FLOAT fPlateConfidence, ICE_U32 u32VehicleColor, ICE_U32 u32PlateType, ICE_U32 u32VehicleDir, 
	ICE_U32 u32AlarmType, ICE_U32 u32Reserved1, ICE_U32 u32Reserved2, ICE_U32 u32Reserved3, ICE_U32 u32Reserved4);

/**
*  @brief  ���û�ö�������ʶ�����ݵ���ػص�����
*  @param  [IN] hSDK               �������ʱ���ص�sdk���
*  @param  [IN] pfOnPastPlate      ����ʶ�����ݣ�ͨ���ûص����
*  @param  [IN] pvPastPlateParam   �ص������еĲ����������ֿ���ͬ��ʹ���߼���
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
*  @brief  ͨ���ûص�������ȡ���������״̬
*  @param  [OUT] pvParam             ������ӻص�����, �������ֲ�ͬ��������¼�(ICE_IPCSDK_SetDeviceEventCallBack��������һ������)
*  @param  [OUT] pcIP                ���ip
*  @param  [OUT] u32EventType        �¼����� 0������ 1������ 2:IO�仯
*  @param  [OUT] u32EventData1       �¼�����1 �¼�����Ϊ0����1ʱ������ص����;�¼�����Ϊ2ʱ������IO1��״̬;��
*  @param  [OUT] u32EventData2       �¼�����2 ���¼�����Ϊ2ʱ������IO2��״̬��
*  @param  [OUT] u32EventData3       �¼�����3 ���¼�����Ϊ2ʱ������IO3��״̬��
*  @param  [OUT] u32EventData4       �¼�����4 ���¼�����Ϊ2ʱ������IO4��״̬��
*/
typedef void (__stdcall * ICE_IPCSDK_OnDeviceEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32EventData1, ICE_U32 u32EventData2, ICE_U32 u32EventData3, ICE_U32 u32EventData4);

/**
*  @brief  �����������״̬�ص��¼�
*  @param  [IN] hSDK                         �������ʱ���ص�sdk���
*  @param  [IN] pfOnDeviceEvent              ������ӻص�
*  @param  [IN] pvDeviceEventParam           ������ӻص�����,�������ֲ�ͬ��������¼�
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetDeviceEventCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnDeviceEvent pfOnDeviceEvent, void *pvDeviceEventParam);

/**
*  @brief  ������mac��ַ
*  @param  [IN] hSDK                  �������ʱ���ص�sdk���
*  @param  [OUT] szDevID              ���mac��ַ
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDevID(ICE_HANDLE hSDK, ICE_CHAR* szDevID);

/**
*  @brief  ��ʼ¼��
*  @param  [IN] hSDK                 �������ʱ���ص�sdk���
*  @param  [IN] pcFileName           ¼���ļ���
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartRecord(ICE_HANDLE hSDK, const ICE_CHAR *pcFileName);

/**
*  @brief  ����¼��
*  @param  [IN] hSDK                 �������ʱ���ص�sdk���
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_StopRecord(ICE_HANDLE hSDK);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetHDTriggerParam(ICE_HANDLE hSDK, HDTrigger_Param *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetHDTriggerParam(ICE_HANDLE hSDK, const HDTrigger_Param *pstParam);

/**
 *  @brief  д���û�����
 *  @param  [IN] hSDK       ����������ӿڻ�õľ��
 *  @parame [IN] pcData     ��Ҫд����û�����
 *  @return 1��ʾ�ɹ���0��ʾʧ��
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WriteUserData(ICE_HANDLE hSDK, const char* pcData);

/**
 *  @brief  ��ȡ�û�����
 *  @param  [IN] hSDK       ����������ӿڻ�õľ��
 *  @param  [OUT] szData    ��ȡ���û�����
 *  @param  [IN]  nSize     ���������ݵ���󳤶�, ���û����ݷ���Ĵ�С
 *  @return 1 ��ʾ�ɹ���0 ��ʾʧ��
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ReadUserData(ICE_HANDLE hSDK, char* pcData, int nSize);

/**
*  @brief  д����������
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [IN] pcData      ��Ҫд�������
*  @param  [IN] nOffset     ƫ����
*  @param  [IN] nLen        д�����ݵĳ���
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_WriteUserData_Binary(
	ICE_HANDLE hSDK, const char* pcData, ICE_U32 nOffset, ICE_U32 nLen);

/**
*  @brief  ������������
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [OUT] pcData     ��ȡ���û�����
*  @param  [IN] nSize       ���������ݵ���󳤶�,����������С
*  @param  [IN] nOffset     ƫ����
*  @param  [OUT] nLen       ��Ҫ�������ݵ�����,���ڶ��������Ĵ�С
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ReadUserData_Binary(
	ICE_HANDLE hSDK, char* pcData, ICE_U32 nSize, ICE_U32 nOffset, ICE_U32 nLen);

/**
*  @brief  ��ȡ��������������������������
*  @param  [IN] hSDK              �������ʱ���ص�sdk���
*  @param  [OUT] pu32Count        ������������
*  @param 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetWhiteCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  ��ȡ��������(������������,ͨ�������Ż�ȡ)
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] s32Index         ��Ҫ��ȡ�İ�����������
*  @param  [OUT] pcNumber        ���������еĳ��ƺ�
*  @param  [OUT] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcRemark        ��ע
*  @param  [OUT] pcRsrv2         Ԥ���ֶ�2
*  @param  [OUT] pcRsrv3         Ԥ���ֶ�3
*  @param  [OUT] pcRsrv4         Ԥ���ֶ�4
*  @return 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetWhiteItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  �༭��������(������������)
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pcNumber        ���������еĳ��ƺ�
*  @param  [IN] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcRemark        ��ע
*  @param  [IN] pcRsrv2         Ԥ���ֶ�2
*  @param  [IN] pcRsrv3         Ԥ���ֶ�3
*  @param  [IN] pcRsrv4         Ԥ���ֶ�4
*  @return 1 �༭�ɹ� 0 �༭ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EditWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  ��Ӱ�������(������������)
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pcNumber        ���������еĳ��ƺ�
*  @param  [IN] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcRemark        ��ע
*  @param  [IN] pcRsrv2         Ԥ���ֶ�2
*  @param  [IN] pcRsrv3         Ԥ���ֶ�3
*  @param  [IN] pcRsrv4         Ԥ���ֶ�4
*  @return 1 ��ӳɹ� 0 ���ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_InsertWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief ��ú���������
*  @param  [IN]  hSDK             �������ʱ���ص�sdk���
*  @param  [OUT] pu32Count        ����������
*  @return 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetBlackCount(ICE_HANDLE hSDK, ICE_U32 *pu32Count);

/**
*  @brief  ��ȡ��������
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] s32Index         ��Ҫ��ȡ�İ�����������
*  @param  [OUT] pcNumber        ���������еĳ��ƺ�
*  @param  [OUT] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcRemark        ��ע
*  @param  [OUT] pcRsrv2         Ԥ���ֶ�2
*  @param  [OUT] pcRsrv3         Ԥ���ֶ�3
*  @param  [OUT] pcRsrv4         Ԥ���ֶ�4
*  @return 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetBlackItem(ICE_HANDLE hSDK, ICE_S32 s32Index, ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  �༭��������
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pcNumber        ���������еĳ��ƺ�
*  @param  [IN] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcRemark        ��ע
*  @param  [IN] pcRsrv2         Ԥ���ֶ�2
*  @param  [IN] pcRsrv3         Ԥ���ֶ�3
*  @param  [IN] pcRsrv4         Ԥ���ֶ�4
*  @return 1 �༭�ɹ� 0 �༭ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EditBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  ��Ӻ�������
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pcNumber        ���������еĳ��ƺ�
*  @param  [IN] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [IN] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [IN] pcRemark        ��ע
*  @param  [IN] pcRsrv2         Ԥ���ֶ�2
*  @param  [IN] pcRsrv3         Ԥ���ֶ�3
*  @param  [IN] pcRsrv4         Ԥ���ֶ�4
*  @return 1 ��ӳɹ� 0 ���ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_InsertBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	const ICE_CHAR* pcDateBegin, const ICE_CHAR* pcDateEnd, const ICE_CHAR* pcTimeBegin, const ICE_CHAR* pcTimeEnd, 
	const ICE_CHAR* pcRemark, const ICE_CHAR* pcRsrv2, const ICE_CHAR* pcRsrv3, const ICE_CHAR* pcRsrv4);

/**
*  @brief  ɾ�����а�������(����������)
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @return 0 ɾ��ʧ�� 1 ɾ���ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DelAllWhiteItems(ICE_HANDLE hSDK);

/**
*  @brief  ɾ�����к�������(����������)
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @return 0 ɾ��ʧ�� 1 ɾ���ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DelAllBlackItems(ICE_HANDLE hSDK);

/**
*  @brief  ɾ��һ���������(����������)
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pcNumber		 ��Ҫɾ���ĳ��ƺ�
*  @return 0 ɾ��ʧ�� 1 ɾ���ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DeleteWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  ����һ���������(����������)
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pcNumber         ���������еĳ��ƺ�
*  @param  [OUT] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcRemark        ��ע
*  @param  [OUT] pcRsrv2         Ԥ���ֶ�2
*  @param  [OUT] pcRsrv3         Ԥ���ֶ�3
*  @param  [OUT] pcRsrv4         Ԥ���ֶ�4
*  @return 1 ���ҳɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_FindWhiteItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

/**
*  @brief  ɾ��һ���������
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pcNumber		 ��Ҫɾ���ĳ��ƺ�
*  @return 0 ɾ��ʧ�� 1 ɾ���ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DeleteBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber);

/**
*  @brief  ���Һ�������
*  @param  [IN] hSDK             �������ʱ���ص�sdk���
*  @param  [IN] pcNumber         ���������еĳ��ƺ�
*  @param  [OUT] pcDateBegin     ���������еĿ�ʼ����(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcDateEnd       ���������еĽ�������(��ʽΪyyyy/MM/dd)
*  @param  [OUT] pcTimeBegin     ���������еĿ�ʼʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcTimeEnd       ���������еĽ���ʱ��(��ʽΪHH:mm:ss)
*  @param  [OUT] pcRemark        ��ע
*  @param  [OUT] pcRsrv2         Ԥ���ֶ�2
*  @param  [OUT] pcRsrv3         Ԥ���ֶ�3
*  @param  [OUT] pcRsrv4         Ԥ���ֶ�4
*  @return 1 ���ҳɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_FindBlackItem(ICE_HANDLE hSDK, const ICE_CHAR* pcNumber, 
	ICE_CHAR* pcDateBegin, ICE_CHAR* pcDateEnd, ICE_CHAR* pcTimeBegin, ICE_CHAR* pcTimeEnd, 
	ICE_CHAR* pcRemark, ICE_CHAR* pcRsrv2, ICE_CHAR* pcRsrv3, ICE_CHAR* pcRsrv4);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAutoRebootParam(ICE_HANDLE hSDK, AutoRebootParam *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAutoRebootParam(ICE_HANDLE hSDK, const AutoRebootParam *pstParam);

/**
*  @brief  ��������
*  @param  [IN] hSDK       �������ʱ���ص�sdk���
*  @param  [IN] nIndex     �����ļ�����
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Broadcast(ICE_HANDLE hSDK, ICE_U16 nIndex);

/**
*  @brief  ��������
*  @param  [IN] hSDK         �������ʱ���ص�sdk���
*  @param  [IN] u32Index     ���ȳ��е�������
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetCity(ICE_HANDLE hSDK, ICE_U32 u32Index);

/**
*  @brief  �����鲥
*  @param  [IN] hSDK         �������ʱ���ص�sdk���
*  @param  [IN] pcIndex      ����������ŵ��ַ���
*							 ע���м������, ; \t \n���߿ո�ֿ����磺1 2 3 4����1,2,3,4
*  @return 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BroadcastGroup(ICE_HANDLE hSDK, const ICE_CHAR* pcIndex);

/**
*  @brief  �����豸
*  @param  [IN] szDevs       �豸mac��ַ��ip��ַ���ַ���
*							   �豸mac��ַ��ip��ַ���ַ�������ʽΪ��mac��ַ ip��ַ ���磺
*							   00-00-00-00-00-00 192.168.55.150\r\n
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SearchDev(char* szDevs);

/**
*  @brief  �����豸
*  @param  [IN] pcDeveloperID ������ID
*  @param  [IN] pcKey         ������Key
*  @param  [IN] pcSN		  �豸���к��ַ��������磺XXXXXXXX\r\nYYYYYYYY\r\nZZZZZZZ\r\n
*  @param  [IN] szSNsLen      �豸���к��ַ���������󳤶�
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SearchDev_P2P(const ICE_CHAR *pcDeveloperID, const ICE_CHAR *pcKey, char* szSNs, int szSNsLen);

/**
*  @brief  ��ȡDNS
*  @param  [IN] hSDK		�������ʱ���ص�sdk���
*  @param  [OUT] pu32DNS	��ѡDNS
*  @param  [OUT] pu32DNS2	��ѡDNS	
*  @return 0 ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDNSAddr(ICE_HANDLE hSDK, ICE_U32 *pu32DNS, ICE_U32 *pu32DNS2);

/**
*  @brief  ����DNS
*  @param  [IN] hSDK		�������ʱ���ص�sdk���
*  @param  [IN] pu32DNS		��ѡDNS
*  @param  [IN] pu32DNS2	��ѡDNS	
*  @return 0 ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDNSAddr(ICE_HANDLE hSDK, ICE_U32 u32DNS, ICE_U32 u32DNS2);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLightParam(ICE_HANDLE hSDK, LightParam *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLightParam(ICE_HANDLE hSDK, const LightParam *pstParam);

/**
*  @brief  ��־����
*  @param  [IN] openLog     �Ƿ�����־
*  @param  [IN] logPath     ��־·����Ĭ��ΪD:\
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_LogConfig(int openLog, char *logPath);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_LogConfigEx(ICE_HANDLE hSDK, int openLog, char *logPath);

/**
*  @brief  ץ����Ϣ�����������
*  @param  [IN] hSDK       �������ʱ���ص�sdk���
*  @param  [IN] enable     �Ƿ���UTF-8�������ץ����Ϣ
*  @return void
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_EnableUTF8(ICE_HANDLE hSDK, int enable);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetReOpenParam(ICE_HANDLE hSDK, ReOpenParam *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetReOpenParam(ICE_HANDLE hSDK, const ReOpenParam *pstParam);

/**  
*  @brief  ������Ƚ�
*  @param  [IN] _pfResFeat1     ��Ҫ�Ƚϵ�������1
*  @param  [IN] _iFeat1Len      ������1�ĳ��ȣ�Ŀǰ������20
*  @param  [IN] _pfReaFeat2     ��Ҫ�Ƚϵ�������2
*  @param  [IN] _iFeat2Len      ������2�ĳ��ȣ�Ŀǰ������20
*  @return  ƥ��ȣ���Χ��0-1��ֵԽ��Խƥ��
*/
ICE_IPCSDK_API ICE_FLOAT ICE_IPCSDK_TYPE ICE_IPCSDK_VBR_CompareFeat(ICE_FLOAT *_pfResFeat1, ICE_U32 _iFeat1Len,
												   ICE_FLOAT *_pfReaFeat2, ICE_U32 _iFeat2Len);

/**
*  @brief �ѻ�������������
typdef struct
{
	ICE_U32 u32Mode;//0 ��������1��ֻ������ӭ����/һ·˳�� 2��������ӭ����/һ·˳�� + ����
	ICE_U32 u32Reserved[16];
}
*/

/**
*  @brief  ��ȡ�ѻ�������������
*  @param  [IN]  hSDK          �������ʱ���ص�sdk���
*  @param  [OUT] pstParam      �ѻ�������������
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineAoParam(ICE_HANDLE hSDK, OfflineAoParam *pstParam);

/**
*  @brief  ��ȡ�ѻ�������������
*  @param  [IN] hSDK          �������ʱ���ص�sdk���
*  @param  [IN] pstParam      �ѻ�������������
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineAoParam(ICE_HANDLE hSDK, const OfflineAoParam *pstParam);

/**
*  @brief  ͨ���ļ�����������������������
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [IN] pcName      ���������ļ���
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Broadcast_ByName(ICE_HANDLE hSDK, const ICE_CHAR* pcName);

/**
*  @brief  ͨ���ļ��������鲥
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [IN] pcName      ���������ļ������ַ���
*							ע���м������, ; \t \n���߿ո�ֿ����磺1 2 3 4����1,2,3,4
*  @return 0 ʧ�� 1 �ɹ�
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
*  @brief  ��ȡǿ���ѻ�����
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [OUT] pcName     ǿ���ѻ��ṹ��
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetForceCareraOfflineParam(ICE_HANDLE hSDK, Force_camera_offline_cfg_param *pstParam);

/**
*  @brief  ����ǿ���ѻ�����
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [IN] pcName     ǿ���ѻ��ṹ��
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetForceCareraOfflineParam(ICE_HANDLE hSDK, const Force_camera_offline_cfg_param *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetStrobeLightParam(ICE_HANDLE hSDK, strobe_light_param_st *pstParam);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetStrobeLightParam(ICE_HANDLE hSDK, const strobe_light_param_st *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Update(ICE_HANDLE hSDK, const ICE_CHAR *szFilePath);

/**
*  @brief  �����Ƿ����
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [IN] ucEncId     ���Ϊ0��Ϊ������,���Ϊ��������Ϊ����
*  @param  [IN] szPwd       �������
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_EnableEnc(ICE_HANDLE hSDK, 
	ICE_U32 u32EncId, const char *szPwd);

/**
*  @brief  �޸ĳ��ƽ�������
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [IN] szOldPwd    ���ƽ��ܾ�����
*  @param  [IN] szNewPwd    ���ƽ���������
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ModifyEncPwd(ICE_HANDLE hSDK, 
	const char *szOldPwd, const char *szNewPwd);

/**
*  @brief  ���ó��ƽ�������
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [IN] szPwd       ���ƽ�������
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDecPwd(ICE_HANDLE hSDK, const char *szPwd);


/**
*  @brief  ��ȡϵͳ�汾
*  @param  [IN] hSDK        �������ʱ���ص�sdk���
*  @param  [IN] pstSysVersion       ϵͳ�汾��Ϣ
*  @return 0 ʧ�� 1 �ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetCameraInfo(ICE_HANDLE hSDK, ICE_CameraInfo *pstCameraInfo);

/**
*  @brief  �����Զ���У����Ϣ
*  @param  [IN] hSDK           �������ʱ���ص�sdk���
*  @param  [IN] old_lics       ���Զ�����Ϣ ע:����ǵ�һ������ʱ,�ò���Ϊ��
*  @param  [IN] new_lics       ���Զ�����Ϣ
*  @return 0 ʧ�� 1 �ɹ� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLicense(ICE_HANDLE hSDK, char *old_lics, char *new_lics);

/**
*  @brief  У���Զ�����Ϣ
*  @param  [IN] hSDK           �������ʱ���ص�sdk���
*  @param  [IN] license        ��ҪУ����Զ�����Ϣ
*  @return 0 ʧ�� 1 �ɹ� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CheckLicense(ICE_HANDLE hSDK, char *license);

/**
*  @brief  ����ʶ������        ע�⣺����ʱ�����¡�����Ϊ�������������ʶ����ο�
*  @param  [IN] hSDK           sdk���
*  @param  [IN] nLeft          ʶ������������㣨�����Ͻ�Ϊ����ԭ�㣩
*  @param  [IN] nBottom        ʶ������������㣨�����Ͻ�Ϊ����ԭ�㣩
*  @param  [IN] nRight         ʶ������������㣨�����Ͻ�Ϊ����ԭ�㣩
*  @param  [IN] nTop           ʶ������������㣨�����Ͻ�Ϊ����ԭ�㣩
*  @param  [IN] nWidth         ��������ʲô�ֱ�����ȡ�õģ���ʾ������1280*720��ȡ�õģ���Ϊ1280��
*  @param  [IN] nHeight        ��������ʲô�ֱ�����ȡ�õģ���ʾ�ߣ�����1280*720��ȡ�õģ���Ϊ720��
*  @return ����״̬ 1 ���óɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLoop(ICE_HANDLE hSDK, ICE_U32 nLeft, ICE_U32 nBottom, 
	ICE_U32 nRight, ICE_U32 nTop, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  ��ȡʶ������        ע�⣺����ʱ�����¡�����Ϊ�������������ʶ����ο�
*  @param  [IN] hSDK           sdk���
*  @param  [OUT] nLeft          ʶ������������㣨�����Ͻ�Ϊ����ԭ�㣩
*  @param  [OUT] nBottom        ʶ������������㣨�����Ͻ�Ϊ����ԭ�㣩
*  @param  [OUT] nRight         ʶ������������㣨�����Ͻ�Ϊ����ԭ�㣩
*  @param  [OUT] nTop           ʶ������������㣨�����Ͻ�Ϊ����ԭ�㣩
*  @param  [OUT] nWidth         ��������ʲô�ֱ�����ȡ�õģ���ʾ������1280*720��ȡ�õģ���Ϊ1280��
*  @param  [OUT] nHeight        ��������ʲô�ֱ�����ȡ�õģ���ʾ�ߣ�����1280*720��ȡ�õģ���Ϊ720��
*  @return ����״̬ 1 ��ȡ�ɹ� 0 ��ȡʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLoop(ICE_HANDLE hSDK, ICE_U32 *nLeft, ICE_U32 *nBottom, 
	ICE_U32 *nRight, ICE_U32 *nTop, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  ���ô���ģʽ
*  @param  [IN] hSDK           sdk���
*  @param  [IN] u32TriggerMode ����ģʽ��0����Ȧ���� 1����Ƶ������
*  @return  ����״̬ 1 ���óɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTriggerMode(ICE_HANDLE hSDK, ICE_U32 u32TriggerMode);

/**
*  @brief  ��ȡ����ģʽ
*  @param  [IN] hSDK           sdk���
*  @param  [OUT] u32TriggerMode ����ģʽ��0����Ȧ���� 1����Ƶ������
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTriggerMode(ICE_HANDLE hSDK, ICE_U32 *pu32TriggerMode);

//�����Ƿ���ӱ�
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetShowPlate(ICE_HANDLE hSDK,int nEnableShow);


/*
*  @brief  ��ȡ��ʱ
*  @param  [IN] hSDK           sdk���
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetNeedTime(ICE_HANDLE hSDK);


ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDrawLoop(ICE_HANDLE hSDK, int nEnableDraw);


/*
*  @brief  ����LED��������Ϣ
*  @param  [IN] hSDK           sdk���
*  @param  [IN]                �ṹ��
*  @return  ����״̬ 1 ���óɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLedCreen_Config(ICE_HANDLE hSDK,ICE_OFFLINE_LED_CONFIG* ledConfig);

/*
*  @brief  ��ȡLED��������Ϣ
*  @param  [IN] hSDK           sdk���
*  @param  [IN]                �ṹ��
*  @return  ��ȡ״̬ 1 ���óɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLedCreen_Config(ICE_HANDLE hSDK, ICE_OFFLINE_LED_CONFIG* ledConfig);

/*
*  @brief  �����ѻ��Ʒѹ���
*  @param  [IN] hSDK           sdk���
*  @param  [IN]                �ṹ��
*  @return  ����״̬ 1 ���óɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineCharge_Rule(ICE_HANDLE hSDK, ICE_OFFLINE_CHARGE_RULE* charRule);

/*
*  @brief  ��ȡ��ȡ�ѻ��Ʒѹ���
*  @param  [IN] hSDK           sdk���
*  @param  [IN]                �ṹ��
*  @return  ��ȡ״̬ 1 ���óɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineCharge_Rule(ICE_HANDLE hSDK, ICE_OFFLINE_CHARGE_RULE* charRule);


/*
*  @brief  �����ѻ��鲥��Ϣ
*  @param  [IN] hSDK           sdk���
*  @param  [IN]                �ṹ��
*  @return  ����״̬ 1 ���óɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOfflineMulticast_Config(ICE_HANDLE hSDK, ICE_OFFLINE_MULTICAST_CONFIG* multiCast);

/*
*  @brief  ��ȡ�ѻ��鲥��Ϣ
*  @param  [IN] hSDK           sdk���
*  @param  [IN]                �ṹ��
*  @return  ��ȡ״̬ 1 ���óɹ� 0 ����ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetOfflineMulticast_Config(ICE_HANDLE hSDK, ICE_OFFLINE_MULTICAST_CONFIG* multiCast);


/*
*  @brief  �����ѻ��ƷѵĻص�
*  @param  [IN] hSDK           sdk���
*  @param  [IN]                �ص�ָ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartPayrule(ICE_HANDLE hSDK, ICE_IPCSDK_Payrule pfpayrule);

/*
*  @brief  �����ѻ��ƷѵĻص�
*  @param  [IN] hSDK           sdk���
*  @param  [IN] psVersion      �ص�ָ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetCustom_Version(ICE_HANDLE hSDK, ICE_DEVICE_INFO* psVersion);

/*
*  @brief  �����ѻ��Ʒ����Դ���
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstUARTCfg     ���ڽṹ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOffline_UART(ICE_HANDLE hSDK, const ICE_UART_PARAM *pstUARTCfg);


/*
*  @brief  ɾ���ѻ��Ʒ���������
*  @param  [IN] hSDK           sdk���
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_Delete_OfflineInfo(ICE_HANDLE hSDK);


/*
*  @brief  ɾ���ѻ��Ʒ���������
*  @param  [IN] hSDK           sdk���
*  @param  [OUT] pstParam      �����ṹ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetMainSubModeParam(ICE_HANDLE hSDK, ICE_MAIN_SUB_MODE_INFO *pstParam);


/*
*  @brief  ɾ���ѻ��Ʒ���������
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetMainSubModeParam(ICE_HANDLE hSDK, ICE_MAIN_SUB_MODE_INFO *pstParam);

/*
�ѻ��ϱ���������
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_payrule_send(ICE_HANDLE hSDK);
*/

/*
*  @brief  ��ȡ�����ڳ���Ϣ
*  @param  [IN] hSDK				 sdk���
*  @param  [OUT] pcVehicleInfo       �����ڳ���Ϣ��������ַ 
*  @param  [IN] u32PicSize			 �����ڳ���Ϣ��������ַ��С
*  @param  [OUT] pu32PicLen	         �����ڳ���Ϣʵ�ʳ���
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getOfflineVehicleInfo(ICE_HANDLE hSDK, ICE_CHAR * pcVehicleInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  ��ȡָ�����ƺŵĳ����ڳ���Ϣ
*  @param  [IN] hSDK				 sdk���
*  @param  [IN] pcPlateNumber		 Ҫ��ѯ�ĳ��ƺ�
*  @param  [OUT] pcVehicleInfo       �����ڳ���Ϣ��������ַ 
*  @param  [IN] u32PicSize			 �����ڳ���Ϣ��������ַ��С
*  @param  [OUT] pu32PicLen	         �����ڳ���Ϣʵ�ʳ���
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getOfflineVehicleInfo_ByNumber(ICE_HANDLE hSDK, const ICE_CHAR *pcPlateNumber, 
																 ICE_CHAR * pcVehicleInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  ��ȡ�ѻ��Ʒ�����
*  @param  [IN] hSDK				 sdk���
*  @param  [OUT] pcVehicleInfo       �ѻ��Ʒ����ݻ�������ַ 
*  @param  [IN] u32PicSize			 �ѻ��Ʒ����ݻ�������ַ��С
*  @param  [OUT] pu32PicLen	         �ѻ��Ʒ�����ʵ�ʳ���
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  ��ȡ�����ѻ��Ʒ����ݣ������ѻ��Ʒ�Ϊ0�����ݣ�
*  @param  [IN] hSDK				 sdk���
*  @param  [OUT] pcVehicleInfo       �ѻ��Ʒ����ݻ�������ַ 
*  @param  [IN] u32PicSize			 �ѻ��Ʒ����ݻ�������ַ��С
*  @param  [OUT] pu32PicLen	         �ѻ��Ʒ�����ʵ�ʳ���
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getAllPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/**
*  @brief  ͨ���ûص�������ȡ�����IO״̬�仯
*  @param  [OUT] pvParam             ������ӻص�����, �������ֲ�ͬ���IO�¼�(ICE_IPCSDK_SetIOEventCallBack��������һ������)
*  @param  [OUT] pcIP                ���ip
*  @param  [OUT] u32EventType        �¼����� 0��IO�仯
*  @param  [OUT] u32IOData1       �¼�����1 �¼�����Ϊ0ʱ������IO1��״̬;��
*  @param  [OUT] u32IOData2       �¼�����2 ���¼�����Ϊ0ʱ������IO2��״̬��
*  @param  [OUT] u32IOData3       �¼�����3 ���¼�����Ϊ0ʱ������IO3��״̬��
*  @param  [OUT] u32IOData4       �¼�����4 ���¼�����Ϊ0ʱ������IO4��״̬��
*/
typedef void (__stdcall * ICE_IPCSDK_OnIOEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, 
	ICE_U32 u32IOData1, ICE_U32 u32IOData2, ICE_U32 u32IOData3, ICE_U32 u32IOData4);

/**
*  @brief  �������IO״̬�仯�ص��¼�
*  @param  [IN] hSDK                     �������ʱ���ص�sdk���
*  @param  [IN] pfOnIOEvent              IO�¼��ص�
*  @param  [IN] pvIOEventParam           IO�¼��ص�����,�������ֲ�ͬIO�仯�¼�
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetIOEventCallBack(ICE_HANDLE hSDK, 
	ICE_IPCSDK_OnIOEvent pfOnIOEvent, void *pvIOEventParam);

/**
*  @brief  �������Ƴ�������Ƿ�֧�ֳ���ʶ��
*  @param  [IN] hSDK							�������ʱ���ص�sdk���
*  @param  [IN] s32FilterByPlate				�Ƿ�������Ƴ���1�����ˣ���������Ƴ���0�������ˣ�������Ƴ�;ע�⣺����Ϊ��Ȧģʽʱ������ǿ��Ϊ0��
*  @param  [IN] s32EnableNoPlateVehicleBrand    �Ƿ�֧�����Ƴ��ĳ���ʶ��(1:�����0���������ע�⣺����������Ƴ�ʱ������ǿ��Ϊ0)
*  @param  [IN] s32EnableNoPlateVehicleBrand    �Ƿ�֧�����Ƴ��ĳ���ʶ��1�������0���������
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetVehicleBrand(ICE_HANDLE hSDK, ICE_S32 s32FilterByPlate, 
	ICE_S32 s32EnableNoPlateVehicleBrand, ICE_S32 s32EnableVehicleBrand);

/**
*  @brief  ��ȡ���Ƴ�������Ƿ�֧�ֳ���ʶ��
*  @param  [IN] hSDK							�������ʱ���ص�sdk���
*  @param  [OUT] s32FilterByPlate				�Ƿ�������Ƴ���1�����ˣ���������Ƴ���0�������ˣ�������Ƴ���
*  @param  [OUT] s32EnableNoPlateVehicleBrand    �Ƿ�֧�����Ƴ��ĳ���ʶ��(1:�����0�������)
*  @param  [OUT] s32EnableNoPlateVehicleBrand    �Ƿ�֧�����Ƴ��ĳ���ʶ��1�������0���������
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetVehicleBrand(ICE_HANDLE hSDK, ICE_S32 *ps32FilterByPlate, 
	ICE_S32 *ps32EnableNoPlateVehicleBrand, ICE_S32 *ps32EnableVehicleBrand);

/*
*  @brief  ��ȡ�����ѻ��Ʒ���Ϣ
*  @param  [IN] hSDK				 sdk���
*  @param  [OUT] pcVehicleInfo       �ѻ��Ʒ����ݻ�������ַ 
*  @param  [IN] u32PicSize			 �ѻ��Ʒ����ݻ�������ַ��С
*  @param  [OUT] pu32PicLen	         �ѻ��Ʒ�����ʵ�ʳ���
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_getLocalPayInfo(ICE_HANDLE hSDK, ICE_CHAR *pcPayInfo, ICE_U32 u32InfoSize, ICE_U32 *pu32InfoLen);

/*
*  @brief  ��ȡ�����Ϣ
*  @param  [IN] hSDK				 sdk���
*  @param  [OUT] stDeviceParam       �����Ϣ�ṹ�� 
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDeviceParam(ICE_HANDLE hSDK, ICE_DEVICE_PARAM *stDeviceParam);

/*
*  @brief  ��ȡ������ͣ�82/83��
*  @param  [IN] hSDK				 sdk���
*  @param  [OUT] pu32DevType       ������ͣ�1:82�����2:83�����
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDeviceType(ICE_HANDLE hSDK, ICE_U32 *pu32DevType);

/*
*  @brief  ��ȡ������ͣ�82/83��
*  @param  [IN] hSDK				 sdk���
*  @param  [OUT] pcCamType			 ��������ͺ�
*  @param  [IN] u32StrLen			 pcCamType����
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetDeviceTypeExt(ICE_HANDLE hSDK, ICE_CHAR *pcCamType, ICE_U32 u32StrLen);

/*
*  @brief  Wav��������
*  @param  [IN] hSDK	  sdk���
*  @param  [IN] pcData    Wav����
*  @param  [IN] u32Len    ���ݳ���
*  @return  ��ȡ״̬ 1 �ɹ� 0 ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_BroadcastWav(ICE_HANDLE hSDK, ICE_CHAR *pcData, ICE_U32 u32Len);

/*
*  @brief  ���������ڰ�������֧��csv�ļ�����
*  @param  [IN] hSDK	  sdk���
*  @param  [IN] pFileName �ڰ������ļ�·��
*  @param  [IN] s32Type   �������� 0�����벢׷�ӣ�1���벢����
*  @return  0 ����ԭ��������ʧ��
			1 �����ɹ�
			2 Flash�ռ䲻��
			3 У��ʧ��	
			4 ��ʱ
			5 �ļ�������
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UpdateWhiteListBatch(ICE_HANDLE hSDK, ICE_CHAR *szFilePath, ICE_S32 s32Type);

/*
*  @brief  ���ò�Ʒ�ͺ�
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetProductInfoParam(ICE_HANDLE hSDK, T_ProductInfo *pstParam);

/*
*  @brief  ��ȡ��Ʒ�ͺ�
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetProductInfoParam(ICE_HANDLE hSDK, T_ProductInfo *pstParam);

/*
*  @brief  ��IO����
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetDevAlarmIn(ICE_HANDLE hSDK, T_DevAlarmIn *pstParam);

/*
*  @brief  ��IO���
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SeDevAlarmOutBindCfg(ICE_HANDLE hSDK, T_DevAlarmOutBindCfg *pstParam);


/*
*  @brief  ���Ӵ���Э��
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_AddUartOperPro(ICE_HANDLE hSDK, T_UartOperPro *pstParam);

/*
*  @brief  ɾ������Э��
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DelUartOperPro(ICE_HANDLE hSDK, T_UartOperPro *pstParam);

/*
*  @brief  �󶨴���Э��
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UartBindPro(ICE_HANDLE hSDK, T_UartBindPro *pstParam);

/*
*  @brief  ��ȡ����Э���б�
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetProtocolList(ICE_HANDLE hSDK, T_ProtocolList *pstParam);

/*
*  @brief  ��ȡ����ı����������
*  @param  [IN] hSDK           sdk���
*  @param  [OUT] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetAlarmInExt(ICE_HANDLE hSDK, ALARM_IN_EXT *pstParam);

/*
*  @brief  ���ö���ı����������
*  @param  [IN] hSDK           sdk���
*  @param  [IN] pstParam       �����ṹ��  
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAlarmInExt(ICE_HANDLE hSDK, ALARM_IN_EXT *pstParam);


/**
*  @brief  ͨ���ûص�������ȡ����ĶԽ�״̬�仯
*  @param  [OUT] pvParam             ������ӻص�����, �������ֲ�ͬ����Խ��¼�(ICE_IPCSDK_SetTalkEventCallBack��������һ������)
*  @param  [OUT] pcIP                ���ip
*  @param  [OUT] u32EventType        �¼����� 0����ͨ�ǶԽ�״̬ 1�������Խ� 2�����ڶԽ� 3:����˷���Խ��󣬱�ĳ������˾ܾ�ͨ�� 4:ͨ���ж�
*  @param  [OUT] pcTalkIp			 �¼�����Ϊ2ʱ����ʾ������˽�ͨ�Ĺ����ip���¼�����Ϊ3ʱ����ʾ�ܾ������ͨ���Ĺ����ip
*  @param  [OUT] u32Reserve1		Ԥ��1 
*  @param  [OUT] u32Reserve2        Ԥ��2 
*  @param  [OUT] u32Reserve3        Ԥ��3 
*  @param  [OUT] u32Reserve4        Ԥ��4 
*/
typedef void (__stdcall * ICE_IPCSDK_OnTalkEvent)(void *pvParam, const ICE_CHAR *pcIP, ICE_U32 u32EventType, const ICE_CHAR *pcTalkIp, 
											   ICE_U32 u32Reserve1, ICE_U32 u32Reserve2, ICE_U32 u32Reserve3, ICE_U32 u32Reserve4);

/**
*  @brief  ��������Խ�״̬�仯�ص��¼�
*  @param  [IN] hSDK                     �������ʱ���ص�sdk���
*  @param  [IN] pfOnIOEvent              �Խ��¼��ص�
*  @param  [IN] pvIOEventParam           �Խ��¼��ص�����,�������ֲ�ͬ�Խ��仯�¼�
*/
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetTalkEventCallBack(ICE_HANDLE hSDK, ICE_IPCSDK_OnTalkEvent pfOnTalkEvent, void *pvTalkEventParam);

/**
*  @brief  ��ȡ������ʶ������
*  @param  [IN]  hSDK                     �������ʱ���ص�sdk���
*  @param  [OUT] stVLoopRect              ������ʶ������ṹ��
*  @param  [IN]  nWidth					  ��������ʲô�ֱ�����ȡ�õģ���ʾ������1280*720��ȡ�õģ���Ϊ1280��
*  @param  [IN]  nHeight				  ��������ʲô�ֱ�����ȡ�õģ���ʾ�ߣ�����1280*720��ȡ�õģ���Ϊ720��
*  @return 0ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetQuadRangle(ICE_HANDLE hSDK, ICE_QUADRANGLE_S *stVLoopRect, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  ���ò�����ʶ������
*  @param  [IN]  hSDK                     �������ʱ���ص�sdk���
*  @param  [IN]  stVLoopRect              ������ʶ������ṹ��
*  @param  [IN]  nWidth					  ��������ʲô�ֱ�����ȡ�õģ���ʾ������1280*720��ȡ�õģ���Ϊ1280��
*  @param  [IN]  nHeight				  ��������ʲô�ֱ�����ȡ�õģ���ʾ�ߣ�����1280*720��ȡ�õģ���Ϊ720��
*  @return 0ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetQuadRangle(ICE_HANDLE hSDK, const ICE_QUADRANGLE_S *stVLoopRect, ICE_U32 nWidth, ICE_U32 nHeight);

/**
*  @brief  ��ȡ���UID
*  @param  [IN]   hSDK                     �������ʱ���ص�sdk���
*  @param  [OUT]  pstParam				   UID�����ṹ��
*  @return 0ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetUID(ICE_HANDLE hSDK, UID_PARAM *pstParam);

/**
*  @brief  ��ȡ����û��ͺ�
*  @param  [IN]   hSDK                     �������ʱ���ص�sdk���
*  @param  [OUT]  pstParam				   �û��ͺŲ����ṹ��
*  @return 0ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetUserModel(ICE_HANDLE hSDK, UserModelParam *pstParam);

/**
*  @brief  ��������û��ͺ�
*  @param  [IN]   hSDK                     �������ʱ���ص�sdk���
*  @param  [OUT]  pstParam				   �û��ͺŲ����ṹ��
*  @return 0ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetUserModel(ICE_HANDLE hSDK, UserModelParam *pstParam);

/**
*  @brief  ���þɵ�����ģʽ
*  @param  [IN]   hSDK                     �������ʱ���ص�sdk���
*  @return 0ʧ�� 1�ɹ�
*/
ICE_IPCSDK_API ICE_S32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetOldUpdateModeEnable(ICE_HANDLE hSDK);

/**
*  @brief  ����evtp(�¼��ַ�Э�飬����ʶ���¼��������������˴�Э��Ļ����ϲŻ��ϱ�����)
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pcPasswd		�������루����ΪnullʱΪ���������ӣ���ΪnullΪ�������ӣ�
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StartEvtp(ICE_HANDLE hSDK, const ICE_CHAR* pcPasswd);

/**
*  @brief  �Ͽ�evtp����
*  @param  [IN] hSDK			sdk���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_StopEvtp(ICE_HANDLE hSDK);

/**
*  @brief  �۽�����
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam		�۽������ṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetAFZoom(ICE_HANDLE hSDK, const ICE_IPC_AF_ZOOM *pstParam);

/**
*  @brief  ��ȡ��ͷ�Ǿ۽����Ǳ佹
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pu32LensType	1������ 2���佹
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetLensType(ICE_HANDLE hSDK, ICE_U32 *pu32LensType);

/**
*  @brief  ����NTP����
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam	    NTP�����ṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetNtpCfg(ICE_HANDLE hSDK, T_SntpCfg *pstParam);

/**
*  @brief  ��ȡNTP����
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam	    NTP�����ṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetNtpCfg(ICE_HANDLE hSDK, T_SntpCfg *pstParam);

/**
*  @brief  ����ʱ������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam	    ʱ�������ṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTimeZone(ICE_HANDLE hSDK, T_TimeZone *pstParam);

/**
*  @brief  ��ȡʱ������
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam	    ʱ�������ṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTimeZone(ICE_HANDLE hSDK, T_TimeZone *pstParam);

/**
*  @brief  ����ʱ��
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam	    ʱ�������ṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTime(ICE_HANDLE hSDK, T_TimeCfgInfo *pstParam);

/**
*  @brief  ��ȡʱ��
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam	    ʱ�������ṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTime(ICE_HANDLE hSDK, T_TimeCfgInfo *pstParam);

ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SyncPcTime(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SupportNewNtp(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SupportNewTimeZone(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SupportNewTime(ICE_HANDLE hSDK);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CgiGet(const char *ip, int port, const char *key, char *data, int size);
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CgiSet(const char *ip, int port, const char *key, const char *data, char *rsp);

/**
*  @brief  ��ȡץ��ͼƬosd��������
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam	    ͼƬosd��������
*  @return 0ʧ�ܣ�1�ɹ���2����汾��֧��
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSnapOsdCfg(ICE_HANDLE hSDK, T_SnapOsdCfg *pstParam);

/**
*  @brief  ����ץ��ͼƬosd��������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam	    ͼƬosd��������
*  @return 0ʧ�ܣ�1�ɹ���2����汾��֧��
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSnapOsdCfg(ICE_HANDLE hSDK, const T_SnapOsdCfg *pstParam);

/**
*  @brief  ������������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam	    �������ýṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetVolumeParam(ICE_HANDLE hSDK, const  ICE_TALK_BACK_VOLUME_PARAM *pstParam);

/**
*  @brief  ��ȡ��������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam	    �������ýṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetVolumeParam(ICE_HANDLE hSDK, ICE_TALK_BACK_VOLUME_PARAM *pstParam);

/**
*  @brief  ��������ļ�
*  @param  [IN] hSDK			sdk���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ClearAudioDir(ICE_HANDLE hSDK);

/**
*  @brief  ���������ļ�
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pcFilePath		�����ļ�·��
*  @return 0ʧ�ܣ�1�ɹ�,2�ļ������ڣ�3�ļ������Ϲ淶
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UploadAudioFile(ICE_HANDLE hSDK, const char* pcFilePath);

/**
*  @brief  ������Э������ӣ�Ŀǰ�ڰ�����ʹ����Э����������Ҫͨ���˽ӿ�������Э�飩
*  @param  [IN] hSDK			sdk���
*  @return 0ʧ�ܣ�1�ɹ���2������
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ConnectNormalSdk(ICE_HANDLE hSDK);

/**
*  @brief  �Ͽ���Э������ӣ�����Ҫʹ�úڰ�����ʱ����ͨ���˽ӿڶϿ����ӣ�
*  @param  [IN] hSDK			sdk���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_DisconnectNormalSdk(ICE_HANDLE hSDK);

/**
*  @brief  �Ƿ�֧����ģʽ��Ŀǰ��Ҫ�����жϺڰ�����ʹ����ģʽ���Ǿ�ģʽ��
*  @param  [IN] hSDK			sdk���
*  @return 0��֧�֣�1֧�֣�2 ��ȡʧ�ܣ�3 sdkδ���ӣ�4��Э��δ����
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SupportNewMode(ICE_HANDLE hSDK);

/**
*  @brief  ���úڰ�����ʹ����ģʽ���Ǿ�ģʽ
*  @param  [IN] hSDK			sdk���
*  @param  [IN] mode			0 ��ģʽ������Ϊgbk����1��ģʽ������Ϊutf8)
*  @return 0�����֧�֣�1���óɹ���2 ����ʧ�ܣ�3 sdkδ���ӣ�4��Э��δ����
*/
ICE_IPCSDK_API	ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetWBListMode(ICE_HANDLE hSDK, ICE_U32 mode);

/**
*  @brief  ��ȡhttp postģʽ5����
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam		http post����
*  @param  [OUT] pstExtParam	ģʽ5���ⶨ�Ʋ���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetHttpPostMode5Cfg(ICE_HANDLE hSDK, ICE_HTTP_POST_NEW_PARAM *pstParam, 
																	ICE_HTTP_POST5_EXTPARAM *pstExtParam);

/**
*  @brief  ����http postģʽ5����
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam		http post����
*  @param  [IN] pstExtParam	ģʽ5���ⶨ�Ʋ���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetHttpPostMode5Cfg(ICE_HANDLE hSDK, const ICE_HTTP_POST_NEW_PARAM *pstParam, 
																	const ICE_HTTP_POST5_EXTPARAM *pstExtParam);

/**
*  @brief  ETC�۷�����
*  @param  [IN] hSDK			sdk���
*  @param  [IN] ptEtcCharge		ETC�۷���������
*  @param  [OUT] ptEtcChargeRsp	ETC�۷�����Ӧ������
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SendEtcCharge(ICE_HANDLE hSDK, const T_EtcCharge *ptEtcCharge, 
																T_EtcChargeRsp *ptEtcChargeRsp);

/**
*  @brief  ��ȡ��ƽ̨����
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam		��ƽ̨����
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetCloudCfgParam(ICE_HANDLE hSDK, T_CloudCfgParamExt *pstParam);

/**
*  @brief  ������ƽ̨����
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam		��ƽ̨����
*  @return 0ʧ�ܣ�1�ɹ���2���������Ϲ淶
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetCloudCfgParam(ICE_HANDLE hSDK, const T_CloudCfgParamExt *pstParam);

/**
*  @brief  ��ȡУʱ��������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam		Уʱ��������
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetSyncTimeParam(ICE_HANDLE hSDK, T_SyncTimeParam *pstParam);

/**
*  @brief  ����Уʱ��������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam		Уʱ��������
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSyncTimeParam(ICE_HANDLE hSDK, const T_SyncTimeParam *pstParam);

/**
*  @brief  ��ȡMQTT��������
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam		MQTT�������ýṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetMqttCfg(ICE_HANDLE hSDK, T_MqttCfgParam *pstParam);

/**
*  @brief  ����MQTT��������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam		MQTT�������ýṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetMqttCfg(ICE_HANDLE hSDK, const T_MqttCfgParam *pstParam);

/**
*  @brief  ��ȡMQTT����Ĭ������
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam		MQTT�������ýṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetMqttDefCfg(ICE_HANDLE hSDK, T_MqttCfgParam *pstParam);

/**
*  @brief  ����ң������������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] pstParam		ң���������������ýṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetRemCtrlCfg(ICE_HANDLE hSDK, const T_RemCtrlCfg *pstParam);

/**
*  @brief  ��ȡң������������
*  @param  [IN] hSDK			sdk���
*  @param  [OUT] pstParam		ң���������������ýṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetRemCtrlCfg(ICE_HANDLE hSDK, T_RemCtrlCfg *pstParam);

/**
*  @brief  ң���������¼�
*  @param  [OUT] pvParam		�ص�������
*  @param  [OUT] pcIP			���ip
*  @param  [OUT] pstParam		ң�����¼��ṹ��
*  @return void
*/
typedef void (__stdcall *ICE_IPCSDK_OnRemCtrlEvent)(void *pvParam, const ICE_CHAR *pcIP, T_RemCtrlData *ptRemCtrlData);

/**
*  @brief  ����ң���������¼��ص�
*  @param  [IN] hSDK				sdk���
*  @param  [IN] pfOnRemCtrlEvent	ң���������¼�
*  @param  [IN] pvParam				�ص�������
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetRemCtrlEventCallBack(ICE_HANDLE hSDK, 
																  ICE_IPCSDK_OnRemCtrlEvent pfOnRemCtrlEvent, void *pvParam);

/**
 *  @brief  ����ʶ�����ݿ����¼�����ػص�����
 *  @param  [IN] hSDK               �������ʱ���ص�sdk���
 *  @param  [IN] pfFastPlate		ʶ�����ݿ����¼�
 *  @param  [IN] pvFastPlateParam  	�ص�������
 *  @return void
 */
ICE_IPCSDK_API void ICE_IPCSDK_TYPE ICE_IPCSDK_SetFastPlateCallback(ICE_HANDLE hSDK, ICE_IPCSDK_OnFastPlate pfFastPlate, void *pvFastPlateParam);

/**
 *  @brief  ��ȡ�Խ�����
 *  @param  [IN] hSDK               �������ʱ���ص�sdk���
 *  @param  [OUT] ptTalkBackCfg		�Խ����ýṹ��
 *  @return 0ʧ�ܣ�1�ɹ�
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_GetTalkBackCfg(ICE_HANDLE hSDK, T_TalkBackCfg *ptTalkBackCfg);

/**
 *  @brief  ���öԽ�����
 *  @param  [IN] hSDK               �������ʱ���ص�sdk���
 *  @param  [IN] ptTalkBackCfg		�Խ����ýṹ��
 *  @return 0ʧ�ܣ�1�ɹ�
 */
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetTalkBackCfg(ICE_HANDLE hSDK, const T_TalkBackCfg *ptTalkBackCfg);
/*************************************************LCD/LED����ؽӿ�**************************************************/
//LCD��
/**
*  @brief  �������
*  @param  [IN] hSDK			sdk���
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ConnectUserApp(ICE_HANDLE hSDK);

/**
*  @brief  ����������ģʽ
*  @param  [IN] hSDK				sdk���
*  @param  [IN] uiCtrlMode			������ģʽ 1 ����ģʽ 2 ����ģʽ
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLcdCtrlMode(ICE_HANDLE hSDK, ICE_U32 uiCtrlMode);

/**
*  @brief  ����LCD�����ȿ���
*  @param  [IN] hSDK				sdk���
*  @param  [IN] uiLcdBkLight		��Ļ���ȣ�1-10���ȼ�
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLcdBkLight(ICE_HANDLE hSDK, ICE_U32 uiLcdBkLight);

/**
*  @brief  ����LCD������
*  @param  [IN] hSDK				sdk���
*  @param  [IN] uiSplitScreen		1ȫ�� 2���� 
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*  2��ģʽ�У���Ϊ���������ʾģʽʱ����Ҫע�����¼��㣺
	����ʱ�����֣������һ�θ��µ���������Ϊ׼
	��ά�벿��ʧЧ��ֻ�ֲ��������ͼƬ

*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetSplitScreen(ICE_HANDLE hSDK, ICE_U32 uiSplitScreen);

/**
*  @brief  ����LCD����ʾ��������������
*  @param  [IN] hSDK				sdk���
*  @param  [IN] tLcdShowInfo		LCD����ʾ��Ϣ
*  @param  [IN] uiSetQRCodeUrl		�Ƿ����ö�ά��ͼƬ��URL��ַ��0�����ã�1����
*  @param  [IN] pucQRCodeUrl		��ά��ͼƬ��URL��ַ
*  @param  [IN] uiSetVoiceInfo		0��������������Ϣ�� 1����������������Ϣ 2������TTS����
*  @param  [IN] pucVoiceInfo		������Ϣ��
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*  ע���˽ӿڻ��Զ���LCD����Ϊ������ʾģʽ��
	�������ά�룬������ʾ����һֱ�Ƕ�ά��ͼƬ��������Ϊ�������ͼƬ�ֲ���
	���������ά�룬������ʾ��һֱ�ֲ��������ͼƬ��

*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLcdShowInfo(ICE_HANDLE hSDK, const T_LcdShowInfo *ptLcdShowInfo, 
																ICE_U32 uiSetQRCodeUrl, const ICE_U8 *pucQRCodeUrl, 
																ICE_U32 uiSetVoiceInfo, const ICE_U8 *pucVoiceInfo);

/**
*  @brief  LCD�����ֵ�����գ������복�ƺ�OSDȫ��
*  @param  [IN] hSDK				sdk���
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ClearOsd(ICE_HANDLE hSDK);

/**
*  @brief	LCD����������
*  @param  [IN] hSDK				sdk���
*  @param  [IN] ptLcdParam			LCD�������ṹ��
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLcdParam(ICE_HANDLE hSDK, const T_LcdParam *ptLcdParam);

/**
*  @brief	�ϴ����ͼƬ
*  @param  [IN] hSDK				sdk���
*  @param  [IN] uiAdPicType			ͼƬ���ͣ�1ȫ�����ͼƬ 2�������ͼƬ 3����ͼƬ
*									ȫ�����ߴ磺DME88-V2001C��768*1366����
*												  DMG88-V2001C��1080*1920����
*												  DMF88-V2001C��768*1024����
*												  DCF88-V2001C��768*1024����
*												  DCE88-V3002C��768*1366����
*												  DCG88-V3002C��1080*1920����
*									�������ߴ磺DME88-V2001C��768*672����
*												  DMG88-V2001C��1080*960����
*												  DMF88-V2001C��768*512����
*												  DCF88-V2001C��768*512����
*												  DCE88-V3002C��768*672����
*												  DCG88-V3002C��1080*960����
*									����ͼƬ�ߴ磺DME88-V2001C��768*694 / 768*704����
*												  DMG88-V2001C��1080*960����
*												  DMF88-V2001C��768*512����
*												  DCF88-V2001C��768*512����
*												  DCE88-V3002C��768*694 / 768*704����
*												  DCG88-V3002C��1080*960����
*  @param  [IN] pcAdPicPath			���ͼƬ·��
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_UploadAdvertPic(ICE_HANDLE hSDK, ICE_U32 uiAdPicType, const char *pcAdPicPath);

/**
*  @brief	LCD�����ͼƬ���
*  @param  [IN] hSDK				sdk���
*  @param  [IN] uiAdPicType			1ȫ�����ͼƬ 2�������ͼƬ 
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ClearAdvertPic(ICE_HANDLE hSDK, UINT32 uiAdPicType);

//LED
/**
*  @brief  LED������
*  @param  [IN] hSDK			sdk���
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_ClearLedOsd(ICE_HANDLE hSDK);

/**
*  @brief  ����LED������
*  @param  [IN] hSDK			sdk���
*  @param  [IN] ptLedCfgInfo	LED������
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLedCfgInfo(ICE_HANDLE hSDK, const T_LedCfgInfo *ptLedCfgInfo);

/**
*  @brief  ����LED����ʾ����
*  @param  [IN] hSDK			sdk���
*  @param  [IN] ptLedShowInfo	LED����ʾ������Ϣ
*  @param  [IN] uiSetVoiceInfo	0��������������Ϣ�� 1����������������Ϣ 2������TTS����
*  @param  [IN] pucVoiceInfo	������Ϣ�� 
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_SetLedShowInfo(ICE_HANDLE hSDK, const T_LedShowInfo *ptLedShowInfo,
											  UINT32 uiSetVoiceInfo, const UINT8 *pucVoiceInfo);

/**
*  @brief  �Ͽ�����
*  @param  [IN] hSDK	sdk���
*  @return 0�ɹ�����������ֵ���E_ICE_SDK_STATUS
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_IPCSDK_CloseUserApp(ICE_HANDLE hSDK);

/*************************************************LCD/LED����ؽӿ�**************************************************/

/*************************************************�Խ�����ؽӿ�****************************************************/
/**
*  @brief  ���ӶԽ���
*  @param  [IN] pcIP		�Խ���IP
*  @param  [IN] pcResrv1	Ԥ��
*  @param  [IN] pcResvr2	Ԥ��
*  @param  [IN] iResvr		Ԥ��
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_RCZ_HANDLE ICE_IPCSDK_TYPE ICE_RCZSDK_Connect(const ICE_CHAR *pcIP, const ICE_CHAR *pcResrv1, const ICE_CHAR *pcResvr2, int iResvr);

/**
*  @brief  �Խ�����ά�뷴ɨ�¼�
*  @param  [OUT] param		�ص�������
*  @param  [OUT] pcIP		���ip
*  @param  [OUT] pacUrl		��ά��url
*  @param  [OUT] iUrlLen	��ά��url����
*  @param  [OUT] pacResrv1	Ԥ��
*  @param  [OUT] pacResrv2	Ԥ��
*  @param  [OUT] iResvr1	Ԥ��
*  @param  [OUT] iResvr2	Ԥ��
*  @return void
*/
typedef void (__stdcall *ICE_RCZ_OnPayCodeEvent)(void *param, const ICE_CHAR *pcIP, const ICE_CHAR *pacUrl, int iUrlLen, const void *pacResrv1, 
												 const void *pacResrv2, int iResvr1, int iResvr2);

/**
*  @brief  ע��Խ�����ά�뷴ɨ�¼�������
*  @param  [IN] hRczSdk				�Խ���SDK���
*  @param  [IN] pfOnPayCodeEvent	�Խ�����ά�뷴ɨ�¼�
*  @param  [IN] pvParam				�ص�������
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_RegPayCodeEvent(ICE_RCZ_HANDLE hRczSdk, ICE_RCZ_OnPayCodeEvent pfOnPayCodeEvent, void *pvParam);

/**
*  @brief  ע���Խ�����ά�뷴ɨ�¼�������
*  @param  [IN] hRczSdk		�Խ���SDK���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_UnregPayCodeEvent(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  ��������
*  @param  [IN] hRczSdk		�Խ���SDK���
*  @param  [IN] pcText		�����������ݣ�utf8���룬���90�ֽڣ�������������
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_Broadcast(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pcText);

/**
*  @brief  ���ÿ���ģʽ
*  @param  [IN] hRczSdk		�Խ���SDK���
*  @param  [IN] uiCtrlMode	����ģʽ��1.�Կ�ģʽ��2.�������Խ�ģʽ
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_SetCtrlMode(ICE_RCZ_HANDLE hRczSdk, ICE_U32 uiCtrlMode);

/**
*  @brief  ��ȡ����ģʽ
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [OUT] puiCtrlMode	����ģʽ��1.����ģʽ��2.����ģʽ
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_GetCtrlMode(ICE_RCZ_HANDLE hRczSdk, ICE_U32 *puiCtrlMode);

/**
*  @brief  ����LCD����������
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [IN] uiLcdBkLight	�������ȣ���Χ��0-10
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_SetLcdBkLight(ICE_RCZ_HANDLE hRczSdk, ICE_U32 uiLcdBkLight);

/**
*  @brief  ��ȡLCD����������
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [OUT] puiLcdBkLight	�������ȣ���Χ��0-10
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_GetLcdBkLight(ICE_RCZ_HANDLE hRczSdk, ICE_U32 *puiLcdBkLight);

/**
*  @brief  LCD������OSD����
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [IN] tRczTextOsd		���ֵ��ӽṹ��
*  @return 0ʧ�ܣ�1�ɹ�
*  ע������Ҫͬʱ��ʾ��ά���osd����ʱ����Ҫ����ʾ��ά�롢�ٵ���osd���֡�
*  ע���������ÿһ�����ݶ�Ϊ��ʱ���ӿڷ���ʧ��
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_SetTextOsd(ICE_RCZ_HANDLE hRczSdk, const T_RczTextOsd *tRczTextOsd);

/**
*  @brief  LCD�����ֵ������
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @return 0ʧ�ܣ�1�ɹ�
*  ע��������ֵ��ӺͶ�ά����ʾ
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_ClearOsd(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  LCD��ͼƬɾ��
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [IN] pacPicName		ͼƬ���ƣ�utf8����
*  @return 0ʧ�ܣ�1�ɹ��� 2�������ͼƬ������
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_DelPic(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pacPicName);

/**
*  @brief  ��ʾ��ά��ͼƬ
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [IN] pacQrCodeUrl	��ά��ͼƬurl,utf8���룬��󳤶�256�ֽ�
*  @param  [IN] iPosX			X���꣬��Χ��0-800
*  @param  [IN] iPosY			Y���꣬��Χ��0-1280			
*  @return 0ʧ�ܣ�1�ɹ���2���óɹ�����ͼƬ��ʾ��Խ��
*  ע������Ҫͬʱ��ʾ��ά���osd����ʱ����Ҫ����ʾ��ά�롢�ٵ���osd���֡�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_ShowQRCodePic(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pacQrCodeUrl, int iPosX, int iPosY);

/**
*  @brief  �ϴ�ͼƬ
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [IN] pcAdPicPath		ͼƬ·����utf8����
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_UploadPic(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pcAdPicPath);

/**
*  @brief  LCD��ͼƬ��ʾ
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [IN] pacPicName		ͼƬ���ƣ�utf8����
*  @return 0ʧ�ܣ�1�ɹ��� 2�������ͼƬ������
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_PicPlay(ICE_RCZ_HANDLE hRczSdk, const ICE_CHAR *pacPicName);

/**
*  @brief  Զ�̿���բ
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_RemoteSwitch(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  ��������
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @param  [IN] uiVolumn		��������Χ0-10
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_SetSayVol(ICE_RCZ_HANDLE hRczSdk, ICE_U32 uiVolume);

/**
*  @brief  ��ʼ��Ƶ
*  @param  [IN] hRczSdk          �Խ���SDK���
*  @param  [IN] u8MainStream	�Ƿ�Ϊ��������1�������� 0����������
*  @param  [IN] hWnd          ��Ƶ���Ŵ��ھ��
*  @return 1 �ɹ� 0 ʧ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_StartStream(ICE_RCZ_HANDLE hRczSdk, 
															  ICE_U8 u8MainStream, ICE_U32 hWnd);

/**
*  @brief  ������Ƶ
*  @param  [IN] hRczSdk          �Խ���SDK���
*  @return 1 �ɹ� 0 ʧ�� 
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_StopStream(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  ���ƶԽ�������բ
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_Switch(ICE_RCZ_HANDLE hRczSdk);

/**
*  @brief  �Ͽ��Խ�������
*  @param  [IN] hRczSdk			�Խ���SDK���
*  @return 0ʧ�ܣ�1�ɹ�
*/
ICE_IPCSDK_API ICE_U32 ICE_IPCSDK_TYPE ICE_RCZSDK_DisConnect(ICE_RCZ_HANDLE hRczSdk);
/*************************************************�Խ�����ؽӿ�****************************************************/

#ifdef __cplusplus
}
#endif

#endif